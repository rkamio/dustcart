#pragma once
namespace mycart {

class Dustcart {

    private:
    engine::Caterpillar *left_caterpillar;
    engine::Caterpillar *right_caterpillar;

    
    public:
    Dustcart(engine::Caterpillar *l_caterpillar, engine::Caterpillar *r_caterpillar);
    void move(int verocity[2]);
    void forward(int speed);
    void backward(int speed);
    void turnRight(int speed);
    void turnLeft(int speed);
    void stop();
    ~Dustcart();

};

}