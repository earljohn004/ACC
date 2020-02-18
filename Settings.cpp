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
    setTransitionSetting(2000);
    setCafeNameSetting("MPG Pisonet");
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
