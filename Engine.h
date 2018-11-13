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
#include <cstdint>
#include <random>


using namespace std;


struct event_data{
    double value;
};


class Engine{
private:
<<<<<<< HEAD
   map<string, Event> gEvents;
   map<string, Stat> gStats;
   map<string, event_data> eventdata;
   
=======
    map<string, Event> gEvents;
    map<string, Stat> gStats;

    multimap<string, event_data> eventdata;

    /* testStat still needed cos it will be different values than gStats*/
    map<string, Stat> testStat;
    map<string, Stat> liveStat;
    
>>>>>>> 6d46c89f7860bdfbbbb1efc7a60d2e4ab1822355
public:
    Engine();
    ~Engine();

    void push_event(Event);
    void push_stat(Stat);
    void startEngine(int);
    void gen_sample(int);

    int checkEventStats();

    void push_stat_live(Stat);
    void gen_sample_live(int);


    void clear_sample_data();

};

#endif
