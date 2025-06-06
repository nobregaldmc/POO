#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

template <class CONTAINER, class FUNC>
string map_join(const CONTAINER &cont, FUNC func, string sep = " ")
{
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++)
    {
        ss << (it == cont.begin() ? "" : sep) << func(*it);
    }
    return ss.str();
}

class Fone{
    private:
        string id;
        string number;

    public:
        Fone(string id = "", string number = "") : id(id), number(number){

        }

        string getId()const{
            return id;
        }

        string getNumber()const{
            return number;
        }

        bool isValid()const{
            const string validChars = "0123456789().";
            return all_of(number.begin(), number.end(), [&](char c){
                return validChars.find(c) != string::npos;
            });
        }

        string str() const {
            return id.empty() ? "" : id + ":" + number;
        }
};

class Contato{
    private:
        string name;
        bool favorited = false;
        vector<Fone> fones;

    public:
        Contato(string name = "") : name(name){

        }

        string getName()const{
            return name;
        }

        vector<Fone> getFones()const{
            return fones;
        }

        void addFone(const string& id, const string& number){
            Fone fone(id, number);
            if(fone.isValid()){
                fones.push_back(fone);
            }else{
                cout << "fail: invalid number" << endl;
            }
        }

        void rmFone(int index){
            if(index >= 0 && index < (int)fones.size()){
                fones.erase(fones.begin() + index);
            }
        }

        void toogleFavorited(){
            favorited = !favorited;
        }

        bool isFavorited()const{
            return favorited;
        }

        string str()const{
            return (favorited ? "@ " : "- ") + name + " [" + map_join(fones, [](const Fone &f){
                return f.str();}, ", ") + "]";
        }
};

ostream& operator << (ostream& out, const Contato& contato){
    return out << contato.str();
}

ostream& operator << (ostream& out, const Fone& fone){
    return out << fone.str();
}

int main(){
    Contato contato;

    while (true){

        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;
        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end")
        {
            break;
        }
        else if (cmd == "init")
        {
            string name;
            ss >> name;
            contato = Contato(name);
        }
        else if (cmd == "add")
        {
            string id, number;
            ss >> id >> number;
            contato.addFone(id, number);
        }
        else if (cmd == "rm")
        {
            int index{};
            ss >> index;
            contato.rmFone(index);
        }
        else if (cmd == "tfav")
        {
            contato.toogleFavorited();
        }
        else if (cmd == "show")
        {
            cout << contato << endl;
        }
        else
        {
            cout << "fail: comando invalido" << endl;
        }
    }
}
