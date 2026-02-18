#include "WiFi.h"
#include <HTTPClient.h>
#include "time.h"
#include "DHT.h" 

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 25200;  
const int daylightOffset_sec = 0;
const char* ssid = "Tucklyz";
const char* password = "pond17399";

String GOOGLE_SCRIPT_ID = "AKfycbyMoIPusIydbCXjYU_ISbbwytqqxaOhvgbwWDiV_pQK7ZsMsEE7q0G0k-q435cg132RvA";  // change Gscript ID
char timeStringBuff[80];                                                                               // 50 chars should be enough for YYYYMMDD-HHMMSS
int nCounter = 0;

#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  Serial.flush();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // เริ่มต้นการใช้งาน DHT22
  dht.begin();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    static bool flag = false;
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      Serial.println("Failed to obtain time");
      return;
    }
    strftime(timeStringBuff, sizeof(timeStringBuff), "%Y%m%d_%H%M%S", &timeinfo);
    String asString(timeStringBuff);

    String currentSSID = WiFi.SSID(); // Get current SSID

    uint8_t mac[6];
    WiFi.macAddress(mac);
    String MACAddress = WiFi.macAddress();

    float internalTemp = temperatureRead();

    float temperature = dht.readTemperature(); 
    float humidity = dht.readHumidity(); 

    Serial.print("Time >> ");
    Serial.println(asString);

    
    String urlFinal = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?" +
                      "&Item=" + String(nCounter+1) + 
                      "&DateTime=" + asString +
                      "&intData_1=" + String(random(0,299)) + 
                      "&intData_2=" + String(random(400, 599)) + 
                      "&intData_3=" + String(random(700, 999) ) + 
                      "&WiFi_Name=" + currentSSID+
                      "&MAC_Address=" + MACAddress+
                      "&Internal_ESP32_Tempperature=" + String(internalTemp)+
                      "&DHT22_Tempp=" + String(temperature) + // เพิ่มค่าอุณหภูมิ
                      "&DHT22_Humidity=" + String(humidity); // เพิ่มค่าความชื้น
    Serial.print("POST data to spreadsheet >> ");
    Serial.println(urlFinal);
    HTTPClient http;
    http.begin(urlFinal.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();
    Serial.print("HTTP Status Code: ");
    Serial.println(httpCode);
    //---------------------------------------------------------------------
    //getting response from google sheet
    String payload;
    if (httpCode > 0) {
      payload = http.getString();
      Serial.println("Payload: " + payload);
    }
    //---------------------------------------------------------------------
    http.end();
  }
  nCounter++;
  delay(30000);
}
