// Project TipidBox
//
// Project Name:			Centralized Coinslot 
// Author:					Earl John P. Abaquita
// File name:				Setings.cpp 
// Version:					0.1
// Description:				This file contains the getter/setter functions of settings
//
// Copyright Abaquitronics 2020

#ifndef Settings_h
#define Settings_h

class Settings{
    private:
        int transition_duration_;
        char* cafe_name_;
       
    public:
		// -------------------------------------------------------------------------
		// Function name:				Settings
		// Function description: 		Constructor
		// Input:						N/A
		// type:						Settings
		// -------------------------------------------------------------------------
        Settings();

		// -------------------------------------------------------------------------
		// Function name:				getTransitionSetting
		// Function description: 		get Transition settings for panel transition
		// Input:						N/A
		// return type:					integer
		// -------------------------------------------------------------------------
        int getTransitionSetting();

		// -------------------------------------------------------------------------
		// Function name:				getCafeNameSetting
		// Function description: 		get Cafe name settings for panel transition
		// Input:						N/A
		// return type:					char
		// -------------------------------------------------------------------------
        char * getCafeNameSetting();

    private:
		// -------------------------------------------------------------------------
		// Function name:				setTransitionSettings
		// Function description: 		setting the transition in maintenance mode
		// Input:						transition in ms
		// return type:					integer
		// -------------------------------------------------------------------------
        int setTransitionSetting(int transition);

		// -------------------------------------------------------------------------
		// Function name:				setCafeNameSetting
		// Function description: 		setting the cafe name in maintenance mode
		// Input:						Cafe name
		// return type:					char*
		// -------------------------------------------------------------------------
        char * setCafeNameSetting(char* cafe_name);

};

#endif
