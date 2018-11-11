// g++ -std=c++11 IDS.cpp -o IDS.exe

int main(int argc, char const *argv[]) {
   if (argc != 4) {
      cout << argv[0] << " EventFile.txt StatsFile.txt Days" << endl;
      return -1;
   }

   string eventFile = argv[1];
   string statsFile = argv[2];
   string sDays = argv[3];
   int Days = stoi(sDays);
   return 0;
}

void readEvent(string fileName){
   ifstream file;
	file.open(fileName);

   if(file.fail()){
		cout << "Error reading file!" << endl;
	} else {
      cout << "Reading file..." << endl;
      while (getline(file,line)) {
         stringstream linestream(line);
         string eName, eCD, sMin, sMax, sWgt;
         int eMin, eMax, eWgt;

         //Get variables in line
         getline(linestream, eName, ':');
         getline(linestream, eCD, ':');
         getline(linestream, sMin, ':');
         getline(linestream, sMax, ':');
         getline(linestream, sWgt, ':');

         //Variables into glob variables
         
      }
   }
   cout << "Closing file" << endl;
   file.close();
}

void readStats(string fileName){
   ifstream file;
	file.open(fileName);

   if(file.fail()){
		cout << "Error reading file!" << endl;
	} else {
      cout << "Reading file..." << endl;
      while (!file.eof()) {
         //Keep reading
         getline(file,line);
         string tmp = "";

         //Trimming the line
         line = line.substr(0, line.find("\r", 0));
         line = line.substr(0, line.find("\n", 0));
      }
   }
   cout << "Closing file" << endl;
   file.close();
}

void displayEvent(){

}

void displayStats(){

}
