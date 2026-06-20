const int ledPin = 2; 
unsigned long previousMillis = 0;
const long interval = 500; 
int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis(); // 获取当前系统运行的毫秒数

  // 如果当前时间减去上次记录的时间，大于等于我们设置的间隔(500ms)
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // 更新时间记录

    // 翻转 LED 的状态
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState); // 输出状态到引脚
  }
}