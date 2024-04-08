/*
  Author: Joe Glogowski
  Project: Plant Pal
  Purpose: This project is for the Plant Pal project at the Tech Showcase.
  Date: April 5, 2024
*/

#include "DHT.h"; // Include DHT library.

const int soilAnalog = A0; // Soil moisture analog pin.
const int waterAnalog = A1; // Water level analog pin.
const int tempMoistureAnalog = A2; // Temperature and moisture analog pin.
const int lightAnalog = A3; // Light analog pin.
const int pumpPin = 8; // Pump digital pin.

int soilMoistureLevel = 0; // Soil moisture level.
int waterLevel = 0; // Water level.
int temperatureLevel = 0; // Temperature level.
int humidityLevel = 0; // Humidity level.
int lightLevel = 0; // Light level.

// DHT object for temperature and humidity sensor.
DHT dht(tempMoistureAnalog, DHT11);

void setup() {
  Serial.begin(9600);

  dht.begin();
  pinMode(pumpPin, OUTPUT); // Set pump pin mode to output.
}

// Read sensor values.
void readSensorValues() {
  soilMoistureLevel = analogRead(soilAnalog);
  waterLevel = analogRead(waterAnalog);
  temperatureLevel = dht.readTemperature();
  humidityLevel = dht.readHumidity();
  lightLevel = analogRead(lightAnalog);
}

// Send sensor data.
void sendSensorData() {
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureLevel);
  Serial.print("Water Level: ");
  Serial.println(waterLevel);
  Serial.print("Temperature: ");
  Serial.print(temperatureLevel);
  Serial.print(" degrees celsius");
  Serial.print("\nHumidity: ");
  Serial.println(humidityLevel);
  Serial.print("Light: ");
  Serial.println(lightLevel);
}

// Control the pump based on soil moisture level.
void controlPump() {
  if (soilMoistureLevel < 500) {
    digitalWrite(pumpPin, HIGH); // Turn on pump.
    Serial.println("\nPump turned on.");
    delay(1000); // Run pump for 5 seconds.
    digitalWrite(pumpPin, LOW); // Turn off pump.
    Serial.println("\nPump turned off.");
  } else {
    Serial.println("\nPump off");
  }
}




void loop() {
  readSensorValues();
  sendSensorData();
  controlPump();
  delay(10000); // Delay between sensor readings.
  Serial.println("\n\n\n");
}
