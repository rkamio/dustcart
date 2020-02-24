#include <iostream>
#include <tuple>

#include "gpio_wrapper.h"
#include "caterpillar.h"


namespace engine {

Caterpillar::Caterpillar(utils::GpioPin *p_pin, utils::GpioPin *n_pin) {
    positive_pin = p_pin;
    negative_pin = n_pin;
}

std::tuple<utils::GpioPin, utils::GpioPin> Caterpillar::getPins() {
    return std::forward_as_tuple(*positive_pin, *negative_pin);
}

// TODO: 自前でPWM制御書きたい。。。
void Caterpillar::forward(int speed) {
    negative_pin->sendDigital(0);
    positive_pin->sendDigital(1);
    // std::cout << "caterpillar forward." << std::endl;
}

void Caterpillar::stop() {
    negative_pin->sendDigital(0);
    positive_pin->sendDigital(0);
}

void Caterpillar::reverse(int speed) {
    positive_pin->sendDigital(0);
    negative_pin->sendDigital(1);
}

Caterpillar::~Caterpillar() {
    stop();
}

}