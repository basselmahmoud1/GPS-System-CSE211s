#include <math.h>
#include <stdio.h>
#include "../LIB/STD_TYPES.h"
#include "gps_interface.h"
// Uniinatialized ///////////////////////////////////////////////////////////////////////////
Landmark landmarks[] = {
    {.name = "Hall A", .latitude = 0.0, .longitude = 0.0, .range = 15.0, .distance = 0.0},
    {.name = "Hall C", .latitude = 0.0, .longitude = 0.0, .range = 15.0, .distance = 0.0},
    {.name = "Library", .latitude = 0.0, .longitude = 0.0, .range = 25.0, .distance = 0.0},
    {.name = "Main", .latitude = 0.0, .longitude = 0.0, .range = 20.0, .distance = 0.0},
    {.name = "Fountain", .latitude = 0.0, .longitude = 0.0, .range = 10.0, .distance = 0.0},
    {.name = "Gate 2", .latitude = 0.0, .longitude = 0.0, .range = 30.0, .distance = 0.0},
    {.name = "Gate 6", .latitude = 0.0, .longitude = 0.0, .range = 30.0, .distance = 0.0},
    {.name = "Credit", .latitude = 0.0, .longitude = 0.0, .range = 10.0, .distance = 0.0},
    {.name = "Modargat", .latitude = 0.0, .longitude = 0.0, .range = 10.0, .distance = 0.0},
    {.name = "Loban", .latitude = 0.0, .longitude = 0.0, .range = 10.0, .distance = 0.0},
    {.name = "Civil", .latitude = 0.0, .longitude = 0.0, .range = 10.0, .distance = 0.0}};
 //function to extract latt,long
    u8 extract_info(u8 gps_input[100], f64 *Latitude, f64 *longitude)
    {
    u8 copy_message[100];
    u16 message_count = 0;
    u8 *message;
    u8 activate = 0, lat_direction = 0, long_direction = 0;
    
    // Correct copying
    strncpy((char*)copy_message, (char*)gps_input, sizeof(copy_message) - 1);
    copy_message[sizeof(copy_message) - 1] = '\0';
    
    message = strtok((char*)copy_message, ",");
    
    while (message != NULL) {
    switch (message_count) {
    case 1: // 'A'
    activate = message[0];
    if (activate == 'A') return 1;
    break;
    case 2:
    *Latitude = convert_to_degrees(atof(message));
    break;
    case 3:
    lat_direction = message[0];
    break;
    case 4:
    *longitude = convert_to_degrees(atof(message));
    break;
    case 5:
    long_direction = message[0];
    break;
    }
    message = strtok(NULL, ",");
    message_count++;
    }
    
    if (lat_direction == 'S') *latitude *= -1;
    if (long_direction == 'W') *longitude *= -1;
    } 
f64 convert_to_degrees(f64 latitude)
{
    // ddmmm.mm
    f64 degrees = (s32)(latitude / 100);
    f64 minutes = latitude - (degrees * 100);
    return degrees + (minutes / 60.0);
}

// Convert degrees to radians
f64 deg2rad(f64 degrees)
{
    return convert_to_degrees(degrees) * (M_PI / 180.0);
}

// Calculating distance between two points on Earth's sphere ///
f64 calculate_distance(f64 lat1, f64 lon1, f64 lat2, f64 lon2)
{
    // Convert latitude and longitude from degrees to radians
    lat1 = deg2rad(lat1);
    lon1 = deg2rad(lon1);
    lat2 = deg2rad(lat2);
    lon2 = deg2rad(lon2);

    // Differences
    f64 dlat = lat2 - lat1;
    f64 dlon = lon2 - lon1;

    // Haversine formula
    f64 a = sin(dlat / 2) * sin(dlat / 2) +
            cos(lat1) * cos(lat2) *
                sin(dlon / 2) * sin(dlon / 2);

    f64 c = 2 * atan2(sqrt(a), sqrt(1 - a));

    // Distance in kilometers
    return EARTH_RADIUS_KM * c;
}


    void CheckTheNearest(u8 gps_location[100],f64 *currentLat,f64 *currentLon){
        UART0_voidReceiveString(gps_location);

        if (extract_info(gps_location[100], &currentLat, &currentLon) == 1)
        {
            u8 insideRange = 0;
            u8 nearestIndex = -1;
            f64 minimum_distance = 100000.0;
            u8 LANDMARK_COUNT =(sizeof(landmarks) / sizeof(landmarks[0]));
            for (int i = 0; i < LANDMARK_COUNT; i++)
            {
                landmarks[i].distance = GPS_f32CalculateDistance(
                    currentLat, currentLon,
                    landmarks[i].latitude, landmarks[i].longitude);

                if (landmarks[i].distance < minimum_distance)
                {
                    minimum_distance = landmarks[i].distance;
                    nearestIndex = i;
                }
            }

            if (minimum_distance < landmarks[nearestIndex].range)
            {
                LCD_voidClearScreen();
                LCD_voidSendString("You are at:");
                LCD_voidMoveCursor(1, 0);
                LCD_voidSendString(landmarks[nearestIndex].name);
                insideRange = 1;
            }

            if (!insideRange && nearestIndex != -1)
            {
                LCD_voidClearScreen();
                LCD_voidSendString("Nearest:");
                LCD_voidMoveCursor(1, 0);
                LCD_voidSendString(landmarks[nearestIndex].name);
            }
        }

        Systick_voidDelay_ms(1000); // wait 1 second before next GPS read
    }