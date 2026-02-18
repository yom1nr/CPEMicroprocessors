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
<br><br>

<button type="button" onclick="sendData(10)" style="background: rgb(100,116,255);">LED1 OFF</button>
<button type="button" onclick="sendData(20)" style="background: rgb(100,116,255);">LED2 OFF</button>
<button type="button" onclick="sendData(30)" style="background: rgb(100,116,255);">LED3 OFF</button>
<button type="button" onclick="sendData(40)" style="background: rgb(100,116,255);">LED4 OFF</button>
<br><br>

State of [LED1, LED2, LED3, LED4] is >> <span id="LEDState">NA NA NA NA</span><br>
</div>
<div>
<br>DHT-22 sensor : <span id="ADCValue">0</span><br>
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
<br><a href="https://web.facebook.com/pangpond.nattapat.9">By Nadthapat Phuttaruksa)</a>
<br>
<br> 
<a href="https://github.com/Tucklyz"><img src="https://scontent.fbkk4-1.fna.fbcdn.net/v/t39.30808-6/327170533_568007628556197_6071965835600377522_n.jpg?_nc_cat=111&ccb=1-7&_nc_sid=5f2048&_nc_eui2=AeFyEXZbXs_e5qk2bHgTqed2NLWMPv-WSV80tYw-_5ZJX5SekNXDR4h-ONUUCwVD23oO5RlEeB0Ffpi9onAUHgaN&_nc_ohc=sa0vy4JGdEoAX9TAuVt&_nc_zt=23&_nc_ht=scontent.fbkk4-1.fna&oh=00_AfDRJMrCYJPUt864kClvEu7AJ3y6fSAiwLyUzt8MNiUy_g&oe=660A4A86" alt= width="250" height="250"></a>


</body>
</html>
)=====";
