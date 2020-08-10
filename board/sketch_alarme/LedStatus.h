/**
 * @file LedStatus.h
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Contem a classe que gerencia o alarme
 * @version 1.0.6
 * @date 2020-07-27
 * 
 * @copyright Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 * 
 */

#ifndef LEDSTATUS_H_
#define LEDSTATUS_H_

#include "Led.h"

class LedStatus {
 private:
  Led* statusLed;
  short status;

 public:
  LedStatus(const short, const short);
  Led* getLed(void);
  String getStatus(void);
  void setStatus(const short);
  short getStatusNumber(void);
};

/**
 * @brief Construct a new Led Status:: Led Status object
 * 
 * @param pin Porta do Led de status
 * @param newStatus Status inicial do led
 */
LedStatus::LedStatus(const short pin = LED_BUILTIN, const short newStatus = 0) {
  if (newStatus == 0) {
    statusLed = new Led(pin, false);
  } else {
    statusLed = new Led(pin, true);
  }
}

/**
 * @brief Get the Led object
 * 
 * @return Led* Led do status
 */
Led* LedStatus::getLed(void) {
  return statusLed;
}

/**
 * @brief Set the Status object
 * 
 * @param num Código do status
 */
void LedStatus::setStatus(const short num) {
  status = num;
}

/**
 * @brief Get the Status object
 * 
 * @return String Mensagem do código do status
 */
String LedStatus::getStatus(void) {
  switch (status) {
    case 0:
      statusLed->turnOff();
      return "Alarme não configurado";
    case 1:
      statusLed->turnOn();
      return "Alarme desarmado";
    case 2:
      statusLed->turnOn();
      delay(200);
      statusLed->turnOff();
      delay(200);
      return "Alarme armado";
    case 3:
      statusLed->turnOn();
      delay(300);
      statusLed->turnOff();
      delay(300);
      return "Alarme disparando";
    default:
      statusLed->turnOff();
      return "Alarme erro";
  }
}

/**
 * @brief Get the Status Number object
 * 
 * @return short Número do status do led
 */
short LedStatus::getStatusNumber(void) {
  getStatus();
  return status;
}

#endif