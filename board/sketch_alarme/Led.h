/**
 * @file Led.h
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Contem a classe que gerencia o led
 * @version 1.0.6
 * @date 2020-07-27
 * 
 * @copyright Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 * 
 */

#ifndef LED_H_
#define LED_H_

class Led {
 private:
  short pinNumber;
  bool statusLed = false;

 public:
  Led(const short);
  bool turnOn(void);
  bool turnOff(void);
  bool status(void);
};

/**
 * @brief Construct a new Led Status:: Led Status object
 * 
 * @param pin Porta do Led
 */
Led::Led(const short pin) {
  pinNumber = pin;
  pinMode(pinNumber, OUTPUT);
}

/**
 * @brief Ligar o Led
 * 
 * @return true Se o led estiver ligado
 * @return false Se o led estiver desligado
 */
bool Led::turnOn(void) {
  if (!statusLed) {
    digitalWrite(pinNumber, HIGH);
    statusLed = true;
  }
  return statusLed;
}

/**
 * @brief Desligar o Led
 * 
 * @return true Se o led estiver ligado
 * @return false Se o led estiver desligado
 */
bool Led::turnOff(void) {
  if (statusLed) {
    digitalWrite(pinNumber, LOW);
    statusLed = false;
  }
  return statusLed;
}

/**
 * @brief Status do led
 * 
 * @return true Se estiver ligado
 * @return false Se estiver desligado
 */
bool Led::status(void) {
  return statusLed;
}

#endif