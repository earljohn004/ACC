// Project TipidBox
//
// Project Name:			Centralized Coinslot 
// Author:					Earl John P. Abaquita
// File name:				Setings.cpp 
// Version:					0.1
// Description:				This file contains the getter/setter functions of settings
//
// Copyright Abaquitronics 2020

#ifndef Entity_h
#define Entity_h
#include <WString.h>

class Entity{
    private:
        String pc_selected;
       
    public:
		// -------------------------------------------------------------------------
		// Function name:				Entity
		// Function description: 		Constructor
		// Input:						N/A
		// type:						Entity
		// -------------------------------------------------------------------------
        Entity();

		// -------------------------------------------------------------------------
		// Function name:				getTransitionSetting
		// Function description: 		get Transition settings for panel transition
		// Input:						N/A
		// return type:					integer
		// -------------------------------------------------------------------------
        String getSelectedPC();

		// -------------------------------------------------------------------------
		// Function name:				setTransitionEntity
		// Function description: 		setting the transition in maintenance mode
		// Input:						transition in ms
		// return type:					integer
		// -------------------------------------------------------------------------
        void setSelectedPC(const String pc);

};

#endif
