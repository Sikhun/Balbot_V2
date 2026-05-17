#include <Wire.h>
#include <MPU6050_light.h>


MPU6050 mpu(Wire);


unsigned long timer = 0;
const unsigned long samplePeriodMs = 50; // 20 Hz for smooth plotting


void setup() {
  Serial.begin(9600);
  Wire.begin(22, 19);


  byte status = mpu.begin();
  while (status != 0) {
    Serial.print("MPU6050 status:");
    Serial.println(status);
    delay(1000);
 }


  Serial.println("Calibrating MPU6050, keep it still...");
  delay(1000);
  mpu.calcOffsets(true, true);
  Serial.println("Calibration done");



  Serial.println("angX,angY,angZ");
}


void loop() {
  mpu.update();


  if (millis() - timer >= samplePeriodMs) {
    timer = millis();


  
    Serial.print(mpu.getAngleX());
    Serial.print(',');
    Serial.print(mpu.getAngleY());
    Serial.print(',');
    Serial.println(mpu.getAngleZ());
  }
}