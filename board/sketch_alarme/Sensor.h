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
  bool active;     //! Se está ativo
  bool fired;      //! Se foi disparado
  void setNumber(const short);

 public:
  Sensor(const short, const bool);
  bool getStatus(void);
  void setStatus(const bool);
  short getNumber(void);
  void setActive(bool);
  bool getActive(void);
  void setFired(bool);
  bool getFired(void);
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
  setActive(false);
  setFired(false);
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
    if (getActive()) {
      setFired(true);
    }
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

/**
 * @brief Set the Active object
 * 
 * @param flag Se o sensor está ativo ao armar
 */
void Sensor::setActive(bool flag) {
  active = flag;
}

/**
 * @brief Get the Active object
 * 
 * @return true Se o sensor estiver ativo
 * @return false Se o sensor estiver bypassado
 */
bool Sensor::getActive(void) {
  return active;
}

/**
 * @brief Set the Fired object
 * 
 * @param flag Se o Sensor foi disparado
 */
void Sensor::setFired(bool flag) {
  fired = flag;
}

/**
 * @brief Get the Fired object
 * 
 * @return true Se o sensor disparou quando estava armado da última vez
 * @return false Se o sensor não disparou quando estava armado da última vez
 */
bool Sensor::getFired(void) {
  return fired;
}

#endif