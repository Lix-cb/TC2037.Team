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
    if(c >= '0' && c <= '9') return "digit";
    if (c == '.') return "dot";
    if (c == '=') return "equal";
    if (c == '+') return "plus";
    if (c == '-') return "minus";
    if (c == '*') return "star";
    if (c == '/') return "slash";
    if (c == '(') return "lparen";
    if (c == ')') return "rparen";
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r') return "space";
    return "other";
}

void Lexer::buildAutomaton(){
    // Crear todos los estados del automata
    State* inicial = new State("Inicial", false);
    State* variable = new State("Variable", true, "variable");
    State* entero = new State("Entero", true, "integer");
    State* puntoDecimal = new State("Punto Decimal", false);
    State* flotante = new State("Flotante", true, "float");
    State* asignacion = new State("Asignacion", true, "assignment");
    State* suma = new State("Suma", true, "sum");
    State* resta = new State("Resta", true, "subtract");
    State* producto = new State("Producto", true, "product");
    State* division = new State("Division", true, "division");
    State* parentesisIzq = new State("Parentesis Izquierdo", true, "left parenthesis");
    State* parentesisDer = new State("Parentesis Derecho", true, "right parenthesis");
    State* error = new State("Error", false);

    // Aqui van todas las transiciones de la tabla
    // Si, son un monton pero no hay de otra mas que hacerlo manual
    
    // Transiciones para estado inicial
    inicial->addTransition("letter", variable);
    inicial->addTransition("digit", entero);
    inicial->addTransition("dot", error);
    inicial->addTransition("equal", asignacion);
    inicial->addTransition("plus", suma);
    inicial->addTransition("minus", resta);
    inicial->addTransition("star", producto);
    inicial->addTransition("slash", division);
    inicial->addTransition("lparen", parentesisIzq);
    inicial->addTransition("rparen", parentesisDer);
    inicial->addTransition("space", inicial);
    inicial->addTransition("other", error);

    // trancisiones variable
    variable->addTransition("letter", variable);
    variable->addTransition("digit", entero);
    variable->addTransition("dot", error);
    variable->addTransition("equal", asignacion);
    variable->addTransition("plus", suma);
    variable->addTransition("minus", resta);
    variable->addTransition("star", producto);
    variable->addTransition("slash", division);
    variable->addTransition("lparen", parentesisIzq);
    variable->addTransition("rparen", parentesisDer);
    variable->addTransition("space", inicial);
    variable->addTransition("other", error);

    // Transiciones entero
    entero->addTransition("letter", variable);
    entero->addTransition("digit", entero);
    entero->addTransition("dot", puntoDecimal);
    entero->addTransition("equal", asignacion);
    entero->addTransition("plus", suma);
    entero->addTransition("minus", resta);
    entero->addTransition("star", producto);
    entero->addTransition("slash", division);
    entero->addTransition("lparen", parentesisIzq);
    entero->addTransition("rparen", parentesisDer);
    entero->addTransition("space", inicial);
    entero->addTransition("other", error);

    //Trans punto decimal, solo acepta dígitos sin mandar error, por el tema de manejo de tokens inválidos
    puntoDecimal->addTransition("digit", flotante);
    puntoDecimal->addTransition("letter", error);
    puntoDecimal->addTransition("dot", error);
    puntoDecimal->addTransition("equal", error);
    puntoDecimal->addTransition("plus", error);
    puntoDecimal->addTransition("minus", error);
    puntoDecimal->addTransition("star", error);
    puntoDecimal->addTransition("slash", error);
    puntoDecimal->addTransition("lparen", error);
    puntoDecimal->addTransition("rparen", error);
    puntoDecimal->addTransition("space", error);
    puntoDecimal->addTransition("other", error);

    //float transitions
    flotante->addTransition("digit", flotante);
    flotante->addTransition("letter", error);
    flotante->addTransition("dot", error);
    flotante->addTransition("equal", asignacion);
    flotante->addTransition("plus", suma);
    flotante->addTransition("minus", resta);
    flotante->addTransition("star", producto);
    flotante->addTransition("slash", division);
    flotante->addTransition("lparen", parentesisIzq);
    flotante->addTransition("rparen", parentesisDer);
    flotante->addTransition("space", inicial);
    flotante->addTransition("other", error);

    // equal transiciones
    asignacion->addTransition("letter", variable);
    asignacion->addTransition("digit", entero);
    asignacion->addTransition("equal", asignacion);
    asignacion->addTransition("plus", suma);
    asignacion->addTransition("minus", resta);
    asignacion->addTransition("star", producto);
    asignacion->addTransition("slash", division);
    asignacion->addTransition("lparen", parentesisIzq);
    asignacion->addTransition("rparen", parentesisDer);
    asignacion->addTransition("space", inicial);
    asignacion->addTransition("dot", error);
    asignacion->addTransition("other", error);

    // sum trans
    suma->addTransition("letter", variable);
    suma->addTransition("digit", entero);
    suma->addTransition("equal", asignacion);
    suma->addTransition("plus", suma);
    suma->addTransition("minus", resta);
    suma->addTransition("star", producto);
    suma->addTransition("slash", division);
    suma->addTransition("lparen", parentesisIzq);
    suma->addTransition("rparen", parentesisDer);
    suma->addTransition("space", inicial);
    suma->addTransition("dot", error);
    suma->addTransition("other", error);

    // rt resta
    resta->addTransition("letter", variable);
    resta->addTransition("digit", entero);
    resta->addTransition("equal", asignacion);
    resta->addTransition("plus", suma);
    resta->addTransition("minus", resta);
    resta->addTransition("star", producto);
    resta->addTransition("slash", division);
    resta->addTransition("lparen", parentesisIzq);
    resta->addTransition("rparen", parentesisDer);
    resta->addTransition("space", inicial);
    resta->addTransition("dot", error);
    resta->addTransition("other", error);

    // rt
    producto->addTransition("letter", variable);
    producto->addTransition("digit", entero);
    producto->addTransition("equal", asignacion);
    producto->addTransition("plus", suma);
    producto->addTransition("minus", resta);
    producto->addTransition("star", producto);
    producto->addTransition("slash", division);
    producto->addTransition("lparen", parentesisIzq);
    producto->addTransition("rparen", parentesisDer);
    producto->addTransition("space", inicial);
    producto->addTransition("dot", error);
    producto->addTransition("other", error);

    // rt
    division->addTransition("letter", variable);
    division->addTransition("digit", entero);
    division->addTransition("equal", asignacion);
    division->addTransition("plus", suma);
    division->addTransition("minus", resta);
    division->addTransition("star", producto);
    division->addTransition("slash", division);
    division->addTransition("lparen", parentesisIzq);
    division->addTransition("rparen", parentesisDer);
    division->addTransition("space", inicial);
    division->addTransition("dot", error);
    division->addTransition("other", error);

    // rt
    parentesisIzq->addTransition("letter", variable);
    parentesisIzq->addTransition("digit", entero);
    parentesisIzq->addTransition("equal", asignacion);
    parentesisIzq->addTransition("plus", suma);
    parentesisIzq->addTransition("minus", resta);
    parentesisIzq->addTransition("star", producto);
    parentesisIzq->addTransition("slash", division);
    parentesisIzq->addTransition("lparen", parentesisIzq);
    parentesisIzq->addTransition("rparen", parentesisDer);
    parentesisIzq->addTransition("space", inicial);
    parentesisIzq->addTransition("dot", error);
    parentesisIzq->addTransition("other", error);

    //rt
    parentesisDer->addTransition("letter", variable);
    parentesisDer->addTransition("digit", entero);
    parentesisDer->addTransition("equal", asignacion);
    parentesisDer->addTransition("plus", suma);
    parentesisDer->addTransition("minus", resta);
    parentesisDer->addTransition("star", producto);
    parentesisDer->addTransition("slash", division);
    parentesisDer->addTransition("lparen", parentesisIzq);
    parentesisDer->addTransition("rparen", parentesisDer);
    parentesisDer->addTransition("space", inicial);
    parentesisDer->addTransition("dot", error);
    parentesisDer->addTransition("other", error);

    //Error, todas llevan a él mismo, para mantener consistencia no tienen sentido salir del estado de error
    error->addTransition("letter", error);
    error->addTransition("digit", error);
    error->addTransition("dot", error);
    error->addTransition("equal", error);
    error->addTransition("plus", error);
    error->addTransition("minus", error);
    error->addTransition("star", error);
    error->addTransition("slash", error);
    error->addTransition("lparen", error);
    error->addTransition("rparen", error);
    error->addTransition("space", error);
    error->addTransition("other", error);

    //Declarar estado inicial
    initialState = inicial;
}

