#ifndef __ALTAIR_MCU_H__
#define __ALTAIR_MCU_H__

#include "altair_display.h"
#include "altair_button.h"
#include "altair_imu.h"
#include "altair_task_states.h"

#define ALTAIR_DISPLAY_TASK_STACK_SIZE      32000
#define ALTAIR_DISPLAY_TASK_PRIORITY        1
#define ALTAIR_DISPLAY_TASK_CORE            1
#define ALTAIR_DISPLAY_TASK_DELAY           30
#define ALTAIR_DISPLAY_TASK_REQ_QUEUE_LEN   8
#define ALTAIR_DISPLAY_TASK_REQ_WAIT_MS     0

#define ALTAIR_BUTTON_TASK_STACK_SIZE       54000
#define ALTAIR_BUTTON_TASK_PRIORITY         2
#define ALTAIR_BUTTON_TASK_CORE             1
#define ALTAIR_BUTTON_TASK_DELAY            40
#define ALTAIR_BUTTON_TASK_REQ_QUEUE_LEN    8
#define ALTAIR_BUTTON_TASK_REQ_WAIT_MS      0

#define ALTAIR_IMU_TASK_STACK_SIZE          32000
#define ALTAIR_IMU_TASK_PRIORITY            1
#define ALTAIR_IMU_TASK_CORE                0
#define ALTAIR_IMU_TASK_DELAY               0
#define ALTAIR_IMU_TASK_REQ_QUEUE_LEN       8
#define ALTAIR_IMU_TASK_REQ_WAIT_MS         0

namespace altair {

  extern uint8_t            imu_calib_sys,
                            imu_calib_gyro,
                            imu_calib_accel,
                            imu_calib_mag;

  extern QueueHandle_t      display_req_queue,
                            button_req_queue,
                            imu_req_queue;

  extern SemaphoreHandle_t  i2c_mutex,
                            imu_calib_data_mutex;

  void display_task(void* pvParameters);
  void button_task(void* pvParameters);
  void imu_task(void* pvParameters);
  void begin();
}

#endif