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

#include <WString.h>

class Settings{
    private:
        int transition_duration_;
		int timeout_settings_;
        String cafe_name_;
		int max_pc_count_;
		String passcode_;
		String fw_version_;
       
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
        String  getCafeNameSetting();

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
        void setCafeNameSetting(String cafe_name);

		void setTimeOutSettings(int timeOut);
		int getTimeOutSettings();

		void setMaxPCCountSettings( int num );
		int getMaxPCCountSettings();

		void setPasscodeSettings(String passcode);
		String getPasscodeSettings();

		void setFWVersion(String fwversion);
		String getFWVersion();
};

#endif
