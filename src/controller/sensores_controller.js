const Sensores = require('../models/sensor');// ruteo a models

module.exports = {
    index: async(req, res, next) =>{//uso de funcion async la cual devuelve un objeto
        const sensor = await Sensores.find({});//funcion await pausa la funcion async en lo que resuelve la promesa pasada
        res.status(200).json(sensor);
    },
    newSensor: async(req,res,next) => {
        console.log('POST')
        console.log(req.body)//Nos manda por consola el POST agregado

        const sensor = new Sensores();

        sensor.estado = req.body.estado
        await sensor.save();// resuelve la promesa con una funcion await
    }
};
