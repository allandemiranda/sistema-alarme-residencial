/**
 * @file Voltage.h
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Contem a classe que gerencia a voltagem dos sensores
 * @version 1.0.6
 * @date 2020-07-27
 * 
 * @copyright Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 * 
 */

#ifndef VOLTAGE_H_
#define VOLTAGE_H_

class Voltage {
 private:
  double normalVoltageBothSensor;        //! Voltagem esperada para ambos os sensores estarem fechados
  double normalVoltageOddSensor;         //! Voltagem esperada para somente o sensor ímpar está fechado (par aberto)
  double normalVoltageEvenSensor;        //! Voltagem esperada para somente o sensor par está fechado (ímpar aberto)
  double normalVoltageOffSensor;         //! Voltagem esperada para ambos os sensores estarem abertos
  double toleranceBetweenSensorVoltage;  //! Voltagem de tolerância do normal
  double voltageConst;                   //! Constante para verificar voltagem do pin
  double getNormalVoltageBothSensor(void);
  void setNormalVoltageBothSensor(const double);
  double getNormalVoltageOddSensor(void);
  void setNormalVoltageOddSensor(const double);
  double getNormalVoltageEvenSensor(void);
  void setNormalVoltageEvenSensor(const double);
  double getNormalVoltageOffSensor(void);
  void setNormalVoltageOffSensor(const double);
  double getToleranceBetweenSensorVoltage(void);
  void setToleranceBetweenSensorVoltage(const double);
  double getVoltageConst(void);
  void setVoltageConst(const double);

 public:
  Voltage(const double, const double, const double, const double, const double, const double);
  bool getOddSensorStatus(const int);
  bool getEvenSensorStatus(const int);
  // String getStatusZone(const int);
  double convertToVoltage(const int);
};

/**
 * @brief Construct a new Voltage:: Voltage object
 * 
 * @param newNormalVoltageBothSensor Voltagem esperada para ambos os sensores estarem fechados
 * @param newNormalVoltageOddSensor Voltagem esperada para somente o sensor ímpar está fechado (par aberto)
 * @param newNormalVoltageEvenSensor Voltagem esperada para somente o sensor par está fechado (ímpar aberto)
 * @param newNormalVoltageOffSensor Voltagem esperada para ambos os sensores estarem abertos
 * @param newToleranceBetweenSensorVoltage Voltagem de tolerância do normal
 * @param newVoltageConst Constante para verificar voltagem do pin
 */
Voltage::Voltage(const double newNormalVoltageBothSensor = 3.08, const double newNormalVoltageOddSensor = 2.59, const double newNormalVoltageEvenSensor = 1.64, const double newNormalVoltageOffSensor = 0.00, const double newToleranceBetweenSensorVoltage = 0.18, const double newVoltageConst = 0.004882813) {
  setNormalVoltageBothSensor(newNormalVoltageBothSensor);
  setNormalVoltageOddSensor(newNormalVoltageOddSensor);
  setNormalVoltageEvenSensor(newNormalVoltageEvenSensor);
  setNormalVoltageOffSensor(newNormalVoltageOffSensor);
  setToleranceBetweenSensorVoltage(newToleranceBetweenSensorVoltage);
  setVoltageConst(newVoltageConst);
}

/**
 * @brief Get the Odd Sensor Status object
 * 
 * @param voltageNow Voltagem da zona
 * @return true Sensor ímpar está aberto
 * @return false Sensor ímpar está fechado
 */
bool Voltage::getOddSensorStatus(const int voltageNow) {
  if (convertToVoltage(voltageNow) <= (getNormalVoltageBothSensor() + getToleranceBetweenSensorVoltage())) {
    if (convertToVoltage(voltageNow) >= (getNormalVoltageBothSensor() - getToleranceBetweenSensorVoltage())) {
      return false;
    }
  }

  if (convertToVoltage(voltageNow) <= (getNormalVoltageOddSensor() + getToleranceBetweenSensorVoltage())) {
    if (convertToVoltage(voltageNow) >= (getNormalVoltageOddSensor() - getToleranceBetweenSensorVoltage())) {
      return false;
    }
  }

  return true;
}

/**
 * @brief Get the Even Sensor Status object
 * 
 * @param voltageNow Voltagem da zona
 * @return true Sensor par está aberto
 * @return false Sensor par está fechado 
 */
bool Voltage::getEvenSensorStatus(const int voltageNow) {
  if (convertToVoltage(voltageNow) <= (getNormalVoltageBothSensor() + getToleranceBetweenSensorVoltage())) {
    if (convertToVoltage(voltageNow) >= (getNormalVoltageBothSensor() - getToleranceBetweenSensorVoltage())) {
      return false;
    }
  }

  if (convertToVoltage(voltageNow) <= (getNormalVoltageEvenSensor() + getToleranceBetweenSensorVoltage())) {
    if (convertToVoltage(voltageNow) >= (getNormalVoltageEvenSensor() - getToleranceBetweenSensorVoltage())) {
      return false;
    }
  }

  return true;
}

// /**
//  * @brief Get the Status Zone object
//  *
//  * @param voltageNow Voltagem da zona
//  * @return String Status real da voltagem na zona
//  */
// String Voltage::getStatusZone(const int voltageNow) {
//   const double voltage = convertToVoltage(voltageNow);

//   if (voltage == getNormalVoltageBothSensor()) {
//     return "Voltagem esperada para ambos os sensores estarem fechados";
//   }

//   if (voltage == getNormalVoltageOddSensor()) {
//     return "Voltagem esperada para somente o sensor ímpar está fechado (par aberto)";
//   }

//   if (voltage == getNormalVoltageEvenSensor()) {
//     return "Voltagem esperada para somente o sensor par está fechado (ímpar aberto)";
//   }

