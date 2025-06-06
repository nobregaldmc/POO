#define __LIST
#define __MEMORY
#include "fn.hpp"
#include "student.hpp"

int main() {
    Budega bank(0);

    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);

        if      (args[0] == "end"   ) { break;                                          }
        else if (args[0] == "init"  ) { bank = Budega(+args[1]);                             }
        else if (args[0] == "call"  ) { bank.chamarNoCaixa(+args[1]);                             }
        else if (args[0] == "finish") { bank.finalizar(+args[1]);                           }
        else if (args[0] == "arrive") { bank.chegar(std::make_shared<Pessoa>(args[1]));                            }
        else if (args[0] == "show"  ) { fn::write(bank);                          }
        else                          { fn::write("fail: comando invalido");            }
    }
}

