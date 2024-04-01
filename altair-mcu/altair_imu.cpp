#include "altair_imu.h"



altair::AltairIMU::AltairIMU() {}



altair::AltairIMU::~AltairIMU() {}



void altair::AltairIMU::begin() {
  Serial.begin(ALTAIR_IMU_UART_BAUDRATE);
  EEPROM.begin(ALTAIR_EEPROM_FLASH_ALLOC_SIZE);
  while(!imu.begin()) {}

  EEPROM.get(this->eeprom_addr, this->bno_id);
  imu.getSensor(&this->sensor_type);

  if(this->bno_id != this->sensor_type.sensor_id) {
    this->is_calib_data_found = false;
  }

  else {
    this->is_calib_data_found = true;

    this->eeprom_addr += sizeof(long);
    EEPROM.get(this->eeprom_addr, this->calib_data);
    imu.setSensorOffsets(this->calib_data);
  }

  vTaskDelay(pdMS_TO_TICKS(1000));
  imu.setExtCrystalUse(true);
}



bool altair::AltairIMU::isCalibDataExist() {
  return this->is_calib_data_found;
}



bool altair::AltairIMU::isCalibrated() {
  return this->imu.isFullyCalibrated();
}



void altair::AltairIMU::calibrate() {
  this->imu.getEvent(&this->sensor_event_type);
}



void altair::AltairIMU::getCalibrationStatus(uint8_t *system, uint8_t *gyro, uint8_t *accel, uint8_t *mag) {
  this->imu.getCalibration(system, gyro, accel, mag);
}



void altair::AltairIMU::saveCalibrationData() {

  this->eeprom_addr = 0;
  this->imu.getSensor(&this->sensor_type);
  this->bno_id = this->sensor_type.sensor_id;
  EEPROM.put(this->eeprom_addr, this->bno_id);

  this->eeprom_addr += sizeof(long);
  this->imu.getSensorOffsets(this->calib_data);
  EEPROM.put(this->eeprom_addr, this->calib_data);

  vTaskDelay(pdMS_TO_TICKS(1000));
}



void altair::AltairIMU::sendData2UART() {

}



void altair::AltairIMU::getEulerData() {

}



void altair::AltairIMU::getGyroData() {

}



void altair::AltairIMU::getAccelData() {

}