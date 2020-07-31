/**
 * @file auth.js
 * @author Allan de Miranda Silva
 * @description Rotas de autenticação e registro de usuário
 * @version 1.0.0
 * 
 * @copyright Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 */

const express = require("express"); //! Importação do gerenciador da api
const bcrypt = require("bcryptjs"); //! Importação do gerenciador da criptografia
const jwt = require("jsonwebtoken"); //! Importação do gerenciador de token

const authConfig = require("../config/auth.json"); //! Configuraçẽs para autenticação
const User = require("../models/User"); //! Modelo dos usuários do sistema
const router = express.Router();

/**
 * @description Função que gera o token do usuário
 *
 * @param {object} params Id do usuário
 * @returns Token do usuário
 */
function generateToken(params = {}) {
  return jwt.sign(params, authConfig.secret, {
    expiresIn: 86400,
  });
}

/**
 * @description Registrar usuário no sistema
 *
 * @requires name Nome do usuário
 * @requires login Login do usuário
 * @requires password Senha do usuário
 * @returns {object} Usuário
 */
router.post("/register", async (req, res) => {
  try {
    const { login } = req.body;
    if (await User.findOne({ login })) {
      return res.status(400).send({
        error: {
          code: "preconditionFailed",
          message: "User alredy exists.",
          target: "Registration new User",
        },
      });
    } else {
      const user = await User.create(req.body);
      user.password = undefined;
      return res.status(202).send({ user });
    }
  } catch (error) {
    return res.status(400).send({
      error: {
        code: "generalException",
        message: "Registration failed",
        target: "Registration new User",
        innerError: {
          code: error.name,
          message: error.message,
        },
      },
    });
  }
});

/**
 * @description Autenticar usuário no sistema
 *
 * @requires login Login do usuário
 * @requires password Senha do usuário
 * @returns {object} Usuário
 */
router.get("/authenticate", async (req, res) => {
  try {
    const { login, password } = req.body;
    const user = await User.findOne({ login }).select("+password");
    if (!user) {
      return res.status(401).send({
        error: {
          code: "accessDenied",
          message: "User not found",
          target: "Authenticate User",
        },
      });
    } else {
      if (!(await bcrypt.compare(password, user.password))) {
        return res.status(401).send({
          error: {
            code: "accessDenied",
            message: "Invalid Password",
            target: "Authenticate User",
          },
        });
      } else {
        return res.send({
          user,
          token: generateToken({ id: user.id }),
        });
      }
    }
  } catch (error) {
    return res.status(400).send({
      error: {
        code: "generalException",
        message: "Authenticate failed",
        target: "Authenticate User",
      },
    });
  }
});

module.exports = (app) => app.use("/auth", router);
