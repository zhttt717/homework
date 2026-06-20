const int ledPin = 2;
unsigned long previousMillis = 0;
int patternIndex = 0; // 当前运行到数组的哪一步了

// 定义一个数组，偶数位(0,2,4...)代表亮的时间，奇数位(1,3,5...)代表灭的时间
const long pattern[] = {
  // S: 短闪3次 (亮200ms, 灭200ms)
  200, 200, 200, 200, 200, 600, // 最后的600是字母 S 和 O 之间的停顿
  // O: 长闪3次 (亮600ms, 灭200ms)
  600, 200, 600, 200, 600, 600, // 字母 O 和 S 之间的停顿
  // S: 短闪3次
  200, 200, 200, 200, 200, 3000 // 3000是整个SOS发送完毕后的较长停顿
};
// 计算数组的长度
const int patternLength = sizeof(pattern) / sizeof(pattern[0]);

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // 一上来先点亮，对应数组的第0位
}

void loop() {
  // 核心逻辑暂时留空
}