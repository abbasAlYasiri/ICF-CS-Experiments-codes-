#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "HONOR X9c";
const char* password = "1234567890";

WebServer server(80);

const int SERVO_PIN = 5;
Servo myServo;
int servoPos = 90; // الحالة الحالية للسيرفو

const int ledPins[4] = {16, 17, 18, 19};
bool ledState[4] = {false, false, false, false};

void handleRoot();
void handleState();
void handleServo();
void handleLed();

void setup() {
  Serial.begin(115200);
  delay(100);

  // تهيئة المخرجات
  for (int i = 0; i < 4; ++i) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
    ledState[i] = false;
  }

  myServo.attach(SERVO_PIN);
  myServo.write(servoPos);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());

  // تعريف مسارات الويب
  server.on("/", HTTP_GET, handleRoot);
  server.on("/state", HTTP_GET, handleState);        // يعيد JSON بالحالة الحالية
  server.on("/servo", HTTP_GET, handleServo);        // ?pos=ANGLE
  server.on("/led", HTTP_GET, handleLed);            // ?id=1..4&state=0|1

  server.begin();
}

void loop() {
  server.handleClient();
}

/* --- Handlers --- */

void handleRoot(){
  // HTML صفحة الواجهة (CSS + JS مدمجين)
  String page = R"rawliteral(
<!DOCTYPE html>
<html lang="ar">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>ESP32 - تحكم سيرفو و LEDs</title>
<style>
body{background:#1e1e2f;color:#fff;font-family:Arial,Helvetica,sans-serif;text-align:center;padding:20px}
h1{color:#ffcc00}
input[type=range]{-webkit-appearance:none;width:80%;height:14px;border-radius:10px;background:linear-gradient(90deg,#ff6600,#ffcc00);outline:none}
input[type=range]::-webkit-slider-thumb{-webkit-appearance:none;width:24px;height:24px;border-radius:50%;background:#fff;border:2px solid #ffcc00;cursor:pointer}
.btn{display:inline-block;padding:10px 16px;margin:6px;border-radius:6px;color:#fff;border:none;cursor:pointer;font-size:15px}
.on{background:green} .off{background:red}
.sep{height:18px}
.card{background:rgba(255,255,255,0.03);padding:14px;border-radius:8px;display:inline-block;min-width:260px}
</style>
</head>
<body>
  <h1>تحكم في السيرفو و الـ LEDs</h1>

  <div class="card">
    <h3>السيرفو</h3>
    <input id="slider" type="range" min="0" max="180" value="90" oninput="moveServo(this.value)">
    <p>الزاوية: <span id="angle">90</span>°</p>
  </div>

  <div class="sep"></div>

  <div class="card">
    <h3>الـ LEDs</h3>
    <div id="ledButtons">
      <!-- أزرار ستُملأ عبر جافاسكربت -->
    </div>
  </div>

<script>
function el(id){ return document.getElementById(id); }

function updateLedButton(id, state){
  var btn = document.getElementById('led'+id);
  if(!btn){
    btn = document.createElement('button');
    btn.id = 'led'+id;
    btn.className = 'btn off';
    btn.onclick = function(){ toggleLED(id); };
    document.getElementById('ledButtons').appendChild(btn);
  }
  if(state){
    btn.classList.remove('off'); btn.classList.add('on');
    btn.innerText = 'LED' + id + ' ✓';
  } else {
    btn.classList.remove('on'); btn.classList.add('off');
    btn.innerText = 'LED' + id + ' ✕';
  }
}

function setInitialState(s){
  // سيرفو
  el('slider').value = s.servo;
  el('angle').innerText = s.servo;

  // ليدات
  for(var i=0;i<4;i++){
    updateLedButton(i+1, s.led[i] == 1);
  }
}

window.onload = function(){
  fetch('/state').then(r=>r.json()).then(setInitialState).catch(function(e){
    console.log('state error', e);
  });
};

function moveServo(val){
  el('angle').innerText = val;
  // طلب الى /servo?pos=val
  fetch('/servo?pos=' + val).catch(function(e){ console.log(e); });
}
function toggleLED(id){
  var btn = document.getElementById('led'+id);
  var currentOn = btn.classList.contains('on');
  var newState = currentOn ? 0 : 1;
  fetch('/led?id=' + id + '&state=' + newState)
    .then(r=>r.json())
    .then(function(j){
      updateLedButton(id, j.state == 1);
    }).catch(function(e){ console.log(e); });
}
</script>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", page);
}

void handleState(){
  // بناء JSON بسيط: {"servo":90,"led":[1,0,0,1]}
  String s = "{\"servo\":" + String(servoPos) + ",\"led\":[";
  for (int i = 0; i < 4; ++i) {
    s += (ledState[i] ? "1" : "0");
    if (i < 3) s += ",";
  }
  s += "]}";
  server.send(200, "application/json", s);
}

void handleServo(){
  if (server.hasArg("pos")) {
    int p = server.arg("pos").toInt();
    p = constrain(p, 0, 180);
    servoPos = p;
    myServo.write(servoPos);
    server.send(200, "application/json", "{\"result\":\"ok\",\"servo\":" + String(servoPos) + "}");
  } else {
    server.send(400, "text/plain", "missing pos");
  }
}

void handleLed(){
  if (server.hasArg("id") && server.hasArg("state")) {
    int id = server.arg("id").toInt();   // 1..4
    int st = server.arg("state").toInt(); // 0|1
    if (id >= 1 && id <= 4) {
      int idx = id - 1;
      ledState[idx] = (st != 0);
      digitalWrite(ledPins[idx], ledState[idx] ? HIGH : LOW);
      String j = "{\"led\":" + String(id) + ",\"state\":" + String(ledState[idx] ? 1 : 0) + "}";
      server.send(200, "application/json", j);
    } else {
      server.send(400, "text/plain", "bad id");
    }
  } else {
    server.send(400, "text/plain", "missing args");
  }
}