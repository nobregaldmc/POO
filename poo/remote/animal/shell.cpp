#include "fn.hpp"
#include "student.hpp"

int main () {
    Student stu("", "");    //COISA A SER MANIPULADA
    
    if (Debug::debug) {
        Debug::run();
        return 0;
    }

    while (true) {
        fn::write("$", "");     //MOSTRA '$' NA FRENTE
        auto line = fn::input();    //LÊ A LINHA
        auto args = fn::split(line, ' ');   //QUBRA EM ARRAY DE PALAVRAS

        fn::write(line); //test echo

        if      (args[0] == "end"  ) { break;                               }

        else if (args[0] == "init" ) { stu = Student(args[1], args[2]);     }       //AQUI VOCE REPASSA OS PARAMETROS PARA O OBJETO
        else if (args[0] == "grow" ) { stu.grow(+args[1]);                  }       //CONVERTENDO OS QUE PRECISAM SER NUMEROS OU INTEIROS
        else if (args[0] == "noise") { stu.noise();              }
        else if (args[0] == "show" ) { stu.show();               }

        else                         { fn::write("fail: comando invalido"); }
    }
}
