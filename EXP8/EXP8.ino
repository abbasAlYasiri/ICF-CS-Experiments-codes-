#include <DHT.h>
#include <BluetoothSerial.h> // BLS استدعاء مكتبة 

#define DHTPIN 4          // الدبوس الموصول عليه حساس DHT11
#define DHTTYPE DHT11     // نوع الحساس

DHT dht(DHTPIN, DHTTYPE);
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_DHT11"); // اسم جهاز البلوتوث عند الاقتران
  dht.begin();
  Serial.println("Bluetooth DHT11 example started");
}

void loop() {
  delay(2000); // تأخير بين القراءات

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    SerialBT.println("Failed to read from DHT sensor!");
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  String data = "Temp: " + String(temperature) + " *C, Humidity: " + String(humidity) + " %";
  SerialBT.println(data);
  Serial.println(data);
}