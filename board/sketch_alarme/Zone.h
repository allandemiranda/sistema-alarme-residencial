/**
 * @file Zone.h
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Contem a classe que gerencia o sensor
 * @version 1.0.6
 * @date 2020-07-27
 * 
 * @copyright Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 * 
 */

#ifndef ZONE_H_
#define ZONE_H_

#include "Sensor.h"
#include "Voltage.h"

class Zone {
 private:
  short pinNumber;
  short number;
  Sensor* OddSensor;
  Sensor* EvenSensor;
  short getPinNumber(void);
  void setPinNumber(const short);
  short getNumber(void);
  void setNumber(const short);
  int getVoltageInt(void);
  Voltage tempVoltage();

 public:
  Zone(const short, const short);
  String getStatusZone(void);
  Sensor* getOddSensor(void);
  Sensor* getEvenSensor(void);
  double getVoltage(void);
};

/**
 * @brief Construct a new Zone:: Zone object
 * 
 * @param pin 
 * @param newNumber 
 */
Zone::Zone(const short pin, const short newNumber) {
  setPinNumber(pin);
  setNumber(newNumber);
  const short numberEven = getNumber() * 2;
  const short pinEven = numberEven + 1;
  EvenSensor = new Sensor(numberEven);
  const short numberOdd = (getNumber() * 2) - 1;
  const short pinOdd = numberOdd + 1;
  OddSensor = new Sensor(numberOdd);
}

/**
 * @brief Get the Pin Number object
 * 
 * @return short Número da porta da zona
 */
short Zone::getPinNumber(void) {
  return pinNumber;
}

/**
 * @brief Set the Pin Number object
 * 
 * @param newPin Novo número da porta da zona
 */
void Zone::setPinNumber(const short newPin) {
  pinNumber = newPin;
}

/**
 * @brief Get the Number object
 * 
 * @return short Número da zona
 */
short Zone::getNumber(void) {
  return number;
}

/**
 * @brief Set the Number object
 * 
 * @param newNumber Novo número da zona
 */
void Zone::setNumber(const short newNumber) {
  number = newNumber;
}

/**
 * @brief Get the Voltage Int object
 * 
 * @return int Voltagem na escala obtida do Arduino
 */
int Zone::getVoltageInt(void) {
  return analogRead(getPinNumber());
}

/**
 * @brief Get the Status Zone object
 * 
 * @return String Status da zona
 */
String Zone::getStatusZone(void) {
  OddSensor->setStatus(tempVoltage().getOddSensorStatus(getVoltageInt()));
  EvenSensor->setStatus(tempVoltage().getEvenSensorStatus(getVoltageInt()));
  return tempVoltage().getStatusZone(getVoltageInt());
}

/**
 * @brief Get the Odd Sensor Status object
 * 
 * @return Sensor* Sensor
 */
Sensor* Zone::getOddSensor(void) {
  OddSensor->setStatus(tempVoltage().getOddSensorStatus(getVoltageInt()));
  return OddSensor;
}

/**
 * @brief Get the Even Sensor Status object
 * 
 * @return Sensor* Sensor
 */
Sensor* Zone::getEvenSensor(void) {
  EvenSensor->setStatus(tempVoltage().getEvenSensorStatus(getVoltageInt()));
  return EvenSensor;
}

/**
 * @brief Get the Voltage object
 * 
 * @return double Voltagem real da zona
 */
double Zone::getVoltage(void) {
  return tempVoltage().convertToVoltage(getVoltageInt());
}

#endif