#define RELAY_PIN 17  // يمكنك تغييره لأي GPIO مناسب

void setup() {
  Serial.begin(115200);           // بدء الاتصال التسلسلي
  pinMode(RELAY_PIN, OUTPUT);     // تحديد المنفذ كمخرج
  digitalWrite(RELAY_PIN, LOW);   // تأكد أن الريليه مطفأ بالبداية
  Serial.println("اكتب ON لتشغيل أو OFF للإطفاء");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n'); // قراءة الأمر من المستخدم
    command.trim(); // إزالة الفراغات الزائدة

    if (command == "ON") {
      digitalWrite(RELAY_PIN, HIGH); // تشغيل الريليه
      Serial.println("تم تشغيل الإضاءة");
    }
    else if (command == "OFF") {
      digitalWrite(RELAY_PIN, LOW);  // إطفاء الريليه
      Serial.println("تم إطفاء الإضاءة");
    }
    else {
      Serial.println("أمر غير معروف. اكتب ON أو OFF فقط.");
    }
  }
}