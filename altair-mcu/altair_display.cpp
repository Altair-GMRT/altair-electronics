#include "altair_display.h"



altair::AltairDisplay::AltairDisplay() {}



altair::AltairDisplay::~AltairDisplay() {}



void altair::AltairDisplay::begin() {
  this->display.begin(SSD1306_SWITCHCAPVCC, ALTAIR_OLED_ADDR);
  vTaskDelay(pdMS_TO_TICKS(200));

  this->display.setTextColor(SSD1306_WHITE);
  this->display.clearDisplay();
  this->display.display();
}



void altair::AltairDisplay::changeView(altair::AltairDisplay::view_t view, ...) {
  va_list args;
  String  arg_str;

  this->display.clearDisplay();

  switch(view) {

    case altair::AltairDisplay::SPLASH_SCREEN:
      break;



    case altair::AltairDisplay::IMU_CALIB:
      break;



    case altair::AltairDisplay::IMU_CALIB_FOUND:
      break;



    case altair::AltairDisplay::IMU_CALIB_SUCCESS:
      break;



    case altair::AltairDisplay::MAIN_MENU:
      break;
  }
}



void altair::AltairDisplay::refreshView() {
  this->display.display();
}