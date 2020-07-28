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
  short pinNumber;  //! Porta de saída
  bool statusLed;   //! Status atual do led
  short getPinNumber(void);
  void setPinNumber(const short);
  void setStatus(const bool);

 public:
  Led(const short, const bool);
  void turnOn(void);
  void turnOff(void);
  bool getStatus(void);
};

/**
 * @brief Construct a new Led Status:: Led Status object
 * 
 * @param pin Porta do Led
 * @param statusNow Status inicial do led
 */
Led::Led(const short pin, const bool statusNow = false) {
  setPinNumber(pin);
  pinMode(getPinNumber(), OUTPUT);
  if (statusNow) {
    turnOn();
  } else {
    turnOff();
  }
}

/**
 * @brief Ligar led
 * 
 */
void Led::turnOn(void) {
  if (!getStatus()) {
    digitalWrite(getPinNumber(), HIGH);
    setStatus(true);
  }
}

/**
 * @brief Desligar o Led
 * 
 */
void Led::turnOff(void) {
  if (getStatus()) {
    digitalWrite(getPinNumber(), LOW);
    setStatus(false);
  }
}

/**
 * @brief Get the Status object
 * 
 * @return true Led ligado
 * @return false Led desligado
 */
bool Led::getStatus(void) {
  return statusLed;
}

/**
 * @brief Set the Status object
 * 
 * @param newStatus Novo status do led
 */
void Led::setStatus(const bool newStatus) {
  statusLed = newStatus;
}

/**
 * @brief Get the Pin Number object
 * 
 * @return short Número da porta do led
 */
short Led::getPinNumber(void) {
  return pinNumber;
}

/**
 * @brief Set the Pin Number object
 * 
 * @param newPin Novo número da porta do led
 */
void Led::setPinNumber(const short newPin) {
  pinNumber = newPin;
}

#endif