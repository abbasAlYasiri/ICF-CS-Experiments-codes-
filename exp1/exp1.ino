const int Ledpin = 18; // منفذ الليد

void setup() {
  pinMode(Ledpin, OUTPUT); // ضبط المنفذ كمخرج
}

void loop() {
  digitalWrite(LedPin, HIGH); // تشغيل الليد
  delay(500);                 // انتظار نصف ثانية
  digitalWrite(LedPin, LOW);  // إطفاء الليد
  delay(500);                 // انتظار نصف ثانية
}