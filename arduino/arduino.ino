#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include<Keypad.h>
#include<Servo.h>

SoftwareSerial wifi(11,12);

Servo servo;
char* passWord = "856542";
int position = 0;
int wrong = 0;
//float a;
char keys[4][4] = 
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
byte rowPins [4] = {9,8,7,6};
byte colPins[4] = {5,4,3,2};
Keypad keypad = Keypad(makeKeymap(keys),rowPins, colPins, 4, 4);
void setup()
{
  Serial.begin(9600);
  wifi.begin(9600);
  setLocked(true);
  servo.attach(10);
  servo.write(180);
  pinMode(13, OUTPUT);
}
void loop()
{
    StaticJsonDocument<1000> root ; 
  
  char key = keypad.getKey();
  Serial.println(key);
  if((key>= '0' && key <= '9') || (key>= 'A' && key <= 'D') || (key== '*' || key == '#'))
  {
    if (key == '*' || key == '#')
    {
      position = 0;
      wrong = 0;
      setLocked(true);
    }
    else if(key == passWord[position])
    {
      position++;
      wrong = 0;
    }
    else if(key != passWord[position])
    {
      position = 0;
      setLocked(true);
      wrong++;
    }
    if (position == 4)
    {
      setLocked(false);
    }
  }

    root["pass"] = passWord;
    if(wifi.available()>0){
    serializeJson(root,wifi);
  }

}
void setLocked(int locked)
{
  if(locked)
  {
    servo.write(0);
    digitalWrite(13, LOW);
  }
  else
  {
    delay(700);
    servo.write(180);
    digitalWrite(13, HIGH);
  }
}
