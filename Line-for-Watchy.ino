// ---------------------- Line-for-Watchy 0.1 -------------------------------
/////////////////////////////////////////////////////////////////////////////
// Analog Watchface for Watchy E-Paper Watch
// Design inspired by Line Watch Face for Google Wear OS by Seahorsepip
// https://play.google.com/store/apps/details?id=com.seapip.thomas.line_watchface
//
// Copyright (c) 2021 Thomas Schaefer
// thomas@blinky.berlin
/////////////////////////////////////////////////////////////////////////////
// Hardware Setup: SQFMI E-Paper Watch "Watchy"
// https://watchy.sqfmi.com/
// - ESP32-PICO-D4
// - E-Paper Display GDEH0154D67
// - 3-Axis Accelerometer BMA423
// - Real Time Clock DS3231
// - Tactile Buttons K2-1114SA-A4SW-06
// - Vibration Motor 1020
// - Battery LiPo Battery 3.7V 200mAh
/////////////////////////////////////////////////////////////////////////////
// Free Culture License:
// This work is licensed under a Creative Commons
// >>> Attribution-ShareAlike 4.0 International License (CC BY-SA 4.0) <<<
// Adaptations and commercial use are allowed AS LONG AS OTHERS SHARE ALIKE
// License terms: https://creativecommons.org/licenses/by-sa/4.0/
/////////////////////////////////////////////////////////////////////////////

#include <Watchy.h>
#include "RTClib.h"
#include "DSEG7_Classic_Regular_39.h"

//inherit and extend Watchy class
class WatchFace : public Watchy {
  public:
    //override this method to customize how the watch face looks
    void drawWatchFace() {

      // toggle between light and dark mode
      bool light = true;
      
      uint8_t myHour;
      uint8_t myMinute;
      uint8_t radius;
      float angle_hourScale;
      float angle_minuteScale;
      float angle_hourHand;
      float angle_minuteHand;
      float pi = 3.1415926535897932384626433832795;
      
      display.fillScreen(light ? GxEPD_WHITE : GxEPD_BLACK);
      display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
      display.setFont(&DSEG7_Classic_Regular_39);
      
      // draw outer circle
      //display.drawCircle(100, 100, 99, light ? GxEPD_BLACK : GxEPD_WHITE);
      //display.drawCircle(100, 100, 98, light ? GxEPD_BLACK : GxEPD_WHITE);

      myHour   = currentTime.Hour > 12 ? currentTime.Hour - 12 : currentTime.Hour;
      myMinute = currentTime.Minute;
      
      angle_hourScale   = 2*pi/12;
      angle_minuteScale = 2*pi/60;
      angle_hourHand    = angle_hourScale*(myHour-3)+2*pi/720*myMinute;
      angle_minuteHand  = angle_minuteScale*(myMinute-15);
      
      // draw minute scale
      radius = 98;
      for (uint8_t i=0; i<60; i++) {
        display.drawLine(100, 100, 100+radius*cos(angle_minuteScale*i), 100+radius*sin(angle_minuteScale*i), light ? GxEPD_BLACK : GxEPD_WHITE);
      }
      display.fillCircle(100, 100, 93, light ? GxEPD_WHITE : GxEPD_BLACK);

      // draw hour scale
      radius = 98;
      for (uint8_t i=0; i<12; i++) {
        drawHand (radius, angle_hourScale*i, light);
      }
      display.fillCircle(100, 100, 88, light ? GxEPD_WHITE : GxEPD_BLACK);

      // draw hour hand
      //radius = 45;
      //drawHand (radius, angle_hourHand, light);

      // draw minute hand
      radius = 98;
      drawHand (radius, angle_minuteHand, light);

      // draw center point
      display.fillCircle(100, 100, 45, light ? GxEPD_WHITE : GxEPD_BLACK);

      // draw helping lines
      //display.drawCircle(100, 100, 45, light ? GxEPD_BLACK : GxEPD_WHITE);
      //display.drawCircle(100, 100, 25, light ? GxEPD_BLACK : GxEPD_WHITE);

      // positioning of hour display for DSEG7_Classic_Regular_39 font
      if (currentTime.Hour > 9 && currentTime.Hour < 20) {
        display.setCursor(58, 120);
      } else {
        display.setCursor(68, 120);
      }
      
      // display hour (with a leading zero, if necessary)
      if(currentTime.Hour < 10){
          display.print("0");
      }
      display.print(currentTime.Hour);

      // draw helping lines
      //display.drawLine(100, 0, 100, 200, light ? GxEPD_BLACK : GxEPD_WHITE);
      //display.drawLine(0, 100, 200, 100, light ? GxEPD_BLACK : GxEPD_WHITE);
  }

  // helper function for hands drawing
  void drawHand (uint8_t _radius_, float _angle_, bool _light_) {
    float x = _radius_*cos(_angle_);
    float y = _radius_*sin(_angle_);
    display.drawLine(99, 99, 99+x, 99+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawLine(99, 100, 99+x, 100+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawLine(99, 101, 99+x, 101+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawLine(100, 99, 100+x, 99+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawLine(100, 100, 100+x, 100+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawLine(100, 101, 100+x, 101+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawLine(101, 99, 101+x, 99+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawLine(101, 100, 101+x, 100+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawLine(101, 101, 101+x, 101+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
  }
};

//instantiate watchface and rtc
WatchFace m;
RTC_DS3231 rtc;

void setup(){

  // start rtc and set time, if necessary
  rtc.begin();
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  
  m.init();
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
