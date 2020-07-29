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

/**
 * @brief Setup Arduino
 * 
 */
void setup() {
  Serial.begin(9600);
}

/**
 * @brief Loop Arduino
 * 
 */
void loop() {
  alarm.getBell()->getStatus();
  alarm.getControl()->getStatus();
  alarm.getLedStatus()->getStatus();
  for (int i = 1; i <= 8; i++) {
    alarm.getSensorSatus(i);
  }
}

void serialEvent() {
  if (Serial.read() == '1') {
    const size_t capacity = JSON_ARRAY_SIZE(4) + JSON_ARRAY_SIZE(8) + 3 * JSON_OBJECT_SIZE(1) + 16 * JSON_OBJECT_SIZE(2) + 4 * JSON_OBJECT_SIZE(4) + 5 * JSON_OBJECT_SIZE(5) ;
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

    // Vetor de sensores
    JsonArray sensores = doc.createNestedArray("sensores");

    JsonObject sensores_0 = sensores.createNestedObject();
    sensores_0["numero"] = 1;
    sensores_0["status"] = alarm.getSensorSatus(1);

    JsonObject sensores_1 = sensores.createNestedObject();
    sensores_1["numero"] = 2;
    sensores_1["status"] = alarm.getSensorSatus(2);

    JsonObject sensores_2 = sensores.createNestedObject();
    sensores_2["numero"] = 3;
    sensores_2["status"] = alarm.getSensorSatus(3);

    JsonObject sensores_3 = sensores.createNestedObject();
    sensores_3["numero"] = 4;
    sensores_3["status"] = alarm.getSensorSatus(4);

    JsonObject sensores_4 = sensores.createNestedObject();
    sensores_4["numero"] = 5;
    sensores_4["status"] = alarm.getSensorSatus(5);

    JsonObject sensores_5 = sensores.createNestedObject();
    sensores_5["numero"] = 6;
    sensores_5["status"] = alarm.getSensorSatus(6);

    JsonObject sensores_6 = sensores.createNestedObject();
    sensores_6["numero"] = 7;
    sensores_6["status"] = alarm.getSensorSatus(7);

    JsonObject sensores_7 = sensores.createNestedObject();
    sensores_7["numero"] = 8;
    sensores_7["status"] = alarm.getSensorSatus(8);

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
}
