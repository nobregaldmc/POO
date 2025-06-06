#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include <iomanip>
#include <memory>
using namespace std;

template <typename CONTAINER, typename FN>
string map_join(const CONTAINER& container, FN fn, string sep = ", ", string prefix = "[", string suffix = "]") {
    stringstream ss;
    for (auto it = container.begin(); it != container.end(); ++it) {
        ss << (it != container.begin() ? sep : "") << fn(*it);
    }
    return prefix + ss.str() + suffix;
}

class Coin{
    private:
        double value;
        int volume;
        string label;

    public:
        Coin(double value, int volume, string label) : value(value), volume(volume), label(label){
            
        }

        int getValue(){
            return value;
        }

        int getVolume(){
            return volume;
        }

        string getLabel(){
            return label;
        }



        string toString(){

        }        

};

class Item{
    private:
        string label;
        int volume;

    public:
        Item(string label, int volume) : label(label), volume(volume){

        }

        string getLabel(){
            return label;
        }

        int getVolume(){
            return volume;
        }

        void setLabel(string label){
            
        }

        void setVolume(int volume){
            
        }

        string toString(){

        }

};

class Pig{
    private:
        

    public:

};



int main() {
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "init") {
            // int volumeMax;
            // ss >> volumeMax;
        } else if (cmd == "show") {
        } else if (cmd == "break") {
        } else if (cmd == "addCoin") {
            // string label;
            // ss >> label;
        } else if (cmd == "addItem") {
            // string label;
            // int volume;
            // ss >> label >> volume;
        } else if (cmd == "extractItems") {
            // Obtenha os itens com o método extractItems
            // e imprima os itens obtidos
        } else if (cmd == "extractCoins") {
            // Obtenha as moedas com o método extractCoins
            // e imprima as moedas obtidas
        } else {
            cout << "fail: invalid command\n";
        }
    }
}
