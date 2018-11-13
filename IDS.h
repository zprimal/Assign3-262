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
#include "Engine.h"

using namespace std;

int readEvent(string);
int readStats(string);
int readLive(string);
void displayEvent();
void displayStats();

Engine gEngine;
int gDays;

#endif
