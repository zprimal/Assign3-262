#include "Engine.h"

Engine::Engine(){

}

Engine::~Engine(){
   // Deconstructor
}

void Engine::push_event(Event newEvent){
   this->gEvents.insert(std::make_pair<>(newEvent.Name, newEvent));
}

void Engine::push_stat(Stat newStat){
   this->gStats.insert(std::make_pair<>(newStat.Name, newStat));
}

void Engine::startEngine(int Day){

}

void Engine::genInstances(){

}

void Engine::clearInstances(){

}

void Engine::clearEvents(){
   this->gEvents.clear();
}

void Engine::clearStats(){
   this->gStats.clear();
}

int Engine::checkEventStats(){
   // Names different
   for (auto i = gEvents.begin(); i != gEvents.end(); i++) {
      for (auto j = gStats.begin(); j != gStats.end(); j++) {
         /* code */
      }
   }

   // Number of events must be the same


   // Mean exceeds min-max


}
