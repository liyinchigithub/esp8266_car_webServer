# 基于ESP8266 开发板（MCU）遥控小车

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/ea086093-c5bf-4786-9c52-e326af90d327" width="300" height="300">


## 材料

ESP8266主板1个、步进器1个（电机驱动）、3.7V电池1个、车身架1个、2个轮胎和2个小马达、跳线若干。

### 一、ESP8266 NodeMCU 单片机

<img src="https://github.com/liyinchigithub/arduino_8266_wifi_http/assets/19643260/76239ce4-ee90-4eb4-8592-a552edf20d79" width="300" height="400">

#### 引脚图

<img src="https://github.com/liyinchigithub/arduino_8266_wifi_http/assets/19643260/bb6bba64-6fff-4bb0-8efd-cd1b91b4743d" width="400" height="300">

#### Arduino IDE 安装ESP8266Audio库

1. 打开Arduino IDE。

3. 在菜单栏中，选择Sketch -> Include Library -> Manage Libraries...。

5. 在弹出的库管理器窗口中，输入ESP8266Audio库到搜索框中。

7. 在搜索结果中找到ESP8266Audio by Earle FPhlhower，点击Install按钮进行安装。


#### 选择开发板

1. 打开Arduino IDE。

2. 在菜单栏中，选择工具 -> 开发板 -> 选择NodeMcu1.0


<img src="https://github.com/liyinchigithub/arduino_8266_wifi_http/assets/19643260/28203800-5c51-43a8-8af3-ba9499a6872a" width="500" height="300">

#### 选择端口


<img src="https://github.com/liyinchigithub/arduino_8266_wifi_http/assets/19643260/a6f60b7d-fe45-4a72-bc83-d17902110132" width="200" height="150">

### 二、（可变速）L287N直流电机（步进器电机驱动板）

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/4be41a85-daaa-47ba-a8ee-69594b922bd1" width="200" height="550">

1. OUT1和OUT2 电池1、OUT3和OUT4 电池2

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/cc0a4d85-65d7-4f76-acab-0b359a90d4be" width="300" height="200">


2. 12V电源正极、GND电源负极+8266电源负极 、+5V8266引脚

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/c999d437-46b0-43eb-8c7f-5f245023c422" width="300" height="200">


3. ENA：电机1PWM调速引脚

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/4fabed0e-b6d7-4cd6-9a88-b94c54a44d8c" width="300" height="200">

**注意**：不使用调速引脚，那两个塑料不要拔起来，拔起来后需要用“母对母”跳线连接

5. ENB：电机2PWM调速引脚

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/e572ce93-db48-47b2-bff0-e6e7f846b1cb" width="300" height="200">


6. IN1和IN2：电机1 正反转/停止控制
   
<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/73b05a29-3d88-49ee-ac6e-4be1033e2765" width="300" height="200">

7. IN3和IN4：电机2 正反转/停止控制

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/b9c65e78-46da-4abe-b596-874bfc079843" width="300" height="200">


8.左右电机控制

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/f0de3c2f-4cdc-4fba-9f51-eb6617a97c96" width="300" height="200">


9.引脚对接

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/d2b2ce52-44fb-4903-a1cd-41f9e2f1b2eb" width="200" height="200">

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/0c27b5c8-5c60-4ea2-aef6-1f0f54a0f2ec" width="200" height="200">



[B站视频1](https://www.bilibili.com/video/BV1TW4y1y7PT/?spm_id_from=333.337.search-card.all.click&vd_source=73d9ae1d519db8c687b2d2e7b02c99ed)
[B站视频2](https://www.bilibili.com/video/BV1Xt411372X/?spm_id_from=autoNext&vd_source=73d9ae1d519db8c687b2d2e7b02c99ed)





### 三、（不可变速）L9110S直流电机（步进器电机驱动板）

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/4b6524c5-65e4-40f3-8112-f5a8f1a63fd4" width="500" height="500">


<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/427a38aa-8058-4608-b2c3-3a224a8be586" width="500" height="500">


<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/63b7af22-43ba-44dd-9fcb-7d5651c6fffd" width="500" height="500">

## 遥控按钮页面

1.程序烧入ESP8266主板后，生成wifi热点：“遥控小车”；
2.使用手机或平板连接热点密码：12345678
3.浏览器地址：http://192.168.4.1

<img width="300" height="600" alt="image" src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/7ca61931-389f-4d21-8b0d-e1590c4028b9">


## 常见问题

如果你已经将D1和D2设置为高电平，但是马达没有运动，可能有以下几个原因：

1. 电流不足：ESP8266的GPIO引脚只能提供很小的电流（大约12mA），这可能不足以驱动马达。你可能需要一个马达驱动器或者一个适当的晶体管来放大电流。

2. 连接问题：检查你的马达是否正确连接到ESP8266和电源。

3. 马达问题：你的马达可能有问题。试着用另一个马达，或者直接用电源给马达供电，看看马达是否能运动。

4. 代码问题：检查你的代码是否正确设置了GPIO引脚为输出模式，并且设置了高电平。

如果你确定以上问题都没有，但是马达还是不能运动，你可能需要寻求更专业的帮助，或者使用专门的马达控制板（如L293D或者L298N）来驱动你的马达。


