var express = require("express");
var router = express.Router();

const SerialPort = require("serialport");
const Readline = require("@serialport/parser-readline");
const Delimiter = require("@serialport/parser-delimiter");
const { listenerCount } = require("serialport");
const port = new SerialPort("/dev/ttyACM0", { baudRate: 9600 });

/* GET home page. */
router.get("/", async (req, res, next) => {
  //res.render('index', { title: 'Express' });

  port.write("1");

  teste = { };

  const parser = port.pipe(new Readline({ delimiter: "\r\n" }));

  function receberInfo(port, parser) {
    return new Promise(function (resolve, reject) {
        parser.on("data", (data) => {
          resolve(JSON.parse(data));
        });      
    });
  }

  await receberInfo(port, parser).then(async (data, err) => {console.log(data); teste=data });

  res.json(teste);
});

module.exports = router;
