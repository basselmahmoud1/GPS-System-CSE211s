# 📍 GPS Navigation System

## 🚀 Overview

This project implements a **GPS navigation system** for embedded systems. It provides:

- Real-time GPS data parsing  
- Accurate distance calculation  
- Nearest landmark detection  
- Directional navigation and guidance  

It uses NMEA-formatted GPS data and the Haversine formula for geographical calculations, providing clear visual feedback via an LCD module.

---

## 🔑 Key Features

### 🛰️ GPS Data Parsing
- Parses **GPRMC NMEA sentences**  
- Extracts latitude, longitude, speed, and status  
- Validates GPS sentence integrity  

### 📍 Coordinate & Distance Calculations
- Converts NMEA to **decimal degrees**  
- Calculates distance using the **Haversine formula**  
- Supports output in meters or kilometers  

### 🧭 Navigation & Guidance
- Determines compass direction (N, NE, E, etc.)  
- Estimates time to destination based on speed  
- Displays human-readable **navigation messages**  

### 🗺️ Landmark System
- Supports an array of **predefined landmarks**  
- Identifies and displays the **nearest landmark**  
- Allows for easy modification and expansion  

### ⚙️ Hardware Integration
- GPIO configuration for LCD and peripherals  
- UART communication with GPS module  
- LCD feedback via 16x2 display or similar  

---

## 📁 File Structure

```
├── APP/
│   └── main.c                   # Application entry point
├── MCAL/
│   ├── GPIO/
│   │   ├── GPIO_interface.h     # GPIO interface
│   │   ├── GPIO_private.h       # Internal GPIO definitions
│   │   └── GPIO_program.c       # GPIO logic
│   ├── UART/
│   │   ├── UART_interface.h     # UART API
│   │   ├── UART_private.h
│   │   ├── UART_config.h
│   │   └── UART_program.c
│   └── SYSTICK/
│       ├── systick_interface.h
│       ├── systick_private.h
│       ├── systick_config.h
│       └── systick_program.c
├── HAL/
│   ├── GPS/
│   │   ├── GPS.h                # GPS API
│   │   ├── GPS_prog.c           # Parsing & math
│   │   ├── extra.h              # Extended GPS features
│   │   └── extra.c
│   ├── LCD/
│   │   ├── LCD_int.h
│   │   └── LCD_config.h
│   └── BUZZER/
│       └── buzzer.h
├── LIB/
│   ├── BIT_MATH.h              # Bit macros
│   └── STD_TYPES.h             # Standard types
```

---

## 🧪 Usage Examples

### 1. 📡 Parsing GPS Data
```c
char gps_string[] = "$GPRMC,202519.00,A,3003.911667,N,3116.805000,E";
struct GPRMC_formate current_position;
u8 status = GPS_u8ParsGpsString(gps_string, &current_position);
```

### 2. 🧮 Calculating Distance
```c
f64 distance = GPS_f64CalculateDistanceFromCoordinates(&point1, &point2);
```

### 3. 📌 Finding Nearest Landmark
```c
struct Landmark nearest;
f64 distance;
GPS_u8FindNearestLandmark(&current_position, landmarks_array, 
                           num_landmarks, &nearest, &distance);
```

### 4. 🧭 Getting Direction Guidance
```c
u8 direction[20];
GPS_u8GetDirectionGuidance(&current, &destination, direction);
```

### 5. 🗣️ Generating Navigation Message
```c
u8 guidance[100];
GPS_voidGenerateNavigationGuidance(&current, "Home", 1.5, guidance);
```

---

## 🛠️ Hardware Configuration

### 📌 GPIO
- Configure with `GPIO_u8ConfigPin()`
- Enable peripheral clocks as needed

### 📺 LCD
- Set pin mapping in `LCD_config.h`
- Initialize using `LCD_voidInit()`

### 📡 UART
- Connect GPS to UART pins  
- Set baud rate to match GPS module (typically 9600)

---

## 🔧 Customization

### ➕ Landmarks
- Modify the landmarks array in `GPS_voidCheckTheNearest()`  
- Format: `{"Name", latitude, longitude}`

### 🧾 Distance Thresholds
- Edit `GPS_voidGenerateNavigationGuidance()` for different distance message rules

### 💬 LCD Display Format
- Change display text in `GPS_voidDisplayNearestLandmark()` as needed

---

## ⚠️ Limitations

- Floating-point support required  
- Only supports GPRMC NMEA sentences  
- Limited landmark storage (program memory)

---

## 📦 Dependencies

- Standard C libraries: `math.h`, `string.h`  
- Microcontroller headers  
- LCD driver implementation

---

## 📄 License

This project is open-source. Feel free to use, modify, and distribute.
 
