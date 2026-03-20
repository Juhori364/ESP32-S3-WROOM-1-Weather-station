const mysql=require('mysql2');
const dotenv=require('dotenv');
dotenv.config();


//tässä tiedosossa piti muistaa sisällytttää toi dotenv. kirjasto, ku muuten tää ei tajua etsiä tuota connectionstringiä .env tiedostosta.
const connection=mysql.createPool(process.env.MYSQL_SERVER);


module.exports=connection;