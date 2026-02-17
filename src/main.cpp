#include <Arduino.h>
#include <HCSR04.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// --- MEMBER 2 CONFIGURATION ---
// Fill in your specific details here
char auth[] = "Your_Blynk_Auth_Token_Here"; // Found in Blynk Device Info
char ssid[] = "VITBPL";
char pass[] = "123456";

// Deep Sleep Settings (15 minutes = 900 seconds)
#define uS_TO_S_FACTOR 1000000ULL  // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP  900         // Time ESP32 will go to sleep (in seconds)

// --- MEMBER 1 CONFIGURATION (Sensor) ---
const byte triggerPin = 5;
const byte echoPin = 18;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

void setup() {
  Serial.begin(115200);

  // 1. HARDWARE INIT (Member 1)
  pinMode(2, OUTPUT); // Built-in LED

  // 2. CONNECTIVITY (Member 2)
  Serial.println("Waking up...");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to WiFi & Blynk
  Blynk.begin(auth, ssid, pass);

  // simple check to see if we connected
  if (Blynk.connected()) {
    Serial.println("Blynk Connected!");
  } else {
    Serial.println("Failed to connect to Blynk. Running offline logic...");
  }

  // 3. READ SENSOR (Member 1 Logic)
  // We take the measurement immediately after connection
  float distance = distanceSensor.measureDistanceCm();

  Serial.print("Current Trash Level: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Local feedback (LED)
  if (distance > 0 && distance < 10) {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }

  // 4. SEND DATA TO CLOUD (Member 2 Logic)
  if (Blynk.connected()) {
    // Send 'distance' to Virtual Pin V0 (Fill_Level)
    Blynk.virtualWrite(V0, distance);
    
    // IMPORTANT: Let Blynk process the data before we sleep
    Blynk.run();
    delay(2000); // Wait 2 seconds to ensure data transmission
  }

  // 5. POWER MANAGEMENT (Member 2 Logic)
  Serial.println("Data sent. Going to Deep Sleep now...");
  Serial.flush(); // Ensure all serial prints are done

  // Configure wake up timer
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  
  // Enter deep sleep
  esp_deep_sleep_start();
}

void loop() {
  // This is intentionally empty. 
  // When using Deep Sleep, the ESP32 restarts 'setup()' every time it wakes.
  // It never reaches a continuous loop.
}