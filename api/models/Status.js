/**
 * @file Status.js
 * @author Allan de Miranda Silva
 * @description Schema para o status do alarme
 * @version 1.0.0
 *
 * @copyright Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 */

const mongoose = require("../database"); //! Conexão com o banco de dados

/**
 * @description Schema para
 */
const StatusSchema = new mongoose.Schema({
  sirene: { type: Bool, required: true },
  controle: { type: Bool, required: true },
  ledStatus: { type: String, required: true },
  sensores: [{ SensoresSchema }],
  zonas: [{ ZonasSchema }],
  createdAt: {
    type: Date,
    default: Date.now,
  },
  code: { type: Number, default: 0 },
});

const SensoresSchema = new mongoose.Schema({
  numero: { type: Number, required: true },
  status: { type: Bool, required: true },
  code: { type: Number, default: 0 },
});

const ZonasSchema = new mongoose.Schema({
  numero: { type: Number, required: true },
  voltagem: { type: Number, required: true },
  sensorPar: { SensoresSchema },
  sensorImpar: { SensoresSchema },
});

const Status = mongoose.model("Status", StatusSchema);

module.exports = Status;
