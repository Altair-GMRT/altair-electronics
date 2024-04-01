#ifndef __ALTAIR_IMU_H__
#define __ALTAIR_IMU_H__

#include "Wire.h"
#include "EEPROM.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include "utility/imumaths.h"

#define ALTAIR_IMU_BNO055_ADDR          0x28
#define ALTAIR_IMU_UART_BAUDRATE        115200
#define ALTAIR_EEPROM_FLASH_ALLOC_SIZE  512

namespace altair {

  class AltairIMU {

    public:
      AltairIMU();
      ~AltairIMU();
      
      void begin();

      bool isCalibDataExist();
      bool isCalibrated();
      void calibrate();
      void getCalibrationStatus(uint8_t *system, uint8_t *gyro, uint8_t *accel, uint8_t *mag);
      void saveCalibrationData();
      
      void getSensorData();
      void sendData2UART();

    private:
      long                      bno_id;
      int                       eeprom_addr = 0;
      bool                      is_calib_data_found;
      adafruit_bno055_offsets_t calib_data;
      sensor_t                  sensor_type;
      sensors_event_t           sensor_event_type;

      uint8_t                   sys_calib,
                                gyr_calib,
                                accel_calib,
                                mag_calib;

      Adafruit_BNO055 imu = Adafruit_BNO055(55, ALTAIR_IMU_BNO055_ADDR);

      imu::Vector<3> elr;
      imu::Vector<3> gyr;
      imu::Vector<3> acc;

      void getEulerData();
      void getGyroData();
      void getAccelData();
  };
}

#endif