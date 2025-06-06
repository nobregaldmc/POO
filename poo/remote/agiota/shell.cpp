#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

template <typename CONTAINER, typename FN>
string map_join(const CONTAINER& container, FN fn, string sep = ", ") {
    stringstream ss;
    for (auto it = container.begin(); it != container.end(); ++it) {
        ss << (it != container.begin() ? sep : "") << fn(*it);
    }
    return ss.str();
}

enum Label {
    GIVE, TAKE, PLUS 
    };

std::ostream &operator <<(std::ostream &os, Label label){
    switch(label){
        case GIVE:
            os << "give";
            break;
        case TAKE:
            os << "take";
            break;
        case PLUS:
            os << "plus";
            break;
    }
    return os;
}

class Operation{
    private:
        int id;
        std::string name;
        Label label;
        int value;
    public:
        Operation(int id, std::string name, Label label, int value) : id(id), name(name), label(label), value(value){
            
        }

        std::string getName(){
                return name;
            }

        Label getLabel(){
            return label;
        }

        int getValue(){
            return value;
        }

        std::string str(){
            stringstream ss;
            ss << "id:" << id << " " << label << ":" << name << " " << value;
            return ss.str();
        }
};

std::ostream &operator <<(std::ostream &os, Operation &tr){
    return os << tr.str();
}

class Client{
private:
    std::string name;
    int limite;
    std::vector<Operation*> operations;
public:
    Client(std::string name = "", int limite = 0) : name(name), limite(limite){

    }

    std::string getName()const{
        return name;
        }

    int getLimite()const{
        return limite;
        }

    int getBalance() const {
        int balance = 0;
        for (auto op : operations) {
            if (op->getLabel() == GIVE || op->getLabel() == PLUS)
                balance += op->getValue();
            else if (op->getLabel() == TAKE)
                balance -= op->getValue();
        }
        return balance;
    }

    void addOperation(Operation* tr){
        operations.push_back(tr); 
        }
    std::vector<Operation*>& getOperations(){
        return operations; 
        }

    std::string str() const {
        return name + " " + to_string(getBalance()) + "/" + to_string(limite);
    }
};

std::ostream &operator<<(std::ostream &os, Client &cliente){
    return os << cliente.str();
}

class Agiota{
    private:
        std::vector<Client> alive_list;
        std::vector<Client> death_list;
        std::vector<Operation*> alive_oper;
        std::vector<Operation*> death_oper;
        int nextOpId = 0;

        int searchClient(std::string name){
            for (size_t i = 0; i < alive_list.size(); i++) {
                if (alive_list[i].getName() == name)
                    return i;
            }
            return -1;
        }

        void pushOperation(Client &cli, Label label, int value){
            auto op = new Operation(nextOpId++, cli.getName(), label, value);
            alive_oper.push_back(op);
            cli.addOperation(op);
        }
    
    public:
        Agiota(){
            for (auto op : alive_oper)
                delete op;
            for (auto op : death_oper)
                delete op;
        }

        Client *getClient(std::string name){
            int pos = searchClient(name);
            return (pos != -1) ? &alive_list[pos] : nullptr;
        }

        void addClient(std::string name, int limite){
        if (searchClient(name) != -1){
            cout << "fail: cliente ja existe" << endl;
        }else{
            alive_list.push_back(Client(name, limite));
            }
        }

        void showCli(std::string name) {
    Client *cli = getClient(name);
    if (cli) {
        cout << *cli << endl;

        for (auto op : cli->getOperations()) {
            cout << *op << endl;
        }
    } else {
        cout << "fail: cliente nao existe" << endl;
    }
}


        void give(std::string name, int value) {
            Client *cli = getClient(name);
            if (cli) {
                if (cli->getBalance() + value <= cli->getLimite()){
                    pushOperation(*cli, GIVE, value);
                }else{
                    cout << "fail: limite excedido" << endl;
                }
            }else{
                cout << "fail: cliente nao existe" << endl;
            }
        }

        void take(std::string name, int value){
            Client *cli = getClient(name);
            if(cli){
                pushOperation(*cli, TAKE, value);
            }else{
                cout << "fail: cliente nao existe" << endl;
            }
        }

        void plus() {
            std::sort(alive_list.begin(), alive_list.end(), 
                    [](const Client &a, const Client &b) { return a.getName() < b.getName(); });

            for (size_t i = 0; i < alive_list.size(); i++){
                int balance = alive_list[i].getBalance();
                pushOperation(alive_list[i], PLUS, ceil(0.1 * balance));

                if (alive_list[i].getBalance() > alive_list[i].getLimite()){
                    kill(alive_list[i].getName());
                    i--; 
                }
            }
        }


        void kill(std::string name){
    int pos = searchClient(name);
    if (pos != -1){
        Client &cli = alive_list[pos];
        death_list.push_back(cli);
        alive_list.erase(alive_list.begin() + pos);

        for (auto it = alive_oper.begin(); it != alive_oper.end();){
            if ((*it)->getName() == name){
                death_oper.push_back(*it);
                it = alive_oper.erase(it);
            } else {
                ++it;
            }
        }
    } else {
        cout << "fail: cliente nao existe" << endl;
    }
}

std::string str() {
    std::vector<Client> sorted_alive_list = alive_list; 
    std::stable_sort(sorted_alive_list.begin(), sorted_alive_list.end(), 
              [](const Client &a, const Client &b) { return a.getName() < b.getName(); });

    std::vector<std::string> parts;

    if (!sorted_alive_list.empty()) {
        parts.push_back(map_join(sorted_alive_list, 
            [](const Client &cli) { return ":) " + cli.str(); }, "\n"));
    }

    if (!alive_oper.empty()) {
        parts.push_back(map_join(alive_oper, 
            [](Operation *op) { return "+ " + op->str(); }, "\n"));
    }

    if (!death_list.empty()) {
        parts.push_back(map_join(death_list, 
            [](const Client &cli) { return ":( " + cli.str(); }, "\n"));
    }

    if (!death_oper.empty()) {
        parts.push_back(map_join(death_oper, 
            [](Operation *op) { return "- " + op->str(); }, "\n"));
    }

    std::ostringstream oss;
    for (size_t i = 0; i < parts.size(); i++) {
        if (i > 0) oss << "\n";
        oss << parts[i];
    }
    return oss.str() + "\n";
}


};

std::ostream &operator<<(std::ostream &os, Agiota &agiota) {
    return os << agiota.str();

};

int main() {
    Agiota agiota;
    while(true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if(cmd == "end") {
            break;
        }
        else if(cmd == "addCli") {
            string name;
            int limite {};
            ss >> name >> limite;
            agiota.addClient(name, limite);
        }
        else if(cmd == "show") {
            cout << agiota;
        }
        else if(cmd == "showCli") {
            string name;
            ss >> name;
            agiota.showCli(name);
        }
        else if(cmd == "kill") {
            string name;
            ss >> name;
            agiota.kill(name);
        }
        else if(cmd == "give") {
            string name;
            int value;
            ss >> name >> value;
            agiota.give(name, value);
        }
        else if(cmd == "take") {
            string name;
            int value;
            ss >> name >> value;
            agiota.take(name, value);
        }
        else if(cmd == "plus") {
            agiota.plus();
        }
        else {
            cout << "fail: comando invalido\n";
        }
    }
}
