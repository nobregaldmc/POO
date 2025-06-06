#include "fn.hpp" // https://raw.githubusercontent.com/senapk/cppaux/master/fn.hpp
#include <iostream>
#include <string>

using namespace fn;

class Tamagochi{
    private:

    int energyMax;
    int cleanMax;
    int energy{1};
    int clean{1};
    int age{0};
    bool alive{true};

    bool testAlive(){
        if(alive)
        return true;
        std::cout << "fail: pet esta morto" << std::endl;
        return false;
    }
    
    public:

    void setEnergy(int value){
        if(value <= 0){
            energy = 0;
            alive = false;
            std::cout << "fail: pet morreu de fraqueza" << std::endl;
        }else if(value > energyMax){
            energy = energyMax;
        }else{
            energy = value;
        }
    }

    void setClean(int value){
        if(value <= 0){
            clean = 0;
            alive = false;
            std::cout << "fail: pet morreu de sujeira" << std::endl;
        }else if(value > cleanMax){
            clean = cleanMax;
        }else{
            clean = value;
        }
    }

    void init(int energy = 0, int clean = 0){
        this->energyMax = energy;
        this->cleanMax = clean;
        this->setEnergy(energy);
        this->setClean(clean);
    }

    void play(){
        if(!testAlive())return;
        setEnergy(getEnergy() - 2);
        setClean(getClean() - 3);
        age += 1;
        
    }

    void shower(){
        if(!testAlive()){return;}
        setEnergy(getEnergy() - 3);
        setClean(cleanMax);
        age += 2;
    }

    void sleep(){
        if(!testAlive()){return;}
        if(getEnergy() > (energyMax - 5)){
            std::cout << "fail: nao esta com sono" << std::endl;
        }else{
            int t = energyMax - getEnergy();
            setEnergy(energyMax);
            age += t;
        }
        
    }

    int getClean(){
        return clean;
    }

    int getCleanMax(){
        return cleanMax;
    }

    int getEnergy(){
        return energy;
    }

    int getEnergyMax(){
        return energyMax;
    }


    std::string show(){
        return format("E:{}/{}, L:{}/{}, I:{}", energy, energyMax, clean, cleanMax, age);
    }

};
/*
class Game{
    private:

    Tamagochi tamagochi;

    bool testAlive(bool alive){
        if(alive = false){
            std::cout << "fail: pet esta morto" << std::endl;
            return false;
        }
        return true;
    }
    public:

    void game(Tamagochi tamagochi){}
    

    std::string toString(){}

    void play(){
        if(!testAlive)return;
        
    }

    void shower(){}

    void sleep(){}


};

class Adapter {
private:
    // Game game;
public:
    void init(int energy, int clean) {
        (void) energy;
        (void) clean;
        // this->game = Game(Pet(energy, clean));
    }

    void show() {
        // std::cout << this->game.str() << std::endl;
    }

    void play() {
        // this->game.play();
    }

    void shower() {
        // this->game.shower();
    }

    void eat() {
        // this->game.eat();
    }

    void sleep() {
        // this->game.sleep();
    }
};
*/

int main() {
    Tamagochi adp;
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');

        fn::write("$" + line);

        if      (args[0] == "end")    { break;                                       }
        else if (args[0] == "init")   { adp.init(+args[1], +args[2]);                }
        else if (args[0] == "show")   {  fn::write(adp.show());                      }
        else if (args[0] == "play")   { adp.play();                                  }
        else if (args[0] == "sleep")  { adp.sleep();                                 }
        else if (args[0] == "shower") { adp.shower();                                }
        else                          { fn::write("fail: comando invalido");         }
    }
}
