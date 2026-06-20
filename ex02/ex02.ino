const int ledPin = 2; // ESP32 板载 LED 引脚
unsigned long previousMillis = 0; 
const long interval = 500; // 500ms 亮，500ms 灭
int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 核心逻辑暂时留空
}