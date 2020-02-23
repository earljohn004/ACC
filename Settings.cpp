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
	setPasscodeSettings("1234");
	setMaxPCCountSettings(24);
	setFWVersion("0.3");
}

int Settings::getTransitionSetting(){
    return this->transition_duration_;
}

int Settings::setTransitionSetting(int transition){
    this->transition_duration_ = transition;
}

String Settings::getCafeNameSetting(){
    return this->cafe_name_;
}

void Settings::setCafeNameSetting(String cafe_name){
    this->cafe_name_ = cafe_name;
}

int Settings::getTimeOutSettings(){
    return this->timeout_settings_;
}

void Settings::setTimeOutSettings(int timeOut){
    this->timeout_settings_ = timeOut;
}

void Settings::setMaxPCCountSettings( int num ){
	this -> max_pc_count_ = num;
}

int  Settings::getMaxPCCountSettings(){
	return this->max_pc_count_;
}

void Settings::setPasscodeSettings(String passcode){
	this->passcode_ = passcode;
}

String Settings::getPasscodeSettings(){
	return this->passcode_;
}

void Settings::setFWVersion(String fwversion){
	this->fw_version_ = fwversion;
}

String Settings::getFWVersion(){
	return this->fw_version_;
}

