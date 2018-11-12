#include "Stat.h"

Stat::Stat(){

}

Stat::Stat(string nName, double nMean, double nStdDev){
   Name = nName;
   Mean = nMean;
   stdDev = nStdDev;
}

Stat::~Stat(){
   //Deconstructor
}
