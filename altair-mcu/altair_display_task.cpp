#include "altair_mcu.h"



void altair::display_task(void *pvParameters) {
  
  uint8_t task_state    = ALTAIR_DISPLAY_TASK_STATE_SPLASH_SCREEN,
          task_req_in   = ALTAIR_DISPLAY_TASK_REQ_NONE,
          task_req_out  = 0;

  altair::AltairDisplay *display = new altair::AltairDisplay();

  if(xSemaphoreTake(altair::i2c_mutex, portMAX_DELAY) == pdTRUE) {
    display->begin();
    xSemaphoreGive(altair::i2c_mutex);
  }



  while(true) {

    xQueueReceive(
      altair::display_req_queue,
      &task_req_in,
      pdMS_TO_TICKS(ALTAIR_DISPLAY_TASK_REQ_WAIT_MS)
    );
    
    switch(task_req_in) {
      
      case ALTAIR_DISPLAY_TASK_REQ_NONE:
        break;


      case ALTAIR_DISPLAY_TASK_REQ_IMU_CALIB:
        task_state = ALTAIR_DISPLAY_TASK_STATE_IMU_CALIB;
        break;



      case ALTAIR_DISPLAY_TASK_REQ_IMU_CALIB_FOUND:
        task_state = ALTAIR_DISPLAY_TASK_STATE_IMU_CALIB_FOUND;
        break;



      case ALTAIR_DISPLAY_TASK_REQ_IMU_CALIB_SUCCESS:
        task_state = ALTAIR_DISPLAY_TASK_STATE_IMU_CALIB_SUCCESS;
        break;



      case ALTAIR_DISPLAY_TASK_REQ_CURSOR_INC:
        break;



      case ALTAIR_DISPLAY_TASK_REQ_CURSOR_DEC:
        break;



      case ALTAIR_DISPLAY_TASK_REQ_ENTER:
        break;



      case ALTAIR_DISPLAY_TASK_REQ_BACK:
        break;
    }

    task_req_in = ALTAIR_DISPLAY_TASK_REQ_NONE;
  
  

    switch(task_state) {

      case ALTAIR_DISPLAY_TASK_STATE_IDLE:
        break;



      case ALTAIR_DISPLAY_TASK_STATE_SPLASH_SCREEN:
        if(xSemaphoreTake(altair::i2c_mutex, portMAX_DELAY) == pdTRUE) {
          display->changeView(altair::AltairDisplay::SPLASH_SCREEN);
          display->refreshView();
          xSemaphoreGive(altair::i2c_mutex);
        }

        task_req_out = ALTAIR_IMU_TASK_REQ_CHECK_CALIB;
        xQueueSend(altair::imu_req_queue, &task_req_out, portMAX_DELAY);

        task_state = ALTAIR_DISPLAY_TASK_STATE_IDLE;
        break;



      case ALTAIR_DISPLAY_TASK_STATE_IMU_CALIB:
        if(xSemaphoreTake(altair::i2c_mutex, portMAX_DELAY) == pdTRUE) {
          
          if(xSemaphoreTake(altair::imu_calib_data_mutex, portMAX_DELAY) == pdTRUE) {
            display->changeView(
              altair::AltairDisplay::IMU_CALIB, 
              String((int)altair::imu_calib_sys),
              String((int)altair::imu_calib_gyro),
              String((int)altair::imu_calib_accel),
              String((int)altair::imu_calib_mag)
            );
            xSemaphoreGive(altair::imu_calib_data_mutex);
          }

          display->refreshView();

          xSemaphoreGive(altair::i2c_mutex);
        }
        break;



      case ALTAIR_DISPLAY_TASK_STATE_IMU_CALIB_FOUND:
        if(xSemaphoreTake(altair::i2c_mutex, portMAX_DELAY) == pdTRUE) {
          display->changeView(altair::AltairDisplay::IMU_CALIB_FOUND);
          display->refreshView();

          xSemaphoreGive(altair::i2c_mutex);
        }
        break;  



      case ALTAIR_DISPLAY_TASK_STATE_IMU_CALIB_SUCCESS:
        if(xSemaphoreTake(altair::i2c_mutex, portMAX_DELAY) == pdTRUE) {
          display->changeView(altair::AltairDisplay::IMU_CALIB_SUCCESS);
          display->refreshView();

          xSemaphoreGive(altair::i2c_mutex);
        }

        vTaskDelay(pdMS_TO_TICKS(2500));
        task_state = ALTAIR_DISPLAY_TASK_STATE_MAIN_MENU;
        break;



      case ALTAIR_DISPLAY_TASK_STATE_MAIN_MENU:
        break;
    }



    vTaskDelay(pdMS_TO_TICKS(ALTAIR_DISPLAY_TASK_DELAY));
  }
}