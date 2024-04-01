#include "altair_button.h"



altair::AltairButton::AltairButton() {

  pinMode(this->mux_in_pin, INPUT_PULLUP);
  pinMode(this->s0_pin, OUTPUT);
  pinMode(this->s1_pin, OUTPUT);
  pinMode(this->s2_pin, OUTPUT);
  pinMode(this->buzzer_pin, OUTPUT);

  for(uint8_t i = 0; i < ALTAIR_BUTTON_NUMBER; ++i) {
    this->btn_val[i]          = altair::AltairButton::UP;
    this->last_toggle_time[i] = millis();
  }
}



altair::AltairButton::~AltairButton() {}



void altair::AltairButton::deactivate() {
  digitalWrite(this->buzzer_pin, LOW);

  for(uint8_t i = 0; i < ALTAIR_BUTTON_NUMBER; ++i) {
    this->btn_val[i]          = altair::AltairButton::UP;
    this->last_toggle_time[i] = millis();
  }
}



altair::AltairButton::button_event_t altair::AltairButton::getButtonEvent() {
  this->getInputDebounce();
  this->evaluateButtonEvent();

  altair::AltairButton::button_event_t ret_val = this->btn_ev;
  this->btn_ev = altair::AltairButton::NONE;
  return ret_val;
}



void altair::AltairButton::getInputDebounce() {
  uint8_t button_pressed_cnt = 0;

  for(uint8_t i = 0; i < ALTAIR_BUTTON_NUMBER; ++i) {

    uint64_t  current_time  = millis(),
              diff_time     = current_time - this->last_toggle_time[i]; 

    if(diff_time > ALTAIR_BUTTON_DEBOUNCE_MS) {

      digitalWrite(this->s0_pin, HIGH && (i & ALTAIR_BUTTON_S0_MASK));
      digitalWrite(this->s1_pin, HIGH && (i & ALTAIR_BUTTON_S1_MASK));
      digitalWrite(this->s2_pin, HIGH && (i & ALTAIR_BUTTON_S2_MASK));

      bool  now_pressed   = (bool)(analogRead(this->mux_in_pin) < ALTAIR_BUTTON_ANALOG_THRESHOLD),
            prev_pressed  = (bool)((this->btn_val[i] == altair::AltairButton::DOWN) || (this->btn_val[i] == altair::AltairButton::HOLD));

      button_pressed_cnt = (now_pressed) ? button_pressed_cnt + 1 : button_pressed_cnt;

      if(now_pressed && !prev_pressed) {
        this->btn_val[i]          = altair::AltairButton::DOWN;
        this->last_toggle_time[i] = current_time;
      }

      else if(!now_pressed && prev_pressed) {
        this->btn_val[i]          = altair::AltairButton::UP;
        this->last_toggle_time[i] = current_time;
      }

      else if(now_pressed && prev_pressed && (diff_time > ALTAIR_BUTTON_HOLD_MS)) {
        this->btn_val[i] = altair::AltairButton::HOLD;
      }
    }

    digitalWrite(this->buzzer_pin, (button_pressed_cnt > 0) ? HIGH : LOW);
  }
}



void altair::AltairButton::evaluateButtonEvent() {
  altair::AltairButton::button_event_t btn_eval = altair::AltairButton::NONE;

  if(this->btn_val[ALTAIR_BUTTON_A] != altair::AltairButton::UP) {
    btn_eval = (this->btn_val[ALTAIR_BUTTON_A] == altair::AltairButton::DOWN) ? altair::AltairButton::DOWN_A : altair::AltairButton::HOLD_A;
  }

  else if(this->btn_val[ALTAIR_BUTTON_B] != altair::AltairButton::UP) {
    btn_eval = (this->btn_val[ALTAIR_BUTTON_B] == altair::AltairButton::DOWN) ? altair::AltairButton::DOWN_B : altair::AltairButton::HOLD_B;
  }

  else if(this->btn_val[ALTAIR_BUTTON_C] != altair::AltairButton::UP) {
    btn_eval = (this->btn_val[ALTAIR_BUTTON_C] == altair::AltairButton::DOWN) ? altair::AltairButton::DOWN_C : altair::AltairButton::HOLD_C;
  }

  else if(this->btn_val[ALTAIR_BUTTON_D] != altair::AltairButton::UP) {
    btn_eval = (this->btn_val[ALTAIR_BUTTON_D] == altair::AltairButton::DOWN) ? altair::AltairButton::DOWN_D : altair::AltairButton::HOLD_D;
  }

  else if(this->btn_val[ALTAIR_BUTTON_1] != altair::AltairButton::UP) {
    btn_eval = (this->btn_val[ALTAIR_BUTTON_1] == altair::AltairButton::DOWN) ? altair::AltairButton::DOWN_1 : altair::AltairButton::HOLD_1;
  }

  else if(this->btn_val[ALTAIR_BUTTON_2] != altair::AltairButton::UP) {
    btn_eval = (this->btn_val[ALTAIR_BUTTON_2] == altair::AltairButton::DOWN) ? altair::AltairButton::DOWN_2 : altair::AltairButton::HOLD_2;
  }

  else if(this->btn_val[ALTAIR_BUTTON_3] != altair::AltairButton::UP) {
    btn_eval = (this->btn_val[ALTAIR_BUTTON_3] == altair::AltairButton::DOWN) ? altair::AltairButton::DOWN_3 : altair::AltairButton::HOLD_3;
  }

  else if(this->btn_val[ALTAIR_BUTTON_4] != altair::AltairButton::UP) {
    btn_eval = (this->btn_val[ALTAIR_BUTTON_4] == altair::AltairButton::DOWN) ? altair::AltairButton::DOWN_4 : altair::AltairButton::HOLD_4;
  }

  else {
    btn_eval = altair::AltairButton::NONE;
  }

  if(btn_eval != this->btn_ev_latch) {
    this->btn_ev_latch  = btn_val;
    this->btn_ev        = btn_val;
  }
}