#include "GPS.h"
#include <math.h>
#include "LCD_int.h"
#include "systick_interface.h"
#include "GPIO_interface.h"
#include "UART_interface.h"

u8 GPS_u8ParsGpsString(char *gps_string, struct GPRMC_formate *GPS_parsed)
{
	
    u8 *token;
    u16 counter_msg = 0; // Initialize counter
    u8 checker;

    token = (u8 *)strtok(gps_string, ",");

    while (token != NULL)
    {
        switch (counter_msg)
        {
        case GPRMC_sen:
            checker = strcmp(token, "$GPRMC");
            if (checker != 0)
                return Recieve_ERR;
            break;
        case Status_sen:
            if (token[0] != 'A')
                return Recieve_ERR;
            break;
        case Latitude_sen:
					
            GPS_parsed->Latitude = GPS_CustomStringToFloat(token);
				
            break;
        case latitDir_sen:
            GPS_parsed->Latit_dir = token[0];
            break;
        case Longitude_sen:
            GPS_parsed->Longitude = GPS_CustomStringToFloat(token);
            break;
        case LongDir_sen:
            GPS_parsed->Long_dir = token[0];
            break;
        }
        token = (u8 *)strtok(NULL, ",");
				
        counter_msg++;
    }

    // Return success if we've processed at least the minimum required fields
    return (counter_msg >= LongDir_sen) ? Token_done : Recieve_ERR;
}

f64 GPS_CustomStringToFloat(u8 *str)
{
    f64 result = 0.0;
    f64 decimalPlace = 0.1;
    u8 decimalFound = 0;

    while (*str)
    {
        if (*str == '.')
        {
            decimalFound = 1;
        }
        else if (*str >= '0' && *str <= '9')
        {
            if (!decimalFound)
            {
                result = (result * 10) + (*str - '0');
            }
            else
            {
                result += (*str - '0') * decimalPlace;
                decimalPlace *= 0.1;
            }
        }
        str++;
    }

    return result;
}

/**
 * GPS_f64CalculateDistance - Calculate the distance between two GPS coordinates
 * @param lat1: Latitude of first point in decimal degrees
 * @param lon1: Longitude of first point in decimal degrees
 * @param lat2: Latitude of second point in decimal degrees
 * @param lon2: Longitude of second point in decimal degrees
 * @return: Distance between points in meters
 *
 * Uses the Haversine formula to calculate great-circle distance between two points
 */
/*f64 GPS_f64CalculateDistance(f64 lat1, f64 lon1, f64 lat2, f64 lon2)
{
    

    return distance;
}
*/
/**
 * GPS_f64CalculateDistanceFromCoordinates - Calculate distance using GPRMC_formate structures
 * @param point1: Pointer to first GPS coordinate structure
 * @param point2: Pointer to second GPS coordinate structure
 * @return: Distance between points in meters
 *
 * This function handles the conversion from NMEA format and direction indicators
 */
f64 GPS_f64CalculateDistanceFromCoordinates(const struct GPRMC_formate *point1,
                                            const struct GPRMC_formate *point2)
{
    f64 lat1, lon1, lat2, lon2;
    f64 lat1_rad, lon1_rad, lat2_rad, lon2_rad;
    f64 dlat, dlon;
    f64 a, c, distance;

    lat1 = GPS_f64ConvertToDecimalDegrees(point1->Latitude, point1->Latit_dir);
    lon1 = GPS_f64ConvertToDecimalDegrees(point1->Longitude, point1->Long_dir);

    lat2 = GPS_f64ConvertToDecimalDegrees(point2->Latitude, point2->Latit_dir);
    lon2 = GPS_f64ConvertToDecimalDegrees(point2->Longitude, point2->Long_dir);

    lat1_rad = lat1 * M_PI / 180.0;
    lon1_rad = lon1 * M_PI / 180.0;
    lat2_rad = lat2 * M_PI / 180.0;
    lon2_rad = lon2 * M_PI / 180.0;

    dlat = fabs(lat2_rad - lat1_rad);
    dlon = fabs(lon2_rad - lon1_rad);

    // Updated Haversine using powf and atanf
    a = powf(sinf(dlat / 2.0), 2) +
        cosf(lat1_rad) * cosf(lat2_rad) * powf(sinf(dlon / 2.0), 2);

    c = 2 * atanf(sqrtf(a) / sqrtf(1.0 - a));

    distance =fabs( EARTH_RADIUS_M * c);

    return distance;
}


