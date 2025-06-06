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
    void ligar(){
    if(ligado)
        std::cout << "fail: Notebook ja esta ligado\n";
    else if ((bateria && bateria->getCarga() > 0) || (carregador && carregador->getPotencia() > 0))
        ligado = true;
    else
        cout << "fail: nao foi possivel ligar\n";
    }

    
    void desligar(){
        if(ligado) ligado = false;
        else{
            std::cout << "fail: Notebook ja esta desligado\n";
            }
        }

    void usar(int minutos) {
        if (!ligado) { cout << "fail: desligado\n"; return; }
    
        if (bateria && bateria->getCarga() > 0 && !carregador) {
            int consumo = min(bateria->getCarga(), minutos);
            bateria->setCarga(bateria->getCarga() - consumo);
            if (bateria->getCarga() == 0) { cout << "fail: descarregou\n"; ligado = false; }
        }
    
        minutos_usados += minutos;
    
        if (carregador && bateria) {
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
            if (!(bateria && bateria->getCarga() > 0)) ligado = false;
        } else {
            cout << "fail: Sem carregador\n";
        }
    }
    
    void setBateria(int capacidade) { bateria = make_unique<Bateria>(capacidade); }
    
    void removeBateria() {
        if (bateria) {
            cout << "Removido " << bateria->getCarga() << "/" << bateria->getCapacidade() << "\n";
            bateria.reset();
            if (!carregador) ligado = false;
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

int main(){
    Notebook notebook;

    cout << "testando caso 1\n";
    notebook.setBateria(50);
    notebook.ligar();
    notebook.usar(5);
    cout << notebook.str() << endl;

    cout << "testando caso 2\n";
    notebook.removeBateria();
    cout << notebook.str() << endl;

    cout << "testando caso 3\n";
    notebook.setCarregador(10);
    notebook.ligar();
    notebook.usar(10);
    cout << notebook.str() << endl;

    cout << "testando caso 4\n";
    notebook.removeCarregador();
    cout << notebook.str() << endl;

    return 0;
}


    




