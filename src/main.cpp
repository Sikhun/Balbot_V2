#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050_light.h>


#define IN1 17
#define IN2 16
#define IN3 4
#define IN4 2
#define ENA 19
#define ENB 18

MPU6050 mpu(Wire);

void setup(){

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

    // หมุนไปข้างหน้า
    
}

void loop(){

  digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 200); // 0-255 ปรับความเร็วได้
    analogWrite(ENB, 200); // 0-255 ปรับความเร็ว

  //MPU6050 update and print data
 
}