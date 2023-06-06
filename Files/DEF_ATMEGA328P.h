
#define DDRBbits (*(DDBbits)_SFR_MEM_ADDR(DDRB))
#define PORTBbits (*(POBbits)_SFR_MEM_ADDR(PORTB))
#define PINBbits (*(PIBbits)_SFR_MEM_ADDR(PINB))

#define DDRCbits (*(DDCbits)_SFR_MEM_ADDR(DDRC))
#define PORTCbits (*(POCbits)_SFR_MEM_ADDR(PORTC))
#define PINCbits (*(PICbits)_SFR_MEM_ADDR(PINC))

#define DDRDbits (*(DDDbits)_SFR_MEM_ADDR(DDRD))
#define PORTDbits (*(PODbits)_SFR_MEM_ADDR(PORTD))
#define PINDbits (*(PIDbits)_SFR_MEM_ADDR(PIND))


/********************************************
---------- Definición de PUERTO B -----------
*********************************************/

typedef struct DDBbits_t
{
	unsigned DDRB0  :1;
	unsigned DDRB1  :1;
	unsigned DDRB2  :1;
	unsigned DDRB3  :1;
	unsigned DDRB4  :1;
	unsigned DDRB5  :1;
	unsigned DDRB6  :1;
	unsigned DDRB7  :1;
	
}volatile *DDBbits;


typedef struct PBbits_t
{
	unsigned PB0_  :1;
	unsigned PB1_  :1;
	unsigned PB2_  :1;
	unsigned PB3_  :1;
	unsigned PB4_  :1;
	unsigned PB5_  :1;
	unsigned PB6_  :1;
	unsigned PB7_  :1;
	
}volatile *POBbits;

typedef struct PINBbits_t
{
	unsigned PINB0_  :1;		
	unsigned PINB1_  :1;		
	unsigned PINB2_  :1;
	unsigned PINB3_  :1;		
	unsigned PINB4_  :1;		
	unsigned PINB5_  :1;
	unsigned PINB6_  :1;
	unsigned PINB7_  :1;	
	
}volatile *PIBbits;

/********************************************
---------- Definición de PUERTO C -----------
*********************************************/

typedef struct DDCbits_t
{
	unsigned DDRC0  :1;
	unsigned DDRC1  :1;
	unsigned DDRC2  :1;
	unsigned DDRC3  :1;
	unsigned DDRC4  :1;
	unsigned DDRC5  :1;
	unsigned DDRC6  :1;
	unsigned DDRC7  :1;
	
}volatile *DDCbits;

typedef struct PCbits_t
{
	unsigned PC0_  :1;
	unsigned PC1_  :1;
	unsigned PC2_  :1;
	unsigned PC3_  :1;
	unsigned PC4_  :1;
	unsigned PC5_  :1;
	unsigned PC6_  :1;
	unsigned PC7_  :1;
	
}volatile *POCbits;

typedef struct PINCbits_t
{
	unsigned PINC0_  :1;
	unsigned PINC1_  :1;
	unsigned PINC2_  :1;
	unsigned PINC3_  :1;
	unsigned PINC4_  :1;
	unsigned PINC5_  :1;
	unsigned PINC6_  :1;
	unsigned PINC7_  :1;
	
}volatile *PICbits;

/********************************************
---------- Definición de PUERTO D -----------
*********************************************/

typedef struct DDDbits_t
{
	unsigned DDRD0  :1;
	unsigned DDRD1  :1;
	unsigned DDRD2	:1;
	unsigned DDRD3  :1;
	unsigned DDRD4  :1;
	unsigned DDRD5	:1;
	unsigned DDRD6	:1;
	unsigned DDRD7	:1;
	
}volatile *DDDbits;

typedef struct PDbits_t
{
	unsigned PD0_  :1;
	unsigned PD1_  :1;
	unsigned PD2_  :1;
	unsigned PD3_  :1;
	unsigned PD4_  :1;
	unsigned PD5_  :1;
	unsigned PD6_  :1;
	unsigned PD7_  :1;
	
}volatile *PODbits;

typedef struct PINDbits_t
{
	unsigned PIND0_  :1;
	unsigned PIND1_  :1;
	unsigned PIND2_  :1;
	unsigned PIND3_  :1;
	unsigned PIND4_  :1;
	unsigned PIND5_  :1;
	unsigned PIND6_  :1;
	unsigned PIND7_  :1;
	
}volatile *PIDbits;