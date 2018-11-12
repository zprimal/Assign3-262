#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

class Event{
public:
   string Name;
   bool Continuous; // If false, is Discreet
   double Min, Max, Wgt;

   Event();
   Event(string, bool, double, double, double);
   ~Event();
   void enforceCD();
};

#endif
