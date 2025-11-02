////////////////////////////////////////////////////////////////////////////////
// Author      : juloeng                                                      //
// Date        : 01/11/2025                                                   //
// Description : Display temperature, humidity, date and time on display      //
////////////////////////////////////////////////////////////////////////////////

// --------------------------
// LIBRARIES
// --------------------------
#include <main.h>
#include <display_function.h>

// --------------------------
// Main function to display temperature, humidity, date and time 
// --------------------------
void DisplayMeasures(){
  // Manage screen setup 
  digitalWrite(TFT_BL, HIGH);          // T-Display turn on Backlight
  tft.setTextWrap(false);              // Do not return to 
  tft.fillScreen(ST77XX_BLACK);        // Fill screen with black 
  tft.setTextColor(ST77XX_WHITE);      // Set text color to white 
  tft.setTextSize(2);                  // Set text size to 2 
  tft.init(135, 240);                  // Initialize ST7789 240x135
  tft.setRotation(2); 
  getTempHum();  
}

// --------------------------
// Read temperature and humidity from DHT11 sensor 
// --------------------------
void getTempHum(){
  
  // Variables init 
  int temperature, humidity; 
   
  // Read from sensor 
  int result = dht11.readTemperatureHumidity(temperature, humidity);
  
  // Sensor is not defective   
  if (result == 0){
    // Serial print temperature and humidity in console (for debug only) 
    Serial.print("Temp: " + String(temperature) + "°C\tHum: " + String(humidity) + " %"); 
    // Call the function to display temperature and humidity on screen 
    print_on_screen(temperature, humidity);
  } 
  // Sensor is defective 
  else{
    // Serial print error logs (for debug only) 
    Serial.println(DHT11::getErrorString(result));
    // Call the function to display an error message on screen 
    sensorError();
  }
  
}

// --------------------------
// Display temperature and humidity screen
// --------------------------
void print_on_screen(int temp, int hum) {

  tft.enableDisplay(1);                 // Turn display on 
  tft.setCursor(0, 30);                 // Set cursor on column 0 and row 30 
  tft.println(String(temp) + "\x09 C"); // Display <Temperature> °C
  tft.setCursor(0, 60);                 // Set cursor on column 0 and row 60
  tft.println(String(hum) + "%");       // Display <Humidity> %
  delay(5000);                          // 5 seconds delay
  tft.fillScreen(ST77XX_BLACK);         // Fill screen with black              

}

// --------------------------
// Display an error message when sensor is defective 
// --------------------------
void sensorError() {
  tft.setTextColor(ST77XX_RED);
  for (int i = 0; i < 10; i++) {
    tft.enableDisplay(1);
    tft.setCursor(0, 30);
    tft.println("ERROR: ");
    tft.setCursor(0, 60);
    tft.println("defective sensor,"); 
    tft.setCursor(0, 90);
    tft.println("try to reset board!"); 
    delay(10000);
  }
}
