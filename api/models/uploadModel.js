const db = require('../database.js');

const uploadModel = {

sensorUpload: function(data, callback) {
    console.log("in upload function");
    return db.query(
        'INSERT INTO readings (temperature, humidity, pressure, illuminance) VALUES (?, ?, ?, ?)',
        [data.temperature, data.humidity, data.pressure, data.illuminance],
        callback
    );
}}
module.exports = uploadModel;