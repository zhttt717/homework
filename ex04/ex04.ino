const int touchPin = 4;      // 触摸引脚 (例如 GPIO 4 / T0)
const int ledPin = 2;        // LED 引脚 (例如 ESP32 自带的蓝色LED引脚 2)
const int threshold = 30;    // 触摸阈值（根据你的实际板子测试调整，通常触摸时<30）

bool ledState = false;       // 布尔型状态变量，记录LED当前是亮还是灭
bool lastTouchState = false; // 记录上一次的触摸状态

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // 初始状态为灭
  Serial.begin(9600);
}

void loop() {
  // 读取当前触摸值，如果小于阈值认为被触摸 (true)
  bool currentTouchState = touchRead(touchPin) < threshold;

  // 边沿检测：上一次没摸 (!lastTouchState)，并且这一次摸了 (currentTouchState)
  if (currentTouchState && !lastTouchState) {
    delay(30); // 软件防抖：延时一小段时间再次确认
    
    // 再次确认是否真的被触摸
    if (touchRead(touchPin) < threshold) {
      ledState = !ledState;           // 翻转 LED 的状态 (自锁逻辑)
      digitalWrite(ledPin, ledState); // 更新 LED 实际状态
      Serial.println(ledState ? "LED ON" : "LED OFF");
    }
  }
  
  // 更新上一次的状态，供下一次循环使用
  lastTouchState = currentTouchState;
  delay(10); // 短暂延时，避免循环过快
}