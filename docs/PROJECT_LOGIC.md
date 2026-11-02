# ⚙️ ESP32 PLC — Project Control Logic

## 1. Overview

The ESP32 acts as the main PLC-style controller for the automation system.

The control architecture is designed around a cyclic PLC scan concept.

```text
              ┌──────────────────┐
              │      START       │
              └────────┬─────────┘
                       │
                       ▼
              ┌──────────────────┐
              │   Read Inputs    │
              │     I0-I15       │
              └────────┬─────────┘
                       │
                       ▼
              ┌──────────────────┐
              │ Update Memory    │
              │     M0-M31       │
              └────────┬─────────┘
                       │
                       ▼
              ┌──────────────────┐
              │ Execute Control  │
              │      Logic       │
              └────────┬─────────┘
                       │
                       ▼
              ┌──────────────────┐
              │ Process Timers   │
              │     T0-T15       │
              └────────┬─────────┘
                       │
                       ▼
              ┌──────────────────┐
              │ Process Counters │
              │     C0-C15       │
              └────────┬─────────┘
                       │
                       ▼
              ┌──────────────────┐
              │ Update Outputs   │
              │     Q0-Q15       │
              └────────┬─────────┘
                       │
                       └──────────► Repeat
```

---

# 2. PLC Address Structure

## Digital Inputs

```text
I0  - I15
```

These can be assigned to:

- Push buttons
- Limit switches
- Proximity sensors
- Photoelectric sensors
- Float switches
- Pressure switches
- Emergency-stop feedback

---

## Digital Outputs

```text
Q0 - Q15
```

These can control:

- Relays
- Contactors
- Solenoid valves
- Lamps
- Fans
- Pumps
- Motors through suitable contactors/drivers
- Alarm devices

---

## Internal Memory

```text
M0 - M31
```

Memory bits can be used for:

- Run status
- Machine state
- Interlocks
- Alarm flags
- Sequence control
- Auto/manual mode

---

## Timers

```text
T0 - T15
```

Timers can be used for:

- ON delay
- OFF delay
- Motor start delay
- Valve timing
- Alarm delay
- Sequence timing

---

## Counters

```text
C0 - C15
```

Counters can be used for:

- Product counting
- Machine cycles
- Sensor events
- Production quantity
- Batch counting

---

# 3. Example Start/Stop Logic

A basic machine control sequence can be represented as:

```text
START + RUN PERMISSION
          │
          ▼
        MACHINE RUN
          │
          ▼
          Q0
```

Conceptually:

```text
RUN = START AND NOT STOP AND NOT E_STOP
```

Then:

```text
Q0 = RUN
```

---

# 4. Interlock Logic

Industrial systems should use interlocks to prevent unsafe or conflicting operations.

Example:

```text
Q1 = RUN AND SENSOR_OK
```

Another example:

```text
Q2 = Q0 AND NOT FAULT
```

This prevents the output from operating when a fault condition exists.

---

# 5. Motor Control Example

A possible motor sequence:

```text
START
  │
  ▼
Check Emergency Stop
  │
  ▼
Check Safety Interlock
  │
  ▼
Start Motor
  │
  ▼
Q0 = ON
```

Stop conditions:

```text
STOP
OR
E_STOP
OR
OVERLOAD
OR
FAULT
```

Then:

```text
Q0 = OFF
```

---

# 6. Automatic Sequence Example

A future automatic sequence could operate like:

```text
STEP 1
  │
  ├── Start Pump
  │
  ▼
STEP 2
  │
  ├── Wait T0
  │
  ▼
STEP 3
  │
  ├── Open Valve
  │
  ▼
STEP 4
  │
  ├── Wait for Sensor
  │
  ▼
STEP 5
  │
  ├── Close Valve
  │
  ▼
STEP 6
  │
  └── Complete Cycle
```

---

# 7. Manual Mode

In manual mode, the operator can directly control individual outputs.

Example:

```text
Q0 → ON
Q0 → OFF

Q1 → ON
Q1 → OFF
```

The ESP32 web interface can be used for testing and commissioning.

---

# 8. Automatic Mode

In automatic mode, outputs are controlled by the programmed sequence.

Example:

```text
AUTO = TRUE

IF START:
    RUN = TRUE

IF RUN AND SENSOR1:
    Q0 = TRUE

IF Q0 AND TIMER_DONE:
    Q1 = TRUE

IF FAULT:
    ALL OUTPUTS = FALSE
```

---

# 9. Emergency Stop

The emergency-stop system should be designed as a **hardware safety function** where required.

Software monitoring can provide status and additional shutdown logic, but software alone should not be treated as the sole safety mechanism for hazardous machinery.

Conceptually:

```text
E-STOP
   │
   ├──────────────► Hardware Safety Circuit
   │
   └──────────────► ESP32 Input
                         │
                         ▼
                    Fault Status
                         │
                         ▼
                   Disable Outputs
```

---

# 10. Fault Handling

Possible fault conditions:

```text
E_STOP
OVERLOAD
SENSOR_FAULT
COMMUNICATION_FAULT
POWER_FAULT
```

A fault condition can trigger:

```text
Q0 = OFF
Q1 = OFF
Q2 = OFF
...
Q15 = OFF
```

and set:

```text
M0 = FAULT
```

---

# 11. Future PLC Features

The project can be expanded with:

- Ladder logic engine
- Function blocks
- TON timer
- TOF timer
- TP timer
- Up counter
- Down counter
- Rising-edge detection
- Falling-edge detection
- State machine
- Recipe system
- Alarm system
- HMI
- Modbus
- MQTT
- SCADA integration

---

# 12. Project Objective

The main objective is to develop a low-cost and expandable PLC-style industrial automation controller using ESP32 technology.

The project combines:

```text
Electronics
     +
Embedded Programming
     +
PLC Logic
     +
Industrial Automation
     +
IoT
```

to create a flexible automation platform.

---

## 👨‍💻 Developer

**Md Taslim Islam Oyon**

Electronics Engineer | PLC Programmer | Industrial Automation Enthusiast
