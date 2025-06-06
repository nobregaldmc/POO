#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class Jogador{
    private:
        int label;
        int pos;
        bool free;

    public:
        Jogador(int label) : label(label), pos(0), free(true){

        }

        int getLabel()const{
            return label;
        }

        int getPos()const{
            return pos;
        }

        bool isFree()const{
            return free;
        }

        void setPos(int newPos){
            pos = newPos;
        }

        void setFree(bool status){
            free = status;
        }

        string toString()const{
            stringstream ss;
            ss << "Player " << label << " at " << pos << "is" << (free? "free" : "not free");
            return ss.str();
        }
};

class Tabuleiro{
    private:
        vector<int> trapList;
        int size;
        bool running;
        vector<Jogador> jogadores;
    public:
        Tabuleiro(int nJogadores = 0, int size = 0) : size(size + 1), running(true){
            for(int i = 0; i < nJogadores; i++){
                jogadores.emplace_back(i + 1);
            }
        }

        void addTrap(int pos){
            trapList.push_back(pos);
        }

        void rollDice(int value){
            if(!running){
                cout << "game is over" << endl;
                return;
            }

            Jogador &current = jogadores.front();
            int nome = current.getLabel();
            int newPos = current.getPos() + value;

            if(!current.isFree()){
                if(value % 2 == 0){
                    current.setFree(true);
                    cout << "player" << nome << " se libertou" << endl;
                }else{
                    cout << "player" << nome <<" continua preso" << endl;
                }
            }else{
                if(newPos >= size){
                    cout << "player" << nome <<" ganhou" << endl;
                    current.setPos(size - 1);
                    running = false;
                }else{
                    cout << "player" << nome << " andou para " << newPos << endl;
                    for(int trap : trapList){
                        if(newPos == trap){
                            cout << "player" << nome << " caiu em uma armadilha" << endl;
                            current.setPos(newPos);
                            current.setFree(false);
                            rotate(jogadores.begin(), jogadores.begin() + 1, jogadores.end());
                            return;
                    }
                }
                current.setPos(newPos);
            }
        }
        rotate(jogadores.begin(), jogadores.begin() + 1, jogadores.end());
    }

    string toString()const{
        stringstream ss;
        for(const auto &p : jogadores){
            string line(size, '.');
            line[p.getPos()] = p.getLabel() + '0';
            ss << "player" << p.getLabel() << ": " << line << endl;
        }
        string traps(size, '.');
        for(int t : trapList)
            traps[t] = 'x';
        ss << "traps__: " << traps;
        return ss.str();
    }
        
};

int main() {
    Tabuleiro tabuleiro;

    while(true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "init") {
            int nJogadores, size;
            ss >> nJogadores >> size;
            tabuleiro = Tabuleiro(nJogadores, size);
        } else if (cmd == "addTrap") {
            int pos;
            ss >> pos;
            tabuleiro.addTrap(pos);
        } else if (cmd == "roll") {
            int value;
            ss >> value;
            tabuleiro.rollDice(value);
        } else if (cmd == "show") {
            cout << tabuleiro.toString() << endl;
        } else {
            cout << "fail: command not found" << endl;
        }

    }
}
