const int ledPin = 2; // ESP32 板载 LED 通常是 2 号引脚
unsigned long previousMillis = 0; 
const long interval = 500; // 500ms 亮, 500ms 灭，构成 1Hz
int ledState = LOW;               

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis(); 

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
  }
}