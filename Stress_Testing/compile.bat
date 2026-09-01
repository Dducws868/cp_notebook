@echo off
echo compiling %name%...
g++ -std=c++17 %name%.cpp -Wall -o %name%.exe
echo done
