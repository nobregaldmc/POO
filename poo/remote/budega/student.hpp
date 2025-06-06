#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include "fn.hpp"

class Pessoa {
    std::string nome;
public:
    Pessoa(std::string nome) { 
      this->nome = nome;
    }
    std::string getNome() const {
        return this->nome;
    }
    std::string str() const {
        return this->nome; 
    }
};
std::ostream& operator<<(std::ostream& os, const Pessoa& p) {
    return (os << p.str());
}

class Budega {
    std::vector<std::shared_ptr<Pessoa>> caixas; 
    std::list  <std::shared_ptr<Pessoa>> esperando; 

    bool validarIndice(int indice) {
    if (indice < 0 || static_cast<size_t>(indice) >= caixas.size()) {
        return false;
    }
    return true;
}


public:
    Budega(int qtd_caixas) { 
      for(int i = 0; i < qtd_caixas; i++){
        this->caixas.push_back(nullptr);
      }
    }
    
    void chegar(const std::shared_ptr<Pessoa>& person) {
      this->esperando.push_back(person);
    }

    bool chamarNoCaixa(int indice) {
        if(validarIndice(indice)){
          if(this->caixas[indice] == nullptr){
            if(this->esperando.size() != 0){
              this->caixas[indice] = this->esperando.front();
              this->esperando.pop_front();
              return true;
            }else{
              fn::write("fail: sem clientes");
              return false;
            }
          }else{
            fn::write("fail: caixa ocupado");
            return false;
          }
        }else{
          return false;
        }
    }
    
    std::shared_ptr<Pessoa> finalizar(int indice) {
        std::shared_ptr<Pessoa> removed = nullptr;
        
        if(validarIndice(indice)){
          if(this->caixas[indice] != nullptr){
            removed = this->caixas[indice];
            this->caixas[indice] = nullptr;
          }else{
            fn::write("fail: caixa vazio");
          }
        }else{
          fn::write("fail: caixa inexistente");
        }

        return removed;
    }

    std::string str() const {
        auto caixas_str = caixas | fn::MAP([](const std::shared_ptr<Pessoa>& c){
            return c == nullptr ? "-----" : c->getNome();
        });
        return "Caixas: " + fn::tostr(caixas_str) + "\n" + "Espera: " + fn::tostr(esperando);
    }
};

std::ostream& operator<<(std::ostream& os, const Budega& b) {
    return (os << b.str());
}
