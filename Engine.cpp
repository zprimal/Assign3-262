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

void Engine::genInstances(int days){
    random_device rd;
    mt19937 gen(rd());
    for(auto const& it: this->gStats) {
        
        std::cout << "########################## " <<it.second.Name <<  std::endl;

        for(int i=0; i< days; i++){
            std::normal_distribution<> d(it.second.Mean, it.second.stdDev);
            int n = (d(gen));

            event_data newevent;
            newevent.value = n;
            eventdata.insert(make_pair<>(it.second.Name, newevent));
            cout << n << endl;
            // for (int i =0 ; i < n ; i++){
            //     std::normal_distribution<> e(value.second.Mean, value.second.stdDev);
            //     std::cout << round(d(gen)) << std::endl;
            // }
        }
    }
}

void Engine::clearInstances(){

}

void Engine::clearEvents(){
   this->gEvents.clear();
}

void Engine::clearStats(){
   this->gStats.clear();
}
