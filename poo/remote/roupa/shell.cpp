#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Roupa{
    private:
    string tamanho;
    public:

    Roupa(){
        this->tamanho="";
    }
    
    void setTamanho(string tamanho){
        if(tamanho == "PP" ||tamanho == "P" || tamanho == "M" || tamanho == "G" || tamanho == "GG" || tamanho == "XG"){
            this->tamanho=tamanho;
        }else{
            std::cout << "fail: Valor inválido, tente PP, P, M, G, GG ou XG" << endl;
        }
    }

    string getTamanho(){
        return tamanho;
    }

    void toString(){
        std::cout << "size: (" << tamanho << ")" << std::endl;
    }
};

int main() {
    Roupa roupa;
    

    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "size") { // TENTE ATRIBUIR UM TAMANHO
            string size;
            ss >> size;
            roupa.setTamanho(size);
        } else if (cmd == "show") { // MOSTRE AS INFORMAÇÕES DO OBJETO
            roupa.toString();
        } else if (cmd == "end") {
            break;
        } else {
            cout << "fail: Comando inválido" << endl;
        }
    }
}
