#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

enum class Label{
    Deposit, Fee, Opening, Reverse, Withdraw
};

string label_str(Label label){
    switch(label){
        case Label::Deposit: return "deposit";
        case Label::Opening: return "opening";
        case Label::Withdraw: return "withdraw";
        case Label::Fee: return "fee";
        case Label::Reverse: return "reverse";
        default: return "";
    }
}

class Operation{
    private:
        int index, value, balance;
        Label label;
    public:
        Operation(int index = 0, Label label = Label::Opening, int value = 0, int balance = 0): index(index), value(value), balance(balance), label(label) {

        }

        string toStr()const{
            stringstream ss;
            ss << setw(2) << index << ": " << setw(8) << label_str(label) << ": " << setw(4) << value << ": " << setw(4) << balance;
            return ss.str();
        }

        int getBalance()const{
            return balance;
        }
        int getIndex()const{
            return index;
        }
        Label getLabel()const{
            return label;
        }
        int getValue()const{
            return value;
        }
};

class BalanceManager{
    private:
        int balance = 0;
        vector<Operation> extract;
        int nextId= 0;
    public:
        void addOperation(Label label, int value){
            balance += value;
        extract.emplace_back(nextId++, label, value, balance);
        }

        int getBalance() const {
            return balance;
        }

        vector<Operation> getExtract(int qtdOp) const {
        return qtdOp == 0 ? extract : vector<Operation>(extract.end() - min(qtdOp, (int)extract.size()), extract.end());
        }

        const Operation& getOperation(int index) const { return extract.at(index); }
};

class Acount{
    private:
        BalanceManager balanceManager;
        int id;
    public:
        Acount(int id = 0) : id(id){
            balanceManager.addOperation(Label::Opening, 0);
        }
        void deposit(int value){
            if(value < 0){
                cout << "fail: invalid value" << endl;
            }else{
                balanceManager.addOperation(Label::Deposit, value);
            }
        }
        void fee(int value){
            balanceManager.addOperation(Label::Fee, -value); 
        }
        void reverse(int index){
        if (index < 0 || index >= (int)balanceManager.getExtract(0).size()){
            cout << "fail: index " << index << " invalid" << endl;
        }else if (balanceManager.getOperation(index).getLabel() != Label::Fee){
            cout << "fail: index " << index << " is not a fee" << endl;
        }else{
            balanceManager.addOperation(Label::Reverse, -balanceManager.getOperation(index).getValue());
            } 
        }

        void withdraw(int value) {
        if (value > balanceManager.getBalance()) cout << "fail: insufficient balance" << endl;
        else balanceManager.addOperation(Label::Withdraw, -value);
        }

    string toString() const { return "account:" + to_string(id) + " balance:" + to_string(balanceManager.getBalance()); }
    const BalanceManager& getBalanceManager() const { return balanceManager; }
};


int main() {
    Acount acount;
    while(true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        
        if (cmd == "end") {
            break;
        }
        else if (cmd == "init") {
            int id;
            ss >> id;
            acount = Acount(id);
        }
        else if (cmd == "show") {
            cout << acount.toString() << endl;
        }
        else if (cmd == "deposit") {
            int value;
            ss >> value;
            acount.deposit(value);
        }
        else if (cmd == "withdraw") {
            int value;
            ss >> value;
            acount.withdraw(value);
        }
        else if (cmd == "fee") {
            int value;
            ss >> value;
            acount.fee(value);
        }
        else if (cmd == "extract") {
            int qtd;
            ss >> qtd;
            for(const auto& op : acount.getBalanceManager().getExtract(qtd)) 
                cout << op.toStr() << endl;
        }
        else if (cmd == "reverse") {
            int index;
            while(ss >> index)
            acount.reverse(index);
            
        }
        else {
            cout << "fail: invalid command\n";
        }
    }
    return 0;
}
