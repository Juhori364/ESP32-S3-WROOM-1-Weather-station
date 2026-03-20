const db = require('../database.js');

const uploadModel = {

sensorUpload: function(data, callback) {
    console.log("in upload function");
    return db.query(
        'INSERT INTO readings (temperature, humidity) VALUES (?, ?)',
        [data.temperature, data.humidity],
        callback
    );
}}
module.exports = uploadModel;