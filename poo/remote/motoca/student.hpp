#pragma once
#include <iostream>
#include <string>
class Pessoa {
    private:
        int age;
        std::string name;
    public:
        Pessoa(std::string name = "", int age = 0) : age(age), name(name){}


        int getAge() const {
            return age;
        }

        std::string getName() const {
            return name;
        }

        void toString() const {
        std::cout << name << ":" << age;
    }

};
class Moto {
    private:
        int power;
        int time;
        Pessoa pessoa;

public:

    Moto() : power(1), time(0), pessoa(Pessoa()){

    }

    void setPower(int p) {
    power = p;
}


    bool enter(const Pessoa& joao) {
        if(pessoa.getName() != "" ){
            std::cout << "fail: busy motorcycle" << std::endl;
            return false;
        }else{
            pessoa = joao;
            return true;
        }
    }

    bool leave() {
        if(pessoa.getName() == "" ){
            std::cout << "fail: empty motorcycle" << std::endl;
            std::cout << "---" << std::endl;
            return false;
        }else{
            std::cout << pessoa.getName() << ":" << pessoa.getAge() << std::endl;
        pessoa = Pessoa();
        } return true;
        // auto person = motorcycle.remove();
        // fn::write(person == nullptr ? "---" : person->str());
    }

    std::string honk() const {
        return "P" + std::string(power, 'e') + "m";
    }

    void buy(int t) {
        time += t;
        //std::cout << "$buy " << t << std::endl;
        //(void) time;
        // motorcycle.buyTime(time);
    }

    void drive(int t) {
        
        if (time <= 0){
            std::cout << "fail: buy time first" << std::endl;
        }else if(pessoa.getName() == ""){
            std::cout << "fail: empty motorcycle" << std::endl;
        }else if(pessoa.getAge() > 10){
            std::cout << "fail: too old to drive" << std::endl;
        }else if (time < t){
            std::cout << "fail: time finished after " << time << " minutes" << std::endl;
            time = 0;
        } else {
            time -= t;
        }

    }
        
    void show() const{
        std::cout << "power:" << power << ", time:" << time << ", person:(";
        if (pessoa.getName() == "") {
            std::cout << "empty)" << std::endl;
        } else {
            pessoa.toString();
            std::cout << ")" << std::endl;
        }
    }
        //(void) time;
        // motorcycle.drive(time);
    };

    class Adapter {
        private:
            Moto moto;
        public:
        void init(int p) {
            moto = Moto(); 
            moto.setPower(p);
            //if(p > 0){
              //  moto.buy(p);
            //}
             
            //moto.buy(power); 
            //std::cout << "$init " << p << std::endl;
    }

    void enter(const std::string& name, int age){
        Pessoa p(name, age);
        moto.enter(p);
        //if(moto.enter(p)){
          //  std::cout << "$enter " << name << " " << age << std::endl;
        //};
    }
    void leave() {
        moto.leave();
        //if(moto.leave()){
        //    std::cout << "$leave" << std::endl;
        //}
    }
    void buy(int t) { 
        moto.buy(t);
        //std::cout << "$buy " << t << std::endl; 
        }
    void drive(int t) { 
        moto.drive(t);
        //std::cout << "$drive " << t << std::endl; 
        }
    void honk() { 
        std::cout << moto.honk() << std::endl; 
        }
    void show() {
        //std::cout << "$show" << std::endl; 
        moto.show();
        }

    };
