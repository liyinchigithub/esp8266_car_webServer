# 基于ESP8266 开发板（MCU）遥控小车

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/ea086093-c5bf-4786-9c52-e326af90d327" width="500" height="500">

* 8266 wifi 主板

<img src="https://github.com/liyinchigithub/arduino_8266_wifi_http/assets/19643260/76239ce4-ee90-4eb4-8592-a552edf20d79" width="500" height="500">

## 引脚图

<img src="https://github.com/liyinchigithub/arduino_8266_wifi_http/assets/19643260/bb6bba64-6fff-4bb0-8efd-cd1b91b4743d" width="500" height="500">

## 安装ESP8266Audio库

1. 打开Arduino IDE。

3. 在菜单栏中，选择Sketch -> Include Library -> Manage Libraries...。

5. 在弹出的库管理器窗口中，输入ESP8266Audio库到搜索框中。

7. 在搜索结果中找到ESP8266Audio by Earle FPhlhower，点击Install按钮进行安装。


## 选择开发板

1. 打开Arduino IDE。

2. 在菜单栏中，选择工具 -> 开发板 -> 选择NodeMcu1.0


<img src="https://github.com/liyinchigithub/arduino_8266_wifi_http/assets/19643260/28203800-5c51-43a8-8af3-ba9499a6872a" width="500" height="500">

## 选择端口


<img src="https://github.com/liyinchigithub/arduino_8266_wifi_http/assets/19643260/a6f60b7d-fe45-4a72-bc83-d17902110132" width="500" height="500">

## 可变速-L287N直流电机（步进器电机驱动板）

## 不可变速-L9110S直流电机（步进器电机驱动板）

<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/4b6524c5-65e4-40f3-8112-f5a8f1a63fd4" width="500" height="500">


<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/427a38aa-8058-4608-b2c3-3a224a8be586" width="500" height="500">


<img src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/63b7af22-43ba-44dd-9fcb-7d5651c6fffd" width="500" height="500">

## 遥控页面地址

<img width="300" height="200" alt="image" src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/62d7ff29-ab52-46f4-8778-2e42e55429bf">

<img width="300" height="600" alt="image" src="https://github.com/liyinchigithub/esp8266_car_webServer/assets/19643260/1be608d1-c49a-480f-9ca6-871df87c923b">


## 常见问题

如果你已经将D1和D2设置为高电平，但是马达没有运动，可能有以下几个原因：

1. 电流不足：ESP8266的GPIO引脚只能提供很小的电流（大约12mA），这可能不足以驱动马达。你可能需要一个马达驱动器或者一个适当的晶体管来放大电流。

2. 连接问题：检查你的马达是否正确连接到ESP8266和电源。

3. 马达问题：你的马达可能有问题。试着用另一个马达，或者直接用电源给马达供电，看看马达是否能运动。

4. 代码问题：检查你的代码是否正确设置了GPIO引脚为输出模式，并且设置了高电平。

如果你确定以上问题都没有，但是马达还是不能运动，你可能需要寻求更专业的帮助，或者使用专门的马达控制板（如L293D或者L298N）来驱动你的马达。


