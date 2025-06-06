#include <iostream>
#include <sstream>
using namespace std;

class Toalha {
private:
    string cor;
    char tamanho;
    int umidade;

public:
    Toalha(string cor = "", char tamanho = 'P') {
        umidade = 0;
        this->cor = cor;
        this->tamanho = tamanho;
    }

    void enxugar(int umidade) {
        
        if (this->umidade+umidade > pegarMaximoUmidade()) {
            cout << "toalha encharcada" << endl;
            
            return;
        }else if(this->umidade+umidade == pegarMaximoUmidade()){
            cout << "toalha encharcada" << endl;
            this->umidade += umidade;
            return;
        }
        this->umidade += umidade;
        return;
    }

    int torcer() {
        this->umidade = 0;
        return 0;
    }

    int pegarMaximoUmidade() const {
        switch (tamanho) {
            case 'P': return 10;
            case 'M': return 20;
            case 'G': return 30;
            default: return 0;
        }
    }

    bool estaseca() const {
        return umidade == 0;
    }

    string toString() const {
        stringstream ss;
        ss << "Cor: " << cor << ", Tamanho: " << tamanho << ", Umidade: " << umidade;
        return ss.str();
    }
};

int main() {
    Toalha minhaToalha;

    while (true) {
        string line, cmd;
        getline(cin, line);

        // Mostrar o comando digitado
        cout << "$" << line << endl;

        stringstream par(line);
        par >> cmd;

        if (cmd == "mostrar") {
            cout << minhaToalha.toString() << endl;
        } 
        else if (cmd == "criar") {
            string cor;
            char tamanho;
            par >> cor >> tamanho;
            minhaToalha = Toalha(cor, tamanho);
        } 
        else if (cmd == "enxugar") {
            int umidade {};
            par >> umidade;
            minhaToalha.enxugar(umidade);
        } 
        else if (cmd == "torcer") {
            minhaToalha.torcer();
        } 
        else if (cmd == "seca") {
            cout << (minhaToalha.estaseca() ? "sim" : "nao") << endl;
        } 
        else if (cmd == "end") {
            break;
        } 
        else {
            cout << "fail: comando invalido" << endl;
        }
    }
    return 0;
}
