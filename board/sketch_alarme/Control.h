/**
 * @file Control.h
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Contem a classe que gerencia o controle de acionamento do alarme
 * @version 1.0.6
 * @date 2020-07-27
 * 
 * @copyright Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 * 
 */

#ifndef CONTROL_H_
#define CONTROL_H_

class Control {
 private:
  short pinNumber;
  short getPinNumber(void);
  void setPinNumber(const short);

 public:
  Control(const short);
  bool getStatus(void);
};

/**
 * @brief Construct a new Control:: Control object
 * 
 * @param pin Número da porta de entrada do painel de gerenciador de acionamento do alarme
 */
Control::Control(const short pin) {
  setPinNumber(pin);
  pinMode(getPinNumber(), INPUT);
}

/**
 * @brief Get the Status object
 * 
 * @return true Controle foi acionado
 * @return false Controle não está acionado
 */
bool Control::getStatus(void) {
  if (digitalRead(getPinNumber())) {
    return true;
  } else {
    return false;
  }
}

/**
 * @brief Get the Pin Number object
 * 
 * @return short Número da porta do controle
 */
short Control::getPinNumber(void) {
  return pinNumber;
}

/**
 * @brief Set the Pin Number object
 * 
 * @param newNumber Novo número para a porta
 */
void Control::setPinNumber(const short newNumber) {
  pinNumber = newNumber;
}

#endif