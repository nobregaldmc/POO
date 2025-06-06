#include <iostream>
#include <sstream>
#include <memory>
#include <utility>
using namespace std;

class Bateria{
    private:
        int carga, capacidade;
    public:
        Bateria(int capacidade = 0) : carga(capacidade), capacidade(capacidade){
        
        }

        int getCarga(){
                return carga;
        }

        int getCapacidade(){
            return capacidade;
        }

        void setCarga(int c){
            carga = c;
        }

};

class Carregador{
    private:
        int potencia;
    public:
        Carregador(int potencia = 0) : potencia(potencia){

        }

        int getPotencia(){
            return potencia;
        }
};

class Notebook{
    private:
        unique_ptr<Bateria> bateria;
        unique_ptr<Carregador> carregador;
        bool ligado = false;
        int minutos_usados = 0;

    public:
        void ligar() {
        if (ligado) cout << "fail: Notebook já está ligado\n";
        else if ((bateria && bateria->getCarga() > 0) || (carregador && carregador->getPotencia() > 0)) ligado = true;
        else cout << "fail: não foi possível ligar\n";
    }
    void desligar() { if (ligado) ligado = false; else cout << "fail: Notebook já está desligado\n"; }
    void usar(int minutos) {
    if (!ligado) { cout << "fail: desligado\n"; return; }
    
    if (bateria && bateria->getCarga() > 0 && !carregador) {
        int consumo = min(bateria->getCarga(), minutos);
        bateria->setCarga(bateria->getCarga() - consumo);
        if (bateria->getCarga() == 0) { cout << "fail: descarregou\n"; ligado = false; }
    }

    minutos_usados += minutos;

    if (carregador && bateria) {  // <- Verificando se bateria não é nullptr
        int nova_carga = bateria->getCarga() + minutos * carregador->getPotencia();
        bateria->setCarga(min(nova_carga, bateria->getCapacidade()));
    }


    }
    void setCarregador(int potencia) { 
        if (carregador) cout << "fail: carregador já conectado\n";
        else carregador = make_unique<Carregador>(potencia); 
    }
    void removeCarregador() {
    if (carregador) { 
        cout << "Removido " << carregador->getPotencia() << "W\n"; 
        carregador.reset(); 
        
        // Verifica se o notebook pode continuar ligado
        if (!(bateria && bateria->getCarga() > 0)) {
            ligado = false;
        }
    } else {
        cout << "fail: Sem carregador\n";
        }
    }

    void setBateria(int capacidade) { bateria = make_unique<Bateria>(capacidade); }
    void removeBateria() {
    if (bateria) { 
        cout << "Removido " << bateria->getCarga() << "/" << bateria->getCapacidade() << "\n"; 
        bateria.reset();
        
        // Se não houver carregador, o notebook deve ser desligado
        if (!carregador) {
            ligado = false;
        }
    } else {
        cout << "fail: Sem bateria\n";
        }
    }

    string str() {
        string res = "Notebook: " + string(ligado ? "ligado" : "desligado");
        if (ligado) res += " por " + to_string(minutos_usados) + " min"; 
        if (carregador) res += ", Carregador " + to_string(carregador->getPotencia()) + "W";
        if (bateria) res += ", Bateria " + to_string(bateria->getCarga()) + "/" + to_string(bateria->getCapacidade());
        return res;
    }
};

int main() {
    Notebook notebook;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end"){
            break;
        }else if (cmd == "show"){ 
            std::cout << notebook.str() << std::endl;
            }else if (cmd == "turn_on"){
                notebook.ligar(); 
            }else if (cmd == "turn_off"){ 
                notebook.desligar();
            }else if (cmd == "use"){ 
                int minutes;
                ss >> minutes;
                notebook.usar(minutes);
            }else if (cmd == "set_charger"){
                // CRIE UM OBJETO Charger E ATRIBUA AO NOTEBOOK
                int power;
                ss >> power;
                notebook.setCarregador(power);
            }else if (cmd == "rm_charger"){
                notebook.removeCarregador();
             // REMOVA O CARREGADOR DO NOTEBOOK E IMPRIMA SE ELE EXISTIR
            }else if (cmd == "set_battery"){
                // CRIE UM OBJETO Bateria E ATRIBUA AO NOTEBOOK
                int capacity;
                ss >> capacity;
                notebook.setBateria(capacity);
            }else if (cmd == "rm_battery"){
                notebook.removeBateria();
                // REMOVA A BATERIA DO NOTEBOOK E IMPRIMA SE ELA EXISTIR
            }else{
                cout << "fail: comando inválido\n";
        }
    }    
}
