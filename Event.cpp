#include "Event.h"

Event::Event(){

}

Event::Event(string nName, bool nCD, double nMin, double nMax, double nWgt){
   Name = nName;
   Continuous = nCD;
   Min = nMin;
   Max = nMax;
   Wgt = nWgt;
}

Event::~Event(){
   //Deconstructor
}

void Event::enforceCD(){
   if (!Continuous) {
      // Ensure Min Max and Wgt are integers;
      Min = round(Min);
      Max = round(Max);
      Wgt = round(Wgt);
   }
}
