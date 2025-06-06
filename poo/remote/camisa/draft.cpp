#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Roupa {
private:
    string tamanho;
public:
    Roupa() {
        this->tamanho = "";
    }
    
    void setTamanho(string tamanho) {
        if (tamanho == "PP" || tamanho == "P" || tamanho == "M" || tamanho == "G" || tamanho == "GG" || tamanho == "XG") {
            this->tamanho = tamanho;
        } else {
            cout << "fail: Valor inválido, tente PP, P, M, G, GG ou XG" << endl;
        }
    }

    string getTamanho() {
        return tamanho;
    }

    void toString() {
        cout << "size: (" << tamanho << ")" << endl;
    }
};

void executarTeste(vector<string> comandos) {
    Roupa roupa;
    for (const string& linha : comandos) {
        cout << "$" << linha << endl;
        stringstream ss(linha);
        string cmd;
        ss >> cmd;

        if (cmd == "size") {
            string size;
            ss >> size;
            roupa.setTamanho(size);
        } else if (cmd == "show") {
            roupa.toString();
        } else if (cmd == "end") {
            break;
        } else {
            cout << "fail: Comando inválido" << endl;
        }
    }
    cout << "-----------------------" << endl;
}

int main() {
    cout << "Caso de Teste 1: Atribuir tamanho válido" << endl;
    executarTeste({"size M", "show", "end"});
    
    cout << "Caso de Teste 2: Tentar atribuir um tamanho inválido" << endl;
    executarTeste({"size XXL", "show", "end"});
    
    cout << "Caso de Teste 3: Alterar tamanho após uma tentativa inválida" << endl;
    executarTeste({"size XP", "size P", "show", "end"});
    
    return 0;
}
