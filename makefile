rm -rf IDS.exe
g++ Engine.cpp Event.cpp IDS.cpp  Stat.cpp -o IDS.exe  -std=c++11

./IDS.exe Events.txt Stats.txt 5
