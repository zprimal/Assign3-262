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
			std::normal_distribution<float> d(it.second.Mean, it.second.stdDev);
			double n = (d(gen));
            // if descreet round it off
            if(this->gEvents.find(it.second.Name)->second.Continuous == false)
                n = round(n);
            // check for bounds
            if (this->gEvents.find(it.second.Name)->second.Max == -1 || n <= this->gEvents.find(it.second.Name)->second.Max){
                tmp.push_back(n);
                continue;
            }else{
                i--;
            }
        }
        eventdata.insert(make_pair<>(it.second.Name, tmp));
    }

    this->myfile.open("logfile.txt", std::ios_base::app);
    this->myfile << "--------------------" << endl;
    this->myfile << "Training Sample Data" << endl;
    this->myfile << "--------------------" << endl;
    for (int i = 0; i < days ; i++){
        for(auto const& it: this->eventdata) {
           this->myfile << it.first<< ":"<<  it.second.at(i) << endl;
        }
        this->myfile << endl;
    }
    this->myfile.close();

}

void Engine::gen_sample_live(int days){
    random_device rd;
    mt19937 gen(rd());
    for(auto const& it: this->liveStat) {
      vector<double> tmp;
        for(int i=0; i< days; i++){
			std::normal_distribution<float> d(it.second.Mean, it.second.stdDev);
			double n = (d(gen));
            // if descreet round it off
            if(this->gEvents.find(it.second.Name)->second.Continuous == false)
                n = round(n);

            // check for bounds
            if (this->gEvents.find(it.second.Name)->second.Max == -1 || n <= this->gEvents.find(it.second.Name)->second.Max){
                tmp.push_back(n);
                continue;
            }else{
                i--;
            }
        }
        eventdata.insert(make_pair<>(it.second.Name, tmp));
    }

    this->myfile.open("logfile.txt", std::ios_base::app);
    this->myfile << "--------------------" << endl;
    this->myfile << "Live Sample Data" << endl;
    this->myfile << "--------------------" << endl;
    for (int i = 0; i < days ; i++){
        for(auto const& it: this->eventdata) {
           this->myfile << it.first<< ":"<<  it.second.at(i) << endl;
        }
        this->myfile << endl;
    }
    this->myfile.close();

}

void Engine::checkEventStats(){
   cout << "checkEventStats" << endl;
   // Names different
   bool matched = false;
   for (auto i = gEvents.begin(); i != gEvents.end(); i++) {
      for (auto j = gStats.begin(); j != gStats.end(); j++) {
         if (i->first == j->first) {
            matched = true;
         }
      }
      if (!matched) {
         cout << i->first << " has no match!\nExiting program" << endl;
         exit(0);
      }
      matched = false;
   }
   //Check if live stats matches event names
}

void Engine::checkEventLive(){
   cout << "checkEventLive" << endl;
   // Names different
   bool matched = false;
   for (auto i = gEvents.begin(); i != gEvents.end(); i++) {
      for (auto j = liveStat.begin(); j != liveStat.end(); j++) {
         if (i->first == j->first) {
            matched = true;
         }
      }
      if (!matched) {
         cout << i->first << " has no match!\nExiting program" << endl;
         exit(0);
      }
      matched = false;
   }
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
   cout << "Generating training stats" << endl;
   for (auto i = eventdata.begin(); i != eventdata.end(); i++) {
      double daMean = getMean(i->second);
      double daSD = getSD(i->second, daMean);
      string daName = i->first;
      this->testStat.insert(std::make_pair<>(daName, Stat(daName, daMean, daSD)));
   }
}

void Engine::getLiveStat(){
   cout << "Generating live stats" << endl;
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

// double Engine::getSMean(string eventName){
//    auto it = this->gStats.find(eventName);
//    Stat tmpStat = it->second;
//    return tmpStat.Mean;
// }
//
// double Engine::getSSD(string eventName){
//    auto it = this->gStats.find(eventName);
//    Stat tmpStat = it->second;
//    return tmpStat.stdDev;
// }

double Engine::checkAnomaly(string eventName, double sampleData){
   auto it = this->gStats.find(eventName);
   Stat tmpStat = it->second;
   double mean = tmpStat.Mean;
   double sd = tmpStat.stdDev;
   double holder = sampleData;
   int i = 0; // Counts how many SD from the mean
   if (mean == sampleData) {
      return 0;
   } else if (mean < holder) {
      holder = holder - mean;
      return holder/sd;
   } else {
      holder = mean - holder;
      return holder/sd;
   }
}

void Engine::Alertium(int liveDays){
   cout << "=====================\nAlert Engine starting up" << endl;
   // Count total event anomaly threshold for one day
   double threshold = 0; // Generate anomaly threshold
   for (auto i = eventdata.begin(); i != eventdata.end(); i++) {
      string tmpName = i->first;
      vector<double> tmpVector = i->second;
      double weight = getEWeight(tmpName);
      threshold = threshold + weight;
   }
   threshold = threshold*2;

    this->myfile.open("logfile.txt", std::ios_base::app);
    this->myfile << "--------------------" << endl;
    this->myfile << "Alert Log" << endl;
    this->myfile << "--------------------" << endl;


   // Run event data for each day
   for (int a = 0; a < liveDays; a++) {
      double dailyOff = 0;
      vector<double> tmpVector;
      for (auto i = eventdata.begin(); i != eventdata.end(); i++) {
         string tmpName = i->first;
         tmpVector = i->second;
         double off = checkAnomaly(tmpName, tmpVector[a]);

         // get total event anomaly for each day
         dailyOff = dailyOff + off;
      }
      // Compare against total event anomaly
      if (dailyOff >= threshold) {
         cout << "[ALERT] Day " << a+1 << ": " << tmpVector[a] << " Off by " << dailyOff << endl;
         this->myfile << "[ALERT] Day " << a+1 << ": " << tmpVector[a] << " Off by " << dailyOff << endl;

      }
   }
    this->myfile<< std::endl;
   this->myfile.close();

   //ORIGINAL CODE
   // for (auto i = eventdata.begin(); i != eventdata.end(); i++) {
   //    string tmpName = i->first;
   //    vector<double> tmpVector = i->second;
   //    double weight = getEWeight(tmpName);
   //    double threshold = weight * 2; // Generate anomaly threshold
   //    int dayC = 1;
   //    cout << tmpName << endl;
   //    for (auto j = tmpVector.begin(); j != tmpVector.end(); j++) {
   //       //Run for each entry in the vector
   //       double off = checkAnomaly(tmpName, *j);
   //       if (off >= threshold) {
   //          cout << "[ALERT] Day " << dayC << ": " << *j << " Off the mean by " << off << endl;
   //       }
   //
   //       dayC++;
   //    }
   //
   // }
   cout << "=====================\nAlertium complete\n=====================" << endl;
}
