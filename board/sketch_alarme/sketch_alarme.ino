/**
 * @file sketch_alarme.ino
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Contem o main do projeto
 * @version 1.0.6
 * @date 2020-07-27
 * 
 * @copyright Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 * 
 */

#include "Alarm.h"
#include "ArduinoJson-v6.15.2.h"

Alarm alarm(10, 12);

bool controleStatus;
bool lastFired[8];

/**
 * @brief Status do Alarme
 * 
 */
void sendStatus() {
  const size_t capacity = JSON_ARRAY_SIZE(4) + 2 * JSON_ARRAY_SIZE(8) + 3 * JSON_OBJECT_SIZE(1) + 16 * JSON_OBJECT_SIZE(2) + 12 * JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(6);
  DynamicJsonDocument doc(capacity);

  // Configuração da Sirene
  JsonObject sirene = doc.createNestedObject("sirene");
  sirene["status"] = alarm.getBell()->getStatus();

  // Configuração do controle
  JsonObject controle = doc.createNestedObject("controle");
  controle["status"] = alarm.getControl()->getStatus();

  // Configuração do Led de Status
  JsonObject ledStatus = doc.createNestedObject("ledStatus");
  ledStatus["status"] = alarm.getLedStatus()->getStatus();

  // últimos sensores disparados
  JsonArray ultimosDisparados = doc.createNestedArray("ultimosDisparados");

  JsonObject ultimosDisparados_0 = ultimosDisparados.createNestedObject();
  ultimosDisparados_0["numero"] = 1;
  ultimosDisparados_0["disparado"] = lastFired[0];

  JsonObject ultimosDisparados_1 = ultimosDisparados.createNestedObject();
  ultimosDisparados_1["numero"] = 2;
  ultimosDisparados_1["disparado"] = lastFired[1];

  JsonObject ultimosDisparados_2 = ultimosDisparados.createNestedObject();
  ultimosDisparados_2["numero"] = 3;
  ultimosDisparados_2["disparado"] = lastFired[2];

  JsonObject ultimosDisparados_3 = ultimosDisparados.createNestedObject();
  ultimosDisparados_3["numero"] = 4;
  ultimosDisparados_3["disparado"] = lastFired[3];

  JsonObject ultimosDisparados_4 = ultimosDisparados.createNestedObject();
  ultimosDisparados_4["numero"] = 5;
  ultimosDisparados_4["disparado"] = lastFired[4];

  JsonObject ultimosDisparados_5 = ultimosDisparados.createNestedObject();
  ultimosDisparados_5["numero"] = 6;
  ultimosDisparados_5["disparado"] = lastFired[5];

  JsonObject ultimosDisparados_6 = ultimosDisparados.createNestedObject();
  ultimosDisparados_6["numero"] = 7;
  ultimosDisparados_6["disparado"] = lastFired[6];

  JsonObject ultimosDisparados_7 = ultimosDisparados.createNestedObject();
  ultimosDisparados_7["numero"] = 8;
  ultimosDisparados_7["disparado"] = lastFired[7];

  // Vetor de sensores
  JsonArray sensores = doc.createNestedArray("sensores");

  JsonObject sensores_0 = sensores.createNestedObject();
  sensores_0["numero"] = 1;
  sensores_0["status"] = alarm.getSensor(1)->getStatus();
  sensores_0["ativo"] = alarm.getSensor(1)->getActive();
  sensores_0["disparado"] = alarm.getSensor(1)->getFired();

  JsonObject sensores_1 = sensores.createNestedObject();
  sensores_1["numero"] = 2;
  sensores_1["status"] = alarm.getSensor(2)->getStatus();
  sensores_1["ativo"] = alarm.getSensor(2)->getActive();
  sensores_1["disparado"] = alarm.getSensor(2)->getFired();

  JsonObject sensores_2 = sensores.createNestedObject();
  sensores_2["numero"] = 3;
  sensores_2["status"] = alarm.getSensor(3)->getStatus();
  sensores_2["ativo"] = alarm.getSensor(3)->getActive();
  sensores_2["disparado"] = alarm.getSensor(3)->getFired();

  JsonObject sensores_3 = sensores.createNestedObject();
  sensores_3["numero"] = 4;
  sensores_3["status"] = alarm.getSensor(4)->getStatus();
  sensores_3["ativo"] = alarm.getSensor(4)->getActive();
  sensores_3["disparado"] = alarm.getSensor(4)->getFired();

  JsonObject sensores_4 = sensores.createNestedObject();
  sensores_4["numero"] = 5;
  sensores_4["status"] = alarm.getSensor(5)->getStatus();
  sensores_4["ativo"] = alarm.getSensor(5)->getActive();
  sensores_4["disparado"] = alarm.getSensor(5)->getFired();

  JsonObject sensores_5 = sensores.createNestedObject();
  sensores_5["numero"] = 6;
  sensores_5["status"] = alarm.getSensor(6)->getStatus();
  sensores_5["ativo"] = alarm.getSensor(6)->getActive();
  sensores_5["disparado"] = alarm.getSensor(6)->getFired();

  JsonObject sensores_6 = sensores.createNestedObject();
  sensores_6["numero"] = 7;
  sensores_6["status"] = alarm.getSensor(7)->getStatus();
  sensores_6["ativo"] = alarm.getSensor(7)->getActive();
  sensores_6["disparado"] = alarm.getSensor(7)->getFired();

  JsonObject sensores_7 = sensores.createNestedObject();
  sensores_7["numero"] = 8;
  sensores_7["status"] = alarm.getSensor(8)->getStatus();
  sensores_7["ativo"] = alarm.getSensor(8)->getActive();
  sensores_7["disparado"] = alarm.getSensor(8)->getFired();

  // Vetor de Zonas
  JsonArray zonas = doc.createNestedArray("zonas");

  JsonObject zonas_0 = zonas.createNestedObject();
  zonas_0["numero"] = 1;
  zonas_0["voltagem"] = alarm.getZone(1)->getVoltage();
  // zonas_0["status"] = alarm.getZone(1)->getStatusZone();

  JsonObject zonas_0_sensorPar = zonas_0.createNestedObject("sensorPar");
  zonas_0_sensorPar["numero"] = alarm.getZone(1)->getEvenSensor()->getNumber();
  zonas_0_sensorPar["status"] = alarm.getZone(1)->getEvenSensor()->getStatus();

  JsonObject zonas_0_sensorImpar = zonas_0.createNestedObject("sensorImpar");
  zonas_0_sensorImpar["numero"] = alarm.getZone(1)->getOddSensor()->getNumber();
  zonas_0_sensorImpar["status"] = alarm.getZone(1)->getOddSensor()->getStatus();

  JsonObject zonas_1 = zonas.createNestedObject();
  zonas_1["numero"] = 2;
  zonas_1["voltagem"] = alarm.getZone(2)->getVoltage();
  // zonas_1["status"] = alarm.getZone(2)->getStatusZone();

  JsonObject zonas_1_sensorPar = zonas_1.createNestedObject("sensorPar");
  zonas_1_sensorPar["numero"] = alarm.getZone(2)->getEvenSensor()->getNumber();
  zonas_1_sensorPar["status"] = alarm.getZone(2)->getEvenSensor()->getStatus();

  JsonObject zonas_1_sensorImpar = zonas_1.createNestedObject("sensorImpar");
  zonas_1_sensorImpar["numero"] = alarm.getZone(2)->getOddSensor()->getNumber();
  zonas_1_sensorImpar["status"] = alarm.getZone(2)->getOddSensor()->getStatus();

  JsonObject zonas_2 = zonas.createNestedObject();
  zonas_2["numero"] = 3;
  zonas_2["voltagem"] = alarm.getZone(3)->getVoltage();
  // zonas_2["status"] = alarm.getZone(3)->getStatusZone();

  JsonObject zonas_2_sensorPar = zonas_2.createNestedObject("sensorPar");
  zonas_2_sensorPar["numero"] = alarm.getZone(3)->getEvenSensor()->getNumber();
  zonas_2_sensorPar["status"] = alarm.getZone(3)->getEvenSensor()->getStatus();

  JsonObject zonas_2_sensorImpar = zonas_2.createNestedObject("sensorImpar");
  zonas_2_sensorImpar["numero"] = alarm.getZone(3)->getOddSensor()->getNumber();
  zonas_2_sensorImpar["status"] = alarm.getZone(2)->getOddSensor()->getStatus();

  JsonObject zonas_3 = zonas.createNestedObject();
  zonas_3["numero"] = 4;
  zonas_3["voltagem"] = alarm.getZone(4)->getVoltage();
  // zonas_3["status"] = alarm.getZone(4)->getStatusZone();

  JsonObject zonas_3_sensorPar = zonas_3.createNestedObject("sensorPar");
  zonas_3_sensorPar["numero"] = alarm.getZone(4)->getEvenSensor()->getNumber();
  zonas_3_sensorPar["status"] = alarm.getZone(4)->getEvenSensor()->getStatus();

  JsonObject zonas_3_sensorImpar = zonas_3.createNestedObject("sensorImpar");
  zonas_3_sensorImpar["numero"] = alarm.getZone(4)->getOddSensor()->getNumber();
  zonas_3_sensorImpar["status"] = alarm.getZone(4)->getOddSensor()->getStatus();

  serializeJson(doc, Serial);
  Serial.println();
}

