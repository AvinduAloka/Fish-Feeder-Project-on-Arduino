#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid     = "AndroidAP";
const char* password = "aaaaaaaaa";

ESP8266WebServer WebServer (80);

int SERVOCurrent = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(200);
  Serial.println("Verbinde Servo.");
  
  connectWifi();
  beginServer();
}

void loop() {
  // put your main code here, to run repeatedly:
  WebServer.handleClient();
}

void connectWifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi verbunden");
  Serial.println("IP Addresse: ");
  Serial.println(WiFi.localIP());
}

void beginServer()
{
  WebServer.on ( "/", handleRoot ); // Wenn die URL aufgerufen wird (ohne etwas hinter dem /) wird die Funktion "handleRoot" gestartet
  WebServer.begin();
  Serial.println ( "HTTP Webserver gestartet!" );
}

void handleRoot() {
  if ( WebServer.hasArg("SERVO") ) { // Wir wurden mit dem Argument "SERVO" aufgerufen - es gibt also gleich etwas zu tun!
    handleSubmit();
  } else {
    // Einfach nur die Webseite ausliefern
    WebServer.send ( 200, "text/html", getPage());
  }
}

void handleSubmit(){
  String SERVOValue;
  SERVOValue =WebServer.arg("SERVO");
  
  if (SERVOValue == "FeedNow") {
    //SERVOCurrent = SERVOCurrent + 15;
      pinMode(0, OUTPUT);
      soundDeep();
      pinMode(2, OUTPUT);
      stop();
      SERVOValue = "-15";
  }
  else if (SERVOValue == "1s.Apply") {
    //SERVOCurrent = SERVOCurrent + 15;
      pinMode(0, OUTPUT);
      soundDeep();
      pinMode(2, OUTPUT);
      stop1();
      SERVOValue = "-15";
  }
  else if (SERVOValue == "2s.Apply") {
    //SERVOCurrent = SERVOCurrent + 15;
      pinMode(0, OUTPUT);
      soundDeep();
      pinMode(2, OUTPUT);
      stop2();
      SERVOValue = "-15";
  }
  else if (SERVOValue == "3s.Apply") {
    //SERVOCurrent = SERVOCurrent + 15;
      pinMode(0, OUTPUT);
      soundDeep();
      pinMode(2, OUTPUT);
      stop4();
      SERVOValue = "-15";
  }
  else if (SERVOValue == "StopFeed") {
    //SERVOCurrent = SERVOCurrent + 15;
      pinMode(5, OUTPUT);
      onLight();
      pinMode(0, OUTPUT);
      soundDeep();
      pinMode(2, OUTPUT);
      stop3();
      SERVOValue = "-15";
  }
  

  Serial.print("Setze Winkel ");
  //int value1 = int(SERVOCurrent);
  //Serial.print(SERVOCurrent);
  Serial.println(" Grad.");
  //Servo_SG90.write(SERVOCurrent);
  // Webseite wieder aktualiseren
  WebServer.send ( 200, "text/html", getPage());  
}

void stop(){
  
  digitalWrite(2, LOW);  // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(750);                      // Wait for a second
  digitalWrite(2, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);
}

void stop1(){
  digitalWrite(2, LOW);  // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(750);                      // Wait for a second
  digitalWrite(2, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);
}

void stop2(){
  digitalWrite(2, LOW);  // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(1500);                      // Wait for a second
  digitalWrite(2, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);
}

void stop3(){
  delay(750);// Wait for a second
  digitalWrite(2, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);
}

void stop4(){
  digitalWrite(2, LOW);  // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(2250);  // Wait for a second
  digitalWrite(2, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);
}

void onLight(){
  digitalWrite(5,HIGH);
  delay(100);
  digitalWrite(5,LOW);
  delay(500);
}

void soundDeep(){
  digitalWrite(0,100);
  delay(100);
  digitalWrite(0,0);
  delay(500);
}

