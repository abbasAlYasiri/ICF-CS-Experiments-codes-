// تعريف المنافذ التي ترتبط بها الليدات
const int led1 = 16;
const int led2 = 17;
const int led3 = 18;
const int led4 = 19;

void setup() {
  Serial.begin(115200);  // بدء الاتصال التسلسلي بسرعة 115200

  // تعيين جميع المنافذ كمخارج لأنها تتحكم بالليدات
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  // التأكد من أن جميع الليدات مطفأة في البداية
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

  // طباعة تعليمات للمستخدم في الشاشة التسلسلية
  Serial.println("اكتب أوامر مثل: ON1 أو OFF3 لتشغيل/إطفاء الليدات");
}

void loop() {
  // التحقق من وجود أمر وارد من الشاشة التسلسلية
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n'); // قراءة الأمر كاملاً حتى نهاية السطر
    command.trim(); // إزالة الفراغات الزائدة من البداية والنهاية

    // التحكم بالليد رقم 1
    if (command == "ON1") {
      digitalWrite(led1, HIGH); // تشغيل الليد 1
      Serial.println("LED1 ON");
    } else if (command == "OFF1") {
      digitalWrite(led1, LOW); // إطفاء الليد 1
      Serial.println("LED1 OFF");
    }

    // التحكم بالليد رقم 2
    else if (command == "ON2") {
      digitalWrite(led2, HIGH);
      Serial.println("LED2 ON");
    } else if (command == "OFF2") {
      digitalWrite(led2, LOW);
      Serial.println("LED2 OFF");
    }

    // التحكم بالليد رقم 3
    else if (command == "ON3") {
      digitalWrite(led3, HIGH);
      Serial.println("LED3 ON");
    } else if (command == "OFF3") {
      digitalWrite(led3, LOW);
      Serial.println("LED3 OFF");
    }

    // التحكم بالليد رقم 4
    else if (command == "ON4") {
      digitalWrite(led4, HIGH);
      Serial.println("LED4 ON");
    } else if (command == "OFF4") {
      digitalWrite(led4, LOW);
      Serial.println("LED4 OFF");
    }

    // طباعة رسالة إذا كان الأمر غير معروف
    else {
      Serial.println("أمر غير معروف");
    }
  }
}