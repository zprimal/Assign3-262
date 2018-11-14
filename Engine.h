#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <map>
#include <vector>
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
    map<string, Event> gEvents;
    map<string, Stat> gStats;

    map<string, vector<double>> eventdata;

    /* testStat still needed cos it will be different values than gStats*/
    map<string, Stat> testStat;
    map<string, Stat> liveStat;

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
    void clear_live_stat();
    void getTestStat();
    void getLiveStat();
    double getMean(vector<double>);
    double getSD(vector<double>, double);

    //Alert Module
    double getEWeight(string);
    // double getSMean(string);
    // double getSSD(string);
    double checkAnomaly(string, double);
    void Alertium();
};

#endif
