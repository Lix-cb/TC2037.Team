#ifndef STATE_H
#define STATE_H

//.h para definir la estructura básoca de cada estado.

#include <string>
#include <unordered_map>
using namespace std;

class State {
public:
    string name;
    bool isFinal;
    string tokenType;
    unordered_map<string, State*> transitions;

    State(string name, bool isFinal, string tokenType = "");
    
    void addTransition(string symbol, State* state);
    
    State* getNextState(string symbol);
};

#endif