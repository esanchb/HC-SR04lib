//
//  HC_SR04_lib.cpp
//  SensorArch
//
//  Created by Eric on 23/04/16.
//  Copyright (c) 2016 Eric Sanchez B. All rights reserved.
//
#include <Arduino.h>
#include "HC_SR04_lib.h"

void HC_SR04Dev::HC_SR04_hw_Trigger() const{
    
    digitalWrite(Hc_sr04_trigger, LOW);
    delayMicroseconds(TRIG_OFF_MS);
    digitalWrite(Hc_sr04_trigger, HIGH);
    delayMicroseconds(TRIG_ON_MS);
    digitalWrite(Hc_sr04_trigger, LOW);

}
unsigned long HC_SR04Dev::HC_SR04_hw_Read(){
    HC_SR04_hw_Trigger();
    Hc_sr04_MeasureHw=pulseIn(Hc_sr04_echo, HIGH);
    return Hc_sr04_MeasureHw;
}

void HC_SR04Dev::HC_SR04_hw_Config(){
    pinMode(Hc_sr04_trigger, OUTPUT);
    pinMode(Hc_sr04_echo, INPUT);
}

unsigned char HC_SR04Dev::Sync(){
    
    Hc_sr04_MeasureHw=HC_SR04_hw_Read();
    
    if(Hc_sr04_MeasureHw == TIMEOUT_ERROR_VALUE){
        Hc_sr04_Status=HC_SR04_TIMEOUT_READ;
    }else
    {
     switch (Hc_sr04_units) {
        case UNITS_METRIC:
            Hc_sr04_Status=MetricConv();
            break;
            
        case UNITS_ENGLISH:
            Hc_sr04_Status=EngConv();
            break;
            
        default:
            break;
     }
    }
    return Hc_sr04_Status;
}
unsigned long HC_SR04Dev::Read(){
    return Hc_sr04_Measure;
}

unsigned char HC_SR04Dev::Status(){
    return Hc_sr04_Status;
}

unsigned char HC_SR04Dev::MetricConv(){
    unsigned long temp;
    
    temp = Hc_sr04_MeasureHw/UNITS_ENGLISH_DIV;
    
    if (temp < m_thmin)
    {
        Hc_sr04_Measure=ERROR_VALUE;
        return HC_SR04_UNDER_MIN;
    }
    else if (temp > m_thmax)
    {
        Hc_sr04_Measure=ERROR_VALUE;
        return HC_SR04_OVER_MAX;
    }else{
        // Looks Good :)
        Hc_sr04_Measure=temp;
        
    }
    
    return HC_SR04_READ_OK;
}
unsigned char HC_SR04Dev::EngConv(){
    unsigned long temp;
    
    temp = Hc_sr04_MeasureHw/UNITS_METRIC_DIV;
    
    if (temp < m_thmin)
    {
        Hc_sr04_Measure=ERROR_VALUE;
        return HC_SR04_UNDER_MIN;
    }
    else if (temp > m_thmax)
    {
        Hc_sr04_Measure=ERROR_VALUE;
        return HC_SR04_OVER_MAX;
    }else{
        // Looks Good :)
        Hc_sr04_Measure=temp;
        
    }
    return HC_SR04_READ_OK;
}
void HC_SR04Dev::SetMinMax(unsigned long _min_range, unsigned long _max_range){
    m_thmax=_max_range;
    m_thmin=_min_range;
    
}


HC_SR04Dev::HC_SR04Dev(int _trigger_pin,int _echo_pin,System_unit _units_conf):
Hc_sr04_Measure(ERROR_VALUE),
Hc_sr04_MeasureHw(ERROR_VALUE),
Hc_sr04_Status(HC_SR04_OFF)
{
    Hc_sr04_trigger=_trigger_pin;
    Hc_sr04_echo=_echo_pin;
    if(_units_conf==UNITS_ENGLISH){
        m_thmax=ENG_SYSTEM_MAX_INCH;
        m_thmin=ENG_SYSTEM_MIN_INCH;
    }else{
        m_thmax=METRIC_SYSTEM_MAX_CM;
        m_thmin=METRIC_SYSTEM_MIN_CM;
    }
    HC_SR04_hw_Config();
}

HC_SR04Dev::HC_SR04Dev(int _trigger_pin,int _echo_pin):
Hc_sr04_Measure(ERROR_VALUE),
Hc_sr04_MeasureHw(ERROR_VALUE),
Hc_sr04_Status(HC_SR04_OFF),
m_thmax(METRIC_SYSTEM_MAX_CM),
m_thmin(METRIC_SYSTEM_MIN_CM),
Hc_sr04_units(UNITS_METRIC)
{
    Hc_sr04_trigger=_trigger_pin;
    Hc_sr04_echo=_echo_pin;
    HC_SR04_hw_Config();
}

