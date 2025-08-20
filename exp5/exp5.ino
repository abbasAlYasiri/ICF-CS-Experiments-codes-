#include <ESP32Servo.h> // ESP32servo استدعاء مكتبة 

Servo myServo;
#define SERVO_PIN 18  // المنفذ الموصول بالسيرفو

void setup() {
  myServo.attach(SERVO_PIN);
}

void loop() {
  myServo.write(0);    // زاوية 0°
  delay(1000);
  myServo.write(90);   // زاوية 90°
  delay(1000);
  myServo.write(180);  // زاوية 180°
  delay(1000);
}
