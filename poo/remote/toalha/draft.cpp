#include <iostream>

class Toalha{
    private:
    std::string cor;
    char tamanho;
    int umidade;

    public:

    Toalha(std::string cor, char tamanho){
        umidade = 0;
        this->cor = cor;
        this->tamanho = tamanho;

    }

    int enxugar(int umidade){
        this->umidade += umidade;
        return 0;
    }

    int torcer(){
        this->umidade = 0;
        return 0;
    }

    int pegarMaximoUmidade()const{
        switch (tamanho){
        case 'P': return 10;
        case 'M': return 20;
        case 'G': return 30;
        default: return 0;
        }
    }

    bool estaseca()const{
        return umidade == 0;
    }

};

    int main(){
         // Criar uma toalha de tamanho M e cor azul
    Toalha minhaToalha("azul", 'M');
    
    // Testar se está seca inicialmente
    std::cout << "A toalha está seca? " << (minhaToalha.estaseca() ? "Sim" : "Não") << std::endl;

    // Testar enxugar com uma quantidade de umidade
    minhaToalha.enxugar(10);
    std::cout << "A toalha está seca após enxugar? " << (minhaToalha.estaseca() ? "Sim" : "Não") << std::endl;

    // Testar o máximo de umidade para o tamanho M
    std::cout << "O máximo de umidade permitido para a toalha é: " << minhaToalha.pegarMaximoUmidade() << std::endl;

    // Testar torcer a toalha
    minhaToalha.torcer();
    std::cout << "A toalha está seca após torcer? " << (minhaToalha.estaseca() ? "Sim" : "Não") << std::endl;

    // Testar enxugar além do limite de umidade permitido
    minhaToalha.enxugar(25); // Acima do limite para tamanho M
    std::cout << "A toalha tem umidade acima do limite permitido? " 
              << (minhaToalha.enxugar(15), minhaToalha.estaseca() ? "Não" : "Sim") << std::endl;

    return 0;
    }