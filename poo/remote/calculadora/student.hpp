#pragma once
#include "fn.hpp"

class Student {
    public:
    int battery;
    int batteryMax;
    float display;

    // Calculator c;
    void student(int batteryMax){     //construtor
        // c = Calculator(0);
        battery = 0;
        this-> batteryMax = batteryMax;
        display = 0;
    }
    void show() {
        std::cout << std::fixed;
        std::cout << std::setprecision(2);
        std::cout << "display = "<< display <<", battery = "<< battery << std::endl;
        
    }
    void init(int batteryMax) {
        // c = Calculator(batteryMax);
        (void) batteryMax;
    }
    void charge(int value) {
        if(value + battery >= batteryMax){
            battery = batteryMax;
        }else{
            battery = value + battery;
        }
        // c.chargeBattery(value);
        // // ACT!
        // // (void) value;
    }
    void sum(int a, int b) {
        if(battery <= 0){
        std::cout << "fail: bateria insuficiente" << std::endl;
        }else{
        int s;
        s = a + b;
        display = s;
        battery = battery - 1;
        // c.sum(a, b);
        // // ACT!
        // //(void) a;
        // //(void) b;
        }
    }
    void div(float num, float den) {
        if(battery <= 0){
        std::cout << "fail: bateria insuficiente" << std::endl;
        }else if(den == 0){std::cout << "fail: divisao por zero" << std::endl;
        battery = battery - 1;}else{
        float d;
        d = num / den ;
        display = d;
        // c.division(num, den);
        // // ACT!
        battery = battery - 1;
        }
        
    }

    void toString(){
        //std::cout << "pass: " << pass << ", gas: " << gas << ", km: " << km << std::endl;
    }

};
