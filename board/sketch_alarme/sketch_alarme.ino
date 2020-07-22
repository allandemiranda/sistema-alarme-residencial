/**
 * @brief Gerenciador da placa do alarme
 * @author Allan de Miranda
 * @file sketch_alarme.ino
 * @version 1.0.3
 *
 * @license Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 */

int incomingByte = 0;                     //! Dados recebidos na porta serial
const double voltageConst = 0.004882813;  //! Constante para verificar voltagem do pin

// Zonas do alarme
const int pinZone1 = A0;  //! Zona Um dos sensores 1 e 2
const int pinZone2 = A1;  //! Zona Dois dos sensores 3 e 4
const int pinZone3 = A2;  //! Zona Três dos sensores 5 e 6
const int pinZone4 = A3;  //! Zona Quantro dos sensores 7 e 8

// Voltagens esperadas para cada par da zona do alarme
const double normalVoltageBothSensor = 3.08;        //! Voltagem esperada para ambos os sensores estarem fechados
const double normalVoltageOddSensor = 2.59;         //! Voltagem esperada para somente o sensor ímpar está fechado (par aberto)
const double normalVoltageEvenSensor = 1.64;        //! Voltagem esperada para somente o sensor par está fechado (ímpar aberto)
const double normalVoltageOffSensor = 0.00;         //! Voltagem esperada para ambos os sensores estarem abertos
const double toleranceBetweenSensorVoltage = 0.18;  //! Voltagem de tolerância do normal

/**
 * @brief Função para verificar as configuraçoes da voltagem dos sensores do alarme
 * 
 * @param bothSensor Voltagem esperada para ambos os sensores estarem fechados
 * @param oddSensor Voltagem esperada para somente o sensor ímpar está fechado (par aberto)
 * @param evenSensor Voltagem esperada para somente o sensor par está fechado (ímpar aberto)
 * @param offSensor Voltagem esperada para ambos os sensores estarem abertos
 * @param tolerance Voltagem de tolerância do normal
 * @param newVoltageConst Constante para verificar voltagem do pin
 * @return true Teste bem sucedido
 * @return false Teste apresenta erro
 */
bool expectedVoltagesSensorConf(const double bothSensor, const double oddSensor, const double evenSensor, const double offSensor, const double tolerance, const double newVoltageConst) {
  if (normalVoltageBothSensor > normalVoltageOddSensor) {
    double test = normalVoltageBothSensor - normalVoltageOddSensor;
    if (test <= (tolerance + tolerance)) {
      return false;
    }
  } else {
    return false;
  }

  if (normalVoltageOddSensor > normalVoltageEvenSensor) {
    double test = normalVoltageOddSensor - normalVoltageEvenSensor;
    if (test <= (tolerance + tolerance)) {
      return false;
    }
  } else {
    return false;
  }

  if (normalVoltageEvenSensor > normalVoltageOffSensor) {
    double test = normalVoltageEvenSensor - normalVoltageOffSensor;
    if (test <= (tolerance + tolerance)) {
      return false;
    }
  } else {
    return false;
  }

  if (newVoltageConst <= 0) {
    return false;
  }

  return true;
}

/**
 * @brief Função para verificar Voltagem na Zona do Alarme
 * 
 * @param zoneNumber Número da zona do alarme
 * @return double Voltagem da zona
 */
