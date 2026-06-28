#include <WiFi.h>
#include <WebServer.h>

// 已配置的 Wi-Fi 凭据
const char* ssid = "iQOO";
const char* password = "11111111";

WebServer server(80); // 运行在 80 端口的 Web 服务器
const int ledPin = 2; // LED 引脚

// 网页的 HTML 代码
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>ESP32 无极调光器</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { text-align: center; font-family: Arial; padding-top: 50px; }
    input[type=range] { width: 80%; max-width: 400px; }
  </style>
</head>
<body>
  <h1>LED 亮度调节</h1>
  <p>当前亮度: <span id="brightnessVal">0</span></p >
  <input type="range" min="0" max="255" value="0" id="pwmSlider" oninput="updatePWM(this.value)">
  <script>
    function updatePWM(val) {
      document.getElementById("brightnessVal").innerText = val;
      fetch("/set?val=" + val); 
    }
  </script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 0);

  // 连接 WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected! IP Address: ");
  Serial.println(WiFi.localIP());

  // 配置路由
  server.on("/", []() {
    server.send(200, "text/html", htmlPage); 
  });

  server.on("/set", []() {
    if (server.hasArg("val")) {
      String valStr = server.arg("val"); 
      int pwmValue = valStr.toInt();
      analogWrite(ledPin, pwmValue);     // 改变 LED 亮度
    }
    server.send(200, "text/plain", "OK");
  });

  server.begin(); // 启动服务器
}

void loop() {
  server.handleClient(); // 处理网页客户端的请求
}