#include <iostream>

class OnePole{
public:
    OnePole(){
        std::cout << "OnePole" << std::endl;
    }

    float output(float input){
        float output = input * b + y1 * a;
        y1 = output;
        return output;
    }

    void setCoefficient(float coefficient){
        a = coefficient;
        b = 1.0f - a;
    }

private:
//formula: y[n] = x[n]*b + y[n-1]*a
    float y1 { 0.0 };
    float b { 0.0 };
    float a { 0.0 };
};