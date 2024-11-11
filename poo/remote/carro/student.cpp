#include "fn.hpp"

class Car{      //classe
    public:     //atributos públicos
    int pass;
    int passMax;
    int gas;
    int gasMax;
    int km;

    Car(){       //construtor
        pass = 0;
        gas = 0;
        km = 0;
        passMax = 2;
        gasMax = 100;
    }

    void enter(){       //métodos
        if(pass == passMax){
            std::cout << "fail: limite de pessoas atingido"<< std::endl;
        }else{
            pass++;
        }
    }

    void leave(){
        if(pass > 0){
            pass --;
        }else{
            std::cout << "fail: nao ha ninguem no carro" << std::endl;
        }
    }

    void drive(int value){
        if(pass == 0){
            std::cout << "fail: nao ha ninguem no carro" << std::endl;
        }else if(gas == 0){
            std::cout << "fail: tanque vazio" << std::endl;
        }else if(gas < value){
            std::cout << "fail: tanque vazio apos andar " << gas << " km" << std::endl;
            km += gas;
            gas = 0;
        }else{
            km = km+value;
            gas = gas-value;
        }
    }

    void fuel(int value){
        if(gas+value >= gasMax){
            gas = gasMax;
        }else{
            gas = gas+value;
        }
    }

    void toString(){
        std::cout << "pass: " << pass << ", gas: " << gas << ", km: " << km << std::endl;
    }
};

struct Student {
    Car car;
    Student() {}

    void enter() {
         car.enter();
    }
    void leave() {
         car.leave();
    }
    void fuel(int q) {
         car.fuel(q);
        (void) q;
    }
    void drive(int q) {
         car.drive(q);
        (void) q;
    }
    void show() {
        car.toString();
    }
};

struct Debug {
    // Se a variável debug for true, os testes não serão executados
    // Apenas o conteúdo do método run() será executado
    // Você pode usar isso para testar seu código manualmente
    static const bool debug = false;
    static void run() {
        std::cout << "Debug ativado" << std::endl;
    }
};