/**
 * GPS_f64ConvertToDecimalDegrees - Convert NMEA format to decimal degrees
 * @param value: Coordinate value in NMEA format (DDMM.MMMM)
 * @param direction: Direction character ('N', 'S', 'E', or 'W')
 * @return: Coordinate in decimal degrees
 */
f64 GPS_f64ConvertToDecimalDegrees(f64 value, u8 direction)
{
    /* Extract degrees and minutes from NMEA format */
    int degrees = (int)(value / 100);
    f64 minutes = value - (degrees * 100);

    /* Convert to decimal degrees */
    f64 decimal_degrees = degrees + (minutes / 60.0);

    /* Apply sign based on direction */
    if (direction == 'S' || direction == 'W')
    {
        decimal_degrees = -decimal_degrees;
    }

    return decimal_degrees;
}

/**
 * GPS_f64CalculateDistanceToLandmark - Calculate distance between current position and a specific landmark
 * @param current_position: Pointer to current GPS position
 * @param landmark: Pointer to landmark
 * @return: Distance in meters, or -1.0 if error
 */
f64 GPS_f64CalculateDistanceToLandmark(const struct GPRMC_formate *current_position,
                                       const struct Landmark *landmark)
{
    // Create temporary GPRMC_formate structure for the landmark
    struct GPRMC_formate landmark_position;
    
    if (current_position == NULL || landmark == NULL)
    {
        return -1.0; // Error code
    }
		
    // Convert landmark coordinates to GPRMC format
    landmark_position.Latitude = landmark->Latitude;
    landmark_position.Latit_dir = 'N'; // Assuming all landmarks use the same hemisphere
    landmark_position.Longitude = landmark->Longitude;
    landmark_position.Long_dir = 'E'; // Assuming all landmarks use the same hemisphere
		
    // Calculate and return distance
    return GPS_f64CalculateDistanceFromCoordinates(current_position, &landmark_position);
}

/**
 * GPS_u8FindNearestLandmark - Find the nearest landmark from current position
 * @param current_position: Pointer to current GPS position
 * @param landmarks: Array of landmarks to check
 * @param num_landmarks: Number of landmarks in the array
 * @param nearest: Pointer to store nearest landmark info
 * @param distance: Pointer to store distance to nearest landmark
 * @return: Token_done if successful, Recieve_ERR otherwise
 */
u8 GPS_u8FindNearestLandmark(const struct GPRMC_formate *current_position,
                             const struct Landmark *landmarks,
                             u8 num_landmarks,
                             struct Landmark *nearest,
                             f64 *distance)
{
    u8 i;
    f64 min_distance = -1; // Initialize to an invalid value
    u8 nearest_index = 0;
    f64 curr_distance;
    // Create temporary GPRMC_formate structures for distance calculation
    struct GPRMC_formate landmark_position;

    if (current_position == NULL || landmarks == NULL || num_landmarks == 0 ||
        nearest == NULL || distance == NULL)
    {
        return Recieve_ERR;
    }



    // Find the nearest landmark
    for (i = 0; i < num_landmarks; i++)
    {
        // Calculate distance using our new function
        curr_distance = GPS_f64CalculateDistanceToLandmark(current_position, &landmarks[i]);

        // Update nearest if this is closer or first check
        if (min_distance < 0 || curr_distance < min_distance)
        {
            min_distance = curr_distance;
            nearest_index = i;
        }
    }
		
    // Store the result
    *nearest = landmarks[nearest_index];
    *distance = min_distance;

    return Token_done;
}

/**
 * GPS_voidDisplayNearestLandmark - Display nearest landmark info on LCD
 * @param nearest: Pointer to nearest landmark
 * @param distance: Distance to the landmark in meters
 */
void GPS_voidDisplayNearestLandmark(const struct Landmark *nearest, f64 distance)
{
    u8 distance_str[10];
    LCD_voidClearScreen();

    // Display landmark name
    LCD_voidMoveCursor(0, 0);
    LCD_voidSendString("Nearest: ");
    LCD_voidSendString((u8 *)nearest->name);

    // Display distance in meters
    LCD_voidMoveCursor(1, 0);
    LCD_voidSendString("Distance: ");

    // Convert distance to string
    
    LCD_voidSendString(floatToString(distance,3));
}

