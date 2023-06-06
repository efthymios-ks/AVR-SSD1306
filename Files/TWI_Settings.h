#ifndef TWI_SETTINGS_H_
#define TWI_SETTINGS_H_
/*
||
||  Filename:	 		TWI_Settings.h
||  Title: 			    TWI Driver Settings
||  Author: 			Efthymios Koktsidis
||	Email:				efthymios.ks@gmail.com
||  Compiler:		 	AVR-GCC
||	Description:
||	Settings for the TWI hardware.
||
*/

//----- Configuration -------------//
//SCL Frequency
#define F_SCL				100000UL

//TWI pins
#define TWI_SCL				C, 5
#define TWI_SDA				C, 4
//---------------------------------//
#endif
