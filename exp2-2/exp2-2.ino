// تعرف المنافذ كمخرجات
void setup() {
  pinMode(16, OUTPUT); 
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
}
// اوامر الاطفاء و التشغيل 
void loop() {
  digitalWrite(16, HIGH);
  delay(500); // فترة التأخير 0.5 ثانية
  digitalWrite(16, LOW);

  digitalWrite(17, HIGH);
  delay(500);
  digitalWrite(17, LOW);

  digitalWrite(18, HIGH);
  delay(500);
  digitalWrite(18, LOW);

  digitalWrite(19, HIGH);
  delay(500);
  digitalWrite(19, LOW);
}