#define RELAY_PIN 17  // غيّر رقم المنفذ حسب توصيلك

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  digitalWrite(RELAY_PIN, LOW);  // تشغيل الريليه (تشغيل الإضاءة)
  delay(1000);                   // انتظار 1 ثانية

  digitalWrite(RELAY_PIN, HIGH); // إطفاء الريليه (إطفاء الإضاءة)
  delay(1000);                   // انتظار 1 ثانية
}