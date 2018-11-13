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

void Engine::push_stat_live(Stat newStat){
   this->liveStat.insert(std::make_pair<>(newStat.Name, newStat));
}

void Engine::startEngine(int Day){

}

void Engine::gen_sample(int days){
    random_device rd;
    mt19937 gen(rd());
    for(auto const& it: this->gStats) {
        
        for(int i=0; i< days; i++){
			std::normal_distribution<> d(it.second.Mean, it.second.stdDev);
			int n = (d(gen));

			event_data newevent;
			newevent.value = n;
			eventdata.insert(make_pair<>(it.second.Name, newevent));
        }
    }

	// for(auto const& it: this->eventdata) {
	// 	std::cout << it.first << " "<<  it.second.value << std::endl;
	// }

}

void Engine::gen_sample_live(int days){
    random_device rd;
    mt19937 gen(rd());
    for(auto const& it: this->liveStat) {
        
        for(int i=0; i< days; i++){
			std::normal_distribution<> d(it.second.Mean, it.second.stdDev);
			int n = (d(gen));

			event_data newevent;
			newevent.value = n;
			eventdata.insert(make_pair<>(it.second.Name, newevent));
        }
    }

	// for(auto const& it: this->eventdata) {
	// 	std::cout << it.first << " "<<  it.second.value << std::endl;
	// }

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

void Engine::clear_sample_data(){
    //  Log this data first

    this->eventdata.clear();
}