/**
 * GPS_voidCheckTheNearest - Check current position against landmarks
 * Assumes a global array of landmarks is defined
 */
void GPS_voidCheckTheNearest(void)
{
    // Global landmarks array for consistent access
    static const struct Landmark landmarks[] = {
        {"Hall A", 3003.863, 3116.820},
        {"Hall C", 3003.837, 3116.824},
        {"Gate 3", 3003.840, 3116.672},
        {"Fountain", 3003.941, 3116.703},
        {"Gate 2", 3003.883, 3116.657},
        {"Gate 6", 3003.894, 3116.817},
        {"Credit", 3003.823, 3116.703},
        {"Football Stage", 3003.843, 3116.749},
        {"Acoustics Building", 3003.941, 3116.784},
        {"Civil Building", 3003.861, 3116.675}};
    u8 num_landmarks = 10 ;
    u8 state;
    struct Landmark nearest;
    f64 distance;
    // Get current GPS position
    u8 gps_string[100];
    struct GPRMC_formate current_position;
			u8 test[10];

    // In a real implementation, you would read from GPS module
    //////////////////////////////////////////////////////////////////////////////////
    UART1_voidInitialize();
				UART1_voidReceiveString(gps_string);
					UART0_voidSendString(gps_string);
				UART0_voidSendString("/n/r");
		// For testing, we can use a fixed position
    //strcpy(gps_string, "$GPRMC,202519.00,A,3003.911667,N,3116.805000,E");
																																							
    // Parse GPS data
    state = GPS_u8ParsGpsString(gps_string, &current_position);
		UART0_voidSendString("\n\r");
				/*UART0_voidSendString(floatToString(current_position.Latitude,3));
					UART0_voidSendString("\n\r");
					UART0_voidSendString(floatToString(current_position.Longitude,3));
					UART0_voidSendString("\n\r");
					UART0_voidSendByte(current_position.Latit_dir);
					UART0_voidSendString("\n\r");
					UART0_voidSendByte(current_position.Long_dir);
					UART0_voidSendString("\n\r");
					UART0_voidSendString("\n\r");
					UART0_voidSendString("State : ");
					UART0_voidSendString(floatToString(state,0));
					UART0_voidSendString("\n\r");
				*/
    if (state == Token_done)
    {
        // Find nearest landmark
        

        state = GPS_u8FindNearestLandmark(&current_position, landmarks, num_landmarks, &nearest, &distance);
																																																										
        if (state == Token_done)
        {
            // Display on LCD
            GPS_voidDisplayNearestLandmark(&nearest, distance);
        }
        else
        {
					GPS_voidDisplayNearestLandmark(&nearest, distance);
            // Error handling
            /*LCD_voidClearScreen();
            LCD_voidMoveCursor(0, 0);
            LCD_voidSendString("Error finding");
            LCD_voidMoveCursor(1, 0);
            LCD_voidSendString("nearest landmark");
        */
					}
    }
    else
    {
        GPS_voidDisplayNearestLandmark(&nearest, distance);
			// Error handling
        /*LCD_voidClearScreen();
        LCD_voidMoveCursor(0, 0);
        LCD_voidSendString("Error parsing");
        LCD_voidMoveCursor(1, 0);
        LCD_voidSendString("GPS data");
    */
			}
}

