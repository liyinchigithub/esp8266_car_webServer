#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

// const char* ssid = "302"; // WiFi账号
// const char* password = "123456781"; // WiFi密码

const char *ssid = "遥控小车";      // 你想要的热点名称
const char *password = "12345678";  // 热点的密码，至少8个字符

// 定义L298N电机驱动板的引脚
const int motorLeftIn1 = D1;   // 左电机输入1
const int motorLeftIn2 = D2;   // 左电机输入2
const int motorRightIn1 = D3;  // 右电机输入1
const int motorRightIn2 = D4;  // 右电机输入2
const int motorLeftEn = D5;    // 左电机使能
const int motorRightEn = D6;   // 右电机使能

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
// JavaScript代码
function startCommand(action) {
  // 发送开始运动的指令到Arduino
  fetch('/start', {
    method: 'POST',
    body: JSON.stringify({ action: action }),
    headers: {
      'Content-Type': 'application/json'
    }
  });
}

function stopCommand() {
  // 发送停止运动的指令到Arduino
  fetch('/stop', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    }
  });
}

// 修改事件监听器来处理按下和松开
document.addEventListener('DOMContentLoaded', function() {
  const buttons = document.querySelectorAll('button');
  buttons.forEach(button => {
    // 鼠标事件
    button.addEventListener('mousedown', () => startCommand(button.dataset.action));
    button.addEventListener('mouseup', stopCommand);
    button.addEventListener('mouseleave', stopCommand);
    // 触摸事件
    button.addEventListener('touchstart', (e) => {
      e.preventDefault(); // 阻止触摸时屏幕的滚动
      startCommand(button.dataset.action);
    });
    button.addEventListener('touchend', stopCommand);
  });
});
</script>
</head>
<body>
<div id="control-panel">
  <button id="forward" class="blue-button" data-action="3">前</button>
  <div id="horizontal-controls">
    <button id="left" class="blue-button" data-action="1">左</button>
    <button id="right" class="blue-button" data-action="2">右</button>
  </div>
  <button id="backward" class="blue-button" data-action="5">后</button>
</div>
<!-- MJPEG流 -->
<div style="margin-top: 20px;">
  // <img style="display: block; -webkit-user-select: none; margin: auto; background-color: hsl(0, 0%, 25%);" src="http://192.168.4.2/mjpeg/1">
</div>
</body>
</html>
)rawliteral";

ESP8266WebServer server(80);

// 函数原型声明
void setMotorState(int action, bool continuous);
void handleGet();
void handlePost();

// 停止所有电机
void stopMotors() {
  digitalWrite(motorLeftIn1, LOW);
  digitalWrite(motorLeftIn2, LOW);
  digitalWrite(motorRightIn1, LOW);
  digitalWrite(motorRightIn2, LOW);
}

// 处理开始运动的请求
void handleStart() {
  if (server.method() == HTTP_POST) {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, server.arg("plain"));
    int action = doc["action"].as<int>();
    setMotorState(action, true);  // 开始运动
    server.send(200, "text/plain", "Start action received.");
  }
}

// 处理停止运动的请求
void handleStop() {
  if (server.method() == HTTP_POST) {
    stopMotors();  // 停止所有电机
    server.send(200, "text/plain", "Stop action received.");
  }
}



// 初始化
void setup() {
  Serial.begin(115200);
  // 连接WiFi
  // WiFi.begin(ssid, password);
  // Serial.println("Attempting to connect to WiFi network...");

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.print(".");
  // }

  bool ssid_hidden = false; // 设置为true可以隐藏SSID
  int channel = 1;          // 设置WiFi信道
  int max_connection = 4;   // 设置最大连接数
  // 设置ESP8266为AP模式，使用上面定义的SSID和密码
  bool result = WiFi.softAP(ssid, password, channel, ssid_hidden, max_connection);
  Serial.println("ESP8266 is set as a WiFi Access Point with SSID: " + String(ssid));

  if(result) {
    Serial.println("Access Point Started");
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
  } else {
    Serial.println("Access Point Failed to Start");
  }

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
  server.on("/command", handlePost);  // 短按命令
  server.on("/start", handleStart);   // 开始运动的请求
  server.on("/stop", handleStop);     // 停止运动的请求
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}

// 处理GET请求以返回HTML页面
void handleGet() {
  if (server.method() == HTTP_GET) {
    server.send(200, "text/html", webpage);
  }
}

// 处理POST请求以控制电机
void handlePost() {
  if (server.method() == HTTP_POST) {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, server.arg("plain"));
    int action = doc["action"].as<int>();
    bool longPress = doc["longPress"].as<bool>();  // 长按标志

    setMotorState(action, longPress);

    if (!longPress) {
      delay(1000);   // 短按持续1秒
      stopMotors();  // 停止电机
    }

    server.send(200, "text/plain", "Action received.");
  }
}

void setMotorState(int action, bool continuous) {
  // 根据action设置电机状态
  switch (action) {
    case 1:  // 左转
      digitalWrite(motorLeftIn1, HIGH);
      digitalWrite(motorLeftIn2, LOW);  // 一个电机向前
      digitalWrite(motorRightIn1, LOW);
      digitalWrite(motorRightIn2, HIGH);  // 另一个电机向后
      break;
    case 2:  // 右转
      digitalWrite(motorLeftIn1, LOW);
      digitalWrite(motorLeftIn2, HIGH);  // 一个电机向后
      digitalWrite(motorRightIn1, HIGH);
      digitalWrite(motorRightIn2, LOW);  // 另一个电机向前
      break;
    case 3:  // 前进
      digitalWrite(motorLeftIn1, HIGH);
      digitalWrite(motorLeftIn2, LOW);  // 两个电机都向前
      digitalWrite(motorRightIn1, HIGH);
      digitalWrite(motorRightIn2, LOW);
      break;
    case 5:  // 后退
      digitalWrite(motorLeftIn1, LOW);
      digitalWrite(motorLeftIn2, HIGH);  // 两个电机都向后
      digitalWrite(motorRightIn1, LOW);
      digitalWrite(motorRightIn2, HIGH);
      break;
    default:
      // 如果收到的action不是预期的，停止所有电机
      stopMotors();
      break;
  }
  // 如果不是长按，不需要在这里停止电机，因为会有单独的停止请求
}
