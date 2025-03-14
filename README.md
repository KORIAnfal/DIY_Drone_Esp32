# ESP32-Based Quadcopter Drone

## Overview
This project is a **custom-built quadcopter drone** using the **ESP32 microcontroller**, an **MPU6050 IMU sensor**, and **electronic speed controllers (ESCs)** to control four **brushless motors**. The drone is designed for **stabilized flight**, **remote control operation**, and **real-time telemetry feedback**.

---

## Components
- **Flight Controller**: ESP32 (WiFi & Bluetooth-enabled)
- **IMU (Inertial Measurement Unit)**: MPU6050 (Gyroscope & Accelerometer)
- **Motors**: 4x Brushless Motors
- **ESCs (Electronic Speed Controllers)**: 4x ESCs to regulate motor speed
- **Power Source**: LiPo Battery
- **2.4GHz Radio Receiver** (PWM output to ESP32)  
- **2.4GHz Transmitter** (RC remote controller)  

---

## Wiring Schematic  

### MPU6050 Wiring (I2C)  

| MPU6050 Pin | ESP32 Pin |
|------------|----------|
| **VCC** | 3.3V |
| **GND** | GND |
| **SDA** | GPIO 21 |
| **SCL** | GPIO 22 |

### RC Receiver Wiring  

| RC Receiver Pin | ESP32 Pin / Power Source |
|----------------|-------------------------|
| **VCC (5V)** | From one ESC BEC |
| **GND** | ESP32 GND |
| **Channel 1 (Throttle)** | GPIO 34 |
| **Channel 2 (Roll)** | GPIO 35 |
| **Channel 3 (Pitch)** | GPIO 32 |
| **Channel 4 (Yaw)** | GPIO 23 |

### ESC Wiring  

| ESC | ESP32 Pin | Motor Position |
|-----|----------|----------------|
| **ESC1** | GPIO 25 | Motor 1 - Front Left |
| **ESC2** | GPIO 26 | Motor 2 - Front Right |
| **ESC3** | GPIO 27 | Motor 3 - Back Left |
| **ESC4** | GPIO 14 | Motor 4 - Back Right |
| **ESC 5V BEC** | ESP32 VCC (one ESC only!) | Power Supply |
| **ESC GND** | ESP32 GND (at least one ESC) | Ground Connection |

