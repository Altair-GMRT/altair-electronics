#include "altair_mcu.h"



void altair::imu_task(void *pvParameters) {
  
  uint8_t task_state    = ALTAIR_IMU_TASK_STATE_IDLE,
          task_req_in   = ALTAIR_IMU_TASK_REQ_NONE,
          task_req_out  = 0;

  altair::AltairIMU *imu = new altair::AltairIMU();

  if(xSemaphoreTake(altair::i2c_mutex, portMAX_DELAY) == pdTRUE) {
    imu->begin();
    xSemaphoreGive(altair::i2c_mutex);
  }



  while(true) {

    xQueueReceive(
      altair::imu_req_queue,
      &task_req_in,
      pdMS_TO_TICKS(ALTAIR_IMU_TASK_REQ_WAIT_MS)
    );
    
    switch(task_req_in) {
      
      case ALTAIR_IMU_TASK_REQ_NONE:
        break;



      case ALTAIR_IMU_TASK_REQ_CHECK_CALIB:
        if(imu->isCalibDataExist()) {
          task_req_out  = ALTAIR_DISPLAY_TASK_REQ_IMU_CALIB_FOUND;
          task_state    = ALTAIR_IMU_TASK_STATE_LIGHT_CALIB;
        }

        else {
          task_req_out  = ALTAIR_DISPLAY_TASK_REQ_IMU_CALIB;
          task_state    = ALTAIR_IMU_TASK_STATE_INIT_CALIB;
        }

        xQueueSend(altair::display_req_queue, &task_req_out, portMAX_DELAY);
        break;



      case ALTAIR_IMU_TASK_REQ_READ:
        task_state = ALTAIR_IMU_TASK_STATE_READ;
        break;
    }

    task_req_in = ALTAIR_IMU_TASK_REQ_NONE;
  
  

    switch(task_state) {

      case ALTAIR_IMU_TASK_STATE_IDLE:
        break;



      case ALTAIR_IMU_TASK_STATE_INIT_CALIB:
        if(xSemaphoreTake(altair::i2c_mutex, portMAX_DELAY) == pdTRUE) {
          imu->calibrate();

          if(xSemaphoreTake(altair::imu_calib_data_mutex, portMAX_DELAY) == pdTRUE) {
            imu->getCalibrationStatus(&altair::imu_calib_sys, &altair::imu_calib_gyro, &altair::imu_calib_accel, &altair::imu_calib_mag);
            xSemaphoreGive(altair::imu_calib_data_mutex);
          }

          xSemaphoreGive(altair::i2c_mutex);
        }

        if(imu->isCalibrated()) {
          if(xSemaphoreTake(altair::i2c_mutex, portMAX_DELAY) == pdTRUE) {
            imu->saveCalibrationData();
            xSemaphoreGive(altair::i2c_mutex);
          }

          task_req_out = ALTAIR_DISPLAY_TASK_REQ_IMU_CALIB_SUCCESS;
          xQueueSend(altair::display_req_queue, &task_req_out, portMAX_DELAY);

          task_state = ALTAIR_IMU_TASK_STATE_IDLE;
        }
        break;



      case ALTAIR_IMU_TASK_STATE_LIGHT_CALIB:
        if(xSemaphoreTake(altair::i2c_mutex, portMAX_DELAY) == pdTRUE) {
          imu->calibrate();
          xSemaphoreGive(altair::i2c_mutex);
        }

        if(imu->isCalibrated()) {
          if(xSemaphoreTake(altair::i2c_mutex, portMAX_DELAY) == pdTRUE) {
            imu->saveCalibrationData();
            xSemaphoreGive(altair::i2c_mutex);
          }

          task_req_out = ALTAIR_DISPLAY_TASK_REQ_IMU_CALIB_SUCCESS;
          xQueueSend(altair::display_req_queue, &task_req_out, portMAX_DELAY);

          task_state = ALTAIR_IMU_TASK_STATE_IDLE;
        }
        break;



      case ALTAIR_IMU_TASK_STATE_READ:
        break;
    }



    vTaskDelay(pdMS_TO_TICKS(ALTAIR_IMU_TASK_DELAY));
  }
}