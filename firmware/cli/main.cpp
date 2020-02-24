#include <iostream>
#include <csignal>
#include <string>
#include "../src/parts/gpio_wrapper.h"
#include "../src/parts/caterpillar.h"
#include "../src/dustcart.h"
#include <chrono>
#include <thread>

namespace {

volatile std::sig_atomic_t signal_status;
static const int L_POSITIVE_PIN = 18;
static const int L_NEGATIVE_PIN = 17;
static const int R_POSITIVE_PIN = 12;
static const int R_NEGATIVE_PIN = 6;
static const int OUTPUT_MODE = 1;

}

void signalHandler(int signal);
int acceptStdinCmd();



int main(int args, char *argv[]) {
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

    int command_id;
    while (1) {

        command_id = acceptStdinCmd();
        switch (command_id) {
            case 1:
                dustcart.forward(10);
                break;
            case 2:
                dustcart.backward(10);
                break;
            case 3:
                dustcart.turnLeft(10);
                break;
            case 4:
                dustcart.turnRight(10);
                break;
            case 5:
                dustcart.stop();
                break;
            case 999:
                std::raise(SIGQUIT);
                break;
            default:
                std::cout << "コマンド一覧内の番号を入力してください。" << std::endl;
                break;
        }


        if (signal_status == SIGINT) {
            std::cout << "Ctrl + c" << std::endl;
            break;
        } else if (signal_status == SIGTERM) {
            std::cout << "kill -term [pid]" << std::endl;
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

int acceptStdinCmd() {

    int command_id;
    std::cout << std::endl;
    std::cout << "コマンド一覧 :" << std::endl;
    std::cout << "1. 前進" << std::endl;
    std::cout << "2. 後退" << std::endl;
    std::cout << "3. 左折" << std::endl;
    std::cout << "4. 右折" << std::endl;
    std::cout << "5. 停止" << std::endl;
    std::cout << "999. 終了" << std::endl;
    
    std::cout << "番号を入力してください: ";
    std::cin >> command_id;

    return command_id;
}