#ifndef STAT_H
#define STAT_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

class Stat{
public:
   string Name;
   double Mean, stdDev;

   Stat();
   Stat(string, double, double);
   ~Stat();
};

#endif
