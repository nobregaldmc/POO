#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
using namespace std;

template<class CONTAINER, class FUNC>
string map_join(const CONTAINER& c, FUNC f, string sep) {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); it++) {
        ss << (it == c.begin() ? "" : sep);
        ss << f(*it);
    }
    return ss.str();
}

class Client{

    private:

    std::string id;
    int phone;

    public:

    Client(std::string id="", int phone=0) : id(id), phone(phone){

    }

    std::string getId() const {
        return id;
    }

    int getPhone() const {
        return phone;
    }

    void setId( const std::string& newId){
        id = newId;
    }

    void setPhone( int newPhone){
        phone = newPhone;
    }

    std::string toString() const{
        return id.empty() ? "-" : id + ":" + to_string(phone);
    }

};

class Cinema {
    private:
        vector<Client> seats;
        bool search(const std::string& name) const {
            for(const auto& c : seats){
                if(c.getId() == name){
                    return true;
                }
            }
            return false;
        }

        bool verifyIndix(int index) const{
            return index >= 0 && index < static_cast<int>(seats.size());
        }


    public:
    Cinema(int qtd = 0) : seats(qtd){

        }

        void reserve(const std::string& id, int phone, int index){
            if(search(id)){
                std::cout << "fail: cliente ja esta no cinema" << std::endl;
            }else if(!verifyIndix(index)){
                std::cout << "fail: cadeira nao existe" << std::endl;
            }else if(!seats[index].getId().empty()){
                std::cout << "fail: cadeira ja esta ocupada" << std::endl;
            }else{
                seats[index] = Client(id, phone);
            }
        }

        void cancel(const std::string& id){
            for(auto& seat : seats){
                if(seat.getId() == id){
                    seat = Client();
                    return;
                }
            }
            std::cout << "fail: cliente nao esta no cinema" << std::endl;
        }

        //void getSeat(){
        //}

        std::string toString() const{
            vector<string> seatString;
            for(const auto& c : seats){
                seatString.push_back(c.toString());
            }
            return "[" + map_join(seatString, [](const std::string& s){
                return s;
            }, " ") + "]";
        }
};

int main() {
    Cinema cinema;
    std::string line;
    while (getline(cin, line)) {
        std::cout << "$" << line << std::endl;
        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "end") {
            break;    
        } else if (command == "show") {
            std::cout << cinema.toString() << std::endl;
        } else if (command == "init") {
             int qtd;
             iss >> qtd;
             cinema = Cinema(qtd);
        } else if (command == "reserve") {
             std::string id;
             int index, phone;
             iss >> id >> phone >> index;
             cinema.reserve(id, phone, index);
        } else if (command == "cancel") {
             std::string id;
             iss >> id;
             cinema.cancel(id);
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
