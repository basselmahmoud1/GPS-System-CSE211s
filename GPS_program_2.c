#include <math.h>
#include <stdio.h>
#include "STD_TYPES.h"

/////NOte -- All printfs will be changed
// #include "BIT_MATH.h"

// Definitions /////////////////////////////////////////////////

#define EARTH_RADIUS_KM 6371.0

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define MAX_LOCATIONS 20

// Conversions /////////////////////////////////////////////////

f64 convert_to_degrees(f64 latitude)
{
    f64 degrees = (s32)(latitude / 100);
    f64 minutes = latitude - (degrees * 100);
    return degrees + (minutes / 60.0);
}

// Convert degrees to radians
f64 deg2rad(f64 degrees)
{
    return degrees * (M_PI / 180.0);
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

// Saving Halls Locations //////////////////////////////////////

f64 saved_latitudes[MAX_LOCATIONS];
f64 saved_longitudes[MAX_LOCATIONS];
s32 saved_count = 0;

void save_location(f64 raw_lat, f64 raw_lon)
{
    if (saved_count < MAX_LOCATIONS)
    {
        saved_latitudes[saved_count] = convert_to_degrees(raw_lat);
        saved_longitudes[saved_count] = convert_to_degrees(raw_lon);
        saved_count++;
    }
    else
    {
        printf("Location storage full!\n");
    }
}

u8 get_saved_location(s32 index, f64 *lat, f64 *lon)
{
    if (index >= 0 && index < saved_count)
    {
        *lat = saved_latitudes[index];
        *lon = saved_longitudes[index];
        return TRUE; // Successfully retrieved
    }
    else
    {
        return FALSE; // Invalid index
    }
}

// Checking What Location we are close to  //////////////////////////////////////
s32 check_nearby_location(f64 current_lat, f64 current_lon, f64 threshold_km)
{
    for (s32 i = 0; i < saved_count; i++)
    {
        f64 dist = calculate_distance(
            current_lat, current_lon,
            saved_latitudes[i], saved_longitudes[i]);

        if (dist <= threshold_km)
        {
            printf("%d!\n", location);
            return i; // Return the index of the matched location
        }
    }

    printf("No nearby saved locations.\n");
    return -1; // No nearby location found
}