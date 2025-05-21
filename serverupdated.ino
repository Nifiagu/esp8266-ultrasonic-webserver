#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "one piece_2.4";
const char* password = "Babynanaytatay.01";

const int trigPin = D1;
const int echoPin = D2;

long duration;
float distance;

ESP8266WebServer server(80);

void updateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);
  distance = (duration == 0) ? -1 : (duration * 0.0343) / 2.0;
}

void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>Mechatronics Project</title>
      <style>
        body {
          margin: 0;
          font-family: 'Segoe UI', sans-serif;
          background: url('https://i.imgur.com/EkH21BO.gif') no-repeat center center fixed;
          background-size: cover;
          color: white;
          text-align: center;
        }
        .main-box {
          margin-top: 60px;
          padding: 20px;
          border-radius: 15px;
          background: rgba(0, 0, 0, 0.6);
          animation: glow 2s infinite alternate;
          width: 80%;
          max-width: 700px;
          margin-left: auto;
          margin-right: auto;
        }
        @keyframes glow {
          from { box-shadow: 0 0 10px cyan; }
          to { box-shadow: 0 0 30px magenta; }
        }
        h1, h2 {
          margin: 10px;
        }
        .rainbow-button {
          display: inline-block;
          margin: 20px 10px;
          padding: 15px 25px;
          font-size: 18px;
          font-weight: bold;
          border: none;
          border-radius: 10px;
          cursor: pointer;
          color: white;
          background: linear-gradient(270deg, red, orange, yellow, green, cyan, blue, violet);
          background-size: 1400% 1400%;
          animation: rainbow 5s ease infinite;
          box-shadow: 0 0 10px white;
        }
        @keyframes rainbow {
          0% { background-position: 0% 50%; }
          50% { background-position: 100% 50%; }
          100% { background-position: 0% 50%; }
        }
        .desc-box {
          margin-top: 30px;
          margin-left: auto;
          margin-right: auto;
          width: 80%;
          background: rgba(0, 0, 0, 0.5);
          padding: 15px;
          border-radius: 10px;
          animation: glowDesc 3s ease-in-out infinite alternate;
          text-align: left;
          font-size: 14px;
        }
        @keyframes glowDesc {
          from { box-shadow: 0 0 10px #00ffe7; }
          to { box-shadow: 0 0 20px #ff00ff; }
        }

        .member-list {
          display: none;
          margin-top: 20px;
          animation: slideDown 0.5s ease forwards;
        }
        @keyframes slideDown {
          from { max-height: 0; opacity: 0; }
          to { max-height: 500px; opacity: 1; }
        }
        .member-item {
          margin: 10px;
          padding: 10px;
          cursor: pointer;
          display: inline-block;
        }
        .member-photo {
          display: none;
          margin-right: 15px;
          margin-bottom: 15px;
          animation: fadeIn 0.5s ease forwards;
        }
        @keyframes fadeIn {
          from { opacity: 0; transform: translateX(-20px); }
          to { opacity: 1; transform: translateX(0); }
        }
        .member-container {
          display: flex;
          align-items: center;
          justify-content: flex-start;
        }
      </style>
    </head>
    <body>
      <div class="main-box">
        <h1>FINAL PROJECT IN MECHTRONICS APPLIED ROBOTICS MX 326</h1>
        <h2>BSMX 3A-DAY</h2>
        <button class="rainbow-button" onclick="location.href='/ESP2688'">Distance</button>
        <button class="rainbow-button" onclick="toggleMembers()">Members</button>
        <div id="memberList" class="member-list">
          <div class="member-container" onmouseover="showPhoto('patinio')" onmouseout="hidePhoto('patinio')">
            <img id="patinio" class="member-photo" src="https://i.yourpicturelink.jpg" width="100">
            <span class="member-item">PATINIO, RAMELYN JAYNE</span>
          </div>
          <div class="member-container" onmouseover="showPhoto('puno')" onmouseout="hidePhoto('puno')">
            <img id="puno" class="member-photo" src="https://i.yourpicturelink.jpg" width="100">
            <span class="member-item">PUNO, NIKKO M.</span>
          </div>
          <div class="member-container" onmouseover="showPhoto('omega')" onmouseout="hidePhoto('omega')">
            <img id="omega" class="member-photo" src="https://i.yourpicturelink.jpg" width="100">
            <span class="member-item">OMEGA, JESTER F.</span>
          </div>
          <div class="member-container" onmouseover="showPhoto('pila')" onmouseout="hidePhoto('pila')">
            <img id="pila" class="member-photo" src="https://i.yourpicturelink.jpg" width="100">
            <span class="member-item">PILA, JHADE MAURENE L.</span>
          </div>
          <div class="member-container" onmouseover="showPhoto('ponce')" onmouseout="hidePhoto('ponce')">
            <img id="ponce" class="member-photo" src="https://i.yourpicturelink.jpg" width="100">
            <span class="member-item">PONCE, MARC VINCENT G.</span>
          </div>
          <div class="member-container" onmouseover="showPhoto('arafol')" onmouseout="hidePhoto('arafol')">
            <img id="arafol" class="member-photo" src="https://i.yourpicturelink.jpg" width="100">
            <span class="member-item">ARAFOL, MARC LOUIE A.</span>
          </div>
          <div class="member-container" onmouseover="showPhoto('cortes')" onmouseout="hidePhoto('cortes')">
            <img id="cortes" class="member-photo" src="https://i.yourpicturelink.jpg" width="100">
            <span class="member-item">CORTES, JOHN PATRICK KHARLO</span>
          </div>
          <div class="member-container" onmouseover="showPhoto('bughao')" onmouseout="hidePhoto('bughao')">
            <img id="bughao" class="member-photo" src="https://i.yourpicturelink.jpg" width="100">
            <span class="member-item">BUGHAO, HANNY CLAIRE</span>
          </div>
        </div>
      </div>

      <div class="desc-box">
        <strong>Project Overview:</strong><br>
        ESP8266-Based Web Server with Ultrasonic Sensor<br><br>
        This project uses an ESP8266 microcontroller to host a multi-page web server that displays real-time distance data using an ultrasonic sensor (HC-SR04). It visually represents the sensor readings on a stylish web interface with glowing UI elements and animations.<br><br>
        <strong>Hardware Components:</strong><br>
        - ESP8266 Module (e.g., NodeMCU)<br>
        - Ultrasonic Sensor (HC-SR04)<br><br>
        <strong>Wiring:</strong><br>
        - Trig pin: D1<br>
        - Echo pin: D2<br>
        - VCC pin : 3v<br>
        - Ground pin : Ground<br><br>
      </div>

      <script>
        function toggleMembers() {
          const list = document.getElementById("memberList");
          if (list.style.display === "block") {
            list.style.display = "none";
          } else {
            list.style.display = "block";
          }
        }
        function showPhoto(id) {
          document.getElementById(id).style.display = "block";
        }
        function hidePhoto(id) {
          document.getElementById(id).style.display = "none";
        }
      </script>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void handleDistancePage() {
  updateDistance();

  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>ESP2688</title>
      <style>
        body {
          font-family: 'Segoe UI', sans-serif;
          background: url('https://i.imgur.com/efReeSv.gif') no-repeat center center fixed;
          background-size: cover;
          color: #fff;
          text-align: center;
          margin: 0;
          padding: 0;
        }
        .container {
          margin-top: 100px;
          background: rgba(0, 0, 0, 0.6);
          display: inline-block;
          padding: 40px;
          border-radius: 15px;
          box-shadow: 0 0 15px #00ffe7;
        }
        h1 {
          font-size: 36px;
          margin-bottom: 20px;
          color: #00ffe7;
        }
        p {
          font-size: 24px;
        }
        .rainbow-btn {
          margin-top: 30px;
          font-size: 20px;
          font-weight: bold;
          padding: 12px 30px;
          border: none;
          border-radius: 12px;
          cursor: pointer;
          background: linear-gradient(45deg, red, orange, yellow, green, cyan, blue, violet);
          background-size: 400% 400%;
          color: white;
          animation: rainbowGlow 5s ease infinite;
          box-shadow: 0 0 15px white;
        }
        @keyframes rainbowGlow {
          0% { background-position: 0% 50%; }
          50% { background-position: 100% 50%; }
          100% { background-position: 0% 50%; }
        }
      </style>
      <script>
        function fetchDistance() {
          fetch('/distanceData')
            .then(response => response.json())
            .then(data => {
              document.getElementById('distanceValue').innerText = data.distance + ' cm';
              document.getElementById('statusValue').innerText = data.status;
              document.getElementById('statusValue').style.color = data.color;
            });
        }
        setInterval(fetchDistance, 1000);
      </script>
    </head>
    <body onload="fetchDistance()">
      <div class='container'>
        <h1>ULTRASONIC SENSOR</h1>
        <p><b>Distance:</b> <span id="distanceValue">Loading...</span></p>
        <p><b>Status:</b> <span id="statusValue">Loading...</span></p>
        <button class='rainbow-btn' onclick="location.href='/'">BACK</button>
      </div>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void handleDistanceData() {
  updateDistance();

  String statusText = "NONE";
  String statusColor = "white";

  if (distance > 0 && distance <= 10) {
    statusText = "NEAR";
    statusColor = "lime";
  } else if (distance > 10 && distance <= 30) {
    statusText = "NOT TOO FAR";
    statusColor = "yellow";
  } else if (distance > 30) {
    statusText = "FAR";
    statusColor = "red";
  }

  String json = "{";
  json += "\"distance\":" + String(distance) + ",";
  json += "\"status\":\"" + statusText + "\",";
  json += "\"color\":\"" + statusColor + "\"";
  json += "}";

  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected. IP:");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/ESP2688", handleDistancePage);
  server.on("/distanceData", handleDistanceData);

  server.begin();
}

void loop() {
  server.handleClient();
}
