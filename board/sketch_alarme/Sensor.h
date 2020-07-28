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

#include "Led.h"

class Sensor {
 private:
  bool status;     //! Status do sensor
  short number;    //! Número do sensor
  Led* ledPainel;  //! Led do sensor no painel
  void setNumber(const short);

 public:
  Sensor(const short, const bool);
  bool getStatus(void);
  void setStatus(const bool);
  short getNumber(void);
};

/**
 * @brief Construct a new Sensor:: Sensor object
 * 
 * @param newNumber Número do sensor
 * @param newLed Led do painel referente ao sensor
 * @param nowStatus Status atual do sensor
 */
Sensor::Sensor(const short newNumber, const bool nowStatus = false) {
  setNumber(newNumber);
  setStatus(nowStatus);
  const short ledNumberNow = newNumber + 1;
  ledPainel = new Led(ledNumberNow, getStatus());
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
  if (getStatus()) {
    ledPainel->turnOn();
  } else {
    ledPainel->turnOff();
  }
}

/**
 * @brief Get the Number object
 * 
 * @return short Número do sensor
 */
short Sensor::getNumber(void) {
  return number;
}

/**
 * @brief Set the Number object
 * 
 */
void Sensor::setNumber(const short newNumber) {
  number = newNumber;
}

#endif