double checkZoneVoltage(const short zoneNumber) {
  double firstVal;  //! Primeiro valor recebido
  int val;
  double nowVal;

  // Obtenha o primeiro valor base
  switch (zoneNumber) {
    case 1:
      val = analogRead(pinZone1);     //! Lê o pino de entrada
      firstVal = val * voltageConst;  //! Converte para voltagem
      break;
    case 2:
      val = analogRead(pinZone2);     //! Lê o pino de entrada
      firstVal = val * voltageConst;  //! Converte para voltagem
      break;
    case 3:
      val = analogRead(pinZone3);     //! Lê o pino de entrada
      firstVal = val * voltageConst;  //! Converte para voltagem
      break;
    case 4:
      val = analogRead(pinZone4);     //! Lê o pino de entrada
      firstVal = val * voltageConst;  //! Converte para voltagem
      break;
    default:
      firstVal = -1;  //! Zona inexistente
  }

  bool flag = false;  //! Flag verificadora do segundo parametro congruente

  // Loop de verificações congruentes de 3 etapas
  while (true) {
    delay(250);  //! Delay para minimizar valores inconsistentes

    double nowVal;  //! Voltagem atual na zona

    switch (zoneNumber) {
      case 1:
        val = analogRead(pinZone1);   //! Lê o pino de entrada
        nowVal = val * voltageConst;  //! Converte para voltagem
        break;
      case 2:
        val = analogRead(pinZone2);   //! Lê o pino de entrada
        nowVal = val * voltageConst;  //! Converte para voltagem
        break;
      case 3:
        val = analogRead(pinZone3);   //! Lê o pino de entrada
        nowVal = val * voltageConst;  //! Converte para voltagem
        break;
      case 4:
        val = analogRead(pinZone4);   //! Lê o pino de entrada
        nowVal = val * voltageConst;  //! Converte para voltagem
        break;
      default:
        nowVal = -1;  //! Zona inexistente
    }

    // Verifica se o valor atual bate com o anterior
    if (nowVal == firstVal) {
      // Verifica se a segunda etapa já foi confirmada
      if (flag) {
        break;
      } else {
        flag = true;
      }
    } else {
      firstVal = nowVal;
      flag = false;
    }
  }

  return firstVal;
}

/**
 * @brief Função para verificar Status da Zona do Alarme
 * 
 * @param voltage Voltagem capturada da zona enteriormente checkZoneVoltage()
 * @param zoneNumber Caso não tenha a voltagem (-1), expecificar a zona a ser analizada
 * @return String Status da Zona do Alarme
 */
String checkZoneStatus(double voltage = -1, const short zoneNumber = 0) {
  if (voltage < 0) {
    if (zoneNumber > 0) {
      voltage = checkZoneVoltage(zoneNumber);
    } else {
      return "Erro ao checar o status da Zona";
    }
  }

  if (voltage == normalVoltageBothSensor) {
    return "Voltagem esperada para ambos os sensores estarem fechados";
  }

  if (voltage == normalVoltageOddSensor) {
    return "Voltagem esperada para somente o sensor ímpar está fechado (par aberto)";
  }

  if (voltage == normalVoltageEvenSensor) {
    return "Voltagem esperada para somente o sensor par está fechado (ímpar aberto)";
  }

  if (voltage == normalVoltageOffSensor) {
    return "Voltagem esperada para ambos os sensores estarem abertos";
  }

  if (voltage > normalVoltageOddSensor) {
    if (voltage <= (normalVoltageOddSensor + toleranceBetweenSensorVoltage)) {
      return "Sobre Voltagem esperada para somente o sensor ímpar está fechado (par aberto)";
    } else {
      if (voltage < (normalVoltageBothSensor - toleranceBetweenSensorVoltage)) {
        return "Voltagem da Zona fora do padrão, entre ÍMPAR e AMBOS";
      } else {
        if (voltage < normalVoltageBothSensor) {
          return "Sub Voltagem esperada para ambos os sensores estarem fechados";
        } else {
          if (voltage <= (normalVoltageBothSensor + toleranceBetweenSensorVoltage)) {
            return "Sobre Voltagem esperada para ambos os sensores estarem fechados";
          } else {
            return "Sobre carga na zona";
          }
        }
      }
    }
  } else {
    if (voltage >= (normalVoltageOddSensor - toleranceBetweenSensorVoltage)) {
      return "Sub Voltagem esperada para somente o sensor ímpar está fechado (par aberto)";
    } else {
      if (voltage > (normalVoltageEvenSensor + toleranceBetweenSensorVoltage)) {
        return "Voltagem da Zona fora do padrão, entre PAR e ÍMPAR";
      } else {
        if (voltage > normalVoltageEvenSensor) {
          return "Sobre Voltagem esperada para somente o sensor par está fechado (ímpar aberto)";
        } else {
          if (voltage >= (normalVoltageEvenSensor - toleranceBetweenSensorVoltage)) {
            return "Sub Voltagem esperada para somente o sensor par está fechado (ímpar aberto)";
          } else {
            if (voltage > (normalVoltageOffSensor + toleranceBetweenSensorVoltage)) {
              return "Voltagem da Zona fora do padrão, entre OFF e PAR";
            } else {
              if (voltage > normalVoltageOffSensor) {
                return "Sobre Voltagem esperada para ambos os sensores estarem abertos";
              } else {
                if ((voltage < normalVoltageOffSensor) & (voltage <= 0)) {
                  return "Sub Voltagem esperada para ambos os sensores estarem abertos";
                } else {
                  return "Erro ao coletar voltagem da Zona, menor de 0.00v";
                }
              }
            }
          }
        }
      }
    }
  }
}

