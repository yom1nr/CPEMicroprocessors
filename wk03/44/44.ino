#include <WiFi.h>
#include "esp_wpa2.h"
#include "DHTesp.h"

// --- ตั้งค่า WiFi มหาวิทยาลัย ---
const char* ssid = "@SUT-Wifi"; 
#define EAP_ID       "B6729875"              // รหัสนักศึกษาของคุณ
#define EAP_USERNAME "B6729875"              // รหัสนักศึกษาของคุณ
#define EAP_PASSWORD "Phatsakorn@2005yom1nr" // รหัสผ่านของคุณ

// --- กำหนดขาอุปกรณ์ ---
#define Pin_DHT22 4
const int ledPins[] = {19, 18, 5, 17}; 
bool ledStates[] = {false, false, false, false};

DHTesp dht;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  dht.setup(Pin_DHT22, DHTesp::DHT22);
  for(int i=0; i<4; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  // --- ขั้นตอนการเชื่อมต่อ WPA2-Enterprise ---
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_ID, strlen(EAP_ID));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_USERNAME, strlen(EAP_USERNAME));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
  esp_wifi_sta_wpa2_ent_enable();

  WiFi.begin(ssid);

  Serial.print("\nConnecting to University WiFi");
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print("."); 
  }
  
  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    // 1. ส่วนส่งข้อมูล JSON (Telemetric Data)
    if (request.indexOf("GET /data") != -1) {
      float t = dht.getTemperature();
      float f = dht.toFahrenheit(t); // ฟาเรนไฮต์สำหรับรหัสคี่
      float h = dht.getHumidity();
      String lStat = "";
      for(int i=0; i<4; i++) lStat += (ledStates[i] ? "ON " : "OFF ");

      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: application/json");
      client.println("Connection: close");
      client.println();
      client.printf("{\"t\":\"%.2f\",\"h\":\"%.2f\",\"l\":\"%s\"}", f, h, lStat.c_str());
    }
    // 2. ส่วนควบคุม LED ผ่าน AJAX
    else if (request.indexOf("GET /update") != -1) {
      int ledIdx = request.substring(request.indexOf("led=") + 4, request.indexOf("&")).toInt();
      String state = request.substring(request.indexOf("state=") + 6, request.indexOf(" HTTP"));
      if(ledIdx >= 0 && ledIdx < 4) {
        ledStates[ledIdx] = (state == "on");
        digitalWrite(ledPins[ledIdx], ledStates[ledIdx] ? HIGH : LOW);
      }
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/plain");
      client.println();
      client.print("OK");
    }
    // 3. ส่วนหน้าเว็บสไตล์ SpaceX
    else {
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("Connection: close");
      client.println();
      client.println("<!DOCTYPE html><html lang='en'><head>");
      client.println("<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>");
      client.println("<title>SpaceX Control</title><script src='https://cdn.jsdelivr.net/npm/chart.js'></script>");
      
      client.println("<style>");
      client.println("body { background:#0b0d0f; color:white; font-family:'Segoe UI',sans-serif; display:flex; flex-direction:column; align-items:center; margin:0; padding:20px; }");
      client.println(".card { background:rgba(255,255,255,0.05); backdrop-filter:blur(10px); border:1px solid rgba(255,255,255,0.1); padding:25px; border-radius:15px; width:100%; max-width:600px; box-shadow:0 15px 35px rgba(0,0,0,0.8); }");
      client.println("h1 { letter-spacing:5px; text-transform:uppercase; border-bottom:1px solid #005288; padding-bottom:10px; font-size:1.2rem; text-align:center; color:#888; }");
      client.println(".btn-grid { display:grid; grid-template-columns:repeat(4,1fr); gap:10px; margin:20px 0; }");
      client.println(".btn { border:1px solid #005288; background:transparent; color:white; padding:10px 5px; cursor:pointer; font-size:0.7rem; transition:0.2s; }");
      client.println(".btn:hover { background:#005288; box-shadow:0 0 10px #00f2ff; }");
      client.println(".status { background:rgba(0,0,0,0.4); padding:15px; border-radius:10px; border-left:3px solid #00f2ff; font-family:monospace; font-size:0.8rem; }");
      client.println(".neon { color:#00f2ff; text-shadow:0 0 5px #00f2ff; }");
      client.println("a { color:#555; text-decoration:none; font-size:0.8rem; margin-top:20px; } a:hover { color:#00f2ff; }");
      client.println("</style></head><body>");

      client.println("<div class='card'><h1>Mission Telemetry</h1>");
      client.println("<canvas id='g' style='margin-bottom:20px;'></canvas>");
      client.println("<div class='btn-grid'>");
      for(int i=0; i<4; i++) client.printf("<button class='btn' onclick='cmd(%d,\"on\")'>L%d ON</button>", i, i+1);
      for(int i=0; i<4; i++) client.printf("<button class='btn' style='border-color:#444' onclick='cmd(%d,\"off\")'>L%d OFF</button>", i, i+1);
      client.println("</div>");
      client.println("<div class='status'>");
      client.println("<div>> SYSTEM: [<span id='l' class='neon'>READY</span>]</div>");
      client.println("<div>> TEMP: <span id='t' class='neon'>0.00</span> &deg;F</div>");
      client.println("<div>> HUMI: <span id='h' class='neon'>0.00</span> %</div>");
      client.println("</div>");
      client.println("<div style='text-align:center; margin-top:20px;'>");
      client.println("<a href='https://web.facebook.com/phatsakorn.watthanawongsa' target='_blank'>COMMANDER: PHATSAKORN W. (B6729875)</a>");
      client.println("</div></div>");

      client.println("<script>");
      client.println("let ctx=document.getElementById('g').getContext('2d');");
      client.println("let chart=new Chart(ctx,{type:'line',data:{labels:[],datasets:[{label:'Temp(F)',borderColor:'#00f2ff',data:[],fill:false,pointRadius:0},{label:'Humi(%)',borderColor:'#fff',data:[],borderDash:[5,5],fill:false,pointRadius:0}]},options:{animation:false,scales:{x:{display:false},y:{grid:{color:'#222'}}}}});");
      client.println("function cmd(l,s){fetch(`/update?led=${l}&state=${s}`);}");
      client.println("setInterval(()=>{fetch('/data').then(r=>r.json()).then(d=>{");
      client.println("document.getElementById('t').innerText=d.t; document.getElementById('h').innerText=d.h; document.getElementById('l').innerText=d.l;");
      client.println("let n=new Date().toLocaleTimeString(); chart.data.labels.push(n); chart.data.datasets[0].data.push(d.t); chart.data.datasets[1].data.push(d.h);");
      client.println("if(chart.data.labels.length>15){chart.data.labels.shift(); chart.data.datasets.forEach(x=>x.data.shift());} chart.update();");
      client.println("});},2000);</script></body></html>");
    }
    client.stop();
  }
}