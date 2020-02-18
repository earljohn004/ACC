// Project TipidBox
//
// Project Name:			Centralized Coinslot 
// Author:					Earl John P. Abaquita
// File name:				Setings.cpp 
// Version:					0.1
// Description:				This file contains the getter/setter functions of settings
//
// Copyright Abaquitronics 2020

#include "Entity.h"

Entity::Entity(){
	setSelectedPC("0");
}

String Entity::getSelectedPC(){
	return this->pc_selected;
}

void Entity::setSelectedPC(const String pc){
	this->pc_selected = pc;
}
