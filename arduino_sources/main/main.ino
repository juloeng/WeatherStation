////////////////////////////////////////////////////////////////////////////////
// Author      : juloeng                                                      //
// Date        : 02/03/2025                                                   //
// Description : Main file for weather station with ESP32                     //
////////////////////////////////////////////////////////////////////////////////

#include <Adafruit_GFX.h>   
#include <Adafruit_ST7789.h> 
#include <SPI.h>
#include <DHT11.h>
#define TFT_MOSI 19
#define TFT_SCLK 18
#define TFT_CS 5
#define TFT_DC 16
#define TFT_RST 23
#define TFT_BL 4
#define BUTTON1_PIN 0 
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

  wakeUp();
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
  esp_deep_sleep_start();                         // Deep sleep starts
}

// Function to read temperature and humidity from the sensor 
void getTempAndHumidity(int &temperature, int &humidity) {

  int result = dht11.readTemperatureHumidity(temperature, humidity);
  if (result == 0) {
    
    Serial.print("Temperature: "   + String(temperature) + "°C"   // Serial print debug for temperature
                 "\tHumidity: "    + String(humidity)    + " %"); // Serial print debug for humidity
    print_on_screen(temperature, humidity);                       // Function to print temperature and humidity on LCD screen
  } 
  else {
    Serial.println(DHT11::getErrorString(result));
    sensorError();
  }
}

// Function to return an error on LCD screen when the sensor is defective
void sensorError() {

  tft.enableDisplay(1);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  for (int i = 0; i < 10; i++) {
    tft.setCursor(0, 30);
    tft.println("ERROR: ");
    tft.setCursor(0, 60);
    tft.println("defective sensor,"); 
    tft.setCursor(0, 90);
    tft.println("try to reset board!"); 
    delay(500); 
    tft.fillScreen(ST77XX_BLACK);
    delay(100);
  }
  
  tft.fillScreen(ST77XX_BLACK);

}

// Function to print temperature and humidity on LCD screen
void print_on_screen(int temp, int hum) {

  tft.enableDisplay(1);                                       // Switch LCD display on 
  tft.setCursor(0, 30);                                       // Set cursor on column 0 and row 30 
  tft.println("Temp\x82rature : " + String(temp) + "\x09 C"); // x09 is the hex ASCII code to print '°' character
  tft.setCursor(0, 60);                                       // Set cursor on column 0 and row 60
  tft.println("Humidit\x82    : " + String(hum) + "%");       // x82 is the hex ASCII code to print 'é' character (such a frenchy thing)
  delay(5000);                                                // 5 seconds delay
  tft.fillScreen(ST77XX_BLACK);

}
