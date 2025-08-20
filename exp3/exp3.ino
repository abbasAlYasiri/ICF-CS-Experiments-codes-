// تعريف منافذ الليدات
const int led1 = 16;
const int led2 = 17;
const int led3 = 18;
const int led4 = 19;

void setup() {
  Serial.begin(115200); // بدء الاتصال التسلسلي

  // إعداد المنافذ كمخارج
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  // إطفاء جميع الليدات في البداية
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

  Serial.println("اكتب ON لتشغيل الليدات، أو OFF لإطفائها");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n'); // قراءة الأمر من المستخدم
    command.trim(); // إزالة الفراغات والأسطر الزائدة

    if (command == "ON") {
      // تشغيل كل الليدات
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      Serial.println("ALL Leds are ON");
    }

    if (command == "OFF") {
      // إطفاء كل الليدات
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      Serial.println("ALL Leds are OFF");
    }
  }
}