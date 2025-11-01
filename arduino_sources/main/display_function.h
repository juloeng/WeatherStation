////////////////////////////////////////////////////////////////////////////////
// Author      : juloeng                                                      //
// Date        : 01/11/2025                                                   //
// Description : Display temperature, humidity, date and time on display      //
////////////////////////////////////////////////////////////////////////////////

#ifndef DISPLAY_FUNCTION.h
#define DISPLAY_FUNCTION.h

void getTempAndHumidity(int &temperature, int &humidity);
void sensorError();
void print_on_screen(int temp, int hum);

#endif
