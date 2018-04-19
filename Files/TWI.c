#include "TWI.h"

#define __TWI_SLA_W(address)	(address<<1)
#define __TWI_SLA_R(address)	((address<<1) | (1<<0))

//----- Prototypes ------------------------------//

//-----------------------------------------------//

//----- Functions -------------//
//Setup TWI hardwarw.
void TWI_Setup(void)
{
	//TWI pins as outputs
	PinMode(TWI_SDA, Output);
	PinMode(TWI_SCL, Output);
	//Activate internal pull-up resistors
	DigitalWrite(TWI_SDA, High);
	DigitalWrite(TWI_SCL, High);

	//Initialize TWI prescaler and bit rate
	TWSR = 0x00;	//Prescaler = 1
	TWBR = (uint8_t)(((F_CPU / F_SCL) - 16) / 2);
	//F_SCL = F_CPU / (16 + 2 * TWBR * PRESCALER)
	//TWBR = ((F_CPU / F_SCL) - 16) / (2 * PRESCALER)

	//Enable TWI  module
	TWCR = (1<<TWEN);
}

//Get TWI status. 
uint8_t TWI_Status(void)
{
	return (TWSR & 0xF8);
}

//Begin TWI transmission. 
uint8_t TWI_BeginTransmission(void)
{
	//Transmit START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	//Wait for TWINT Flag set. This indicates that
	//the START condition has been transmitted.
	while (!BitCheck(TWCR, TWINT));

	//Return status register
	return (TWI_Status());
}

//End TWI transmission. 
void TWI_EndTransmission(void)
{
	//Transmit STOP condition
	TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWSTO);

	//Wait for stop condition to be executed on bus
	//TWINT is not set after a stop condition!
	while(BitCheck(TWCR, TWSTO));
}

//Transmit data. 
uint8_t TWI_Transmit(const uint8_t Data)
{
	//Data to be transmitted
	TWDR = Data;

	//Start transmission
	TWCR = (1<<TWINT) | (1<<TWEN);

	//Wait data to be shifted
	while (!BitCheck(TWCR, TWINT));

	//Return status register
	return (TWI_Status());
}

//Wait until ACK received. 
uint8_t TWI_ReceiveACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	
	//Wait till reception is
	while (!BitCheck(TWCR, TWINT));

	//Return received data
	return TWDR;
}

//Wait until NACK received. 
uint8_t TWI_ReceiveNACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);

	//Wait till reception is
	while (!BitCheck(TWCR, TWINT));

	//Return received data
	return TWDR;
}

//Transmit packet to specific slave address. 
enum TWI_Status_t TWI_PacketTransmit(const uint8_t SLA, const uint8_t SubAddress, uint8_t *Packet, const uint8_t Length)
{
	uint8_t i, status;
	
	do
	{
		//Transmit START signal
		status = TWI_BeginTransmission();
		if ((status != MT_START_TRANSMITTED) && ((status != MT_REP_START_TRANSMITTED)))
		{
			status = TWI_Error;
			break;
		}

		//Transmit SLA+W
		status = TWI_Transmit(__TWI_SLA_W(SLA));
		if ((status != MT_SLA_W_TRANSMITTED_ACK) && (status != MT_SLA_W_TRANSMITTED_NACK))
		{
			status = TWI_Error;
			break;
		}

		//Transmit write address
		status = TWI_Transmit(SubAddress);
		if ((status != MT_DATA_TRANSMITTED_ACK) && (status != MT_DATA_TRANSMITTED_NACK))
		{
			status = TWI_Error;
			break;
		}
		//Transmit DATA
		for (i = 0 ; i < Length ; i++)
		{
			status = TWI_Transmit(Packet[i]);
			if ((status != MT_DATA_TRANSMITTED_ACK) && (status != MT_DATA_TRANSMITTED_NACK))
			{
				status = TWI_Error;
				break;
			}
		}

		//Transmitted successfully
		status = TWI_Ok;
	}
	while (0);

	//Transmit STOP signal
	TWI_EndTransmission();

	return status;
}

//Receive packet from specific slave address. 
enum TWI_Status_t TWI_PacketReceive(const uint8_t SLA, const uint8_t SubAddress, uint8_t *Packet, const uint8_t Length)
{
	uint8_t i = 0, status;

	do 
	{
		//Transmit START signal
		status = TWI_BeginTransmission();
		if ((status != MT_START_TRANSMITTED) && (status != MT_REP_START_TRANSMITTED))
		{
			status = TWI_Error;
			break;
		}

		//Transmit SLA+W
		status = TWI_Transmit(__TWI_SLA_W(SLA));
		if ((status != MT_SLA_W_TRANSMITTED_ACK) && (status != MT_SLA_W_TRANSMITTED_NACK))
		{
			status = TWI_Error;
			break;
		}

		//Transmit read address
		status = TWI_Transmit(SubAddress);
		if ((status != MT_DATA_TRANSMITTED_ACK) && (status != MT_DATA_TRANSMITTED_NACK))
		{
			status = TWI_Error;
			break;
		}

		//Transmit START signal
		status = TWI_BeginTransmission();
		if ((status != MR_START_TRANSMITTED) && (status != MR_REP_START_TRANSMITTED))
		{
			status = TWI_Error;
			break;
		}

		//Transmit SLA+R
		status = TWI_Transmit(__TWI_SLA_R(SLA));
		if ((status != MR_SLA_R_TRANSMITTED_ACK) && (status != MR_SLA_R_TRANSMITTED_NACK))
		{
			status = TWI_Error;
			break;
		}

		//Receive DATA
		//Read all the bytes, except the last one, sending ACK signal
		for (i = 0 ; i < (Length - 1) ; i++)
		{
			Packet[i] = TWI_ReceiveACK();
			status = TWI_Status();
			if ((status != MR_DATA_RECEIVED_ACK) && (status != MR_DATA_RECEIVED_NACK))
			{
				status = TWI_Error;
				break;
			}
		}
		//Receive last byte and send NACK signal
		Packet[i] = TWI_ReceiveNACK();
		status = TWI_Status();
		if ((status != MR_DATA_RECEIVED_ACK) && (status != MR_DATA_RECEIVED_NACK))
		{
			status = TWI_Error;
			break;
		}

		//Received successfully
		status = TWI_Ok;
	} 
	while (0);

	//Transmit STOP signal
	TWI_EndTransmission();
	
	return status;
}

//Set self slave address.
void TWI_SetAddress(const uint8_t Address)
{
	//Set TWI slave address (upper 7 bits)
	TWAR = Address<<1;
}
//-----------------------------//