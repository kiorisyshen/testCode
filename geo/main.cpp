#include <iostream>
#include "spa.h"

int main() {
    spa_data dataStruct;

    dataStruct.year          = 2019;
    dataStruct.month         = 11;
    dataStruct.day           = 21;
    dataStruct.hour          = 9;
    dataStruct.minute        = 54;
    dataStruct.second        = 0;
    dataStruct.delta_t       = 32.184;
    dataStruct.timezone      = 0;
    dataStruct.longitude     = 0.441425;
    dataStruct.latitude      = 51.40081;
    dataStruct.elevation     = 12;
    dataStruct.pressure      = 1000;
    dataStruct.temperature   = 2;
    dataStruct.slope         = 0;
    dataStruct.azm_rotation  = 0;
    dataStruct.atmos_refract = 0.5667;
    dataStruct.function      = 0;

    spa_calculate(&dataStruct);

    std::cout << "Azimuth: " << dataStruct.azimuth << std::endl;
    std::cout << "Azimuth180: " << dataStruct.azimuth180 << std::endl;

    return 0;
}

// int year;            // 4-digit year,    valid range: -2000 to 6000, error code: 1
// int month;           // 2-digit month,         valid range: 1 to 12, error code: 2
// int day;             // 2-digit day,           valid range: 1 to 31, error code: 3
// int hour;            // Observer local hour,   valid range: 0 to 24, error code: 4
// int minute;          // Observer local minute, valid range: 0 to 59, error code: 5
// int second;          // Observer local second, valid range: 0 to 59, error code: 6

// float delta_t;       // Difference between earth rotation time and terrestrial time
//                         //     (from observation)
//                         // valid range: -8000 to 8000 seconds, error code: 7

// float timezone;      // Observer time zone (negative west of Greenwich)
//                         // valid range: -12   to   12 hours,   error code: 8

// float longitude;     // Observer longitude (negative west of Greenwich)
//                         // valid range: -180  to  180 degrees, error code: 9

// float latitude;      // Observer latitude (negative south of equator)
//                         // valid range: -90   to   90 degrees, error code: 10

// float elevation;     // Observer elevation [meters]
//                         // valid range: -6500000 or higher meters,    error code: 11

// float pressure;      // Annual average local pressure [millibars]
//                         // valid range:    0 to 5000 millibars,       error code: 12

// float temperature;   // Annual average local temperature [degrees Celsius]
//                         // valid range: -273 to 6000 degrees Celsius, error code; 13

// float slope;         // Surface slope (measured from the horizontal plane)
//                         // valid range: -360 to 360 degrees, error code: 14

// float azm_rotation;  // Surface azimuth rotation (measured from south to projection of
//                         //     surface normal on horizontal plane, negative west)
//                         // valid range: -360 to 360 degrees, error code: 15

// float atmos_refract; // Atmospheric refraction at sunrise and sunset (0.5667 deg is typical)
//                         // valid range: -5   to   5 degrees, error code: 16

// int function;        // Switch to choose functions for desired output (from enumeration)