const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<div id="demo">
<h1>The ESP-32 Update web page without refresh</h1>
<button type="button" onclick="sendData(11)" style="background: rgb(202, 60, 60);">LED1 ON </button>
<button type="button" onclick="sendData(21)" style="background: rgb(202, 60, 60);">LED2 ON </button>
<button type="button" onclick="sendData(31)" style="background: rgb(202, 60, 60);">LED3 ON </button>
<button type="button" onclick="sendData(41)" style="background: rgb(202, 60, 60);">LED4 ON </button>
<button type="button" onclick="sendData(51)" style="background: rgb(202, 60, 60);">LED5 ON </button>
<button type="button" onclick="sendData(61)" style="background: rgb(202, 60, 60);">LED6 ON </button>
<button type="button" onclick="sendData(71)" style="background: rgb(202, 60, 60);">LED7 ON </button>
<button type="button" onclick="sendData(81)" style="background: rgb(202, 60, 60);">LE8 ON </button>
<br><br>
<button type="button" onclick="sendData(10)" style="background: rgb(100,116,255);">LED1 OFF</button>
<button type="button" onclick="sendData(20)" style="background: rgb(100,116,255);">LED2 OFF</button>
<button type="button" onclick="sendData(30)" style="background: rgb(100,116,255);">LED3 OFF</button>
<button type="button" onclick="sendData(40)" style="background: rgb(100,116,255);">LED4 OFF</button>
<button type="button" onclick="sendData(50)" style="background: rgb(100,116,255);">LED5 OFF</button>
<button type="button" onclick="sendData(60)" style="background: rgb(100,116,255);">LED6 OFF</button>
<button type="button" onclick="sendData(70)" style="background: rgb(100,116,255);">LED7 OFF</button>
<button type="button" onclick="sendData(80)" style="background: rgb(100,116,255);">LED8 OFF</button>
<br><br>

State of [LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8] is >> <span id="LEDState">NA NA NA NA NA NA NA NA</span><br>
</div>
<script>
function sendData(led) {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if (this.readyState == 4 && this.status == 200) {
document.getElementById("LEDState").innerHTML =
this.responseText;
}
};
xhttp.open("GET", "setLED?LEDstate="+led, true);
xhttp.send();
}
setInterval(function() {
// Call a function repetatively with 2 Second interval
getData();
}, 2000); //2000mSeconds update rate
function getData() {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if (this.readyState == 4 && this.status == 200) {
document.getElementById("ADCValue").innerHTML =
this.responseText;
}
};
xhttp.open("GET", "readADC", true);
xhttp.send();
}
</script>
</body>
</html>
)=====";
