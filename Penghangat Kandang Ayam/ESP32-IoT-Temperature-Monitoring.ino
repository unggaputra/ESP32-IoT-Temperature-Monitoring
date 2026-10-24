#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

// INFLUXDB CONFIGURATION
#define INFLUXDB_URL "https://us-east-1-1.aws.cloud2.influxdata.com"
#define INFLUXDB_TOKEN "YOUR_INFLUXDB_TOKEN"
#define INFLUXDB_ORG "YOUR_INFLUXDB_ORG"
#define INFLUXDB_BUCKET "Piranticerdas"
#define TZ_INFO "UTC7"

// BLYNK & WIFI CONFIGURATION
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

// HARDWARE CONFIGURATION
#define RELAY_PIN 19
#define DHT_SENSOR_PIN 21
#define DHT_SENSOR_TYPE DHT22

// OBJECTS
InfluxDBClient client(
  INFLUXDB_URL,
  INFLUXDB_ORG,
  INFLUXDB_BUCKET,
  INFLUXDB_TOKEN,
  InfluxDbCloud2CACert
);

Point sensor("Monitoring");
BlynkTimer timer;
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

// VARIABLES
float temperature = NAN;
float humidity = NAN;

int suhuBawah = 25;
int suhuAtas = 30;

bool relayOn = false;

void checkTemp() {
  float newTemperature = dht_sensor.readTemperature();
  float newHumidity = dht_sensor.readHumidity();

  // Check whether the sensor readings are valid
  if (isnan(newTemperature) || isnan(newHumidity)) {
    Serial.println("Failed to read DHT22 sensor!");
    return;
  }

  temperature = newTemperature;
  humidity = newHumidity;

  // Send data to Blynk
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);

  // Automatic relay control with hysteresis
  if (temperature >= suhuAtas) {
    relayOn = true;
  } 
  else if (temperature <= suhuBawah) {
    relayOn = false;
  }

  // Assumes an active-low relay module
  digitalWrite(RELAY_PIN, relayOn ? LOW : HIGH);

  // Prepare InfluxDB data
  sensor.clearFields();
  sensor.addField("Temperature", temperature);
  sensor.addField("Humidity", humidity);

  // Write data to InfluxDB Cloud
  if (client.writePoint(sensor)) {
    Serial.println("Data successfully written to InfluxDB.");
  } else {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  // Serial monitor output
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.print(" % | Relay: ");
  Serial.println(relayOn ? "ON" : "OFF");
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay initially OFF

  dht_sensor.begin();

  // Initialize Blynk connection
  Blynk.begin(auth, ssid, pass);

  // Synchronize time for InfluxDB timestamps
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // Check InfluxDB connection
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  // Set InfluxDB tags
  sensor.addTag("Device", "ESP32");
  sensor.addTag("Sensor", "DHT22");

  // Membaca sensor setiap 4 detik
  timer.setInterval(4000L, checkTemp);
}

void loop() {
  Blynk.run();
  timer.run();
}

// Sinkronkan nilai pin virtual setelah Blynk terhubung
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V2, V3);
}

// Tetapkan ambang batas suhu yang lebih rendah
BLYNK_WRITE(V2) {
  suhuBawah = param.asInt();
}

// Tetapkan ambang batas suhu atas
BLYNK_WRITE(V3) {
  suhuAtas = param.asInt();
}
