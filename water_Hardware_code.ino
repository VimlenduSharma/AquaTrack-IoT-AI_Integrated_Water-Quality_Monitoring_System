#include <OneWire.h>
#include <DallasTemperature.h>

// === PIN DEFINITIONS ===
#define PH_PIN 33           // pH sensor analog pin
#define TURBIDITY_PIN 34    // Turbidity sensor analog pin
#define TDS_PIN 32          // TDS sensor analog pin
#define ONE_WIRE_BUS 4      // DS18B20 data pin

// === OBJECTS ===
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin(); // Initialize DS18B20
  Serial.println("ESP32 Water Quality Monitor (pH, Turbidity, TDS, Temp)");
}

void loop() {
  // === pH Sensor ===
  int ph_raw = analogRead(PH_PIN);
  float ph_voltage = ph_raw * (3.3 / 4095.0);
  float pH_value = 3.5 * ph_voltage; // Adjust this formula based on calibration

  // === Turbidity Sensor ===
  int turbidity_raw = analogRead(TURBIDITY_PIN);
  float turbidity_voltage = turbidity_raw * (3.3 / 4095.0);

  // === TDS Sensor ===
  int tds_raw = analogRead(TDS_PIN);
  float tds_voltage = tds_raw * (3.3 / 4095.0);
  float tds_value = (133.42 * tds_voltage * tds_voltage * tds_voltage
                    - 255.86 * tds_voltage * tds_voltage
                    + 857.39 * tds_voltage) * 0.5; // Calibrated formula

  // === Temperature Sensor (DS18B20) ===
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  // === Print All Readings ===
  Serial.println("==== Water Quality Readings ====");
  Serial.printf("pH: %.2f\n", pH_value);
  Serial.printf("Turbidity: %.2f V\n", turbidity_voltage);
  Serial.printf("TDS: %.2f ppm\n", tds_value);
  Serial.printf("Temperature: %.2f °C\n", temperature);
  Serial.println("=================================\n");

  delay(2000);
}
