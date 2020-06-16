import https from 'https';
import express from 'express';
import serve_index from 'serve-index';
import fs from 'fs';

const options = {
  key: fs.readFileSync('./cert/localhost.key'),
  cert: fs.readFileSync('./cert/localhost.crt')
};
const config = {
  protocol: 'https',
  port: 443,
  hostname: '0.0.0.0'
}

const app = express();
app.use(serve_index('./public'));
app.use(express.static('./public'));

const https_server = https.createServer(options,app);

https_server.listen(config.port,config.hostname,() => {
  console.log(`server is running at ${config.protocol}://${config.hostname}:${config.port}:`);
})

