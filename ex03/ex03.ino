const int ledPin = 2;
unsigned long previousMillis = 0;
int patternIndex = 0;

const long pattern[] = {
  200, 200, 200, 200, 200, 600, 
  600, 200, 600, 200, 600, 600, 
  200, 200, 200, 200, 200, 3000 
};
const int patternLength = sizeof(pattern) / sizeof(pattern[0]);

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); 
}

void loop() {
  unsigned long currentMillis = millis();

  // 如果当前时间减去上次时间，已经达到了数组里要求的时间长度
  if (currentMillis - previousMillis >= pattern[patternIndex]) {
    previousMillis = currentMillis; // 更新时间
    patternIndex++; // 移动到数组的下一个时间

    // 如果整个数组播完了，就从头开始
    if (patternIndex >= patternLength) {
      patternIndex = 0; 
    }

    // 核心判断：偶数索引应该亮，奇数索引应该灭
    if (patternIndex % 2 == 0) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  }
}