/**
 * @file auth.js
 * @author Allan de Miranda Silva
 * @description Middlewares de autenticação de usuário
 * @version 1.0.0
 * 
 * @copyright Copyright (c) 2020 ALLAN DE MIRANDA SILVA
 */

const jwt = require("jsonwebtoken"); //! Importação do gerenciador de token
const authConfig = require("../config/auth.json"); //! Configuração do autenticador

/**
 * @description Verifica a autenticidade do token
 * 
 * @param {object} req Requisição com o cabeçalho
 * @param {*} res
 * @param {*} next
 * @returns Continuação da ação de autenticação
 */
module.exports = (req, res, next) => {
  const authHeader = req.headers.authorization;

  if (!authHeader) {
    return res.status(401).send({
      error: {
        code: "accessDenied",
        message: "No token provided",
        target: "Authenticate User",
      },
    });
  }

  const parts = authHeader.split(" ");

  if (!parts.length === 2) {
    return res.status(401).send({
      error: {
        code: "accessDenied",
        message: "Token error",
        target: "Authenticate User",
      },
    });
  }

  const [scheme, token] = parts;

  if (!/^Bearer$/i.test(scheme)) {
    return res.status(401).send({
      error: {
        code: "accessDenied",
        message: "Token malformatted",
        target: "Authenticate User",
      },
    });
  }

  jwt.verify(token, authConfig.secret, async (error, decoded) => {
    if (error) {
      return res.status(401).send({
        error: {
          code: "accessDenied",
          message: "Token invalid",
          target: "Authenticate User",
        },
      });
    }
    req.userId = decoded.id;
    return next();
  });
};