//   if (voltage == getNormalVoltageOffSensor()) {
//     return "Voltagem esperada para ambos os sensores estarem abertos";
//   }

//   if (voltage > getNormalVoltageOddSensor()) {
//     if (voltage <= (getNormalVoltageOddSensor() + getToleranceBetweenSensorVoltage())) {
//       return "Sobre Voltagem esperada para somente o sensor ímpar está fechado (par aberto)";
//     } else {
//       if (voltage < (getNormalVoltageBothSensor() - getToleranceBetweenSensorVoltage())) {
//         return "Voltagem da Zona fora do padrão, entre ÍMPAR e AMBOS";
//       } else {
//         if (voltage < getNormalVoltageBothSensor()) {
//           return "Sub Voltagem esperada para ambos os sensores estarem fechados";
//         } else {
//           if (voltage <= (getNormalVoltageBothSensor() + getToleranceBetweenSensorVoltage())) {
//             return "Sobre Voltagem esperada para ambos os sensores estarem fechados";
//           } else {
//             return "Sobre carga na zona";
//           }
//         }
//       }
//     }
//   } else {
//     if (voltage >= (getNormalVoltageOddSensor() - getToleranceBetweenSensorVoltage())) {
//       return "Sub Voltagem esperada para somente o sensor ímpar está fechado (par aberto)";
//     } else {
//       if (voltage > (getNormalVoltageEvenSensor() + getToleranceBetweenSensorVoltage())) {
//         return "Voltagem da Zona fora do padrão, entre PAR e ÍMPAR";
//       } else {
//         if (voltage > getNormalVoltageEvenSensor()) {
//           return "Sobre Voltagem esperada para somente o sensor par está fechado (ímpar aberto)";
//         } else {
//           if (voltage >= (getNormalVoltageEvenSensor() - getToleranceBetweenSensorVoltage())) {
//             return "Sub Voltagem esperada para somente o sensor par está fechado (ímpar aberto)";
//           } else {
//             if (voltage > (getNormalVoltageOffSensor() + getToleranceBetweenSensorVoltage())) {
//               return "Voltagem da Zona fora do padrão, entre OFF e PAR";
//             } else {
//               if (voltage > getNormalVoltageOffSensor()) {
//                 return "Sobre Voltagem esperada para ambos os sensores estarem abertos";
//               } else {
//                 if ((voltage < getNormalVoltageOffSensor()) & (voltage <= 0)) {
//                   return "Sub Voltagem esperada para ambos os sensores estarem abertos";
//                 } else {
//                   return "Erro ao coletar voltagem da Zona, menor de 0.00v";
//                 }
//               }
//             }
//           }
//         }
//       }
//     }
//   }
// }

/**
 * @brief Set the Normal Voltage Both Sensor object
 * 
 * @param newVolt Nova voltagem
 */
void Voltage::setNormalVoltageBothSensor(const double newVolt) {
  normalVoltageBothSensor = newVolt;
}

/**
 * @brief Set the Normal Voltage Odd Sensor object
 * 
 * @param newVolt Nova voltagem
 */
void Voltage::setNormalVoltageOddSensor(const double newVolt) {
  normalVoltageOddSensor = newVolt;
}

/**
 * @brief Set the Normal Voltage Even Sensor object
 * 
 * @param newVolt Nova voltagem
 */
void Voltage::setNormalVoltageEvenSensor(const double newVolt) {
  normalVoltageEvenSensor = newVolt;
}

/**
 * @brief Set the Normal Voltage Off Sensor object
 * 
 * @param newVolt Nova voltagem
 */
void Voltage::setNormalVoltageOffSensor(const double newVolt) {
  normalVoltageOffSensor = newVolt;
}

/**
 * @brief Set the Tolerance Between Sensor Voltage object
 * 
 * @param newVolt Nova voltagem
 */
void Voltage::setToleranceBetweenSensorVoltage(const double newVolt) {
  toleranceBetweenSensorVoltage = newVolt;
}

/**
 * @brief Set the Voltage Const object
 * 
 * @param newVolt Nova voltagem
 */
void Voltage::setVoltageConst(const double newVolt) {
  voltageConst = newVolt;
}

/**
 * @brief Get the Normal Voltage Both Sensor object
 * 
 * @return double Normal Voltage Both Sensor
 */
double Voltage::getNormalVoltageBothSensor(void) {
  return normalVoltageBothSensor;
}

/**
 * @brief Get the Normal Voltage Odd Sensor object
 * 
 * @return double Normal Voltage Odd Sensor
 */
double Voltage::getNormalVoltageOddSensor(void) {
  return normalVoltageOddSensor;
}

/**
 * @brief Get the Normal Voltage Even Sensor object
 * 
 * @return double Normal Voltage Even Sensor
 */
double Voltage::getNormalVoltageEvenSensor(void) {
  return normalVoltageEvenSensor;
}

/**
 * @brief Get the Normal Voltage Off Sensor object
 * 
 * @return double Normal Voltage Off Sensor
 */
double Voltage::getNormalVoltageOffSensor(void) {
  return normalVoltageOffSensor;
}

/**
 * @brief Get the Tolerance Between Sensor Voltage object
 * 
 * @return double Tolerance Between Sensor Voltage
 */
double Voltage::getToleranceBetweenSensorVoltage(void) {
  return toleranceBetweenSensorVoltage;
}

/**
 * @brief Get the Voltage Const object
 * 
 * @return double Voltage Const
 */
double Voltage::getVoltageConst(void) {
  return voltageConst;
}

/**
 * @brief Get the Convert To Voltage object
 * 
 * @param volt Voltagem em INT
 * @return double Voltagem real
 */
double Voltage::convertToVoltage(const int volt) {
  return volt * getVoltageConst();
}

#endif