#ifndef IDS_H
#define IDS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Stat.h"
#include "Event.h"

using namespace std;

void readEvent(string);
void readStats(string);
void displayEvent();
void displayStats();

vector<Stat> globStat;
vector<Event> globEvent;

#endif