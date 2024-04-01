#include "altair_mcu.h"



uint8_t           altair::imu_calib_sys   = 0,
                  altair::imu_calib_accel = 0,
                  altair::imu_calib_gyro  = 0,
                  altair::imu_calib_mag   = 0;

QueueHandle_t     altair::display_req_queue,
                  altair::button_req_queue,
                  altair::imu_req_queue;

SemaphoreHandle_t altair::i2c_mutex,
                  altair::imu_calib_data_mutex;



void altair::begin() {
  altair::display_req_queue = xQueueCreate(ALTAIR_DISPLAY_TASK_REQ_QUEUE_LEN, sizeof(uint8_t));
  altair::button_req_queue  = xQueueCreate(ALTAIR_BUTTON_TASK_REQ_QUEUE_LEN, sizeof(uint8_t));
  altair::imu_req_queue     = xQueueCreate(ALTAIR_IMU_TASK_REQ_QUEUE_LEN, sizeof(uint8_t));

  altair::i2c_mutex             = xSemaphoreCreateMutex();
  altair::imu_calib_data_mutex  = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(
    altair::display_task,
    "altair_display_task",
    ALTAIR_DISPLAY_TASK_STACK_SIZE,
    NULL,
    ALTAIR_DISPLAY_TASK_PRIORITY,
    NULL,
    ALTAIR_DISPLAY_TASK_CORE
  );

  xTaskCreatePinnedToCore(
    altair::button_task,
    "altair_button_task",
    ALTAIR_BUTTON_TASK_STACK_SIZE,
    NULL,
    ALTAIR_BUTTON_TASK_PRIORITY,
    NULL,
    ALTAIR_BUTTON_TASK_CORE
  );

  xTaskCreatePinnedToCore(
    altair::imu_task,
    "altair_imu_task",
    ALTAIR_IMU_TASK_STACK_SIZE,
    NULL,
    ALTAIR_IMU_TASK_PRIORITY,
    NULL,
    ALTAIR_IMU_TASK_CORE
  );
}