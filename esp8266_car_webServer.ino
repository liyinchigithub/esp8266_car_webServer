#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
const char* ssid = "302";//wifi账号
const char* password = "123456781";// wifi密码

const int leftPin = D1;
const int rightPin = D2;
const int forwardPin = D3;
const int stopPin = D4;



// 前端HTML页面内容定义为字符串
// 前端HTML页面内容定义为字符串
const char* webpage PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ESP8266 Remote Car Control</title>
<style>
  #control-panel {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: space-around;
    height: 100vh;
  }
  #horizontal-controls {
    display: flex;
    justify-content: space-between;
    width: 100%;
  }
  button {
    font-size: 2em;
    padding: 20px;
    margin: 10px;
  }
</style>
<script>
function sendCommand(action) {
  fetch('/goTo',
    {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify({action: action})
    })
    .then(response => response.text())
    .catch(error => console.error('Error:', error));
}

document.addEventListener('DOMContentLoaded', function() {
  const leftBtn = document.getElementById('left');
  const rightBtn = document.getElementById('right');
  const forwardBtn = document.getElementById('forward');
  const stopBtn = document.getElementById('stop');

  leftBtn.addEventListener('click', () => sendCommand(1));
  rightBtn.addEventListener('click', () => sendCommand(2));
  forwardBtn.addEventListener('click', () => sendCommand(3));
  stopBtn.addEventListener('click', () => sendCommand(4));
});
</script>
</head>
<body>
<div id="control-panel">
  <button id="forward">前进</button>
  <div id="horizontal-controls">
    <button id="left">左转</button>
    <button id="right">右转</button>
  </div>
  <button id="stop">停止</button>
</div>
</body>
</html>
)rawliteral";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  
 

  // 连接WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connecting successed");
  // 打印ESP8266的IP地址
  Serial.println(WiFi.localIP());

  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
  pinMode(forwardPin, OUTPUT);
  pinMode(stopPin, OUTPUT);


  digitalWrite(leftPin, HIGH);
  digitalWrite(rightPin, HIGH);

  // 初始化Web服务器并设置主页响应
  server.on("/", handleGet);
  server.on("/goTo", handlePost);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}

// 处理POST请求保持不变

// 新增处理GET请求以返回HTML页面
void handleGet() {
  if (server.method() == HTTP_GET) {
    server.send(200, "text/html", webpage);
  }
}

  // handlePost
  void handlePost() {
  if (server.method() == HTTP_POST) {
    // 使用ArduinoJson库解析请求体
    StaticJsonDocument<200> doc;
    deserializeJson(doc, server.arg("plain"));

    int action = doc["action"].as<int>();

    switch(action) {
      case 1:
        digitalWrite(leftPin, HIGH);
        digitalWrite(rightPin, LOW);
        digitalWrite(forwardPin, LOW);
        digitalWrite(stopPin, LOW);
        break;
      case 2:
        digitalWrite(leftPin, LOW);
        digitalWrite(rightPin, HIGH);
        digitalWrite(forwardPin, LOW);
        digitalWrite(stopPin, LOW);
        break;
      case 3:
        digitalWrite(leftPin, HIGH);
        digitalWrite(rightPin, HIGH);
        digitalWrite(forwardPin, HIGH);
        digitalWrite(stopPin, LOW);
        break;
      case 4:
        digitalWrite(leftPin, LOW);
        digitalWrite(rightPin, LOW);
        digitalWrite(forwardPin, LOW);
        digitalWrite(stopPin, LOW);
        break;
      default:
        // 错误处理或忽略非法输入
        break;
    }

    server.send(200, "text/plain", "Action received.");
  }
}