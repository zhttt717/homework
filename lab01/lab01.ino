// 定义两个外部LED的引脚 (分别接 D4 和 D5)
const int ledPinYellow = 4;  
const int ledPinGreen = 5;   

// 设置PWM属性 (频率 5000Hz, 分辨率 8位)
const int freq = 5000;          
const int resolution = 8;       

void setup() {
  Serial.begin(9600);

  // 为两个引脚分别附加 PWM 功能
  ledcAttach(ledPinYellow, freq, resolution);
  ledcAttach(ledPinGreen, freq, resolution);
}

void loop() {
  // 逐渐变亮 (同步)
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // 同时向两个引脚写入相同的占空比
    ledcWrite(ledPinYellow, dutyCycle);   
    ledcWrite(ledPinGreen, dutyCycle);   
    delay(10);
  }

  // 逐渐变暗 (同步)
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(ledPinYellow, dutyCycle);   
    ledcWrite(ledPinGreen, dutyCycle);   
    delay(10);
  }
  
  Serial.println("Combined breathing cycle completed");
}