/**
 * @brief Setup Arduino
 * 
 */
void setup() {
  Serial.begin(9600);
  controleStatus = false;
  alarm.getLedStatus()->setStatus(1);
  for (int i = 0; i < 8; i++) {
    lastFired[i] = false;
  }
}

/**
 * @brief Loop Arduino
 * 
 */
void loop() {
  for (int i = 0; i < 8; i++) {
    short tempSensor = i + 1;
    if (alarm.getSensor(tempSensor)->getFired()) {
      if (alarm.getLedStatus()->getStatusNumber() == 2) {
        alarm.getLedStatus()->setStatus(3);
      }
    }
  }

  if (alarm.getLedStatus()->getStatusNumber() == 3) {
    alarm.getBell()->ringBell();
  }

  // if (alarm.getControl()->getStatus()) {
  //   if (alarm.getLedStatus()->getStatusNumber() == 3) {
  //     alarm.getBell()->turnOffAlert();
  //     alarm.getLedStatus()->setStatus(1);
  //     for (int i = 0; i < 8; i++) {
  //       short tempSensor = i + 1;
  //       lastFired[i] = alarm.getSensor(tempSensor)->getFired();
  //     }
  //   }

  //   if (alarm.getLedStatus()->getStatusNumber() == 2) {
  //     alarm.getBell()->turnOffAlert();
  //     alarm.getLedStatus()->setStatus(1);
  //     for (int i = 0; i < 8; i++) {
  //       short tempSensor = i + 1;
  //       alarm.getSensor(tempSensor)->setFired(false);
  //     }
  //   }

  //   if (alarm.getLedStatus()->getStatusNumber() == 1) {
  //     alarm.getBell()->turnOnAlert();
  //     alarm.getLedStatus()->setStatus(2);
  //     for (int i = 0; i < 8; i++) {
  //       short tempSensor = i + 1;
  //       alarm.getSensor(tempSensor)->setFired(false);
  //     }
  //   }
  // }
}

