#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <map>
#include "Stat.h"
#include "Event.h"

using namespace std;

class Engine{
private:
   map<string, Event> gEvents;
   map<string, Stat> gStats;

public:
   Engine();
   ~Engine();
   void push_event(Event);
   void push_stat(Stat);
   void startEngine(int);
   void genInstances();
   void clearInstances();
   void clearEvents();
   void clearStats();
   int checkEventStats();

};

#endif
