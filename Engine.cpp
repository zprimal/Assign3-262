#include "Engine.h"

Engine(){

}

~Engine(){
   // Deconstructor
}

void push_event(Event newEvent){
   this->gEvents.insert(newEvent.Name, newEvent);
}

void push_stat(Stat newStat){
   this->gStats.insert(newStat.Name, newStat);
}

void startEngine(int Day){

}

void genInstances(){

}

void clearInstances(){

}

void clearEvents(){
   this->gEvents.clear();
}

void clearStats(){
   this->gStats.clear();
}
