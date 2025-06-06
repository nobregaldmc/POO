#include <iostream>
#include <limits>
using namespace std;
class Chinela {

private:
    int tamanho;

public:
    Chinela():tamanho(0){}

    bool setTamanho(int valor){
        if(valor >= 20 && valor <= 50 && valor % 2 == 0){
            tamanho = valor;
            return true;
        }else{
            std::cout << "Erro: O tamanho deve estar entre 20 e 50 e ser par." << std::endl;
            return false;
        }
    }

    int getTamanho() const{
        return tamanho;
    }

    bool estaValida()const{
        return tamanho >= 20 && tamanho <= 50 && tamanho % 2 == 0;
    }
    
};


int main() {

    Chinela minhaChinela;

    while (minhaChinela.getTamanho() == 0){
        cout << "Digite seu tamanho de chinela: ";
        int tamanho;
        if(std::cin >> tamanho){
            minhaChinela.setTamanho(tamanho);
        }else{
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Erro: Por favor, insira um numero inteiro valido." << std::endl;
        }
    
        
    }
    std::cout << "Parabéns, você comprou uma chinela tamanho "<< minhaChinela.getTamanho() << "!" << std::endl;
    return 0;
}

