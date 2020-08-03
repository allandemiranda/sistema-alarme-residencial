const express = require("express");
//const authMiddleware = require("../middlewares/auth");

const Status = require("../models/Status");

const SerialPort = require("serialport");
const Readline = require("@serialport/parser-readline");
const Delimiter = require("@serialport/parser-delimiter");
const { listenerCount } = require("serialport");
const port = new SerialPort("/dev/ttyACM0", { baudRate: 9600 });

const router = express.Router();

//router.use(authMiddleware);

router.get("/", (req, res) => {
  return res.send({
    ok: true,
    id: req.userId,
  });
});

router.get("/teste/:id", async (req, res, next) => {
  try {
    port.write(req.params.id);

    teste = {};

    const parser = port.pipe(new Readline({ delimiter: "\r\n" }));

    function receberInfo() {
      return new Promise(function (resolve, reject) {
        parser.on("data", (data) => {
          resolve(JSON.parse(data));
        });
      });
    }

    await receberInfo().then(async (data, err) => {
      // console.log(data);
      teste = data;
    });

    //const a = await Status.create(teste);

    return res.status(200).send(teste);
  } catch (error) {
    console.log(error);
    return res.status(400).send({ error: true });
  }
});

router.get("/linha", async (req, res, next) => {

  const parser = new Readline();
  port.pipe(parser);

  parser.on("data", (line) => {console.log(`> ${line}`); console.log("---------")});
});

module.exports = (app) => app.use("/alarm", router);
