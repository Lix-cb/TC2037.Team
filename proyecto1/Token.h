#ifndef TOKEN_H
#define TOKEN_H

//Puse este .h para definir la estructura de cada token, primero lleva el valor y despúes el tipo.
//Esperando que por ejemplo el Token tx(valor: "45.7", tipo: "float");

#include <string>
using namespace std;
struct Token
{
    string value;
    string type;

    Token(string v, string t): value(v), type(t){}
};

#endif
