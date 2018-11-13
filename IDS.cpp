// g++ -std=c++11 IDS.cpp Stat.cpp Event.cpp -o IDS.exe

#include "IDS.h"
using namespace std;

int main(int argc, char const *argv[]) {
   if (argc != 4) {
      cout << argv[0] << " EventFile.txt StatsFile.txt Days" << endl;
      return -1;
   }

   string eventFile = argv[1];
   string statsFile = argv[2];
   string sDays = argv[3];
   string line;
   int eventSize, statSize, liveSize, liveDays;
   gDays = stoi(sDays);
   if (gDays < 25) {
      cout << "/// Warning: Low sample size ///" << endl;
   }

   eventSize = readEvent(eventFile);
   cout << endl;
   statSize = readStats(statsFile);
   if (eventSize != statSize) {
      cout << "eventSize != statSize" << endl;
   }
   gEngine.genInstances(gDays);
   cout << "Enter Live Stat file" << endl;
   getline(cin,line);
   liveSize = readLive(line);
   cout << "Enter Live Stat days" << endl;
   getline(cin,line);
   liveDays = stoi(line);
   return 0;
}

int readEvent(string fileName){
   ifstream file;
   string line;
	file.open(fileName);
   int size = 0;

   if(file.fail()){
		cout << "Error reading file!" << endl;
	} else {
      cout << "Reading events file..." << endl;
      getline(file,line);
      size = stoi(line);
      cout << "Size = " << size << endl;
      while (getline(file,line)) {
         stringstream linestream(line);
         string eName, stCD, stMin, stMax, stWgt;
         bool eCD;
         double eMin = 0, eMax = 0, eWgt = 0;

         //Get variables in line
         getline(linestream, eName, ':');
         getline(linestream, stCD, ':');
         getline(linestream, stMin, ':');
         getline(linestream, stMax, ':');
         getline(linestream, stWgt, ':');

         //Variables into glob variables
         if (stCD == "C") {
            eCD = true;
         } else {
            eCD = false;
         }

         if (!stMin.empty()) {
            eMin = stod(stMin, NULL);
         }

         if (!stMax.empty()) {
            eMax = stod(stMax, NULL);
         }

         if (!stWgt.empty()) {
            eWgt = stod(stWgt, NULL);
         }

         cout << eName << " " << eCD << " " << eMin << " " << eMax << " " << eWgt << endl;
         //Event newEvent(eName, eCD, eMin, eMax, eWgt);
         gEngine.push_event(Event(eName, eCD, eMin, eMax, eWgt));
      }
   }
   cout << "Closing file" << endl;
   file.close();
   return size;
}

int readStats(string fileName){
   ifstream file;
   string line;
	file.open(fileName);
   int size = 0;

   if(file.fail()){
		cout << "Error reading file!" << endl;
	} else {
      cout << "Reading stats file..." << endl;
      getline(file,line);
      size = stoi(line);
      cout << "Size = " << size << endl;
      while (getline(file,line)) {
         stringstream linestream(line);
         string sName, stMean, stSD;
         double sMean, sSD;

         //Get variables in line
         getline(linestream, sName, ':');
         getline(linestream, stMean, ':');
         getline(linestream, stSD, ':');

         //Variables into glob variables
         sMean = stod(stMean);
         sSD = stod(stSD);
         cout << sName << " " << sMean << " " << sSD << endl;
         //Stat newStat(sName, sMean, sSD);
         gEngine.push_stat(Stat(sName, sMean, sSD));
      }
   }
   cout << "Closing file" << endl;
   file.close();
   return size;
}

void displayEvent(){

}

void displayStats(){

}

int readLive(string fileName){
   ifstream file;
   string line;
	file.open(fileName);
   int size = 0;

   if(file.fail()){
		cout << "Error reading file!" << endl;
	} else {
      cout << "Reading livestat file..." << endl;
      getline(file,line);
      size = stoi(line);
      cout << "Size = " << size << endl;
      while (getline(file,line)) {
         stringstream linestream(line);
         string sName, stMean, stSD;
         double sMean, sSD;

         //Get variables in line
         getline(linestream, sName, ':');
         getline(linestream, stMean, ':');
         getline(linestream, stSD, ':');

         //Variables into glob variables
         sMean = stod(stMean);
         sSD = stod(stSD);
         cout << sName << " " << sMean << " " << sSD << endl;
         //Stat newStat(sName, sMean, sSD);
         gEngine.push_stat(Stat(sName, sMean, sSD));
      }
   }
   cout << "Closing file" << endl;
   file.close();
   return size;
}
