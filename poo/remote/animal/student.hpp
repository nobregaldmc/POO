#pragma once
#include "fn.hpp"

//------------------------------------------------CLASSE ANIMAL-------------------------------------
// LÓGICAS
struct Animal           //ESTRUTURA COM ATRIBUTOS E MÉTODOS
{
    int idade;          //ATRUBUTO
    std::string especie;//ATRUBUTO
    std::string barulho;//ATRUBUTO

    Animal(std::string especie = "", std::string barulho = "")          //CONSTRUTOR-INICIALIZA UM ANIMAL COM VALORES OPCIONAIS PARA ESPECIE E BARULHO
    {                                                                   //O ESTÁGIO E INICIALIZADO EM 0 POR ISSO NÃO PRECISA ESTAR DENTRO DO CONSTRUTOR
        this->especie = especie;
        this->barulho = barulho;
        this->idade = 0;
    }

    std::string fazerbarulho() const                //METODO
    { // LÓGICA DO FAZER BARULHO
        if (idade == 0)
        {                 // SE A IDADE FOR IGUAL A ZERO
            return "---"; // SAÍDA SERÁ O GRUNIDO ---
        }
        if (idade == 4)
        {                 // SE A IDADE FOR IGUAL A 4
            return "RIP"; // SAÍDA SERÁ O RIP
        }
        return this->barulho; // QUALQUER OUTRA IDADE A SAÍDA SERÁ O BARULHO DO ANIMAL
    }

    void envelhecer(int tamanho)                    //MÉTODO
    {                     // LÓGICA DA IDADE DO ANIMAL
        idade += tamanho; // ENVELHECIMENTO
        if (idade >= 4)
        { // SE A IDADE FOR MAIOR QUE 4, SERÁ PRINTADA UMA MENSAGEM DE QUE A ESPECIE EM QUESTÃO MORREU
            fn::print("warning: {} morreu\n", especie);
            idade = 4; // NÃO DEIXA PASSAR DO ESTÁGIO DA MORTE
        }
    }
    std::string str() const                         //MÉTODO-RETORNA UMA STRING QUE REPRESENTA O ESTADO DO ANIMA NO FORMATO "especie:idade:barulho:"
    {
        return fn::format("{}:{}:{}", especie, idade, barulho);
    }
};

inline std::ostream &operator<<(std::ostream &os, const Animal &animal)     //ESSE TRECHO PERMITE IMPRIMIR UM OBJETO Animal DIRETAMENTE EM UMA SAIDA COMO std::cout
{
    return os << animal.str();
}
// void crescer(int etapas){
//     idade+=etapas;
//     if
// }
//
// int main(){
//     Animal gato("gato", "miau");
//     std::cout <<gato.str() << '\n';
//     std::cout <<gato.fazer_barulho() << '\n';
//     gato.crescer(1);
// }

struct Student          //ESTRUTURA
{
    Animal animal;
    Student(std::string especie = "", std::string barulho = "")
    {
        // ACT
        (void)especie;
        (void)barulho;
        animal = Animal(especie, barulho);
    }

    void grow(int tamanho)
    {
        (void)tamanho;
        animal.envelhecer(tamanho); //CHAMA O METODO ENVELHECER DO ANIMAL, AUMENTANDO SEU ESTAGIO PELO VALOR DE NIVEL
    }

    void noise()
    {
        // return "";
        std::cout << animal.fazerbarulho() << std::endl; //EXIBE O SOM DO ANIMAL CHAMANDO FAZERBARULHO() E IMPRIMINDO O RESULTADP
    }

    void show()
    {
        // return "";
        std::cout << animal.str() << std::endl; //EXIBE O ESTADO DO ANIMAL CHAMANDO ANIMAL.STR() E IMPRIMINDO O RESULTADO
    }
};

struct Debug
{
    // Se a variável debug for true, os testes não serão executados
    // Apenas o conteúdo do método run() será executado
    // Você pode usar isso para testar seu código manualmente
    static const bool debug = false;
    static void run()
    {
        std::cout << "Debug ativado" << std::endl;
    }
};