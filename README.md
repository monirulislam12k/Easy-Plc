# ⚡ ESP32 16-Channel PLC & Industrial Automation Controller

![ESP32](https://img.shields.io/badge/Controller-ESP32-blue)
![PLC](https://img.shields.io/badge/System-PLC%20Controller-orange)
![Automation](https://img.shields.io/badge/Industrial-Automation-green)
![Arduino](https://img.shields.io/badge/Platform-Arduino-00979D)
![License](https://img.shields.io/badge/License-MIT-lightgrey)

## 👋 Project Overview

This project is an **ESP32-based 16-channel PLC and Industrial Automation Controller** designed for practical control applications.

The system combines an **ESP32 microcontroller, relay modules, screw terminals, and a structured PLC-style control architecture** to create a flexible automation controller.

The prototype is designed to control multiple industrial loads through relay outputs and can be expanded with digital inputs, timers, counters, Modbus communication, MQTT, and an HMI.

---

## 🏗️ System Architecture

```text
                  ┌───────────────────────┐
                  │        ESP32          │
                  │   PLC Main Controller  │
                  └───────────┬───────────┘
                              │
                 ┌────────────┴────────────┐
                 │                         │
          Digital Inputs              Control Logic
             I0 – I15                 M / T / C
                 │                         │
                 └────────────┬────────────┘
                              │
                       ┌──────▼──────┐
                       │ 16 Channel  │
                       │ Relay Board │
                       └──────┬──────┘
                              │
                ┌─────────────┼─────────────┐
                │             │             │
               Q0            Q1            Q2 ... Q15
                │             │             │
                ▼             ▼             ▼
             Load 1        Load 2        Load 16
```

---

## 🔧 Hardware

- ESP32 Development Board
- 16-Channel Relay System
- Screw Terminal Blocks
- LED Indicators
- DC Power Supply
- Prototype PCB
- Connecting Wires
- Industrial/Low-Voltage Loads

### Controller

**ESP32** is used as the main controller because of its:

- Wi-Fi connectivity
- High processing capability
- Large GPIO availability
- Low cost
- Easy programming
- IoT compatibility

---

# 🔌 I/O Configuration

## Digital Outputs

| PLC Address | ESP32 GPIO | Description |
|---|---:|---|
| Q0 | GPIO 4 | Relay Output 1 |
| Q1 | GPIO 5 | Relay Output 2 |
| Q2 | GPIO 13 | Relay Output 3 |
| Q3 | GPIO 14 | Relay Output 4 |
| Q4 | GPIO 16 | Relay Output 5 |
| Q5 | GPIO 17 | Relay Output 6 |
| Q6 | GPIO 18 | Relay Output 7 |
| Q7 | GPIO 19 | Relay Output 8 |
| Q8 | GPIO 21 | Relay Output 9 |
| Q9 | GPIO 22 | Relay Output 10 |
| Q10 | GPIO 23 | Relay Output 11 |
| Q11 | GPIO 25 | Relay Output 12 |
| Q12 | GPIO 26 | Relay Output 13 |
| Q13 | GPIO 27 | Relay Output 14 |
| Q14 | GPIO 32 | Relay Output 15 |
| Q15 | GPIO 33 | Relay Output 16 |

> ⚠️ GPIO mapping must be verified against the actual PCB wiring before connecting field equipment.

---

# 🧠 PLC Addressing Concept

The project follows a PLC-inspired addressing system.

```text
I0  – I15   → Digital Inputs
Q0  – Q15   → Digital Outputs
M0  – M31   → Internal Memory
T0  – T15   → Timers
C0  – C15   → Counters
```

This structure makes the ESP32 easier to expand into a complete PLC-style automation controller.

---

# 🌐 Web-Based HMI

The ESP32 can host a simple web interface.

After connecting to Wi-Fi, the controller provides a browser-based dashboard where each output can be controlled.

Example:

```text
Q0 → ON
Q1 → OFF
Q2 → ON
Q3 → OFF
...
Q15 → OFF
```

The system also provides an emergency-style:

```text
ALL OUTPUTS OFF
```

function for development and testing.

---

# 📡 HTTP API

### Read Output Status

```http
GET /api/status
```

Example:

```json
{
  "q0": 1,
  "q1": 0,
  "q2": 1,
  "q3": 0
}
```

### Turn Output ON

```http
GET /api/set?ch=0&state=1
```

### Turn Output OFF

```http
GET /api/set?ch=0&state=0
```

### Turn All Outputs OFF

```http
GET /api/alloff
```

---

# 💻 Software

### Development Platform

- Arduino IDE
- ESP32 Arduino Core
- C/C++
- HTML
- JavaScript
- REST-style HTTP API

### Main Libraries

```cpp
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
```

---

# ⚙️ Control Logic

The planned PLC scan cycle is:

```text
START
  │
  ▼
Read Inputs
  │
  ▼
Update Memory
  │
  ▼
Execute PLC Logic
  │
  ▼
Process Timers
  │
  ▼
Process Counters
  │
  ▼
Update Outputs
  │
  ▼
Repeat
```

This architecture can later support:

- Start/Stop logic
- Motor control
- Pump control
- Valve control
- Sensor interlocking
- Automatic sequences
- Timers
- Counters
- Alarm systems

---

# 🚀 Future Development

- [ ] 16 Digital Inputs
- [ ] PLC Scan Cycle
- [ ] Ladder Logic
- [ ] Timers
- [ ] Counters
- [ ] Motor Control
- [ ] Sensor Monitoring
- [ ] Emergency Stop Logic
- [ ] Modbus RTU
- [ ] Modbus TCP
- [ ] MQTT
- [ ] IoT Dashboard
- [ ] OTA Firmware Update
- [ ] EEPROM/NVS Configuration
- [ ] Data Logging
- [ ] HMI Integration
- [ ] Industrial Communication

---

# 📸 Prototype

The prototype consists of:

```text
ESP32 Controller
      │
      ├── Relay Module 1
      ├── Relay Module 2
      ├── Relay Module 3
      │
      └── Terminal Blocks
              │
              └── Field Outputs
```

---

# 🎯 Project Goals

The main goal of this project is to develop a **low-cost, flexible and expandable PLC-style automation controller** using ESP32 technology.

The project focuses on:

- Electronics
- Embedded Systems
- PLC Programming
- Industrial Automation
- IoT
- Control Systems
- Hardware Development

---

# 👨‍💻 Developer

**Md Taslim Islam Oyon**

Electronics Engineer | PLC Programmer | Industrial Automation Enthusiast

Interested in:

`Electronics` • `PLC` • `Arduino` • `ESP32` • `Industrial Automation` • `Embedded Systems`

---

## ⭐ If you find this project useful

Feel free to explore the source code, improve the control architecture, and build your own automation system.

**Built with ⚡ ESP32 + Electronics + Automation**
