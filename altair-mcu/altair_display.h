#ifndef __ALTAIR_DISPLAY_H__
#define __ALTAIR_DISPLAY_H__

#include <stdarg.h>
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define ALTAIR_SCREEN_WIDTH   128
#define ALTAIR_SCREEN_HEIGHT  64
#define ALTAIR_OLED_ADDR      0x3C
#define ALTAIR_OLED_RESET     -1

namespace altair {

  class AltairDisplay {

    public:
      AltairDisplay();
      ~AltairDisplay();

      enum view_t {
        SPLASH_SCREEN,
        IMU_CALIB,
        IMU_CALIB_FOUND,
        IMU_CALIB_SUCCESS,
        MAIN_MENU
      };

      void begin();
      void changeView(view_t view, ...);
      void refreshView();

    private:
      Adafruit_SSD1306 display = Adafruit_SSD1306(
        ALTAIR_SCREEN_WIDTH, 
        ALTAIR_SCREEN_HEIGHT, 
        &Wire, 
        ALTAIR_OLED_RESET
      );
  };
}

#endif