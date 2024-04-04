#include "DHT.h"

const int soilAnalog = A0;
const int waterAnalog = A1;
const int tempMoistureAnalog = A2;
const int lightAnalog = A3;
const int pumpPin = 8;

int soilMoistureLevel = 0;
int waterLevel = 0;
int temperatureLevel = 0;
int humidityLevel = 0;
int lightLevel = 0;

// Create the DHT object
DHT dht(tempMoistureAnalog, DHT11);

void setup() {
  Serial.begin(9600);

  dht.begin();
  pinMode(pumpPin, OUTPUT);
}

void readSensorValues() {
  soilMoistureLevel = analogRead(soilAnalog);
  waterLevel = analogRead(waterAnalog);
  temperatureLevel = dht.readTemperature();
  humidityLevel = dht.readHumidity();
  lightLevel = analogRead(lightAnalog);
}

void sendSensorData() {
  Serial.println("Sensor Data:");
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureLevel);
  Serial.print("Water Level: ");
  Serial.println(waterLevel);
  Serial.print("Temperature: ");
  Serial.println(temperatureLevel);
  Serial.print("Humidity: ");
  Serial.println(humidityLevel);
  Serial.print("Light: ");
  Serial.println(lightLevel);
}

void controlPump() {
  if (soilMoistureLevel < 500) {  // Adjust the threshold as needed
    digitalWrite(pumpPin, HIGH);
    Serial.println("\nPump turned on.");
    delay(1000);  // Run the pump for 5 seconds (adjust as needed)
    digitalWrite(pumpPin, LOW);
    Serial.println("\nPump turned off.");
  } else {
    Serial.println("\nPump off");
  }
}

void loop() {
  readSensorValues();
  sendSensorData();
  controlPump();
  delay(10000);  // Adjust delay as needed
}
