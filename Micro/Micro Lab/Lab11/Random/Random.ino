#include "DHTesp.h" 
#include <WiFi.h> 
#include <time.h> 
#include <InfluxDbClient.h>   // https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino 
#include <InfluxDbCloud.h> 

#define Pin_DHT22 15 // D15 

DHTesp dht; 

const char* ssid = "Tucklyz"; 
const char* password = "pond17399"; 

#define HOSTNAME "ESP32 Temperature Sensor" 
#define LOCATION "1000 chem" 

// InfluxDB server URL
#define INFLUXDB_URL "https://us-east-1-1.aws.cloud2.influxdata.com" 
#define INFLUXDB_TOKEN "tXDIwqplkOZCXrMUJb8Dej1SnYImGcCti1Bzm9qMKz9-A3IUdnacY03EGuCD6W8dnn9N9-TceokUcRhiJkfohQ==" 
#define INFLUXDB_ORG "DEV" 
#define INFLUXDB_BUCKET "PP" 

int number = 0;

// InfluxDB client instance with preconfigured InfluxCloud certificate 
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert); 
Point sensor("room_sensor"); 

void sendData(float temp, float humid, float lux, float angle) { 
    Serial.print("Temperature: "); 
    Serial.print(temp); 
    Serial.print(" *C\t"); 
    Serial.print("Humidity: "); 
    Serial.print(humid); 
    Serial.print(" %\t"); 
    Serial.print("Lux: "); 
    Serial.print(lux); 
    Serial.print(" lx\t"); 
    Serial.print("Rotary Angle: "); 
    Serial.print(angle); 
    Serial.println(" deg"); 

    // Store measured value into point 
    sensor.clearFields(); 
    // Add data 
    sensor.addField("count", number); 
    sensor.addField("temperature", temp); 
    sensor.addField("humidity", humid); 
    sensor.addField("lux", lux); 
    sensor.addField("rotary_angle", angle); 

    // Print what we are exactly writing 
    Serial.print("Writing: "); 
    Serial.println(client.pointToLineProtocol(sensor)); 

    // Write point 
    if (!client.writePoint(sensor)) { 
        Serial.print("InfluxDB write failed: "); 
        Serial.println(client.getLastErrorMessage()); 
    } 
} 

void setup() { 
    Serial.begin(115200); 
    randomSeed(analogRead(0)); // Initialize random seed
    dht.setup(Pin_DHT22, DHTesp::DHT22); 
    delay(10); 
    Serial.println(); 
    Serial.print("Connecting to "); 
    Serial.println(ssid); 

    WiFi.begin(ssid, password); 
    while (WiFi.status() != WL_CONNECTED) { 
        delay(500); 
        Serial.print("."); 
    } 

    Serial.println(""); 
    Serial.println("WiFi connected"); 
    Serial.println("IP address: "); 
    Serial.println(WiFi.localIP()); 

    if (client.validateConnection()) { 
        Serial.print("Connected to InfluxDB: "); 
        Serial.println(client.getServerUrl()); 
    } else { 
        Serial.print("InfluxDB connection failed: "); 
        Serial.println(client.getLastErrorMessage()); 
    }
} 

void loop() {  
    float DHT22_Tempp = random(1000, 3000) / 100.0; 
    float DHT22_Humid = random(4000, 6000) / 100.0; 
    float GY_302 = random(7000, 9000) / 100.0; 
    float Rotary_Angle = random(10000, 11000) / 100.0; 

    Serial.print("Count: "); 
    Serial.println(number); 
    Serial.print("Temperature: "); 
    Serial.print(DHT22_Tempp); 
    Serial.print(" *C\t"); 
    Serial.print("Humidity: "); 
    Serial.print(DHT22_Humid); 
    Serial.print(" %\t"); 
    Serial.print("Lux: "); 
    Serial.print(GY_302); 
    Serial.print(" lx\t"); 
    Serial.print("Rotary Angle: "); 
    Serial.print(Rotary_Angle); 
    Serial.println(" deg"); 

    sendData(DHT22_Tempp, DHT22_Humid, GY_302, Rotary_Angle); 
    number++; 
    delay(4000); 
}
