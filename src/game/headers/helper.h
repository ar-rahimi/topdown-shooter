//
// Created by Ahmad Rahimi on 9/6/17.
//

#ifndef HELPER_H
#define HELPER_H
#include <stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>
#include <math.h>
class Helper {
public:
    static  int GetPPM();
    static float radiansToDegrees(double radians);
    static float degreesToRadians(double degrees);
    static std::string getCurrentWorkingDir();
    static double correctTheAngle(double angle);
    static int PPM;
    static double getNewDirection(double olddir);
};

#endif //HELPER_H
