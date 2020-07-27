/**
 * @file Bell.h
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Contem a classe que gerencia a sirene
 * @version 1.0.6
 * @date 2020-07-27
 * 
 * @copyright Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 * 
 */

#ifndef BELL_H_
#define BELL_H_

class Bell {
 private:
  short pinNumber;  //! Porta de saída para despalar relé da sirene
  bool status;      //! Status atual da sirene
  short timeToOff;  //! Tempo (ms) entre toques ao desligar alarme
  short timeToOn;   //! Tempo (ms) entre toques ao ligar alarme
  short getPinNumber(void);
  void setPinNumber(const short);
  void setStatus(const bool);
  short getTimeToOff(void);
  void setTimeToOff(const short);
  short getTimeToOn(void);
  void setTimeToOn(const short);

 public:
  Bell(const short, const bool, const short, const short);
  bool getStatus(void);
  void ringBell(void);
  void stopBell(void);
  void turnOnAlert(void);
  void turnOffAlert(void);
};

/**
 * @brief Construct a new Bell:: Bell object
 * 
 * @param pin Porta de saída da sirene
 * @param statusNow Status inicial da sirene
 * @param timeOff Tempo de delay para alerta de desliagr
 * @param timeOn Tempo de delay para alerta de ligar
 */
Bell::Bell(const short pin, const bool statusNow = false, const short timeOff = 500, const short timeOn = 250) {
  setPinNumber(pin);
  setStatus(statusNow);
  setTimeToOff(timeOff);
  setTimeToOn(timeOn);
  pinMode(getPinNumber(), OUTPUT);
}

/**
 * @brief Get the Status object
 * 
 * @return true Sirene está disparando (ligada)
 * @return false Sirene está silenciosa (desligada)
 */
bool Bell::getStatus(void) {
  return status;
}

/**
 * @brief Disparar sirene
 * 
 */
void Bell::ringBell(void) {
  if (!getStatus()) {
    digitalWrite(getPinNumber(), HIGH);
    setStatus(true);
  }
}

/**
 * @brief Silenciar sirene
 * 
 */
void Bell::stopBell(void) {
  if (getStatus()) {
    digitalWrite(getPinNumber(), LOW);
    setStatus(false);
  }
}

/**
 * @brief Soar sinal de alarme ligando
 * 
 */
void Bell::turnOnAlert(void) {
  stopBell();
  digitalWrite(getPinNumber(), HIGH);
  delay(getTimeToOn());
  digitalWrite(getPinNumber(), LOW);
}

/**
 * @brief Soar sinal de alarme desligando
 * 
 */
void Bell::turnOffAlert(void) {
  stopBell();
  digitalWrite(getPinNumber(), HIGH);
  delay(getTimeToOff());
  digitalWrite(getPinNumber(), LOW);
}

/**
 * @brief Get the Pin Number object
 * 
 * @return short Número da porta de saída
 */
short Bell::getPinNumber(void) {
  return pinNumber;
}
/**
 * @brief Set the Pin Number object
 * 
 * @param newPinNumber Novo número da porta de saída da sirene
 */
void Bell::setPinNumber(const short newPinNumber) {
  pinNumber = newPinNumber;
}

/**
 * @brief Set the Status object
 * 
 * @param newStatus Novo staus da sirene
 */
void Bell::setStatus(const bool newStatus) {
  status = newStatus;
}

/**
 * @brief Get the Time To Off object
 * 
 * @return short Tempo de delay entre toques para alerta de desligar
 */
short Bell::getTimeToOff(void) {
  return timeToOff;
}

/**
 * @brief Set the Time To Off object
 * 
 * @param newTimeToOff Novo tempo de delay para alerta de desligar
 */
void Bell::setTimeToOff(const short newTimeToOff) {
  timeToOff = newTimeToOff;
}

/**
 * @brief Get the Time To On object
 * 
 * @return short Tempo de delay entre toques para alerta de ligar
 */
short Bell::getTimeToOn(void) {
  return timeToOn;
}

/**
 * @brief Set the Time To On object
 * 
 * @param newTimeToOn Novo tempo de delay para alerta de ligar
 */
void Bell::setTimeToOn(const short newTimeToOn) {
  timeToOn = newTimeToOn;
}

#endif