//Lógica principal terminada (creo, falta revisar diversos casos)
bool Lexer::analyze(string filepath){
    ifstream file(filepath);

    if(!file.is_open()){
        cerr << "ERROR: No se pudo abrir el archivo " << filepath << endl;
        return false;
    }

    //Abrir contenido del archivo
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    
    // Variables para el analisis
    State* currentState = initialState;
    string buffer = "";
    int position = 0;
    
    //For caracter a caracter
    for (int i = 0; i < content.length(); i++) {
        char c = content[i];
        string charType = classifyChar(c);
        
        //obtener nexstate
        State* nextState = currentState->getNextState(charType);
        
        //Innecesario, pero para debugs se verifica que la transición exista
        if (nextState == nullptr) {
            cout << "ERROR: Transicion no definida desde " << currentState->name 
                 << " con '" << c << "' en posicion " << position << endl;
            return false;
        }
        
        //Caso en el que tenemos un estado de error.
        if (nextState->name == "Error") {
            printTokens();
            cout << "\nERROR: Caracter invalido '" << c << "' en posicion " << position << endl;
            return false;
        }
        
        // Verificar si tenemos que imprimir un token antes de avanzar al próximo estado.
        bool shouldEmit = false;
        
        // Caso 1: Estado final si tenermos símbolo o paréntesism quiere decir que dicho token ya terminó
        if (currentState->isFinal && 
            (nextState->name == "Asignacion" || nextState->name == "Suma" || 
             nextState->name == "Resta" || nextState->name == "Producto" || 
             nextState->name == "Division" || nextState->name == "Parentesis Izquierdo" || 
             nextState->name == "Parentesis Derecho")) {
            shouldEmit = true;
        }
        
        // Caso 2: Si estamos en un estado final y viene un espacio tambien significa que el token terminó
        if (currentState->isFinal && nextState->name == "Inicial" && charType == "space") {
            shouldEmit = true;
        }
        
        if (currentState->isFinal && nextState->isFinal && nextState != currentState) {
            shouldEmit = true;
        }

        //Imprimir el token si llega a ser necesario
        if (shouldEmit && !buffer.empty()) {
            tokens.push_back(Token(buffer, currentState->tokenType));
            buffer = "";
        }
        
        // Agregar el caracter al buffer, excepto espacios en estado inicial.
        if (!(nextState->name == "Inicial" && charType == "space")) {
            if (charType != "space" || currentState->name != "Inicial") {
                buffer += c;
            }
        }
        
        //Casos para emitir un token inmediatamente, pues son operadores (tokens de un sólo carácter)
        if (nextState->isFinal && 
            (nextState->name == "Asignacion" || nextState->name == "Suma" || 
             nextState->name == "Resta" || nextState->name == "Producto" || 
             nextState->name == "Division" || nextState->name == "Parentesis Izquierdo" || 
             nextState->name == "Parentesis Derecho")) {
            tokens.push_back(Token(buffer, nextState->tokenType));
            buffer = "";
            currentState = initialState;
            position++;
            continue;
        }
        
        ///Move to next state
        currentState = nextState;
        position++;
    }
    
    //Para casos de tokens incompletos (debugging), revisar que ya se haya terminado el escaneado.
    if (!buffer.empty()) {
        if (currentState->isFinal) {
            tokens.push_back(Token(buffer, currentState->tokenType));
        } else {
            printTokens();
            cout << "\nERROR: Token incompleto al final del archivo" << endl;
            return false;
        }
    }
    
    //imprimir Tokens
    printTokens();
    return true;
}

//Función que verdaderamente imprime la tabla de Tokens
void Lexer::printTokens() {
    cout << "Token\t\t\tType" << endl;
    cout << "----------------------------------------" << endl;
    for (const auto& token : tokens) {
        cout << token.value << "\t\t\t" << token.type << endl;
    }
}