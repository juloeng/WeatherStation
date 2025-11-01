////////////////////////////////////////////////////////////////////////////////
// Author      : juloeng                                                      //
// Date        : 02/03/2025                                                   //
// Description : Main file for weather station with ESP32                     //
////////////////////////////////////////////////////////////////////////////////

#include <main.h>
#include <display_function.h>

#define WAKEUP_TIME_US 10 * 1000000ULL  // 60 secondes en microsecondes

DHT11 dht11(27);
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


void setup() {

  Serial.begin(115200);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);  // Pull-up resistance on SW1
  pinMode(TFT_BL, OUTPUT);             // TTGO T-Display enable Backlight pin 4
  digitalWrite(TFT_BL, HIGH);          // T-Display turn on Backlight
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.init(135, 240);                  // Initialize ST7789 240x135
  tft.setRotation(1);
  Serial.println(F("Initialized"));
    
}

void loop() {
  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
  if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT0){
    Serial.println("Woke up because button has been pressed!");
    wakeUp();
  }
  else{
    Serial.println("Woke up because it's been a minute since the last time!");
  }
  
  deepSleep();
}

// Wake-up mode
void wakeUp() {
  int temperature = 0;
  int humidity = 0;
  Serial.println("Deep sleep mode is OFF...");    // Serial print debug 
  getTempAndHumidity(temperature, humidity);
}

// Power-saving/Deep-sleep mode 
void deepSleep() {
  tft.enableDisplay(0);
  Serial.println("\nDeep sleep mode is ON...");   // Serial print debug 
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, LOW);  // Wake-up condition is when button is pressed 
  esp_sleep_enable_timer_wakeup(WAKEUP_TIME_US);
  esp_deep_sleep_start();                         // Deep sleep starts
}
