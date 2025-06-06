#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

class Veiculo{
    private:
        string id;
        string tipo;
    public:
        float horaEntrada = 0;
        Veiculo(string id, string tipo) : id(std::move(id)), tipo(std::move(tipo)){

        }
        virtual ~Veiculo() = default;
        virtual float calcularValor(float horaSaida) = 0;

        float getEntrada()const{
            return horaEntrada;
        }
        
        void setEntrada(float horaEntrada){
            this->horaEntrada = horaEntrada;
        }
        
        string getId()const{
            return id;
        }

        string getTipo()const{
            if(tipo == "Bike"){
                return "Bike";
            }
            if(tipo == "Moto"){
                return "Moto";
            }
            if(tipo == "Carro"){
                return "Carro";
            }
            return "Tipo invalido";
        }

        virtual string toString()const{
            std::stringstream ss;
            ss << std::setw(10) << std::setfill('_') << tipo << " : " << std::setw(10) << std::setfill('_') << id << " : " << horaEntrada;
            return ss.str();
        }
};

class Bike : public Veiculo{
    private:

    public:
        Bike(string id) : Veiculo(std::move(id), "Bike"){

        }

        float calcularValor(float) override{
            return 3.0;
        }
};

class Carro : public Veiculo{
    private:

    public:
        Carro(string id) : Veiculo(std::move(id), "Carro"){

        }
        float calcularValor(float horaSaida) override{
            return std::max((horaSaida - horaEntrada) / 10, 5.0f);
        }
};

class Moto : public Veiculo{
    private:

    public:
        Moto(string id) : Veiculo(std::move(id), "Moto"){

        }

        float calcularValor(float horaSaida) override{
            return (horaSaida - horaEntrada) /20;
        }
};

class Estacionamento{
    private:
        int horaAtual = 0;
        vector<Veiculo*> veiculos;
    public:
        ~Estacionamento(){
            for(auto v : veiculos) delete v;
        }
        
        void passarTempo(int tempo){
            horaAtual += tempo;
        }

        void estacionar(Veiculo* veiculo){
            if(veiculo){
                veiculo->setEntrada(horaAtual);
                veiculos.push_back(veiculo);
            }
        }

        void pagar(string id){
            auto it = std::find_if(veiculos.begin(), veiculos.end(), [&](Veiculo* v){
                return v->getId() == id;
            });

            if(it != veiculos.end()){
                Veiculo* veiculo = *it;
                cout << veiculo->getTipo() << " chegou " << (int)veiculo->getEntrada() << " saiu " << horaAtual << ". Pagar R$ " << std::fixed << std::setprecision(2) << veiculo->calcularValor(horaAtual) << endl;
                veiculos.erase(it);
                delete veiculo;
            }else{
                cout << "Veiculo nao encontrado" << endl;
            }
        }

        void mostrar()const{
            for(const auto& veiculo : veiculos)
                std::cout << veiculo->toString() << std::endl;
            std::cout << "Hora atual: " << horaAtual << std::endl;
        }
};

int main() {
    Estacionamento estacionamento;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") {
            estacionamento.mostrar();
        } else if (cmd == "estacionar") {
            string tipo, id;
            ss >> tipo >> id;
            if(tipo == "carro"){
                estacionamento.estacionar(new Carro(id));
            }else if(tipo == "bike"){
                estacionamento.estacionar(new Bike(id));
            }else if(tipo == "moto"){
                estacionamento.estacionar(new Moto(id));
            }
        } else if (cmd == "tempo") {
            int tempo;
            ss >> tempo;
            estacionamento.passarTempo(tempo);
        } else if (cmd == "pagar") {
            string id;
            ss >> id;
            estacionamento.pagar(id);
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
