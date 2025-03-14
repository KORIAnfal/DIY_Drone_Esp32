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
- **Receiver**: 2.4GHz Radio Receiver (for remote control)

---

## Wiring Schematic

### ESP32 to MPU6050 (I2C Communication)
| ESP32 GPIO | MPU6050 |
|------------|---------|
| SDA (GPIO 21) | SDA |
| SCL (GPIO 22) | SCL |
| GND | GND |
| VCC | 3.3V or 5V (depending on module) |

### ESC to ESP32 (PWM Signal Control)
| ESC | ESP32 GPIO |
|-----|------------|
| ESC1 (Motor 1) | GPIO 25 |
| ESC2 (Motor 2) | GPIO 26 |
| ESC3 (Motor 3) | GPIO 27 |
| ESC4 (Motor 4) | GPIO 14 |

### Battery & Power Distribution
- **LiPo Battery** → **Power Distribution Board** → **ESCs** → **Motors**

