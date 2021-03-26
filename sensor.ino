 
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

int inputPinuno = 5; //D1 izquierda
int inputPincero = 16; //D0 derecha


int valor1 = LOW;
int valor2 = LOW;

 String estado = "Apagado";
//------ para conectar a internet
const char* ssid     = "INFINITUMB(X^2)";
const char* password = "Gsg26#Ji$80A&16";
HTTPClient http;

//----- conexion con arango
//String server = "http://209.151.153.46:8529/_db/nosql_eq3/sensorhumo/humo/insertpost";
String server = "http://192.168.1.78:5000/sensores";

void setup() {
  Serial.begin(9600); // sets the serial port to 9600
   WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
  delay(1000); 

  //codigo
  
  pinMode(inputPinuno, INPUT);
  pinMode(inputPincero, INPUT);
  
}

void loop() {
 valor1 = digitalRead(inputPinuno);  //lectura digital de pin
 valor2 = digitalRead(inputPincero);  //lectura digital de pin
// Serial.println(valor1);
 //Serial.println(valor2);
 if(valor1 == HIGH && valor2 == LOW){
  estado = "IZQUIERDA";
  post(estado);
  //Serial.println("IZQUIERDA");
  delay(100);
  
 }
 else
   if(valor2 == HIGH && valor1 == LOW){
    estado = "DERECHA";
    post(estado);
    //Serial.println("DERECHA");
  delay(100);
 }
 else
 if(valor1==LOW && valor2 == LOW)
 {
  estado = "Apagado";
    post(estado);
  //Serial.println("APAGADO");
  delay(100);
 }
 
}
void post(String estado){
   HTTPClient http;
  String json;
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["estado"] = estado;
  root.printTo(json);
  Serial.println(""); // salto de linea para http.writeToStream(&Serial);
  http.begin(server);
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
  }
