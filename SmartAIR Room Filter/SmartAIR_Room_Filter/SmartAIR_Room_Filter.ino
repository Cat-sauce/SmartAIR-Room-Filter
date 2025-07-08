#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <DHT.h>

char ssid[] = "";
char pass[] = "";

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Sensors
#define DHTPIN 25
#define DHTTYPE DHT11
#define AQI_PIN 34
#define RELAY_PIN 15

DHT dht(DHTPIN, DHTTYPE);

// Variables
bool manualControl = false;
bool fanState = false;
int scrollX = SCREEN_WIDTH;

// Blynk button → V0
BLYNK_WRITE(V0) {
  manualControl = param.asInt();
}

String getAQICategory(int aqi) {
  if (aqi <= 50) return "Good";
  else if (aqi <= 100) return "Satisfactory";
  else if (aqi <= 200) return "Moderate";
  else if (aqi <= 300) return "Poor";
  else if (aqi <= 400) return "Very Poor";
  else return "Severe";
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(25, 24);
  display.println("Welcome to");
  display.setCursor(30, 35);
  display.println("SmartAIR");
  display.display();
  delay(4000);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  int rawAQI = analogRead(AQI_PIN);
  int aqi = map(rawAQI, 0, 4095, 0, 500);
  aqi = constrain(aqi, 0, 500);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  String category = getAQICategory(aqi);

  // Fan Logic
  if (manualControl) {
    fanState = true;
  } else {
    fanState = (aqi >= 150);
  }

  digitalWrite(RELAY_PIN, fanState ? HIGH : LOW);

  // Send data to Blynk
  Blynk.virtualWrite(V1, aqi);
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, humidity);
  Blynk.virtualWrite(V4, category);
  Blynk.virtualWrite(V5, fanState ? "ON" : "OFF");

  // OLED Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(scrollX, 0);
  display.print("SmartAIR");
  scrollX -= 2;
  if (scrollX < -60) scrollX = SCREEN_WIDTH;

  display.setCursor(0, 16);
  display.print("AQI: "); display.println(aqi);

  display.setCursor(0, 26);
  display.println(category);

  display.setCursor(0, 38);
  display.print("Temp: "); display.print(temperature); display.println(" C");

  display.setCursor(0, 50);
  display.print("Hum: "); display.print(humidity); display.println(" %");

  display.display();

  delay(1000);
}
