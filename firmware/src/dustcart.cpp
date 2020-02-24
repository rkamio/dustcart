#include <iostream>
#include <tuple>

#include "parts/gpio_wrapper.h"
#include "parts/caterpillar.h"
#include "dustcart.h"

namespace mycart {

Dustcart::Dustcart(engine::Caterpillar *l_caterpillar, engine::Caterpillar *r_caterpillar) {
    left_caterpillar = l_caterpillar;
    right_caterpillar = r_caterpillar;
    std::cout << "dustcart Initialized." << std::endl;
}

void Dustcart::move(int verocity[2]) {
    std::cout << "move! x=" << verocity[0] << "y=" << verocity[1] << std::endl;
}

void Dustcart::forward(int speed) {
    // std::cout << "forward speed=" << speed << std::endl;
    left_caterpillar->forward(speed);
    right_caterpillar->forward(speed);
    // std::cout << "cart forward." << std::endl;
}

void Dustcart::backward(int speed) {
    // std::cout << "backward speed=" << speed << std::endl;
    left_caterpillar->reverse(speed);
    right_caterpillar->reverse(speed);
}

void Dustcart::turnRight(int speed) {
    // std::cout << "turnRight speed=" << speed << std::endl;
    right_caterpillar->stop();
    left_caterpillar->forward(speed);
    
}

void Dustcart::turnLeft(int speed) {
    // std::cout << "turnLeft speed=" << speed << std::endl;
    left_caterpillar->stop();
    right_caterpillar->forward(speed);
}

void Dustcart::stop() {
    // std::cout << "stop!" << std::endl;
    left_caterpillar->stop();
    right_caterpillar->stop();
}

Dustcart::~Dustcart() {
    stop();
}

} 