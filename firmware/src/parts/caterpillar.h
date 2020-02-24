#pragma once
namespace engine {
    
class Caterpillar {
    //参照渡しで実装し直し。
    
    private:
    utils::GpioPin *positive_pin;
    utils::GpioPin *negative_pin;

    public:
    Caterpillar(utils::GpioPin *p_pin, utils::GpioPin *n_pin); 
    std::tuple<utils::GpioPin, utils::GpioPin> getPins();
    void forward(int speed);
    void stop();
    void reverse(int speed);
    ~Caterpillar();
};

}