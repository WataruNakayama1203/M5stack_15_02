#include "MdWBGTMonitor.h"

DrTHSensor drthSensor;

void MdWBGTMonitor::init(){
    drthSensor.init();
}

void MdWBGTMonitor::getWBGT(double* temperature, double* humidity, WbgtIndex* index){

    double calc_index;
    drthSensor.getTempHumi(temperature,humidity);

    //熱中症アラートの基準値計算には次の式で計算する
    //index = 0.68 * 温度[℃] ＋ 0.12 * 湿度[%]
    calc_index = (0.68 * *temperature) + (0.12 * *humidity);

    if(calc_index <= 15){
        *index = SAFE;
    }
    else if(calc_index <= 24){
        *index = ATTENTION;
    }
    else if(calc_index <= 27){
        *index = ALERT;
    }
    else if(calc_index <= 30){
        *index = HIGH_ALERT;
    }
    else if(calc_index >= 31){
        *index = DANGER;
    }
}