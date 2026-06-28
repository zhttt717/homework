const int touchPin = 4;
const int ledPin = 2;
const int threshold = 30;

int speedGear = 1;           // 速度档位：1(慢), 2(中), 3(快)
int currentDelay = 15;       // 当前档位对应的呼吸延时

bool lastTouchState = false; // 触摸状态
int brightness = 0;          // PWM 占空比 (0-255)
int fadeAmount = 5;          // 每次渐变的步长
unsigned long lastFadeTime = 0; // 记录上次更新亮度的时间

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // ========== 1. 触摸换挡逻辑 (包含边沿检测与防抖) ==========
  bool currentTouchState = touchRead(touchPin) < threshold;
  
  if (currentTouchState && !lastTouchState) {
    delay(30); // 防抖
    if (touchRead(touchPin) < threshold) {
      speedGear++; // 切换档位
      if (speedGear > 3) speedGear = 1; // 1->2->3->1 循环
      
      // 根据档位改变呼吸节奏 (延时越小，呼吸越急促)
      if (speedGear == 1) currentDelay = 15;      // 缓慢
      else if (speedGear == 2) currentDelay = 7;  // 中等
      else if (speedGear == 3) currentDelay = 2;  // 急促
      
      Serial.printf("当前档位: %d\n", speedGear);
    }
  }
  lastTouchState = currentTouchState;

  // ========== 2. 呼吸灯逻辑 (使用 millis 非阻塞方式) ==========
  if (millis() - lastFadeTime >= currentDelay) {
    analogWrite(ledPin, brightness); // 输出 PWM
    brightness = brightness + fadeAmount;
    
    // 到达边界后反转步长方向
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    lastFadeTime = millis(); // 更新时间
  }
}