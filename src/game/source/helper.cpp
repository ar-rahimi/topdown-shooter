//
// Created by Ahmad Rahimi on 9/6/17.
//
#include "helper.h"

int Helper::GetPPM(){
    return 100;
}

float Helper::degreesToRadians(double degrees) {
    return degrees / 180*M_PI;
}

float Helper::radiansToDegrees(double radians) {
    return radians * 180/M_PI;
}

std::string Helper::getCurrentWorkingDir( void ) {
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    return current_working_dir;
}

double Helper::correctTheAngle(double angle) {
    if (angle > 90){
        return (angle - 90);
    }else {
        return angle + 270;
    }
}

double Helper::getNewDirection(double olddir) {
    return olddir+180;
}