# 🔌 ESP32 16-Channel PLC — Wiring Documentation

## 1. Project Overview

This project uses an ESP32 development board as the main controller for a 16-channel relay-based industrial automation system.

The controller provides 16 digital outputs that can be used to control relays, contactors, solenoid valves, lamps, motors, pumps, and other suitable loads.

```text
                ESP32 PLC Controller
                         │
        ┌────────────────┼────────────────┐
        │                │                │
      Q0-Q5            Q6-Q11           Q12-Q15
        │                │                │
        ▼                ▼                ▼
   Relay Module 1   Relay Module 2   Relay Module 3
        │                │                │
        └────────────────┼────────────────┘
                         │
                    Field Outputs
```

---

## 2. Controller

### Main Controller

- ESP32 Development Board
- 3.3 V GPIO logic
- Wi-Fi enabled
- Arduino framework

The ESP32 is responsible for:

- Reading digital inputs
- Executing control logic
- Controlling relay outputs
- Providing web-based monitoring/control
- Future PLC communication

---

# 3. Digital Output Mapping

The current software configuration uses the following proposed GPIO mapping.

| PLC Address | ESP32 GPIO | Output |
|---|---:|---|
| Q0 | GPIO 4 | Relay 1 |
| Q1 | GPIO 5 | Relay 2 |
| Q2 | GPIO 13 | Relay 3 |
| Q3 | GPIO 14 | Relay 4 |
| Q4 | GPIO 16 | Relay 5 |
| Q5 | GPIO 17 | Relay 6 |
| Q6 | GPIO 18 | Relay 7 |
| Q7 | GPIO 19 | Relay 8 |
| Q8 | GPIO 21 | Relay 9 |
| Q9 | GPIO 22 | Relay 10 |
| Q10 | GPIO 23 | Relay 11 |
| Q11 | GPIO 25 | Relay 12 |
| Q12 | GPIO 26 | Relay 13 |
| Q13 | GPIO 27 | Relay 14 |
| Q14 | GPIO 32 | Relay 15 |
| Q15 | GPIO 33 | Relay 16 |

> ⚠️ This GPIO table is a software default. Verify the actual PCB traces and relay input connections before using the controller with field equipment.

---

# 4. Relay Connection

The basic connection is:

```text
ESP32 GPIO
    │
    ▼
Relay Input
    │
    ▼
Relay Coil
    │
    ▼
Relay Contact
    │
    ├── COM
    ├── NO
    └── NC
```

### Relay terminals

| Terminal | Meaning |
|---|---|
| COM | Common |
| NO | Normally Open |
| NC | Normally Closed |

The actual relay module terminal arrangement must be verified from the module's labeling/datasheet.

---

# 5. Power Supply

The controller should use an appropriate regulated power supply.

Typical architecture:

```text
              DC Power Supply
                    │
             ┌──────┴──────┐
             │             │
             ▼             ▼
          ESP32         Relay Supply
         Controller       5 V / Rated
             │             │
             │             │
             └──────┬──────┘
                    │
              Control System
```

The exact voltage and current requirements depend on the selected ESP32 board and relay modules.

---

# 6. Relay Logic

The firmware currently supports both:

```cpp
RELAY_ACTIVE_LOW = true;
```

and:

```cpp
RELAY_ACTIVE_LOW = false;
```

Many relay modules use **active-LOW** inputs, but this must be verified on the actual hardware.

---

# 7. PLC Addressing

The project uses PLC-style addressing.

### Inputs

```text
I0  - I15
```

### Outputs

```text
Q0  - Q15
```

### Internal Memory

```text
M0  - M31
```

### Timers

```text
T0  - T15
```

### Counters

```text
C0  - C15
```

---

# 8. Recommended Field Wiring

A typical low-voltage field connection can be structured as:

```text
Field Supply +
      │
      ▼
     Fuse
      │
      ▼
    Load
      │
      ▼
 Relay NO / COM
      │
      ▼
Field Supply -
```

The exact wiring depends on whether the load requires:

- DC
- AC
- Normally Open operation
- Normally Closed operation
- Contactor control
- Solenoid control
- Motor control

---

# 9. Testing Procedure

Before connecting any real load:

### Step 1

Power the ESP32 and relay system.

### Step 2

Verify that all outputs start in the OFF state.

### Step 3

Test:

```text
Q0 → ON
Q0 → OFF
```

### Step 4

Repeat for:

```text
Q1 ... Q15
```

### Step 5

Verify the relay indicator LEDs.

### Step 6

Test with a suitable low-voltage load.

### Step 7

Only after successful testing, connect the intended field equipment.

---

# 10. Safety

⚠️ **Important**

This project is intended as an educational/prototyping industrial automation controller.

Do not connect mains voltage directly to the prototype unless the complete system has been properly designed and verified.

Before operating mains equipment, verify:

- Relay contact rating
- Fuse/MCB protection
- Isolation
- Creepage and clearance
- Earthing
- Enclosure
- Emergency-stop system
- Cable size
- Load current
- Short-circuit protection

For development, use safe low-voltage loads whenever possible.

---

# 11. Future Expansion

Planned hardware/software improvements:

- 16 digital inputs
- Analog inputs
- Emergency-stop monitoring
- Timers
- Counters
- Motor control
- Sensor interfaces
- Modbus RTU
- Modbus TCP
- MQTT
- HMI
- Data logging
- OTA firmware update

---

## 👨‍💻 Developer

**Md Taslim Islam Oyon**

Electronics Engineer | PLC Programmer | Industrial Automation Enthusiast
