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

void setup() {
  Serial.begin(9600);
}

void loop() {
  
}