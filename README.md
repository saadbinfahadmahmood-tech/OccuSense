# Smart Occupancy Monitoring System

A real-time occupancy monitoring system built using an ESP32 microcontroller, dual IR sensors, and a TM1637 display. The system automatically tracks the number of people entering and exiting a room by detecting the order in which sensors are triggered and applying Finite State Machine (FSM) logic.

---

## Project Overview

Monitoring room occupancy is important for classrooms, laboratories, libraries, offices, and smart buildings. Manual counting methods are often inaccurate and impractical.

This project solves the problem by using two IR sensors positioned at a doorway to detect movement direction:

* IR1 → IR2 = Entry
* IR2 → IR1 = Exit

The occupancy count is displayed in real time on a TM1637 4-digit display.

---

## Features

* Real-time occupancy counting
* Entry and exit detection
* Finite State Machine (FSM) implementation
* Timeout protection against false counts
* Occupancy limit monitoring
* Visual room-status indication using LEDs
* ESP32-based implementation
* Low-cost and scalable design

---

## Hardware Components

| Component              | Quantity    |
| ---------------------- | ----------- |
| ESP32-WROOM-32         | 1           |
| IR Obstacle Sensors    | 2           |
| TM1637 4-Digit Display | 1           |
| Red LED                | 1           |
| Green LED              | 1           |
| 220Ω Resistors         | 2           |
| Breadboard             | 1           |
| Jumper Wires           | As Required |
| USB Cable              | 1           |

---

## System Architecture

### Entry Detection

1. Person crosses IR1.
2. Person crosses IR2.
3. Occupancy count increases by 1.

### Exit Detection

1. Person crosses IR2.
2. Person crosses IR1.
3. Occupancy count decreases by 1.

### Timeout Protection

If the second sensor is not triggered within 2 seconds, the system resets to the idle state without changing the count.

---

## Finite State Machine Logic

### State 0 – Idle

Waiting for sensor activity.

### State 1 – Possible Entry

IR1 triggered first.

Expected:
IR1 → IR2

Action:
Increment count.

### State 2 – Possible Exit

IR2 triggered first.

Expected:
IR2 → IR1

Action:
Decrement count.

---

## Circuit Connections

### TM1637 Display

| TM1637 Pin | ESP32 Pin |
| ---------- | --------- |
| CLK        | GPIO 21   |
| DIO        | GPIO 22   |
| VCC        | 3.3V      |
| GND        | GND       |

### IR Sensors

| Sensor  | ESP32 Pin |
| ------- | --------- |
| IR1 OUT | GPIO 34   |
| IR2 OUT | GPIO 35   |
| VCC     | 3.3V      |
| GND     | GND       |

### LEDs

| LED       | ESP32 Pin |
| --------- | --------- |
| Red LED   | GPIO 26   |
| Green LED | GPIO 27   |

---

## Software Setup

### Step 1: Install Arduino IDE

Download and install Arduino IDE.

### Step 2: Install ESP32 Board Package

1. Open Arduino IDE.
2. Go to Preferences.
3. Add ESP32 Board Manager URL.
4. Install ESP32 boards.

### Step 3: Install TM1637 Library

Library Manager → Search:

TM1637Display

Install the library.

### Step 4: Clone Repository

```bash
git clone https://github.com/yourusername/smart-occupancy-monitoring-system.git
```

### Step 5: Upload Code

1. Connect ESP32.
2. Select the correct COM port.
3. Select ESP32 Dev Module.
4. Upload the code.

---

## Demonstration

### Scenario 1

IR1 → IR2

Output:

```text
ENTRY
Count +1
```

### Scenario 2

IR2 → IR1

Output:

```text
EXIT
Count -1
```

### Scenario 3

IR1 only

Output:

```text
Timeout
No Change
```

---

## Testing Results

The system was tested against multiple scenarios including:

* Entry detection
* Exit detection
* Timeout conditions
* Occupancy limit detection
* Underflow prevention

All defined test cases were successfully passed.

---

## Future Improvements

* Cloud dashboard integration
* Wi-Fi monitoring
* Mobile application support
* Multi-door occupancy tracking
* Data logging and analytics
* MQTT integration
* Smart building management integration

---

## Team Members

* Saad Mahmood
* Huda Shahid
* Aliyan Zawar
* Abdullah Siddique

---

## Instructor

**Prof. Moazzam Ali**

Department of Computer Science

University of Engineering and Technology, Lahore

---

## License

This project is intended for educational and learning purposes.

Feel free to fork, learn, and improve upon it.

⭐ If you found this project useful, consider starring the repository.
