// Project TipidBox
//
// Project Name:			Centralized Coinslot 
// Author:					Earl John P. Abaquita
// File name:				Setings.cpp 
// Version:					0.1
// Description:				This file contains the getter/setter functions of settings
//
// Copyright Abaquitronics 2020

#include "Settings.h"

Settings::Settings(){
    setTransitionSetting(1500);
    setCafeNameSetting("MPG Pisonet");
	setTimeOutSettings(10000);
}

int Settings::getTransitionSetting(){
    return this->transition_duration_;
}

int Settings::setTransitionSetting(int transition){
    this->transition_duration_ = transition;
}

char* Settings::getCafeNameSetting(){
    return this->cafe_name_;
}

char* Settings::setCafeNameSetting(char* cafe_name){
    this->cafe_name_ = cafe_name;
}

int Settings::getTimeOutSettings(){
    return this->timeout_settings_;
}

void Settings::setTimeOutSettings(int timeOut){
    this->timeout_settings_ = timeOut;
}