/**
 * @brief Função para verificar se o sensor esta aberto (disparado) ou fechado
 * 
 * @param sensorNumber Número so sensor para analizar
 * @return true Sensor esta fechado
 * @return false Sensor está aberto
 */
bool checkSensorStatus(const short sensorNumber) {
  int pinZone;
  double voltage;

  switch (sensorNumber) {
    case 1:
      pinZone = pinZone1;
      break;
    case 2:
      pinZone = pinZone1;
      break;
    case 3:
      pinZone = pinZone2;
      break;
    case 4:
      pinZone = pinZone2;
      break;
    case 5:
      pinZone = pinZone3;
      break;
    case 6:
      pinZone = pinZone3;
      break;
    case 7:
      pinZone = pinZone4;
      break;
    case 8:
      pinZone = pinZone4;
      break;
    default:
      return true;  //! Impossivel tratar este erro aqui
  }

  if ((sensorNumber % 2) != 0) {
    while (true) {
      voltage = checkZoneVoltage(pinZone);

      while (voltage < 0.0) {
        voltage = checkZoneVoltage(pinZone);
      }

      if (voltage <= (normalVoltageBothSensor + toleranceBetweenSensorVoltage)) {
        if (voltage >= (normalVoltageBothSensor - toleranceBetweenSensorVoltage)) {
          return true;
        }
      }

      if (voltage <= (normalVoltageOddSensor + toleranceBetweenSensorVoltage)) {
        if (voltage >= (normalVoltageOddSensor - toleranceBetweenSensorVoltage)) {
          return true;
        }
      }

      if (voltage <= (normalVoltageEvenSensor + toleranceBetweenSensorVoltage)) {
        if (voltage >= (normalVoltageEvenSensor - toleranceBetweenSensorVoltage)) {
          return false;
        }
      }

      if (voltage >= normalVoltageOffSensor) {
        if (voltage <= (normalVoltageOffSensor + toleranceBetweenSensorVoltage)) {
          return false;
        }
      }
    }
  } else {
    while (true) {
      voltage = checkZoneVoltage(pinZone);

      while (voltage < 0.0) {
        voltage = checkZoneVoltage(pinZone);
      }

      if (voltage <= (normalVoltageBothSensor + toleranceBetweenSensorVoltage)) {
        if (voltage >= (normalVoltageBothSensor - toleranceBetweenSensorVoltage)) {
          return true;
        }
      }

      if (voltage <= (normalVoltageOddSensor + toleranceBetweenSensorVoltage)) {
        if (voltage >= (normalVoltageOddSensor - toleranceBetweenSensorVoltage)) {
          return false;
        }
      }

      if (voltage <= (normalVoltageEvenSensor + toleranceBetweenSensorVoltage)) {
        if (voltage >= (normalVoltageEvenSensor - toleranceBetweenSensorVoltage)) {
          return true;
        }
      }

      if (voltage >= normalVoltageOffSensor) {
        if (voltage <= (normalVoltageOffSensor + toleranceBetweenSensorVoltage)) {
          return false;
        }
      }
    }
  }
}

/**
 * @brief Verifia eventos de entrada na comunicação serial
 * 
 */
void serialEvent() {
  incomingByte = Serial.read();

  // Responder o que foi recebido:
  Serial.print("Eu recebi: ");
  Serial.println(incomingByte, DEC);
}

/**
 * @brief Função padrão da linguagem para tesets e inicialização de métodos
 * 
 */
void setup() {
  // Led Status
  pinMode(LED_BUILTIN, OUTPUT);

  // Testes
  while (!expectedVoltagesSensorConf(normalVoltageBothSensor, normalVoltageOddSensor, normalVoltageEvenSensor, normalVoltageOffSensor, toleranceBetweenSensorVoltage, voltageConst)) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
  }

  // Inicializações
  Serial.begin(9600);  //! Abre a porta serial com taxa de 9600 bps
}

/**
 * @brief Função padrão da linguagem para continuidade do sistema
 * 
 */
void loop() {
  // put your main code here, to run repeatedly:
}
