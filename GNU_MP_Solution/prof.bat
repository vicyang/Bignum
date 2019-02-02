@echo off
g++ -std=c++11 -pg -o %~n1 %1
%~n1.exe
gprof %~n1.exe gmon.out > %~n1_prof.txt
