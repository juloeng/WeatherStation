////////////////////////////////////////////////////////////////////////////////
// Author      : juloeng                                                      //
// Date        : 01/11/2025                                                   //
// Description : Display temperature, humidity, date and time on display      //
////////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include <display_function.h>

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
