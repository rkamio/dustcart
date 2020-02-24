#include <wiringPi.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include "gpio_wrapper.h"

namespace engine { namespace utils {

std::unordered_map<std::string, int> GpioPin::pins_status;

GpioPin::GpioPin(int pin_id, int mode_id) {
    if (pins_status.empty()) {
        setupGpioPins();
        std::cout << "setupGpioPins is expected to call once." << std::endl;
    }

    if (isUsed(pin_id)) {
        std::cout << "pin_id: " << pin_id << " is used." << std::endl;
        throw "Error: pin_id has already been used...";
    }

    GpioPin::setPin(pin_id);
    GpioPin::setMode(mode_id);
    GpioPin::initialize();
}



bool GpioPin::isUsed(int pin_id) {
    std::string i = std::to_string(pin_id);
    return pins_status.find(i) == pins_status.end() ? false : true ;
}

int GpioPin::setupGpioPins(void) {
    return wiringPiSetupGpio();
}

void GpioPin::initialize() {
    pinMode(pin, mode);
    pins_status[std::to_string(pin)] = mode;
}

void GpioPin::sendDigital(int value) {
    digitalWrite(pin, value);
}

void GpioPin::wait(int time) {
    delay(time);
}

GpioPin::~GpioPin() {
    digitalWrite(pin, 0);
    pins_status.erase(std::to_string(pin));
    if (pins_status.empty()) {
        pins_status.clear();
        std::cout << "cleared is expected to call once." << std::endl;
    }
}

}
}

