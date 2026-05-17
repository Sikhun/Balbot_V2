#include <Wire.h>
#include <MPU6050_light.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, -1);
MPU6050 mpu(Wire);

void drawEye(Adafruit_SSD1306 &disp, int offsetX, int offsetY) {
  disp.clearDisplay();
  disp.drawLine(34, 8 - offsetY, 94, 8 + offsetY, WHITE);
  disp.fillCircle(64, 38, 22, WHITE);
  disp.fillCircle(64 + offsetX, 38 + offsetY, 10, BLACK);
  disp.display();
}

void setup() {
  Serial.begin(9600);
  Wire.begin(22, 19);
  Wire1.begin(27, 32);

  Serial.println("Scanning Wire...");
  for (byte i = 8; i < 120; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found: 0x");
      Serial.println(i, HEX);
    }
  }

  Serial.println("Scanning Wire1...");
  for (byte i = 8; i < 120; i++) {
    Wire1.beginTransmission(i);
    if (Wire1.endTransmission() == 0) {
      Serial.print("Found: 0x");
      Serial.println(i, HEX);
    }
  }

  display1.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display2.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  byte status = mpu.begin();
  while (status != 0) {
    Serial.println("MPU6050 error");
    delay(1000);
  }

  Serial.println("Calibrating...");
  delay(1000);
  mpu.calcOffsets(true, true);
  Serial.println("Done");
}

void loop() {
  mpu.update();
  float angleX = mpu.getAngleX();
  float angleY = mpu.getAngleY();
  int offsetX = map(angleY, -30, 30, -10, 10);
  int offsetY = map(angleX, -30, 30, -10, 10);
  drawEye(display1, offsetX, offsetY);
  drawEye(display2, offsetX, offsetY);
  delay(20);
}