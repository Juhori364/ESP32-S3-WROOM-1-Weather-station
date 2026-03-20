const express = require('express');
const router = express.Router();

const uploadModel = require('../models/uploadModel');

router.post('/', function (request, response) {
    uploadModel.sensorUpload(request.body, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    });
});

console.log("uploadRouter loaded");

module.exports = router;