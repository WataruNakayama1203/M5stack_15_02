#include "DrUltraSonic.h"
#include <M5Stack.h>

DrUltraSonic::DrUltraSonic(int echo_pin, int trig_pin) {
    m_echo_pin = echo_pin;  // echo_pin を m_echo_pin に設定
    m_trig_pin = trig_pin;  // trig_pin を m_trig_pin に設定

    pinMode(m_echo_pin, INPUT);
    pinMode(m_trig_pin, OUTPUT);
}

double DrUltraSonic::measureReturnTime(){
    digitalWrite(m_trig_pin,true);
    delayMicroseconds(10);
    digitalWrite(m_trig_pin,false);
    double t = pulseIn(m_echo_pin,true);
    return t;
}

