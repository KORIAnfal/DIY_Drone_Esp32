#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <MPU6050_tockn.h>
#include <PID_v1.h>

Servo esc1, esc2, esc3, esc4;

#define ESC1_PIN 25  // Front Left Motor
#define ESC2_PIN 26  // Front Right Motor
#define ESC3_PIN 27  // Back Left Motor
#define ESC4_PIN 14  // Back Right Motor

#define THROTTLE_PIN 34
#define ROLL_PIN 35
#define PITCH_PIN 32
#define YAW_PIN 23


MPU6050 mpu6050(Wire);


double rollInput, rollOutput, rollSetpoint;
double pitchInput, pitchOutput, pitchSetpoint;
double yawInput, yawOutput, yawSetpoint;


double kp = 1.2, ki = 0.05, kd = 0.1;
PID rollPID(&rollInput, &rollOutput, &rollSetpoint, kp, ki, kd, DIRECT);
PID pitchPID(&pitchInput, &pitchOutput, &pitchSetpoint, kp, ki, kd, DIRECT);
PID yawPID(&yawInput, &yawOutput, &yawSetpoint, kp, ki, kd, DIRECT);


volatile uint16_t throttle, roll, pitch, yaw;

void readRC() {
  throttle = pulseIn(THROTTLE_PIN, HIGH, 25000);
  roll = pulseIn(ROLL_PIN, HIGH, 25000);
  pitch = pulseIn(PITCH_PIN, HIGH, 25000);
  yaw = pulseIn(YAW_PIN, HIGH, 25000);


  throttle = constrain(throttle, 1000, 2000);
  roll = constrain(roll, 1000, 2000);
  pitch = constrain(pitch, 1000, 2000);
  yaw = constrain(yaw, 1000, 2000);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  esc1.attach(ESC1_PIN, 1000, 2000);
  esc2.attach(ESC2_PIN, 1000, 2000);
  esc3.attach(ESC3_PIN, 1000, 2000);
  esc4.attach(ESC4_PIN, 1000, 2000);

  pinMode(THROTTLE_PIN, INPUT);
  pinMode(ROLL_PIN, INPUT);
  pinMode(PITCH_PIN, INPUT);
  pinMode(YAW_PIN, INPUT);

  mpu6050.begin();
  Serial.println("MPU6050 Connected!");

  delay(1000);
  Serial.println("MPU6050 Connected!");

  
  mpu6050.calcGyroOffsets(true);
  Serial.println("IMU Initialized and Calibrated!");


  rollPID.SetMode(AUTOMATIC);
  pitchPID.SetMode(AUTOMATIC);
  yawPID.SetMode(AUTOMATIC);
}

void loop() {
  readRC();

  mpu6050.update();
  rollInput = mpu6050.getAngleX();
  pitchInput = mpu6050.getAngleY();
  yawInput = mpu6050.getAngleZ();

  rollSetpoint = map(roll, 1000, 2000, -30, 30);
  pitchSetpoint = map(pitch, 1000, 2000, -30, 30);
  yawSetpoint = map(yaw, 1000, 2000, -180, 180);

  rollPID.Compute();
  pitchPID.Compute();
  yawPID.Compute();

  // **Motor Mixing Algorithm**
  int esc1Speed = throttle + pitchOutput - rollOutput - yawOutput;  // Front Left
  int esc2Speed = throttle + pitchOutput + rollOutput + yawOutput;  // Front Right
  int esc3Speed = throttle - pitchOutput - rollOutput + yawOutput;  // Back Left
  int esc4Speed = throttle - pitchOutput + rollOutput - yawOutput;  // Back Right

  esc1Speed = constrain(esc1Speed, 1000, 2000);
  esc2Speed = constrain(esc2Speed, 1000, 2000);
  esc3Speed = constrain(esc3Speed, 1000, 2000);
  esc4Speed = constrain(esc4Speed, 1000, 2000);

  esc1.writeMicroseconds(esc1Speed);
  esc2.writeMicroseconds(esc2Speed);
  esc3.writeMicroseconds(esc3Speed);
  esc4.writeMicroseconds(esc4Speed);

  Serial.print("Throttle: ");
  Serial.print(throttle);
  Serial.print(" Roll: ");
  Serial.print(rollInput);
  Serial.print(" Pitch: ");
  Serial.print(pitchInput);
  Serial.print(" Yaw: ");
  Serial.println(yawInput);

  delay(20);  
}
