#include "State.h"

//Constructor
State::State(string name, bool isFinal, string tokenType) {
    this->name = name;
    this->isFinal = isFinal;
    this->tokenType = tokenType;
}

//Añandir transiciones
void State::addTransition(string symbol, State* state) {
    transitions[symbol] = state;
}

//Transición del siguiente estado
State* State::getNextState(string symbol) {
    if (transitions.find(symbol) != transitions.end()) {
        return transitions[symbol];
    }
    return nullptr;
}