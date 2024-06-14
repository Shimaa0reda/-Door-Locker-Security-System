#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> //to access the registers
#include"std_types.h" // to use words like logic_low


/*GPIO_setupPinDirection
 * description: the fun is responsible for set the dir of the pins input/output
 *input: the port number, pin number and the  wanted direction
 * return void
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num,GPIO_PinDirectionType direction)
{
	//if the entered port number or pin number is greater than the number of total ports and pins then do nothing
	if((port_num>=NUM_OF_PORTS)||(pin_num>=NUM_OF_PINS_PER_PORT))
	{
		/* do nothing */
	}
	/* Setup the pin direction as required */
	else
	{
		switch(port_num)
		{
		case PORTA_ID :
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRA,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRA,pin_num);
			}
			break;
		case PORTB_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRB,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRB,pin_num);
			}
			break;
		case PORTC_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRC,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRC,pin_num);
			}
			break;
		case PORTD_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRD,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRD,pin_num);
			}
			break;
		}
	}
}



/*GPIO_writePin
 * description: the fun is responsible for writing the entered value in the entered pin
 *input: the port number, pin number and the  value to be written in the pin
 * return void
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	//if the entered port number or pin number is greater than the number of total ports and pins then do nothing
	if((port_num>=NUM_OF_PORTS)||(pin_num>=NUM_OF_PINS_PER_PORT))
	{
		/* do nothing */
	}
	/* Write the pin value as required */
	else
	{
		switch(port_num)
		{
		case PORTA_ID :
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTA,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTA,pin_num);
			}
			break;
		case PORTB_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTB,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTB,pin_num);
			}
			break;
		case PORTC_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTC,pin_num);
			}
			break;
		case PORTD_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTD,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTD,pin_num);
			}
			break;
		}
	}
}




/*GPIO_readPin
 * description: the fun is responsible for Read and return the value for the required pin, it should be Logic High or Logic Low.
 *input: the port number and pin number
 * return the value for the required pin
 */

uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	uint8 pin_value=LOGIC_LOW;
	//if the entered port number or pin number is greater than the number of total ports and pins then do nothing
	if((port_num>=NUM_OF_PORTS)||(pin_num>=NUM_OF_PINS_PER_PORT))
	{
		/* do nothing */
	}
	/* return the value of required pin */
	else
	{
		switch(port_num)
		{
		case PORTA_ID :
			if(BIT_IS_SET(PINA,pin_num))
			{
				pin_value= LOGIC_HIGH;
			}
			else
			{
				pin_value= LOGIC_LOW;
			}
			break;
		case PORTB_ID:
			if(BIT_IS_SET(PINB,pin_num))
			{
				pin_value= LOGIC_HIGH;
			}
			else
			{
				pin_value= LOGIC_LOW;
			}
			break;
		case PORTC_ID:
			if(BIT_IS_SET(PINC,pin_num))
			{
				pin_value= LOGIC_HIGH;
			}
			else
			{
				pin_value= LOGIC_LOW;
			}
			break;
		case PORTD_ID:
			if(BIT_IS_SET(PIND,pin_num))
			{
				pin_value= LOGIC_HIGH;
			}
			else
			{
				pin_value= LOGIC_LOW;
			}
			break;
		}
	}
	return pin_value;
}
/*GPIO_setupPortDirection
 * description: the fun is responsible for set the direction of the required port, it should be  input or output.
 *input: the port number and direction
 * return void
 */



void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	//if the entered port number is greater than the number of total ports then do nothing
	if((port_num>=NUM_OF_PORTS))
	{
		/* do nothing */
	}
	/* set the direction of the port as required */
	else
	{
		switch(port_num)
		{
		case PORTA_ID :
			DDRA= direction;
			break;
		case PORTB_ID:
			DDRB= direction;
			break;
		case PORTC_ID:
			DDRC= direction;
			break;
		case PORTD_ID:
			DDRD= direction;
			break;
		}
	}
}

/*GPIO_writePort
 * description: the fun is responsible for writing the entered value in the entered port
 *input: the port number and value
 * return void
 */




void GPIO_writePort(uint8 port_num, uint8 value)
{
	//if the entered port number is greater than the number of total ports then do nothing
	if((port_num>=NUM_OF_PORTS))
	{
		/* do nothing */
	}
	//write the value in the required port
	else
	{
		switch(port_num)
		{
		case PORTA_ID :
			PORTA= value;
			break;
		case PORTB_ID:
			PORTB= value;
			break;
		case PORTC_ID:
			PORTC= value;
			break;
		case PORTD_ID:
			PORTD= value;
			break;
		}
	}
}
/*GPIO_readPort
 * description: the fun is responsible for read and return the value of the required port
 *input: the port number
 * return the value of the required port
 */




uint8 GPIO_readPort(uint8 port_num)
{
	uint8 value = LOGIC_LOW;
	//if the entered port number is greater than the number of total ports then do nothing
	if((port_num>=NUM_OF_PORTS))
	{}
	//read and return the value of the required port
	else
	{
		switch(port_num)
		{
		case PORTA_ID :
			value = PINA;
			break;
		case PORTB_ID:
			value = PINB;
			break;
		case PORTC_ID:
			value = PINC;
			break;
		case PORTD_ID:
			value = PIND;
			break;
		}
	}
	return value;
}
