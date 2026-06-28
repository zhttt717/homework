const int ledA = 2;  // 灯 A 连接的引脚
const int ledB = 4;  // 灯 B 连接的引脚
int delayTime = 5;   // 过渡速度

void setup() {
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() {
  // 占空比从 0 增加到 255
  for (int i = 0; i <= 255; i++) {
    analogWrite(ledA, i);         // 灯 A 变亮 (0 -> 255)
    analogWrite(ledB, 255 - i);   // 灯 B 变暗 (255 -> 0)
    delay(delayTime);
  }
  
  // 占空比从 255 减小到 0
  for (int i = 255; i >= 0; i--) {
    analogWrite(ledA, i);         // 灯 A 变暗 (255 -> 0)
    analogWrite(ledB, 255 - i);   // 灯 B 变亮 (0 -> 255)
    delay(delayTime);
  }
}