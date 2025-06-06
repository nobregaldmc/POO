#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <utility>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>

class Grafite {
    float calibre;
    std::string dureza;
    int tamanho;

public:
    Grafite(float calibre, std::string dureza, int tamanho)
        : calibre(calibre), dureza(dureza), tamanho(tamanho) {}

    int desgastePorFolha() {
        if (dureza == "HB") return 1;
        if (dureza == "2B") return 2;
        if (dureza == "4B") return 4;
        return 6;
    }

    float getCalibre() { return calibre; }
    std::string getDureza() { return dureza; }
    int getTamanho() { return tamanho; }
    void setTamanho(int tamanho) { this->tamanho = tamanho; }

    std::string str() const {
        std::ostringstream os;
        os << std::fixed << std::setprecision(1) << calibre << ":" << dureza << ":" << tamanho;
        return os.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Grafite& g) {
    return os << g.str();
}

using PGrafite = std::shared_ptr<Grafite>;

struct Lapiseira {
    float calibre{ 0.f };
    PGrafite grafite{ nullptr };
    std::list<PGrafite> tambor;

    Lapiseira(float calibre = 0.0) { this->calibre = calibre; }

    bool inserir(PGrafite grafite) {
        if (grafite->getCalibre() != this->calibre) {
            std::cout << "fail: calibre incompatível\n";
            return false;
        }
        this->tambor.push_back(grafite);
        return true;
    }

    PGrafite remover() {
        if (grafite == nullptr) {
            std::cout << "fail: nao tem grafite\n";
            return nullptr;
        }
        PGrafite removed = this->grafite;
        this->grafite = nullptr;
        return removed;
    }

    void write() {
        if (this->grafite == nullptr) {
            std::cout << "fail: nao existe grafite no bico\n";
            return;
        } else if (grafite->getTamanho() <= 10) {
            std::cout << "fail: tamanho insuficiente\n";
            return;
        } else if (grafite->getTamanho() < grafite->desgastePorFolha()) {
            std::cout << "fail: folha incompleta\n";
            grafite->setTamanho(0);
            return;
        } else if ((grafite->getTamanho() - grafite->desgastePorFolha()) < 10) {
            std::cout << "fail: folha incompleta\n";
            grafite->setTamanho(10);
            return;
        } else {
            grafite->setTamanho(grafite->getTamanho() - grafite->desgastePorFolha());
        }
    }

    void puxar() {
        if (this->grafite != nullptr) {
            std::cout << "fail: ja existe grafite no bico\n";
            return;
        }
        if (tambor.empty()) {
            std::cout << "fail: nao ha grafites no tambor\n";
            return;
        }
        this->grafite = this->tambor.front();
        this->tambor.pop_front();
    }

    std::string str() const {
        std::ostringstream os;
        os << "calibre: " << calibre 
           << ", bico: [" << (grafite ? grafite->str() : "") << "]"
           << ", tambor: <";
        
        for (auto it = tambor.begin(); it != tambor.end(); ++it) {
            if (it != tambor.begin()) os << "";
            os << "[" << (*it)->str() << "]";
        }
        os << ">";
        return os.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Lapiseira& l) {
    return os << l.str();
}

int main() {
    Lapiseira lapiseira;
    std::string line;
    while (true) {
        //std::cout << "$";
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::vector<std::string> args((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

        if (args.empty()) continue;

        std::cout << "$" << line << "\n";

        if (args[0] == "end") {
            break;
        } else if (args[0] == "show") {
            std::cout << lapiseira.str() << "\n";
        } else if (args[0] == "init") {
            lapiseira = Lapiseira(std::stof(args[1]));
        } else if (args[0] == "insert") {
            lapiseira.inserir(std::make_shared<Grafite>(std::stof(args[1]), args[2], std::stoi(args[3])));
        } else if (args[0] == "remove") {
            lapiseira.remover();
        } else if (args[0] == "pull") {
            lapiseira.puxar();
        } else if (args[0] == "write") {
            lapiseira.write();
        } else {
            std::cout << "fail: comando invalido\n";
        }
    }
}
