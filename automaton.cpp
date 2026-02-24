#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class State {
public:
    string name;
    bool isFinal;
    bool isDeathState;
    unordered_map<string, State*> transitions;

    State(string name, bool isFinal, bool isDeathState) {
        this->name = name;
        this->isFinal = isFinal;
        this->isDeathState = isDeathState;
    }

    void addTransition(string symbol, State* state) {
        transitions[symbol] = state;
    }

    State* getNextState(string symbol) {
        if (transitions.find(symbol) != transitions.end()) {
            return transitions[symbol];
        }
        return nullptr;
    }

    string toString(){
        return "name: " + this->name +
               " isFinal: " + (this->isFinal ? "true" : "false") +
               " isDeathState: " + (this->isDeathState ? "true" : "false");
    }
};

class automaton{
public:

    State* S;

    automaton(State* S){
        this->S = S;
    }

    bool accept(string word){
        bool result = false;
        
        if(word.length() == 0){
            if(S->isFinal){
                return true;
            }
            else{
                return false;
            }
        }

        State* currentState = S;

        for (int i=0; i<word.length(); i++){
            string symbol = word.substr(i, 1);
            State* nextState = currentState->getNextState(symbol);

            if (nextState == nullptr) return false;

            if (nextState->isDeathState){
                return false;
            }

            if(nextState->isFinal){
                result = true;
            }else{
                result = false;
            }

            currentState = nextState;
        }

        return result;
    }

};

int main(){
    State S("S",false,false);
    State b("b",false, false);
    State bb("bb",true,false);

    S.addTransition("a", &S);
    S.addTransition("b", &b);

    b.addTransition("a",&S);
    b.addTransition("b",&bb);
     
    bb.addTransition("a",&bb);
    bb.addTransition("b",&bb);

    automaton automaton(&S);

    string word ="bb";

    cout << automaton.accept(word) << endl;
}