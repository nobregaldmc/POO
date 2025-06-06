#include <iostream>
#include <sstream>
#include <memory>
using namespace std;

class Pessoa{
    private:
        std::string nome;
        int dinheiro;
    public:
        Pessoa(std::string nome = "", int dinheiro = 0) : nome(nome), dinheiro(dinheiro){

        }

    void setNome(const std::string& nome){
        this->nome = nome;
    }
    void setDinheiro(int dinheiro){
        this->dinheiro = dinheiro;
    }
    std::string getNome() const{
        return nome;
    }
    int getDinheiro() const{
        return dinheiro;
    }

};

class MotoUber{
    private:
        Pessoa motorista;
        Pessoa passageiro;
        int custoAtualCorrida;
    public:
        MotoUber() : custoAtualCorrida(0){

        }

        void setCustoAtualCorrida(int custo){
            custoAtualCorrida = custo;
        }

        int getCustoAtualCorrida() const{
            return custoAtualCorrida;
        }

        void setDriver(const std::string& nome, int dinheiro){
            motorista.setNome(nome);
            motorista.setDinheiro(dinheiro);
        }

        void setPassageiro(const std::string& nome, int dinheiro){
            passageiro.setNome(nome);
            passageiro.setDinheiro(dinheiro);
        }

        void descerPassageiro() {
            if (passageiro.getNome().empty()) {
                std::cout << "fail: No passenger in the vehicle\n";
                return;
            }

            if (passageiro.getDinheiro() >= custoAtualCorrida) {
                motorista.setDinheiro(motorista.getDinheiro() + custoAtualCorrida);
                passageiro.setDinheiro(passageiro.getDinheiro() - custoAtualCorrida);
                std::cout << passageiro.getNome() << ":" << passageiro.getDinheiro() << " left\n"; 
            } else {
                std::cout << "fail: Passenger does not have enough money" << "\n";

            motorista.setDinheiro(motorista.getDinheiro() + custoAtualCorrida);
            passageiro.setDinheiro(0);
            std::cout << passageiro.getNome() << ":0 left\n";
            }

        passageiro = Pessoa();
        custoAtualCorrida = 0;
}




        void drive(int distancia){
            custoAtualCorrida += distancia;
        }

        void show() const{
            std::cout << "Cost: " << custoAtualCorrida << ", Driver: " << (motorista.getNome().empty() ? "None" : motorista.getNome() + ":" + to_string(motorista.getDinheiro()))
            << ", Passenger: " << (passageiro.getNome().empty() ? "None" : passageiro.getNome() + ":" + to_string(passageiro.getDinheiro())) << "\n";
        }

};

int main() {
    MotoUber moto;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } 
        else if (cmd == "show") { 
            moto.show();
        }
        else if (cmd == "setDriver") { 
             string name;
             int money;
             ss >> name >> money;
             moto.setDriver(name, money);
         }
         else if (cmd == "setPass") { 
             string name;
             int money;
             ss >> name >> money;
             moto.setPassageiro(name, money);
         }
         else if (cmd == "drive") { 
             int distance;
             ss >> distance;
             moto.drive(distance);
         }
         else if (cmd == "leavePass") { 
            moto.descerPassageiro();
         }
        else {
            cout << "fail: command not found\n";
        }
    }
}
