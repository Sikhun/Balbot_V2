#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050_light.h>

// Motor Driver Pin Definitions
#define IN1 17
#define IN2 16
#define IN3 4
#define IN4 2
#define ENA 19
#define ENB 18

MPU6050 mpu(Wire);
unsigned long timer = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(); // Initialize I2C communication

  // Initialize Motor Pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Initialize MPU6050
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status != 0){ } // Stop everything if the sensor is not connected
  
  Serial.println(F("Calibrating gyro, do not move the robot..."));
  delay(1000);
  mpu.calcOffsets(); // Calibrate gyro and accelerometer offsets
  Serial.println(F("Done!\n"));
}

void loop() {
  mpu.update(); // Read data from the IMU constantly

  // Print MPU6050 data to Serial Monitor every 100ms
  if ((millis() - timer) > 100) { 
    Serial.print("X : "); Serial.print(mpu.getAngleX());
    Serial.print("\tY : "); Serial.print(mpu.getAngleY());
    Serial.print("\tZ : "); Serial.println(mpu.getAngleZ());
    timer = millis();
  }

  // Example: Drive forward at speed 200
  moveForward(200); 
}

// --- Motor Control Functions ---

void moveForward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}