#include <WiFi.h>
#include <WebServer.h>

// 已配置的 Wi-Fi 凭据
const char* ssid = "iQOO";
const char* password = "11111111";

WebServer server(80);
const int touchPin = 4;

// 网页 HTML
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>ESP32 传感器仪表盘</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { text-align: center; font-family: 'Courier New', Courier, monospace; background-color: #222; color: #0f0; padding-top: 20vh; }
    .sensor-box { border: 2px solid #0f0; padding: 40px; display: inline-block; border-radius: 10px; }
    .value { font-size: 80px; font-weight: bold; }
  </style>
</head>
<body>
  <div class="sensor-box">
    <h2>电容触摸传感器值</h2>
    <div class="value" id="sensorVal">--</div>
  </div>

  <script>
    // 每 200 毫秒执行一次 fetch 请求抓取最新数据
    setInterval(function() {
      fetch("/data")
        .then(response => response.text())
        .then(text => {
          document.getElementById("sensorVal").innerText = text;
        });
    }, 200);
  </script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nIP Address: " + WiFi.localIP().toString());

  // 根目录，下发 HTML 页面
  server.on("/", []() { 
    server.send(200, "text/html", htmlPage); 
  });

  // 数据接口，返回当前的触摸传感器数值
  server.on("/data", []() {
    int val = touchRead(touchPin);
    server.send(200, "text/plain", String(val)); // 将数字转为字符串发送
  });

  server.begin();
}

void loop() {
  server.handleClient(); // 保持监听
}