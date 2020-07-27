/**
 * @file Sensor.h
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Contem a classe que gerencia o sensor
 * @version 1.0.6
 * @date 2020-07-27
 * 
 * @copyright Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 * 
 */

#ifndef SENSOR_H_
#define SENSOR_H_

class Sensor {
 private:
  bool status;

 public:
  Sensor(const bool);
  bool getStatus(void);
  void setStatus(const bool);
};

Sensor::Sensor(const bool nowStatus = false) {
}

/**
 * @brief Get the Status object
 * 
 * @return true Sensor aberto
 * @return false Sensor fechado
 */
bool Sensor::getStatus(void) {
  return status;
}

/**
 * @brief Set the Status object
 * 
 * @param newStatus Novo status do sensor
 */
void Sensor::setStatus(const bool newStatus) {
  status = newStatus;
}

#endif