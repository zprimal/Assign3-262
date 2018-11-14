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
    vector<double> tmp;
    for(auto const& it: this->gStats) {
        vector<double> tmp;
        for(int i=0; i < days; i++){
			std::normal_distribution<> d(it.second.Mean, it.second.stdDev);
			int n = (d(gen));

			tmp.push_back(n);
        }
        eventdata.insert(make_pair<>(it.second.Name, tmp));
    }

	// for(auto const& it: this->eventdata) {
	// 	std::cout << it.first << " "<<  it.second.value << std::endl;
	// }

}

void Engine::gen_sample_live(int days){
    random_device rd;
    mt19937 gen(rd());
    for(auto const& it: this->liveStat) {
      vector<double> tmp;
        for(int i=0; i< days; i++){
			std::normal_distribution<> d(it.second.Mean, it.second.stdDev);
			int n = (d(gen));

			tmp.push_back(n);
        }
        eventdata.insert(make_pair<>(it.second.Name, tmp));
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

   //Check if live stats matches event names


}

void Engine::clear_sample_data(){
    //  Log this data first

    this->eventdata.clear();
}

void Engine::clear_live_stat(){
    //  Log this data first

    this->liveStat.clear();
}

void Engine::getTestStat(){
   for (auto i = eventdata.begin(); i != eventdata.end(); i++) {
      double daMean = getMean(i->second);
      double daSD = getSD(i->second, daMean);
      string daName = i->first;
      this->testStat.insert(std::make_pair<>(daName, Stat(daName, daMean, daSD)));
   }
}

void Engine::getLiveStat(){
   for (auto i = eventdata.begin(); i != eventdata.end(); i++) {
      double daMean = getMean(i->second);
      double daSD = getSD(i->second, daMean);
      string daName = i->first;
      this->liveStat.insert(std::make_pair<>(daName, Stat(daName, daMean, daSD)));
   }
}

double Engine::getMean(vector<double> leVector){
   double sum = 0;
   int counter = 1;
   for (auto i = leVector.begin(); i != leVector.end(); i++) {
      sum = sum + *i;
      counter++;
   }
   return (double) sum/counter;
}

double Engine::getSD(vector<double> leVector, double leMean){
   double SD = 0.0;
   int counter = 1;
   for(auto i = leVector.begin(); i != leVector.end(); ++i){
      SD += pow(*i - leMean, 2);
      counter++;
   }
   return sqrt(SD/counter);
}

double Engine::getEWeight(string eventName){
   auto it = this->gEvents.find(eventName);
   Event tmpEvent = it->second;
   return tmpEvent.Wgt;
}

double Engine::getSMean(string eventName){
   auto it = this->gStats.find(eventName);
   Stat tmpStat = it->second;
   return tmpStat.Mean;
}

double Engine::getSSD(string eventName){
   auto it = this->gStats.find(eventName);
   Stat tmpStat = it->second;
   return tmpStat.stdDev;
}

int Engine::checkAnomaly(string eventName, double sampleData){
   double mean = getSMean(eventName);
   double sd = getSSD(eventName);
   double holder = sampleData;
   int i = 0; // Counts how many SD from the mean
   if (mean == sampleData) {
      return 0;
   } else if (mean < holder) {
      while (mean < holder) {
         holder = holder - sd;
         i++;
      }
      return i--;
   } else {
      while (mean > sampleData) {
         holder = holder + sd;
         i++;
      }
      return i--;
   }
}

void Engine::Alertium(){
   cout << "Alert Engine starting up" << endl;
   for (auto i = eventdata.begin(); i != eventdata.end(); i++) {
      string tmpName = i->first;
      vector<double> tmpVector = i->second;
      for (auto j = tmpVector.begin(); j != tmpVector.end(); j++) {
         //Run for each entry in the vector
         double weight = getEWeight(tmpName);
         double threshold = weight * 2;
         int off = checkAnomaly(tmpName, *j);
         if (off > threshold) {
            cout << "Out of threshold" << endl;
         }

      }

   }
}
