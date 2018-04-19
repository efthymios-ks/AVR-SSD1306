#ifndef TWI_H_
#define TWI_H_
/*
||
||  Filename:	 		TWI.h
||  Title: 			    TWI Driver
||  Author: 			Efthymios Koktsidis
||	Email:				efthymios.ks@gmail.com
||  Compiler:		 	AVR-GCC
||	Description:
||	This library can utilize the TWI hardware of AVR microcontrollers.
||
*/

//----- Headers ------------//
#include <inttypes.h>
#include <avr/io.h>
#include "IO_Macros.h"
#include "TWI_Settings.h"
//--------------------------//

//----- Auxiliary data ---------------------------//
enum TWI_Status_t
{
	TWI_Error,
	TWI_Ok
};

enum TWI_Status_MT_t
{
	MT_START_TRANSMITTED				= 0x08,
	MT_REP_START_TRANSMITTED			= 0x10,
	MT_SLA_W_TRANSMITTED_ACK			= 0x18,
	MT_SLA_W_TRANSMITTED_NACK			= 0x20,
	MT_DATA_TRANSMITTED_ACK				= 0x28,
	MT_DATA_TRANSMITTED_NACK			= 0x30,
	MT_SLA_W_ARB_LOST					= 0x38
};

enum TWI_Status_MR_t
{
	MR_START_TRANSMITTED				= 0x08,
	MR_REP_START_TRANSMITTED			= 0x10,
	MR_SLA_R_ARB_LOST					= 0x38,
	MR_SLA_R_TRANSMITTED_ACK			= 0x40,
	MR_SLA_R_TRANSMITTED_NACK			= 0x48,
	MR_DATA_RECEIVED_ACK				= 0x50,
	MR_DATA_RECEIVED_NACK				= 0x58
};

enum TWI_Status_SR_t
{
	SR_SLA_W_RECEIVED_ACK				= 0x60,
	SR_SLA_RW_ARB_LOST					= 0x68,
	SR_GEN_ADDR_RECEIVED_ACK			= 0x70,
	SSR_SLA_RW_ARB_LOST_2				= 0x78,
	SR_DATA_RECEIVED_SLA_ACK			= 0x80,
	SR_DATA_RECEIVED_SLA_NACK			= 0x88,
	SR_DATA_RECEIVED_GEN_ADDR_ACK		= 0x90,
	SR_DATA_RECEIVED_GEN_ADDR_NACK		= 0x98,
	SR_STOP_REP_START					= 0xA0
};

enum TWI_Status_ST
{
	ST_SLA_R_RECEIVED_ACK				= 0xA8,
	ST_SLA_RW_ARB_LOST					= 0xB0,
	ST_DATA_TRANSMITTED_ACK				= 0xB8,
	ST_DATA_TRANSMITTED_NACK			= 0xC0,
	ST_LAST_DATA_TRANSMITTED_ACK		= 0xC8
};

//------------------------------------------------//

//----- Prototypes ---------------------------------------------------//
void TWI_Setup(void);
uint8_t TWI_BeginTransmission(void);
void TWI_EndTransmission(void);
uint8_t TWI_Status(void);

uint8_t TWI_Transmit(uint8_t Data);
uint8_t TWI_ReceiveACK(void);
uint8_t TWI_ReceiveNACK(void);

enum TWI_Status_t TWI_PacketTransmit(const uint8_t SLA, const uint8_t SubAddress, uint8_t *Packet, const uint8_t Length);
enum TWI_Status_t TWI_PacketReceive(const uint8_t SLA, const uint8_t SubAddress, uint8_t *Packet, const uint8_t Length);

void TWI_SetAddress(const uint8_t Address);
//--------------------------------------------------------------------//
#endif