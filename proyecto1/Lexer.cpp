#include "Lexer.h"
#include <iostream>
#include <fstream>

using namespace std;

Lexer::Lexer(){
    buildAutomaton();
}

/*
Cree un clasificador para omitir el montón de casos, afortunadamente
C++ interpreta los caracteres en operadores lógicos como ascii :).
En la parte de transiciones evitamos meter manualmente todas las transiciones
entre posibles letras y números
*/

string Lexer::classifyChar(char c){
    if(c >= 'a' && c <= 'z') return "letter";
    if(c>= '0'&& c <= '9') return "digit";
    if (c =='.') return "dot";
    if (c =='=') return "equal";
    if (c =='+') return "plus";
    if (c== '-') return "minus";
    if (c=='*') return "star";
    if (c == '/') return "slash";
    if (c =='(') return "lparen";
    if (c== ')') return "rparen";
    if (c==' ' || c == '\t' || c == '\n' || c == '\r') return "space";
    return "other";
}

void Lexer::buildAutomaton(){
    State* inicial = new State("Inicial", false);
    State* variable = new State("Variable", true, "variable");
    State* entero = new State( "Entero", true,"integer");
    State* puntoDecimal = new State("Punto Decimal", false);
    State* flotante = new State("Flotante",true,"float");
    State* asignacion = new State("Asignacion", true,"assignment");
    State* suma = new State("Suma",true,"sum");
    State* resta = new State("Resta", true, "subtract");
    State* producto = new State("Producto", true, "product");
    State* division = new State("Division", true, "division");
    State* parentesisIzq = new State("Parentesis Izquierdo", true, "left parenthesis");
    State* parentesisDer = new State("Parentesis Derecho", true, "right parenthesis");
    State* error = new State("Error", false);

    //Pendiente METER TODAS LAS TRANCISIONES DE LA TABLAAAA (de todos los estados :c)
    inicial->addTransition("letter", variable);
    inicial->addTransition("digit", entero);
    //van a ser un vergal de líneas, no hay de otra más que hacerlo manual

    //Al último declaro el estado inicial
    initialState = inicial;
}

//Parte lógica pendiente

bool Lexer::analyze(string filepath){
    ifstream file(filepath);

    if(!file.is_open()){
        cerr<<"ERROR, NO SE PUDO ABRIR EL ARCHIVO"<<filepath<<endl;
        return false;
    }

    //Pendiente, alch ya me voy a mimir. A ver qué nos dice el profe uwu

}
