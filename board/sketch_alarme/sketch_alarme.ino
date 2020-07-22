/**
 * @description Gerenciador da placa do alarme
 * @author Allan de Miranda
 * @file sketch_alarme.ino
 * @version 1.0.0
 *
 * @license Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 */

int incomingByte = 0;  //! Dados recebidos na porta serial

void setup() {
  Serial.begin(9600);  //! Abre a porta serial com taxa de 9600 bps
}

void loop() {
  // put your main code here, to run repeatedly:
}

void serialEvent() {
  incomingByte = Serial.read();

  // Responder o que foi recebido:
  Serial.print("Eu recebi: ");
  Serial.println(incomingByte, DEC);
}
