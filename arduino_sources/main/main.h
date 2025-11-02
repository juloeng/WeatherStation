////////////////////////////////////////////////////////////////////////////////
// Author      : juloeng                                                      //
// Date        : 01/11/2025                                                   //
// Description : Main header for weather station with ESP32                   //
////////////////////////////////////////////////////////////////////////////////

#ifndef MAIN.h
#define MAIN.h

// --------------------------
// LIBRARIES
// --------------------------
#include <Adafruit_GFX.h>   
#include <Adafruit_ST7789.h> 
#include <SPI.h>
#include <DHT11.h>

// --------------------------
// CONSTANTS
// --------------------------
#define TFT_MOSI 19
#define TFT_SCLK 18
#define TFT_CS 5
#define TFT_DC 16
#define TFT_RST 23
#define TFT_BL 4
#define BUTTON1_PIN 0 

// --------------------------
// MACROS
// --------------------------
extern Adafruit_ST7789 tft;
extern DHT11 dht11;

#endif
