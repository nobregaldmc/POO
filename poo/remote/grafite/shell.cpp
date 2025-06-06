#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

class Grafite {
public:
    double calibre;
    std::string dureza;
    int tamanho;

    Grafite(double calibre, std::string dureza, int tamanho)
        : calibre(calibre), dureza(dureza), tamanho(tamanho) {}

    int usagePerSheet() {
        if (dureza == "HB") return 1;
        if (dureza == "2B") return 2;
        if (dureza == "4B") return 4;
        if (dureza == "6B") return 6;
        return 1;
    }
};

class Lapiseira {
private:
    double calibre;
    std::shared_ptr<Grafite> grafite;

public:
    Lapiseira(double calibre) : calibre(calibre), grafite(nullptr) {}

    bool hasGrafite() {
        return grafite != nullptr;
    }

    bool insert(std::shared_ptr<Grafite> novoGrafite) {
        if (grafite) {
            std::cout << "fail: ja existe grafite" << std::endl;
            return false;
        }
        if (novoGrafite->calibre != calibre) {
            std::cout << "fail: calibre incompativel" << std::endl;
            return false;
        }
        grafite = novoGrafite;
        return true;
    }

    std::shared_ptr<Grafite> remove() {
        auto removido = grafite;
        grafite = nullptr;
        return removido;
    }

    void write() {
    if (!hasGrafite()) {
        std::cout << "fail: nao existe grafite" << std::endl;
        return;
    }

    int gasto = grafite->usagePerSheet();

    if (grafite->tamanho == 10) { 
        // Caso o grafite já esteja em 10mm, não pode mais ser usado
        std::cout << "fail: tamanho insuficiente" << std::endl;
        return;
    }

    if (grafite->tamanho - gasto < 10) {
        // Caso o gasto deixe o grafite abaixo de 10mm, interrompe a escrita
        std::cout << "fail: folha incompleta" << std::endl;
        grafite->tamanho = 10;  
    } else {
        // Escrita normal
        grafite->tamanho -= gasto;
    }
}


    void show() {
        std::cout << "calibre: " << calibre << ", grafite: ";
        if (grafite) {
            std::cout << "[" << grafite->calibre << ":" << grafite->dureza << ":" << grafite->tamanho << "]";
        } else {
            std::cout << "null";
        }
        std::cout << std::endl;
    }
};

class Adapter {
private:
    std::shared_ptr<Lapiseira> lapiseira;

public:
    void execute(const std::string& command) {
    std::istringstream ss(command);
    std::string cmd;
    ss >> cmd;

    if (cmd == "init") {
        double calibre;
        ss >> calibre;
        lapiseira = std::make_shared<Lapiseira>(calibre);
        std::cout << "$init " << calibre << std::endl;
    } 
    else if (cmd == "insert") {
        double calibre;
        std::string dureza;
        int tamanho;
        ss >> calibre >> dureza >> tamanho;
        std::shared_ptr<Grafite> grafite = std::make_shared<Grafite>(calibre, dureza, tamanho);
        std::cout << "$insert " << calibre << " " << dureza << " " << tamanho << std::endl;
        lapiseira->insert(grafite);
    } 
    else if (cmd == "remove") {
        std::cout << "$remove" << std::endl;
        lapiseira->remove();
    } 
    else if (cmd == "write") {
        std::cout << "$write" << std::endl;
        lapiseira->write();
    } 
    else if (cmd == "show") {
        std::cout << "$show" << std::endl;  
        lapiseira->show(); 
    } 
    else if (cmd == "end") {
        std::cout << "$end" << std::endl;
    } 
    else {
        std::cout << "fail: comando desconhecido" << std::endl;
    }
}

};

int main() {
    Adapter adapter;
    std::string line;

    while (std::getline(std::cin, line)) {
        adapter.execute(line);
    }

    return 0;
}
