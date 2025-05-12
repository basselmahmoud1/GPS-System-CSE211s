#ifndef GPS_H_
#define GPS_H_

#include "string.h"
#include "stdio.h"
#include "LCD_int.h"
#include "STD_TYPES.h"
#include <math.h>

struct GPRMC_formate
{ 
    f64 Latitude;
    u8 Latit_dir;
    f64 Longitude;
    u8 Long_dir;
};
struct Landmark
{ 
    const char* name;
    f64 Latitude;
    f64 Longitude;
};
#define Token_done   0
#define Recieve_ERR  1

 
#define GPRMC_sen 0 
#define Time_sen 1 
#define Status_sen 2 
#define Latitude_sen 3 
#define latitDir_sen 4 
#define Longitude_sen 5 
#define LongDir_sen 6 

/* Earth radius in meters */
#define EARTH_RADIUS_M 6371000.0
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define Port1_For_Locations PortD // 0->7
#define Port2_For_Locations PortE //0,1

#define Port_Direction_Indication PortE // 2,3,4,5
#define NorthPin Pin2
#define SouthPin Pin3
#define EastPin Pin4
#define WestPin Pin5
#define TotalNumOfPlaces 10

//function
void Bonus_void_CheckDirection(u8 place);

/* Function to parse GPS string */
u8 GPS_u8ParsGpsString(char* gps_string, struct GPRMC_formate* GPS_parsed);

/* Custom string to float conversion function */
f64 GPS_CustomStringToFloat(u8 *str);

/* Distance calculation functions */
//f64 GPS_f64CalculateDistance(f64 lat1, f64 lon1, f64 lat2, f64 lon2);
f64 GPS_f64CalculateDistanceFromCoordinates(const struct GPRMC_formate* point1, 
                                          const struct GPRMC_formate* point2);
f64 GPS_f64ConvertToDecimalDegrees(f64 value, u8 direction);
/* Function to calculate distance between current position and a specific landmark */
f64 GPS_f64CalculateDistanceToLandmark(const struct GPRMC_formate* current_position,
    const struct Landmark* landmark);

/* Function to find the nearest landmark from a given position */
u8 GPS_u8FindNearestLandmark(const struct GPRMC_formate* current_position, 
const struct Landmark* landmarks,
u8 num_landmarks,
struct Landmark* nearest,
f64* distance);

/* Function to display nearest landmark on LCD */
void GPS_voidDisplayNearestLandmark(const struct Landmark* nearest, f64 distance);

/* Function to check current position against landmarks */
void GPS_voidCheckTheNearest(void);
u8* floatToString(f64 num, u32 precision);

#endif