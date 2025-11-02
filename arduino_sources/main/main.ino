////////////////////////////////////////////////////////////////////////////////
// Author      : juloeng                                                      //
// Date        : 02/03/2025                                                   //
// Description : Main file for weather station with ESP32                     //
////////////////////////////////////////////////////////////////////////////////

// --------------------------
// LIBRARIES
// --------------------------
#include <main.h>
#include <display_function.h>

// --------------------------
// CONSTANTS
// --------------------------
#define WAKEUP_TIME_US 10 * 1000000ULL  // 60 secondes en microsecondes

// --------------------------
// MACROS
// --------------------------
DHT11 dht11(27);
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// --------------------------
// Setup function : Initialization
// --------------------------
void setup(){
  Serial.begin(115200);                // Serial link speed is 115200 bits/s
  pinMode(BUTTON1_PIN, INPUT_PULLUP);  // Pull-up resistance on SW1
  pinMode(TFT_BL, OUTPUT);             // TTGO T-Display enable Backlight pin 4   
  Serial.println(F("Initialized")); 
}

// --------------------------
// Main loop function
// --------------------------
void loop(){
  // Get the wake-up reason 
  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();

  // Button was pressed by operator 
  if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT0){
    Serial.println("Woke up because button was pressed!");
    DisplayMeasures();
  }
  // Time limit has been reached
  else{
    Serial.println("Woke up because time limit has been reached!");
  }

  // Always return in power-save mode 
  DeepSleep();
}


// Power-save/Deep-sleep
void DeepSleep() {
  tft.enableDisplay(0);
  Serial.println("\nDeep sleep mode is ON...");   // Serial print debug 
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, LOW);  // Wake-up condition is when button is pressed 
  esp_sleep_enable_timer_wakeup(WAKEUP_TIME_US);
  esp_deep_sleep_start();                         // Deep sleep starts
}
