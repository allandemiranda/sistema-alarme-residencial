/**
 * @file User.js
 * @author Allan de Miranda Silva
 * @description Schema para os usuários do sistema
 * @version 1.0.0
 * 
 * @copyright Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 */

const mongoose = require("../database"); //! Conexão com o banco de dados
const bcrypt = require("bcryptjs"); //! Gerenciador de criptografia

/**
 * @description Schema para usuários do sistema
 */
const UserSchema = new mongoose.Schema({
  name: {
    type: String,
    required: true,
  },
  login: {
    type: String,
    unique: true,
    required: true,
    lowercase: true,
  },
  password: {
    type: String,
    required: true,
    select: false,
  },
  createdAt: {
    type: Date,
    default: Date.now,
  },
});

/**
 * @description Método para, ao criar um usuário, criptografar sua senha
 */
UserSchema.pre("save", async function (next) {
    const hash = await bcrypt.hash(this.password, 10);
    this.password = hash;
    next();
  });

const User = mongoose.model("User", UserSchema);

module.exports = User;
