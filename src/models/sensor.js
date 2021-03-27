const mongoose = require('mongoose')//usamos modulo mongoose
const Schema = mongoose.Schema

const SensoresSchema = Schema({ //definimos el schema 
    estado: String
})
module.exports = mongoose.model('Sensores', SensoresSchema)