u8* floatToString(f64 num, u32 precision) {
    static u8 buffer[32];  // Adjust size as needed
    u32 int_part;
    f64 frac_part;
    u32 i = 0;
    u32 j;
    u32 digit;
    u32 digits[10], digit_count = 0;

    // Handle negative numbers
    if (num < 0) {
        buffer[i++] = '-';
        num = -num;
    }

    int_part = (u32)num;
    frac_part = num - int_part;

    // Convert integer part
    if (int_part == 0) {
        buffer[i++] = '0';
    } else {
        while (int_part > 0) {
            digits[digit_count++] = int_part % 10;
            int_part /= 10;
        }
        // Safe reverse loop for unsigned int
        for (j = digit_count; j-- > 0;) {
            buffer[i++] = '0' + digits[j];
        }
    }

    buffer[i++] = '.';

    // Convert fractional part
    for (j = 0; j < precision; j++) {
        frac_part *= 10;
        digit = (u32)frac_part;
        buffer[i++] = '0' + digit;
        frac_part -= digit;
    }
		
    buffer[i] = '\0';
    return buffer;
}
///////////////////////////////////////////////////////////////////////////////////////
void Bonus_void_CheckDirection(u8 place){
	    // Global landmarks array for consistent access

  f64 lat_diff,long_diff,curr_lat,curr_long;
  u8 *gps_string;
	
	struct GPRMC_formate GPS_parsed;
    // Global landmarks array for consistent access
    static const struct Landmark landmarks[] = {
        {"Hall A", 3003.863, 3116.820},
        {"Hall C", 3003.837, 3116.824},
        {"Gate 3", 3003.840, 3116.672},
        {"Fountain", 3003.941, 3116.703},
        {"Gate 2", 3003.883, 3116.657},
        {"Gate 6", 3003.894, 3116.817},
        {"Credit", 3003.823, 3116.703},
        {"Football Stage", 3003.843, 3116.749},
        {"Acoustics Building", 3003.941, 3116.784},
        {"Civil Building", 3003.861, 3116.675}};
				
				while(GPS_u8ParsGpsString(gps_string,&GPS_parsed)==Recieve_ERR)	UART1_voidReceiveString(gps_string);
				
        lat_diff=GPS_f64ConvertToDecimalDegrees(landmarks[place].Latitude,'N')-GPS_f64ConvertToDecimalDegrees(GPS_parsed.Latitude,GPS_parsed.Latit_dir) ;
        long_diff=GPS_f64ConvertToDecimalDegrees(landmarks[place].Longitude,'E')-GPS_f64ConvertToDecimalDegrees(GPS_parsed.Longitude,GPS_parsed.Long_dir);
                                                                    
        if(lat_diff>0 && long_diff>0)
				{
				GPIO_u8ConfigPin(Port_Direction_Indication,EastPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0);  //indication to go east
        GPIO_u8ConfigPin(Port_Direction_Indication,NorthPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0); //indication to go north
        Systick_voidDelay_ms(2000);
        GPIO_u8SetPinValue(Port_Direction_Indication,NorthPin,GPIO_OUT_LOW);
				GPIO_u8SetPinValue(Port_Direction_Indication,EastPin,GPIO_OUT_LOW);
				}
        else if(lat_diff<0 && long_diff>0)
				{
				GPIO_u8ConfigPin(Port_Direction_Indication,EastPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0);  //indication to go east
        GPIO_u8ConfigPin(Port_Direction_Indication,SouthPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0);//indication to go south
        Systick_voidDelay_ms(2000);
        GPIO_u8SetPinValue(Port_Direction_Indication,SouthPin,GPIO_OUT_LOW);
				GPIO_u8SetPinValue(Port_Direction_Indication,EastPin,GPIO_OUT_LOW);
				}
        else if(long_diff<0 && lat_diff>0)
				{
				GPIO_u8ConfigPin(Port_Direction_Indication,NorthPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0); //indication to go north
			  GPIO_u8ConfigPin(Port_Direction_Indication,WestPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0);  //indication to go east
        Systick_voidDelay_ms(2000);
        GPIO_u8SetPinValue(Port_Direction_Indication,WestPin,GPIO_OUT_LOW);
				GPIO_u8SetPinValue(Port_Direction_Indication,NorthPin,GPIO_OUT_LOW);
				}
        else if(long_diff<0 && lat_diff<0)
				{
				GPIO_u8ConfigPin(Port_Direction_Indication,SouthPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0);//indication to go south
        GPIO_u8ConfigPin(Port_Direction_Indication,WestPin,GPIO_OUTPUT,GPIO_OUT_HIGH,0);					//indication to go west
        Systick_voidDelay_ms(2000);
				GPIO_u8SetPinValue(Port_Direction_Indication,WestPin,GPIO_OUT_LOW);	
				GPIO_u8SetPinValue(Port_Direction_Indication,SouthPin,GPIO_OUT_LOW);
				}
			}
			