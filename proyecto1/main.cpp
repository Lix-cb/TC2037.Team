#include <iostream>
#include "Lexer.h"

using namespace std;

void lexer(string filepath){
    Lexer lex;
    lex.analyze(filepath);
}

//mainsito
int main(int argc, char* argv[]){
    string filepath = "expressions.txt";

    if (argc > 1){
        filepath = argv[1];
    }

    lexer(filepath);

    return 0;
}