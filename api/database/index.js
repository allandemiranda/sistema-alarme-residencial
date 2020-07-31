/**
 * @file index.js
 * @author Allan de Miranda Silva
 * @description Configuração e execução do banco de dados
 * @version 1.0.0
 * 
 * @copyright Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 */

const mongoose = require("mongoose"); //! Manipulador do banco de dados
const mongodbConf = require("../config/mongodb.json"); //! Configurações do MongoDB

mongoose.connect(mongodbConf.url, mongodbConf.tegs);

mongoose.connection
  .once("open", function () {
    console.log("MongoDB database connection established successfully");
  })
  .on("error", function (error) {
    console.error("Mongo Error is: ", error);
  });

mongoose.Promise = global.Promise;

module.exports = mongoose;
