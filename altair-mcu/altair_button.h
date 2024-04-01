#ifndef __ALTAIR_BUTTON_H__
#define __ALTAIR_BUTTON_H__

#include "altair_pins.h"

#define ALTAIR_BUTTON_NUMBER            8
#define ALTAIR_BUTTON_DEBOUNCE_MS       80
#define ALTAIR_BUTTON_HOLD_MS           2000
#define ALTAIR_BUTTON_ANALOG_THRESHOLD  100

#define ALTAIR_BUTTON_A 0
#define ALTAIR_BUTTON_B 1
#define ALTAIR_BUTTON_C 2
#define ALTAIR_BUTTON_D 3
#define ALTAIR_BUTTON_1 4
#define ALTAIR_BUTTON_2 5
#define ALTAIR_BUTTON_3 6
#define ALTAIR_BUTTON_4 7

#define ALTAIR_BUTTON_S0_MASK B00000001
#define ALTAIR_BUTTON_S1_MASK B00000010
#define ALTAIR_BUTTON_S2_MASK B00000100

namespace altair {

  class AltairButton {

    public:
      AltairButton();
      ~AltairButton();

      enum press_t {
        UP,
        DOWN,
        HOLD
      };

      enum button_event_t {
        NONE,
        DOWN_A, DOWN_B, DOWN_C, DOWN_D,
        DOWN_1, DOWN_2, DOWN_3, DOWN_4,
        HOLD_A, HOLD_B, HOLD_C, HOLD_D,
        HOLD_1, HOLD_2, HOLD_3, HOLD_4
      };

      void            deactivate();
      button_event_t  getButtonEvent();

    private:
      uint8_t         mux_in_pin  = ALTAIR_MUX_IN_PIN,
                      s0_pin      = ALTAIR_MUX_S0_PIN,
                      s1_pin      = ALTAIR_MUX_S1_PIN,
                      s2_pin      = ALTAIR_MUX_S2_PIN,
                      buzzer_pin  = ALTAIR_BUZZER_PIN;

      press_t         btn_val[ALTAIR_BUTTON_NUMBER];

      button_event_t  btn_ev_latch  = NONE,
                      btn_ev        = NONE;

      uint64_t        last_toggle_time[ALTAIR_BUTTON_NUMBER];

      void getInputDebounce();
      void evaluateButtonEvent();
  };
}

#endif