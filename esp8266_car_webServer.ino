#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

// const char* ssid = "302"; // WiFi账号
// const char* password = "123456781"; // WiFi密码

const char *ssid = "遥控小车";     // 你想要的热点名称
const char *password = "12345678"; // 热点的密码，至少8个字符

// 定义L298N电机驱动板的引脚
const int motorLeftIn1 = D1;  // 左电机输入1
const int motorLeftIn2 = D2;  // 左电机输入2
const int motorRightIn1 = D3; // 右电机输入1
const int motorRightIn2 = D4; // 右电机输入2
const int motorLeftEn = D5;   // 左电机使能
const int motorRightEn = D6;  // 右电机使能

// 前端HTML页面内容定义为字符串
const char *webpage PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ESP8266 Remote Car Control</title>
<style>
<style>
  body, html {
    height: 100%;
    margin: 0;
    display: flex;
    justify-content: center;
    align-items: center;
  }
  #control-panel {
    display: flex;
    flex-direction: column;
    align-items: center;
  }
  #horizontal-controls {
    display: flex;
    justify-content: center;
    margin: 20px; /* 为水平控制按钮组添加外边距 */
  }
  button {
    font-size: 2em;
    padding: 20px;
    margin: 10px; /* 为所有按钮添加外边距 */
  }
  .red-button {
    background-color: red;
    color: white; /* 设置文字颜色为白色以提高对比度 */
  }

  .blue-button {
    background-color: blue;
    color: white; /* 设置文字颜色为白色以提高对比度 */
  }

  /* 你可能还想为按钮添加一些hover效果 */
  .red-button:hover, .blue-button:hover {
    opacity: 0.8; /* 鼠标悬停时的透明度变化 */
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
  const backwardBtn = document.getElementById('backward'); // 获取后退按钮
  const stopBtn = document.getElementById('stop');

  leftBtn.addEventListener('click', () => sendCommand(1));
  rightBtn.addEventListener('click', () => sendCommand(2));
  forwardBtn.addEventListener('click', () => sendCommand(3));
  backwardBtn.addEventListener('click', () => sendCommand(5)); // 后退按钮发送5作为动作
  stopBtn.addEventListener('click', () => sendCommand(4));
});
</script>
</head>
<body>
<div id="control-panel">
  <button id="forward" class="blue-button">前</button>
<div id="horizontal-controls">
  <button id="left" class="blue-button">左</button>
  <button id="right" class="blue-button">右</button>
</div>
<button id="backward" class="blue-button">后</button>
<button id="stop" class="red-button">STOP</button>
</div>
</body>
</html>
)rawliteral";

ESP8266WebServer server(80);

void setup()
{
  Serial.begin(115200);

  // 连接WiFi
  // WiFi.begin(ssid, password);
  // Serial.println("Attempting to connect to WiFi network...");

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.print(".");
  // }

  // 设置ESP8266为AP模式，使用上面定义的SSID和密码
  WiFi.softAP(ssid, password);
  Serial.println("ESP8266 is set as a WiFi Access Point with SSID: " + String(ssid));

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // 设置电机驱动引脚为输出模式
  pinMode(motorLeftIn1, OUTPUT);
  pinMode(motorLeftIn2, OUTPUT);
  pinMode(motorRightIn1, OUTPUT);
  pinMode(motorRightIn2, OUTPUT);
  pinMode(motorLeftEn, OUTPUT);
  pinMode(motorRightEn, OUTPUT);

  // 启用电机
  digitalWrite(motorLeftEn, HIGH);
  digitalWrite(motorRightEn, HIGH);

  // 初始化Web服务器并设置主页响应
  server.on("/", handleGet);
  server.on("/goTo", handlePost);
  server.begin();
  Serial.println("Web server started");
}

void loop()
{
  server.handleClient();
}

// 处理GET请求以返回HTML页面
void handleGet()
{
  if (server.method() == HTTP_GET)
  {
    server.send(200, "text/html", webpage);
  }
}

// 处理POST请求以控制电机
void handlePost()
{
  if (server.method() == HTTP_POST)
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, server.arg("plain"));
    int action = doc["action"].as<int>();

    switch (action)
    {
    case 1: // 左转
      digitalWrite(motorLeftIn1, LOW);
      digitalWrite(motorLeftIn2, HIGH); // 一个电机向前
      digitalWrite(motorRightIn1, LOW);
      digitalWrite(motorRightIn2, LOW); // 另一个电机停止
      break;
    case 2: // 右转
      digitalWrite(motorLeftIn1, LOW);
      digitalWrite(motorLeftIn2, LOW); // 一个电机停止
      digitalWrite(motorRightIn1, LOW);
      digitalWrite(motorRightIn2, HIGH); // 另一个电机向前
      break;
    case 3: // 前进是
      digitalWrite(motorLeftIn1, HIGH);
      digitalWrite(motorLeftIn2, LOW); // 两个电机都向前
      digitalWrite(motorRightIn1, HIGH);
      digitalWrite(motorRightIn2, LOW);
      break;
    case 4: // 停止
      digitalWrite(motorLeftIn1, LOW);
      digitalWrite(motorLeftIn2, LOW); // 两个电机都停止
      digitalWrite(motorRightIn1, LOW);
      digitalWrite(motorRightIn2, LOW);
      break;
    case 5: // 后退
      digitalWrite(motorLeftIn1, LOW);
      digitalWrite(motorLeftIn2, HIGH); // 两个电机都向后
      digitalWrite(motorRightIn1, LOW);
      digitalWrite(motorRightIn2, HIGH);
      break;
    default:
      // 错误处理或忽略非法输入
      break;
    }
    server.send(200, "text/plain", "Action received.");
  }
}

// ... 其余的HTML和JavaScript代码保持不变 ...