/*
Config Pin Description: Configure a single pin on the specified port.
Parameters:

 *  PortId : take the PortID from the enum PORT (ex: PORTA , PORTB ..etc)
 *  PinId  : take the pinID from the enum PIN   (ex: Pin0 , Pin1 ..etc)
 *  PinDir : Take the 2 possible values : GPIO_INPUT or GPIO_OUTPUT
 *  PinValue : Take the 2 possible Values : GPIO_OUT_HIGH or GPIO_OUT_LOW
 *  InputState : Take the 2 possible Values : GPIO_PU (PULL UP) or GPIO_PD (PULL Down)
 *
 * Returns NOERR on success

*/


/*
GetPinValue Description: Get the reading of a specified input pin.
Parameters:

 *  PortId : take the PortID from the enum PORT (ex: PORTA , PORTB ..etc)
 *  PinId  : take the pinID from the enum PIN   (ex: Pin0 , Pin1 ..etc)
 *  InputReading : Take an pointer to the value  passed by the user to get the value of the
 *
 * Returns NOERR on success
*/
