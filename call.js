
var request = require("request")
var i = 0

function doit () {
	v = Math.random() * 100

	request("https://api.thingspeak.com/update?api_key=JBFKFKUF2QCPSL3B&field1="+v, function(err,res, body) {console.log(body)})

	console.log('i=${i}')
	if(i++ > 10) return
	setTimeout(doit, 20000);
}

console.log("ready")
doit()