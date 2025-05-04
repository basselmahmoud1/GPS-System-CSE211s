#include "UART_interface.h"
#include "LCD_interface.h"
#include "GPIO_interface.h"
#include "SysTick_interface.h"
#include "../LIB/STD_TYPES.h"

// Struct definition
typedef struct
{
    u8 *name;
    f64 latitude;
    f64 longitude;
    f64 range;
    f64 distance; // Distance ///////////////////////////////////////////////////////////
} Landmark;


// Number of Places ///////////////////////////////////////////////////////
#define EARTH_RADIUS_KM 6371.0
#define M_PI 3.1415926535
#define MAX_LOCATIONS 20


//functions:
void CheckTheNearest(u8 gps_location[100],f64 *currentLat,f64 *currentLon);
f64 convert_to_degrees(f64 latitude);
f64 calculate_distance(f64 lat1, f64 lon1, f64 lat2, f64 lon2);
u8 extract_info(u8 gps_input[100], f64 *latitude, f64 *longitude);