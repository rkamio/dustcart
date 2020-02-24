#pragma once
#include <unordered_map>
namespace engine { namespace utils {

class GpioPin {

    private:
    int pin;
    int mode;
    static std::unordered_map<std::string, int> pins_status;
    bool isUsed(int pin_id);

    public:
    GpioPin(int pin_id, int mode_id);
    int getPin();
    void setPin(int pin_id);
    int getMode();
    void setMode(int mode_id);

    int setupGpioPins();
    void initialize();
    void sendDigital(int value);
    void wait(int time);
    ~GpioPin();

};

inline int GpioPin::getPin() { return pin; }
inline void GpioPin::setPin(int pin_id) { pin = pin_id; }
inline int GpioPin::getMode() { return mode; }
inline void GpioPin::setMode(int mode_id) { mode = mode_id; }
    
}
}