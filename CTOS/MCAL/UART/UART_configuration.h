/*
 * UART_configuration.h
 *
 * Created: 17/04/2025 12:45:05
 *  Author: Khaled Ismail
 */ 


#ifndef UART_CONFIGURATION_H_
#define UART_CONFIGURATION_H_

//////////
//choose UART to be used
/*OPTIONS:
UART_0
UART_1
UART_2
UART_3
UART_4
UART_5
UART_6
UART_7
*/
#define UART_NUM UART_0
/////////////////////////

/////////
/*choose the corresponding port for the UART_NUM
UART_0-->PortA
UART_1-->PortB
UART_2-->PortD
UART_3-->PortC
UART_4-->PortC
UART_5-->PortE
UART_6-->PortD
UART_7-->PortE
*/
#define UART_NUM_Port PortA

#define BaudRate 9600

// deduced from page 916 in the data sheet
#define LineCtrlConfig 0x70

#endif /* UART_CONFIGURATION_H_ */