String getPage() {
  String ServoString = String(SERVOCurrent); // Holt die aktuelle Einstellung und wandelt diese in einen String. Ist untem im Code eingebaut.
  String page = "<html lang=de-DE><head>";
  //page += "<meta http-equiv='refresh' content='60'/>";
  page += "<title>Automatic Fish Feeder - Machine</title>";
  page += "<style>*{margin: 0;padding: 0;font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;}";
  page += ".backgroun_margin{margin: 5%;}";
  page += ".curd_header{width: auto;margin: 1%;padding: 20px;background: rgb(237, 237, 255);border-radius: 10px;}";
  page += ".curd_header h1{font-size: 38px;}";
  page += ".curd_header p{color: rgb(92, 92, 92);font-size: 15px;max-width: 580px;margin-top: 10px;margin-bottom: 10px;}";
  page += ".button{width: 120px;height: 42px;border-radius: 8px;border: 1px solid rgb(0, 110, 255);color: rgb(0, 110, 255);background: transparent;margin: 12px 0 0 0;cursor: pointer;transition: .3s ease-in-out;}";
  page += ".button:hover{width: 120px;height: 42px;border-radius: 8px; border: 1px solid rgb(0, 110, 255);color: white;background: rgb(0, 110, 255);margin: 12px 0 0 0;cursor: pointer;transition: .3s ease-in-out;}";
  page += ".buttond{width: 120px;height: 42px;border-radius: 8px;border: 1px solid rgb(184, 0, 0);color: rgb(184, 0, 0);background: transparent;margin: 12px 0 0 0;cursor: pointer;transition: .3s ease-in-out;}";
  page += ".buttond:hover{width: 120px;height: 42px;border-radius: 8px; border: 1px solid rgb(184, 0, 0);color: white;background: rgb(184, 0, 0);margin: 12px 0 0 0;cursor: pointer;transition: .3s ease-in-out;}";
  page += ".card_manager{display: flex;}";
  page += ".headering{margin: 18px 0 20px 0;}";
  page += ".headering h1{margin: 0 12px;}";
  page += ".headering hr{margin: 0 58% 0px 12px;border: 2px solid rgb(0, 110, 255);border-radius: 10px;}";
  page += ".bolding{font-weight: 600;color: black;}";
  page += "@media all and (max-width: 600px) {.card_manager{display: inline;}.curd_header{margin: 20px;}}</style></head>";
  page += "<div class='backgroun_margin'><div class='card_manager'><div class='curd_header'><h1>Food Feed - <span>Fish</span></h1><p>Apart from the existing automated fish feeders, this has a companion app that can control the fish feeder from anywhere in the world. You can instantly feed the fish or you can set your feeding schedule and change them easily using the scheduler in the companion app.</p>";
  page += "<div><form action='/' method='post'>";
  page += "<input class='button' type='submit' name='SERVO' value='FeedNow'>";
  page += "<input class='buttond' type='submit' name='SERVO' value='StopFeed'>";
  page += "</form></div></div>";
  page += "<div class='curd_header'><h1>Hi User</h1><p>This is an automatic fish feeder you can buildd at your home at low cost, this is a upgrade of my previous feeder it has a better efficiency and give best result to your fish and you.And you coud use this one on your mobile phone, desktop and laptop device.</p></div></div>";
  page += "<div class='headering'><h1>Control Your Fish Feed Machine</h1><hr></div>";
  page += "<form action='/' method='post'>";
  page += "<div class='card_manager'><div class='curd_header'>";
  page += "<h1>Low</h1><p>This function make to your purposes. This one make with the Machine work in Low speed feeds feed for fish.</p><p class='bolding'>1 Seconds</p>";
  page += "<input class='button' name='SERVO' type='submit' value='1s.Apply'></div>";
  page += "<div class='curd_header'>";
  page += "<h1>Normal</h1><p>This function make to your purposes. This one make with the Machine work in Normal speed feeds feed for fish.</p><p class='bolding'>2 Seconds</p>";
  page += "<input class='button' name='SERVO' type='submit' value='2s.Apply'></div>";
  page += "<div class='curd_header'>";
  page += "<h1>High</h1><p>This function make to your purposes. This one make with the Machine work in High speed feeds feed for fish.</p><p class='bolding'>3 Seconds</p>";
  page += "<input class='button' name='SERVO' type='submit' value='3s.Apply'></div>";
  page += "</div></form></div></body></html>";
  return page;
}
