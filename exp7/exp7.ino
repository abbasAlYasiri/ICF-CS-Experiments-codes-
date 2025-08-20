#include "DHT.h"
#include <ESP32Servo.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define SERVO_PIN 18

DHT dht(DHTPIN, DHTTYPE);
Servo myServo;

void setup() {
  Serial.begin(115200);
  dht.begin();
  myServo.attach(SERVO_PIN);
}

void loop() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    Serial.println("فشل في قراءة الحساس!");
    return;
  }

  Serial.print("درجة الحرارة: ");
  Serial.println(temp);

  if (temp > 25) {
    myServo.write(180);  // تحريك السيرفو لزاوية 180°
    Serial.println("حرارة مرتفعة: السيرفو على 180°");
  } else {
    myServo.write(90);    // إرجاع السيرفو لزاوية 0°
    Serial.println("9حرارة طبيعية: السيرفو على 0°");
  }

  delay(2000);
}
