#include "DHT.h" // DHT استدعاء مكتبة

#define DHTPIN 4       // المنفذ الموصول بـ DHT11
#define DHTTYPE DHT11  // نوع الحساس

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature(); // قراءة الحرارة
  float hum  = dht.readHumidity();    // قراءة الرطوبة

  if (isnan(temp) || isnan(hum)) {
    Serial.println("فشل في قراءة الحساس!");
  } else {
    Serial.print("Temp in C°: ");
    Serial.print(temp);
    Serial.print(" Humidity: ");
    Serial.print(hum);
    Serial.println(" %");
  }

  delay(2000);
}