#ifndef LEXER_H
#define LEXER_H

//.h para el analizador léxico

#include <string>
#include <vector>
#include "Token.h"
#include "State.h"
using namespace std;

class Lexer {
private:
    State* initialState; //Apuntador delestaod inicial del autómata
    vector<Token> tokens; //Tokens reconocidos (vector los contendrá)
    
    string classifyChar(char c); //Clasificar entradas, explicado en Lexer.cpp
    void buildAutomaton();
    void printTokens(); //Para imprimir la tabla de los tokens
    
public:
    Lexer();
    bool analyze(string filepath); //Analizar archivo para reconocer tokens.
};

#endif