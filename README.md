#  GPS Navigation System

##  Overview

This project implements a **GPS navigation system** for embedded devices, providing:

- Location parsing  
- Distance calculation  
- Nearest landmark detection  
- Directional guidance  

It parses NMEA GPS data, calculates distances between coordinates using the Haversine formula, and provides clear navigation messages through an LCD interface.

---

##  Key Features

###  GPS Data Parsing
- Parses NMEA GPRMC sentences to extract latitude, longitude, and direction  
- Validates GPS data integrity

###  Coordinate Calculations
- Converts NMEA format to decimal degrees  
- Calculates distances using the Haversine formula  
- Supports both meter and kilometer distance units

###  Navigation
- Provides compass direction (N, NE, E, SE, S, SW, W, NW)  
- Estimates time to destination based on speed  
- Generates navigation messages

###  Landmark System
- Manages predefined locations  
- Identifies the nearest landmark  
- Displays landmark data on the LCD

###  Hardware Integration
- GPIO configuration for LCD and peripherals  
- UART communication with GPS module  
- LCD display interface for visual feedback

---

##  File Structure

```
├── BIT_MATH.h             # Bit manipulation macros
├── STD_TYPES.h            # Standard data types
├── GPIO_interface.h       # GPIO port/pin configuration interface
├── GPIO_private.h         # GPIO hardware definitions and helpers
├── GPIO_program.c         # GPIO function implementations
├── GPS.h                  # GPS data structures and function declarations
├── GPS_prog.c             # GPS implementation (parsing, calculations)
├── extra.h                # Extended GPS functionality headers
├── extra.c                # Extended GPS feature implementations
├── LCD_config.h           # LCD pin configuration
├── LCD_int.h              # LCD interface
├── systick_interface.h    # Systick timer function declarations
├── systick_program.c      # Systick timer implementation
├── systick_config.h       # Systick configuration settings
├── systick_private.h      # Systick internal definitions
├── UART_interface.h       # UART function declarations
├── UART_program.c         # UART implementation
├── UART_config.h          # UART configuration settings
└── UART_private.h         # UART internal definitions

---

## Usage Examples

### 1. Parsing GPS Data
```c
char gps_string[] = "$GPRMC,202519.00,A,3003.911667,N,3116.805000,E";
struct GPRMC_formate current_position;
u8 status = GPS_u8ParsGpsString(gps_string, &current_position);
```

### 2. Calculating Distance
```c
f64 distance = GPS_f64CalculateDistanceFromCoordinates(&point1, &point2);
```

### 3. Finding Nearest Landmark
```c
struct Landmark nearest;
f64 distance;
GPS_u8FindNearestLandmark(&current_position, landmarks_array, 
                         num_landmarks, &nearest, &distance);
```

### 4. Getting Direction Guidance
```c
u8 direction[20];
GPS_u8GetDirectionGuidance(&current, &destination, direction);
```

### 5. Generating Navigation Message
```c
u8 guidance[100];
GPS_voidGenerateNavigationGuidance(&current, "Home", 1.5, guidance);
```

---

##  Hardware Configuration

### GPIO Setup
- Configure pins with `GPIO_u8ConfigPin()`
- Enable clocks for relevant ports

### LCD Connection
- Configure pins in `LCD_config.h`
- Initialize with `LCD_voidInit()`

### UART Setup
- Set up UART for GPS module communication  
- Use a baud rate compatible with your GPS device

---

##  Customization

### Landmarks
- Modify the landmarks array in `GPS_voidCheckTheNearest()`
- Format: `{"Name", latitude, longitude}` in NMEA format

### Distance Thresholds
- Customize thresholds in `GPS_voidGenerateNavigationGuidance()` for different messaging behaviors

### LCD Display Format
- Edit `GPS_voidDisplayNearestLandmark()` to change LCD text format

---

##  Limitations

- Requires floating-point support on the microcontroller  
- GPS module must output GPRMC NMEA sentences  
- Landmark data is stored in program memory (limited capacity)

---

##  Dependencies

- Standard C libraries (`math.h`, `string.h`)  
- Microcontroller-specific headers  
- LCD driver implementation

---

##  License

This project is open-source. Feel free to use, modify, and distribute it as needed.
