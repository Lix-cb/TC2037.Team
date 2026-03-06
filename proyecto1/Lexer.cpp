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
    inicial->addTransition("dot",error);
    inicial->addTransition("equal",asignacion);
    inicial->addTransition("plus",suma);
    inicial->addTransition("minus",resta);
    inicial->addTransition("star",producto);
    inicial->addTransition("splash", division);
    inicial->addTransition("lparen", parentesisIzq);
    inicial->addTransition("rparen", parentesisDer);
    inicial->addTransition("space", inicial);
    inicial->addTransition("other", error);

    variable->addTransition("letter",variable);
    variable->addTransition("digit",error);
    variable->addTransition("dot",error);
    variable->addTransition("equal",asignacion);
    variable->addTransition("plus",suma);
    variable->addTransition("minus",resta);
    variable->addTransition("star",producto);
    variable->addTransition("splash",division);
    variable->addTransition("lparen",parentesisIzq);
    variable->addTransition("rparen",parentesisDer);
    variable->addTransition("space",inicial);
    variable->addTransition("other",error);

    entero->addTransition("letter",);
    entero->addTransition("digit",);
    entero->addTransition("dot",);
    entero->addTransition("equal",);
    entero->addTransition("plus",);
    entero->addTransition("minus",);
    entero->addTransition("star",);
    entero->addTransition("splash",);
    entero->addTransition("lparen",);
    entero->addTransition("rparen",);
    entero->addTransition("space",);
    entero->addTransition("other",error);

    puntoDecimal->addTransition("letter",);
    puntoDecimal->addTransition("digit",);
    puntoDecimal->addTransition("dot",);
    puntoDecimal->addTransition("equal",);
    puntoDecimal->addTransition("plus",);
    puntoDecimal->addTransition("minus",);
    puntoDecimal->addTransition("star",);
    puntoDecimal->addTransition("splash",);
    puntoDecimal->addTransition("lparen",);
    puntoDecimal->addTransition("rparen",);
    puntoDecimal->addTransition("space",);
    puntoDecimal->addTransition("other",error);


    flotante->addTransition("letter",);
    flotante->addTransition("digit",);
    flotante->addTransition("dot",);
    flotante->addTransition("equal",);
    flotante->addTransition("plus",);
    flotante->addTransition("minus",);
    flotante->addTransition("star",);
    flotante->addTransition("splash",);
    flotante->addTransition("lparen",);
    flotante->addTransition("rparen",);
    flotante->addTransition("space",);
    flotante->addTransition("other",error);

    asignacion->addTransition("letter",);
    asignacion->addTransition("digit",);
    asignacion->addTransition("dot",);
    asignacion->addTransition("equal",);
    asignacion->addTransition("plus",);
    asignacion->addTransition("minus",);
    asignacion->addTransition("star",);
    asignacion->addTransition("splash",);
    asignacion->addTransition("lparen",);
    asignacion->addTransition("rparen",);
    asignacion->addTransition("space",);
    asignacion->addTransition("other",error);

    suma->addTransition("letter",);
    suma->addTransition("digit",);
    suma->addTransition("dot",);
    suma->addTransition("equal",);
    suma->addTransition("plus",);
    suma->addTransition("minus",);
    suma->addTransition("star",);
    suma->addTransition("splash",);
    suma->addTransition("lparen",);
    suma->addTransition("rparen",);
    suma->addTransition("space",);
    suma->addTransition("other",error);

    resta->addTransition("letter",);
    resta->addTransition("digit",);
    resta->addTransition("dot",);
    resta->addTransition("equal",);
    resta->addTransition("plus",);
    resta->addTransition("minus",);
    resta->addTransition("star",);
    resta->addTransition("splash",);
    resta->addTransition("lparen",);
    resta->addTransition("rparen",);
    resta->addTransition("space",);
    resta->addTransition("other",error);

    producto->addTransition("letter",);
    producto->addTransition("digit",);
    producto->addTransition("dot",);
    producto->addTransition("equal",);
    producto->addTransition("plus",);
    producto->addTransition("minus",);
    producto->addTransition("star",);
    producto->addTransition("splash",);
    producto->addTransition("lparen",);
    producto->addTransition("rparen",);
    producto->addTransition("space",);
    producto->addTransition("other",error);
    
    division->addTransition("letter",);
    division->addTransition("digit",);
    division->addTransition("dot",);
    division->addTransition("equal",);
    division->addTransition("plus",);
    division->addTransition("minus",);
    division->addTransition("star",);
    division->addTransition("splash",);
    division->addTransition("lparen",);
    division->addTransition("rparen",);
    division->addTransition("space",);
    division->addTransition("other",error);

    parentesisIzq->addTransition("letter",);
    parentesisIzq->addTransition("digit",);
    parentesisIzq->addTransition("dot",);
    parentesisIzq->addTransition("equal",);
    parentesisIzq->addTransition("plus",);
    parentesisIzq->addTransition("minus",);
    parentesisIzq->addTransition("star",);
    parentesisIzq->addTransition("splash",);
    parentesisIzq->addTransition("lparen",);
    parentesisIzq->addTransition("rparen",);
    parentesisIzq->addTransition("space",);
    parentesisIzq->addTransition("other",error);

    parentesisDer->addTransition("letter",);
    parentesisDer->addTransition("digit",);
    parentesisDer->addTransition("dot",);
    parentesisDer->addTransition("equal",);
    parentesisDer->addTransition("plus",);
    parentesisDer->addTransition("minus",);
    parentesisDer->addTransition("star",);
    parentesisDer->addTransition("splash",);
    parentesisDer->addTransition("lparen",);
    parentesisDer->addTransition("rparen",);
    parentesisDer->addTransition("space",);
    parentesisDer->addTransition("other",error);

    error->addTransition("letter",);
    error->addTransition("digit",);
    error->addTransition("dot",);
    error->addTransition("equal",);
    error->addTransition("plus",);
    error->addTransition("minus",);
    error->addTransition("star",);
    error->addTransition("splash",);
    error->addTransition("lparen",);
    error->addTransition("rparen",);
    error->addTransition("space",);
    error->addTransition("other",error);

    

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
