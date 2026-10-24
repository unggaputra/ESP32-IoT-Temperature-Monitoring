#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#define INFLUXDB_URL "https://us-east-1-1.aws.cloud2.influxdata.com"
#define INFLUXDB_TOKEN "-"
#define INFLUXDB_ORG "-"
#define INFLUXDB_BUCKET "Piranticerdas"
  
  // Time zone info
#define TZ_INFO "UTC7"
#define DEVICE "ESP32"

 // Declare InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
  
Point sensor("Monitoring");

char auth[] = "Auth Token Blynk";  // isikan auth token blynk
char ssid[] = "SSID Wifi";   // isikan nama wifi
char pass[] = "Password Wifi";   // isikan password wifi

#define RELAY_PIN 19      // pin modul relay dihubungkan ke pin 25
#define DHT_SENSOR_PIN  21 // ESP32 pin GIOP21 connected to DHT22 sensor
#define DHT_SENSOR_TYPE DHT22


int Suhuatas = 0;       // variabel untuk menyimpan nilai sensor LDR
int Suhubawah = 0;
int Temperature = 0;
double Humidity = 0;

BlynkTimer timer;
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht_sensor.begin(); // initialize the DHT sensor
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  timer.setInterval(4000L, checkTemp);
  sensor.addTag("Device", DEVICE);
  sensor.addTag("Sensor", "DHT22");

      // Check server connection
    if (client.validateConnection()) {
      Serial.print("Connected to InfluxDB: ");
      Serial.println(client.getServerUrl());
    } else {
      Serial.print("InfluxDB connection failed: ");
      Serial.println(client.getLastErrorMessage());
    }
}


void loop()
{
  sensor.clearFields();
  Blynk.run();
  timer.run();
}

void checkTemp()
{ 
  Temperature = dht_sensor.readTemperature();
  Blynk.virtualWrite(V0, Temperature);
  sensor.addField("Temperature", Temperature);
  Humidity = dht_sensor.readHumidity();
  Blynk.virtualWrite(V0, Humidity);
  sensor.addField("Humidity", Humidity);

  Serial.print("Writing: ");
  Serial.println(client.pointToLineProtocol(sensor));

  if (Temperature < Suhubawah) {
    digitalWrite(RELAY_PIN, HIGH);   // jika kondisi di luar gelap, lampu menyala
    //Blynk.virtualWrite(V1, "Malam");  // mengirimkan status malam ke aplikasi Blynk
  }
  else if (Temperature >= Suhuatas){
    digitalWrite(RELAY_PIN, LOW);  // jika kondisi di luar terang, lampu dimatikan
    //Blynk.virtualWrite(V1, "Siang");  // mengirimkan status siang ke aplikasi Blynk
  }
}

BLYNK_CONNECTED() {
   Blynk.syncAll();
}

BLYNK_WRITE(V2)
{
    // here you get default value 1
    Suhubawah = param.asInt();
}

BLYNK_WRITE(V3)
{
    // here you get default value 1
    Suhuatas = param.asInt();
}
