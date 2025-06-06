#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

template<typename Container, typename Func>
string map_join(const Container& cont, Func func, const string& delim) {
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); ++it) {
        if (it != cont.begin()) ss << delim;
        ss << func(*it);
    }
    return ss.str();
}

class Espiral {
private:
    string nome;
    int quantidade;
    double preco;
public:
    Espiral(string nome = "empty", int quantidade = 0, double preco = 0.0)
        : nome(move(nome)), quantidade(quantidade), preco(preco) {}
    
    string getNome(){ 
        return nome; 
        }
    int getQuantidade(){
        return quantidade;
        }
    double getPreco(){
        return preco;
        }
    
    void setNome(const string& nome) { this->nome = nome; }
    void setQuantidade(int quantidade) { this->quantidade = quantidade; }
    void setPreco(double preco) { this->preco = preco; }
    
    string str() const {
        stringstream ss;
        ss << "[" << setw(8) << setfill(' ') << nome
           << " : " << quantidade << " U : "
           << fixed << setprecision(2) << preco << " RS]";
        return ss.str();
    }
};

class Maquina {
private:
    vector<Espiral> espirais;
    double saldo {0.0};
    double lucro {0.0};
public:
    Maquina(int n_espirais) : espirais(n_espirais) {}
    
    void setEspiral(int indice, const string& nome, int quantidade, double preco) {
        if (indice < 0 || indice >= static_cast<int>(espirais.size())) {
            cout << "fail: indice nao existe" << '\n';
            return;
        }
        espirais[indice] = Espiral(nome, quantidade, preco);
    }

    void limpar(int indice) {
        if (indice < 0 || indice >= static_cast<int>(espirais.size())) {
            cout << "fail: indice nao existe" << '\n';
            return;
        }
        espirais[indice] = Espiral();
    }

    void inserirDinheiro(double value) { saldo += value; }
    double pegarTroco() { return exchange(saldo, 0.0); }

    void comprar(int indice) {
        if (indice < 0 || indice >= static_cast<int>(espirais.size())) {
            cout << "fail: indice nao existe" << '\n';
            return;
        }
        auto& espiral = espirais[indice];
        if (espiral.getQuantidade() <= 0) {
            cout << "fail: espiral sem produtos" << '\n';
            return;
        }
        if (espiral.getPreco() > saldo) {
            cout << "fail: saldo insuficiente" << '\n';
            return;
        }
        saldo -= espiral.getPreco();
        lucro += espiral.getPreco();
        espiral.setQuantidade(espiral.getQuantidade() - 1);
        cout << "voce comprou um " << espiral.getNome() << '\n';
    }

    string str() const {
        stringstream ss;
        ss << "saldo: " << fixed << setprecision(2) << saldo << endl;
        for (size_t i = 0; i < espirais.size(); i++) {
            ss << i << " " << espirais[i].str() << endl;
        }
        string saida = ss.str();
        saida.pop_back();
        return saida;
    }
};

int main() {
    Maquina maquina(4);
    string line;
    while (getline(cin, line)) {
        cout << "$" << line << endl;
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "show") {
            cout << maquina.str() << '\n';
        } else if (cmd == "init") {
            int n_espirais;
            ss >> n_espirais;
            maquina = Maquina(n_espirais);
        } else if (cmd == "limpar") {
            int indice;
            ss >> indice;
            maquina.limpar(indice);
        } else if (cmd == "dinheiro") {
            double value;
            ss >> value;
            maquina.inserirDinheiro(value);
        } else if (cmd == "comprar") {
            int index;
            ss >> index;
            maquina.comprar(index);
        } else if (cmd == "set") {
            int index, quantidade;
            double preco;
            string nome;
            ss >> index >> nome >> quantidade >> preco;
            maquina.setEspiral(index, nome, quantidade, preco);
        } else if (cmd == "troco") {
            cout << "voce recebeu " << fixed << setprecision(2) 
                 << maquina.pegarTroco() << " RS" << '\n';
        } else if (cmd == "end") {
            break;
        } else {
            cout << "comando invalido" << endl;
        }
    }
    return 0;
}
