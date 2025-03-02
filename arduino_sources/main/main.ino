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
DHT11 dht11(27);
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
void setup() {

  Serial.begin(9600);
  pinMode(TFT_BL, OUTPUT);      // TTGO T-Display enable Backlight pin 4
  digitalWrite(TFT_BL, HIGH);   // T-Display turn on Backlight
  tft.init(135, 240);           // Initialize ST7789 240x135
  tft.setRotation(1);
  Serial.println(F("Initialized"));
    
}

void loop() {
  int temperature = 0;
  int humidity = 0;
  int result = dht11.readTemperatureHumidity(temperature, humidity);

  if (result == 0) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C\tHumidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    print_on_screen(temperature, humidity);

  } 
  else {
    Serial.println(DHT11::getErrorString(result));
  }
}

void print_on_screen(int temp, int hum){
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.println("Temp\x82rature : " + String(temp) + "\x09 C"); //x09
  tft.setCursor(0, 60);
  tft.println("Humidit\x82    : " + String(hum) + "%");
  //tft.println(temp);
  delay(5000); 
}
