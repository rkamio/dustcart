#include <iostream>
#include <csignal>
#include <string>
#include <unordered_map>

#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../src/parts/gpio_wrapper.h"
#include "../src/parts/caterpillar.h"
#include "../src/dustcart.h"


namespace {

volatile std::sig_atomic_t signal_status;
static const int L_POSITIVE_PIN = 18;
static const int L_NEGATIVE_PIN = 17;
static const int R_POSITIVE_PIN = 12;
static const int R_NEGATIVE_PIN = 6;
static const int OUTPUT_MODE = 1;

static const std::unordered_map<std::string, int> COMMANDS = { 
    {"stop", 0},
    {"forward", 1}, 
    {"backward", 2}, 
    {"left", 3}, 
    {"right", 4},
    {"terminate", 999},
    };

}

void signalHandler(int signal);
std::string parseCommandLineArgs(int argc, char *argv[]);
int acceptStdinCmd();
int acceptUDPCmd();


int main(int argc, char *argv[]) {
    std::cout << "main started!" << std::endl;
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);
    std::signal(SIGQUIT, signalHandler);

    engine::utils::GpioPin l_positive_pin(L_POSITIVE_PIN, OUTPUT_MODE);
    engine::utils::GpioPin l_negative_pin(L_NEGATIVE_PIN, OUTPUT_MODE);

    engine::utils::GpioPin r_positive_pin(R_POSITIVE_PIN, OUTPUT_MODE);
    engine::utils::GpioPin r_negative_pin(R_NEGATIVE_PIN, OUTPUT_MODE);

    engine::Caterpillar l_caterpiller(&l_positive_pin, &l_negative_pin);
    engine::Caterpillar r_caterpiller(&r_positive_pin, &r_negative_pin);
    
    mycart::Dustcart dustcart(&l_caterpiller, &r_caterpiller);

    
    std::string accept_mode = parseCommandLineArgs(argc, argv);
    int (*accept_method)();
    if (accept_mode == "udp") {
        accept_method = acceptUDPCmd;
    } else {
        accept_method = acceptStdinCmd;
    }
    
    int command_id, speed=10;
    while (1) {

        command_id = (*accept_method)();

        switch (command_id) {
            case 0:
                dustcart.stop();
                break;
            case 1:
                dustcart.forward(speed);
                break;
            case 2:
                dustcart.backward(speed);
                break;
            case 3:
                dustcart.turnLeft(speed);
                break;
            case 4:
                dustcart.turnRight(speed);
                break;
            case 999:
                std::raise(SIGQUIT);
                break;
        }


        if (signal_status == SIGINT) {
            // std::cout << "Ctrl + c" << std::endl;
            break;
        } else if (signal_status == SIGTERM) {
            // std::cout << "kill -term [pid]" << std::endl;
            break;
        } else if (signal_status == SIGQUIT) {
            std::cout << "終了します。" << std::endl;
            break;
        }
    }

    dustcart.stop();
    std::cout << "main end." << std::endl;
    return 0;
}

void signalHandler(int signal) {
    signal_status = signal;
}

std::string parseCommandLineArgs(int argc, char *argv[]) {
    int opt;
    std::string accept_mode;
    while ((opt = getopt(argc, argv, "m:")) != -1) {
        //コマンドライン引数のオプションがなくなるまで繰り返す
        switch (opt) {
            case 'm':
                std::cout << "-mがオプションとして渡されました" << std::endl;
                std::cout << "引数optarg = " << optarg << std::endl;
                accept_mode = optarg;
                break;

            default:
                //指定していないオプションが渡された場合
                std::cout << "Usage: " << argv[0] << "[-m argument]" << std::endl;
                break;
        }
    }
    std::cout << "mode : " << accept_mode << std::endl;
    return accept_mode;
}

int acceptStdinCmd() {
    int command_id;
    std::string command;

    std::cout << std::endl;
    std::cout << "コマンド一覧 :" << std::endl;
    std::cout << "stop" << std::endl;
    std::cout << "forward" << std::endl;
    std::cout << "backward" << std::endl;
    std::cout << "left" << std::endl;
    std::cout << "right" << std::endl;
    std::cout << "terminate" << std::endl;
    
    std::cout << "コマンド: ";
    std::cin >> command;
    if (COMMANDS.find(command) == COMMANDS.end()) {
        command_id = COMMANDS.at("stop");
        std::cout << "不明なコマンドです。" << std::endl;
    } else {
        command_id = COMMANDS.at(command);
    }
    return command_id;
}

int acceptUDPCmd() {
    // TODO: ソケット生成とcloseが無駄
    // TODO: タイムアウト(安全に停止), ノンブロッキング , オブジェクト化など
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    std::string command;
    int command_id, sock;
    char buf[2048];
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr *)&addr, sizeof(addr));

    std::memset(buf, 0, sizeof(buf));
    recv(sock, buf, sizeof(buf), 0);
    
    command = buf;
    std::cout << command << std::endl;
    if (signal_status == SIGINT || signal_status == SIGTERM) {
        close(sock);
        return COMMANDS.at("terminate");
    } 

    close(sock);
    if (COMMANDS.find(command) == COMMANDS.end()) {
        command_id = COMMANDS.at("stop");
        std::cout << "不明なコマンドです。" << std::endl;
    } else {
        command_id = COMMANDS.at(command);
    }

    return command_id;
}