/**
 * @file Alarm.h
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Contem a classe que gerencia o alarme
 * @version 1.0.6
 * @date 2020-07-27
 * 
 * @copyright Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 * 
 */

#ifndef ALARM_H_
#define ALARM_H_

#include "Bell.h"
#include "Control.h"
#include "LedStatus.h"
#include "Zone.h"

class Alarm {
 private:
  Zone* zones[4];
  Bell* bell;
  Control* control;
  LedStatus* ledStatus;

 public:
  Alarm(const short, const short);
  bool getSensorSatus(const short);
  Zone* getZone(const short);
  Bell* getBell(void);
  Control* getControl(void);
  LedStatus* getLedStatus(void);
};

/**
 * @brief Construct a new Alarm:: Alarm object
 * 
 * @param pinBellNum Número da porta da sirene
 * @param pinControlNum Número da porta do controle
 */
Alarm::Alarm(const short pinBellNum, const short pinControlNum) {
  for (int i = 1; i <= 4; ++i) {
    int analogPin;
    switch (i) {
      case 1:
        analogPin = A1;
        break;
      case 2:
        analogPin = A2;
        break;
      case 3:
        analogPin = A3;
        break;
      case 4:
        analogPin = A4;
        break;
      default:
        analogPin = A0;
        break;
    }
    zones[i] = new Zone(analogPin, i);
  }

  bell = new Bell(pinBellNum);
  ledStatus = new LedStatus();
}

/**
 * @brief Get the Sensor Satus object
 * 
 * @param num Número do sensor
 * @return true Sensor aberto
 * @return false Sensor fechado
 */
bool Alarm::getSensorSatus(const short num) {
  if (num % 2 == 0) {
    for (int i = 0; i < 4; ++i) {
      if (zones[i]->getEvenSensor()->getNumber() == num) {
        return zones[i]->getEvenSensor()->getStatus();
      }
    }
    return true;
  } else {
    for (int i = 0; i < 4; ++i) {
      if (zones[i]->getOddSensor()->getNumber() == num) {
        return zones[i]->getOddSensor()->getStatus();
      }
    }
    return true;
  }
}

/**
 * @brief Get the Zone object
 * 
 * @param num Número da zona
 * @return Zone* Zona
 */
Zone* Alarm::getZone(const short num) {
  return zones[num - 1];
}

/**
 * @brief Get the Bell object
 * 
 * @return Bell* Sirene
 */
Bell* Alarm::getBell(void) {
  return bell;
}

/**
 * @brief Get the Control object
 * 
 * @return Control* Gerenciador do controle
 */
Control* Alarm::getControl(void) {
  return control;
}

/**
 * @brief Get the Led Status object
 * 
 * @return LedStatus* Led de status
 */
LedStatus* Alarm::getLedStatus(void) {
  return ledStatus;
}

#endif