/**
 * @brief Eventos na porta Serial
 * 
 */
void serialEvent() {

  char leitura = Serial.read();

  // Verificar status do alarme
  if (leitura == 'a') {
    sendStatus();
  }

  // Arma o Alarme
  if (leitura == 'b') {
    if (alarm.getLedStatus()->getStatusNumber() == 1) {
      alarm.getBell()->turnOnAlert();
      alarm.getLedStatus()->setStatus(2);
      for (int i = 0; i < 8; i++) {
        short tempSensor = i + 1;
        alarm.getSensor(tempSensor)->setFired(false);
      }
    }
    sendStatus();
  }

  // Desarmar alarme
  if (leitura == 'c') {
    if (alarm.getLedStatus()->getStatusNumber() == 3) {
      alarm.getBell()->turnOffAlert();
      alarm.getLedStatus()->setStatus(1);
      for (int i = 0; i < 8; i++) {
        short tempSensor = i + 1;
        lastFired[i] = alarm.getSensor(tempSensor)->getFired();
      }
    }
    if (alarm.getLedStatus()->getStatusNumber() == 2) {
      alarm.getBell()->turnOffAlert();
      alarm.getLedStatus()->setStatus(1);
      for (int i = 0; i < 8; i++) {
        short tempSensor = i + 1;
        alarm.getSensor(tempSensor)->setFired(false);
      }
    }
    sendStatus();
  }

  // Tocar sirene
  if (leitura == 'd') {
    alarm.getBell()->ringBell();
    sendStatus();
  }

  // Parar sirene
  if (leitura == 'e') {
    alarm.getBell()->stopBell();
    sendStatus();
  }

  // Setar sensor atividade
  if (leitura == 'f') {
    int numero = 1;
    alarm.getSensor(numero)->setActive(!alarm.getSensor(numero)->getActive());
    sendStatus();
  }

  if (leitura == 'g') {
    int numero = 2;
    alarm.getSensor(numero)->setActive(!alarm.getSensor(numero)->getActive());
    sendStatus();
  }

  if (leitura == 'h') {
    int numero = 3;
    alarm.getSensor(numero)->setActive(!alarm.getSensor(numero)->getActive());
    sendStatus();
  }

  if (leitura == '1') {
    int numero = 4;
    alarm.getSensor(numero)->setActive(!alarm.getSensor(numero)->getActive());
    sendStatus();
  }

  if (leitura == 'j') {
    int numero = 5;
    alarm.getSensor(numero)->setActive(!alarm.getSensor(numero)->getActive());
    sendStatus();
  }

  if (leitura == 'k') {
    int numero = 6;
    alarm.getSensor(numero)->setActive(!alarm.getSensor(numero)->getActive());
    sendStatus();
  }

  if (leitura == 'l') {
    int numero = 7;
    alarm.getSensor(numero)->setActive(!alarm.getSensor(numero)->getActive());
    sendStatus();
  }

  if (leitura == 'm') {
    int numero = 8;
    alarm.getSensor(numero)->setActive(!alarm.getSensor(numero)->getActive());
    sendStatus();
  }
}