//#include <iostream>  
//#include <string>
//#include <sstream> 
//#include <typeinfo>
#include <SoftwareSerial.h> 
#include <ESP8266WiFi.h>
#include <ThingESP.h>
#include <WifiClient.h>
#include <ESP8266WebServer.h>
using namespace std;

ThingESP8266 thing("senamrit7", "Locker", "ABCDEF");

const char *ssid =  "Amrit";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Rony200175";

//const char *ssid =  "Honor Stark";     // replace with your wifi ssid and wpa2 key
//const char *pass =  "password"; 

int D5 = 14, D4 = 2;
SoftwareSerial s(D5, D4);

WiFiClient client;
const int httpPort = 80;
int data1;
StaticJsonDocument<1000> root ;

void setup() {
  // Initialize Serial port
    Serial.begin(9600);
    s.begin(9600);
    thing.initDevice();
    while (!Serial) continue;


    Serial.println("Connecting to ");
       Serial.println(ssid);

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED)  {
        delay(500);
        Serial.print(".");
    }
        Serial.println("");
        Serial.println("WiFi connected to");
        Serial.println(WiFi.SSID());
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        Serial.println("");
}

void loop() 
{
  
    DeserializationError error = deserializeJson(root, s);
    if (error)
    return;

    Serial.println("JSON received and parsed"); 
 
 
    Serial.println("---------------------xxxxx--------------------");
    data1=root["pass"];
    //string str = to_string(data1);
    Serial.print("Pass: "); 
    Serial.print(data1);
//    stringstream stream;
//    //char ex = data1;
//    stream << data1;
//    string str;
//    stream >> str;
    Serial.println("");
    
    thing.Handle();

    client.stop();
    delay(3000);
    Serial.println("Waiting..."); 
}


String HandleResponse(String query)
{  
   //std::string str(1, data1);
   //str.push_back(data1);
   return "Akshay Gupta has irregular health vitals. Please Check!! The unique ID for Digilock A6 is 856542. Do not share with anyone. This ID is valid for the next 10 minutes. Patient name: Akshay Gupta Location: https://www.google.com/maps/place/Vellore+Institute+of+Technology+-+VIT+Chennai/@12.840641,80.1512396,17z/data=!3m1!4b1!4m5!3m4!1s0x3a5259af8e491f67:0x944b42131b757d2d!8m2!3d12.840641!4d80.1534283 Is in need of ambulances. Reach out immediately!"; 
}
