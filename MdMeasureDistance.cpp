#include "MdMeasureDistance.h"

DrUltraSonic drultrasonic(ECHO_PIN, TRIG_PIN);

double MdMeasureDistance::getDistance(){
    double distance;
    double t = drultrasonic.measureReturnTime();
    if(t >= 0){
        distance = (340.0/1000000) * t * 0.5 * 100;
        return distance;
    }
}