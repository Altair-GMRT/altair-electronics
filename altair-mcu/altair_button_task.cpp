#include "altair_mcu.h"



void altair::button_task(void *pvParameters) {
  
  uint8_t task_state    = ALTAIR_BUTTON_TASK_STATE_IDLE,
          task_req_in   = ALTAIR_BUTTON_TASK_REQ_NONE,
          task_req_out  = 0;

  altair::AltairButton                  *button   = new altair::AltairButton();
  altair::AltairButton::button_event_t  btn_ev    = altair::AltairButton::NONE; 



  while(true) {

    xQueueReceive(
      altair::button_req_queue,
      &task_req_in,
      pdMS_TO_TICKS(ALTAIR_BUTTON_TASK_REQ_WAIT_MS)
    );
    
    switch(task_req_in) {
      
      case ALTAIR_BUTTON_TASK_REQ_NONE:
        break;


      
      case ALTAIR_BUTTON_TASK_REQ_ACTIVATE:
        task_state = ALTAIR_BUTTON_TASK_STATE_ACTIVE;
        break;



      case ALTAIR_BUTTON_TASK_REQ_DEACTIVATE:
        state_init  = true;
        task_state  = ALTAIR_BUTTON_TASK_STATE_DEACTIVE;
        break;
    }

    task_req_in = ALTAIR_BUTTON_TASK_REQ_NONE;
  
  

    switch(task_state) {

      case ALTAIR_BUTTON_TASK_STATE_IDLE:
        break;



      case ALTAIR_BUTTON_TASK_STATE_DEACTIVE:
        button->deactivate();
        task_state = ALTAIR_BUTTON_TASK_STATE_IDLE;
        break;



      case ALTAIR_BUTTON_TASK_STATE_ACTIVE:
        btn_ev = button->getButtonEvent();

        switch(btn_ev) {

          case altair::AltairButton::NONE:
            break;



          case altair::AltairButton::DOWN_A:
            break;



          case altair::AltairButton::DOWN_B:
            break;



          case altair::AltairButton::DOWN_C:
            break;



          case altair::AltairButton::DOWN_D:
            break;



          case altair::AltairButton::DOWN_1:
            break;



          case altair::AltairButton::DOWN_2:
            break;



          case altair::AltairButton::DOWN_3:
            break;



          case altair::AltairButton::DOWN_4:
            break;



          case altair::AltairButton::HOLD_A:
            break;



          case altair::AltairButton::HOLD_B:
            break;



          case altair::AltairButton::HOLD_C:
            break;



          case altair::AltairButton::HOLD_D:
            break;



          case altair::AltairButton::HOLD_1:
            break;



          case altair::AltairButton::HOLD_2:
            break;



          case altair::AltairButton::HOLD_3:
            break;



          case altair::AltairButton::HOLD_4:
            break;
        }

        break;
    }



    vTaskDelay(pdMS_TO_TICKS(ALTAIR_BUTTON_TASK_DELAY));
  }
}