
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "LedControl.h" //  need the library
unsigned long myTime;
#include <Wire.h>
LedControl lc=LedControl(D1,D0,D2,1); // lc is our object
// pin 12 D0 is connected to the MAX7219 pin 1
// pin 11 D1 is connected to the CLK pin 13
// pin 10 D2 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219
int tang = D3; //Tăng Thủ Công Kế Hoạch
int giam = D5; //Giảm Thủ Công Kế Hoạch
int nut = D6;  //Tăng Sản lượng Thủ Công
int sen = D7;  //Tăng sản lượng theo cảm biến đếm
const int buttonPin = D4; //Khai báo chân nút nhấn (Button)
int reding = 0;
int conter = 0;
int conter2 = 0;
int conter3 = 0;
int conter4 = 0;
int conter5 = 0;
int conter6 = 0;
int a,b,c,d,e,f;
int buttonPushCounter = 0;   //Số lần button được nhấn
int buttonState = 0;         //Trạng thái hiện tại của button
int lastButtonState = 0;     //Trạng thái trước đó của button
float k = 0;
float s = 0;
//WiFiSetting
const char* ssid      = "Thu Thao"; //Tên Wifi
const char* password  = "12052002";  //Pass Wifi

WiFiClient client;

//ThingSpeakSetting
const int channelID    = 1454544;// Enter Channel ID;
String writeAPIKey    = "PQI57ZOK1K34UKNQ";  //API Key 
const char* server    = "api.thingspeak.com"; //Giữ nguyên

//FunctionDeclare
void    wifiSetup();
void    thingConnect();
void    readSensor(void);
void    printData(void);

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP); //Cài đặt button là INPUT
  pinMode (tang, INPUT_PULLUP);
  pinMode (giam, INPUT_PULLUP);
  pinMode (nut, INPUT_PULLUP);
  pinMode (sen, INPUT_PULLUP);
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,8);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  Serial.println("Start Reading Sensor!\n");
  wifiSetup();
}

void loop() {
  thingConnect();
  readSensor();
  printData();
}

void wifiSetup() {  
  Serial.print("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.print("\r\nWiFi connected");
  logoConsole();
}

void thingConnect() {
  if (client.connect(server, 80)) {
    String body = "field1=" + String(s, 1) + "&field2=" + String(k, 1);
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(body.length());
    client.print("\n\n");
    client.print(body);
    client.print("\n\n");
  }
}

void printData(void) {
   Serial.printf("San Luong: % s    - Ke_Hoach: %s%\r\n", String(s, 1).c_str(), String(k, 1).c_str());
}

void readSensor(void) {
  
  buttonState = digitalRead(buttonPin); //Đọc giá trị nút nhấn
  if (buttonState != lastButtonState) //Nếu trạng thái khác
  {
    if (buttonState == LOW) //Nếu nút được nhấn
    { delay(300);
      buttonPushCounter++; //Tăng biến đếm số lần nhấn
    }}
  lastButtonState = buttonState; //Lưu lại trạng thái hiện tại

  //Tang 1
 if (buttonPushCounter %4 == 1){
 if (digitalRead(tang) == LOW){
      delay(500);
  conter = conter + 1;}}
  a = conter ; 
  if (a < 10){
lc.setDigit(0,0,a,true);
 }
 if (a > 9){
  conter = 0;
  a = 0;
lc.setDigit(0,0,a,false);
 }
//Tang 2
 if (buttonPushCounter %4 == 2){
  if (digitalRead(tang) == LOW){
      delay(500);
  conter2 = conter2 + 1;}}
  b = conter2 ; 
  if (b < 10){
lc.setDigit(0,1,b,false);
 }
 if (b > 9){
  conter2 = 0;
  b = 0;
  
lc.setDigit(0,1,b,false);}
 if (buttonPushCounter %4 == 3){
  if (digitalRead(tang) == LOW){
      delay(500);
  conter3 = conter3 + 1;}}
  c = conter3 ; 
  if (c < 10){
lc.setDigit(0,2,c,false);
 }
 if (c > 9){
  conter3 = 0;
  c = 0;
  
lc.setDigit(0,2,c,false);
 }

// KE HOACH
  if (buttonPushCounter %4 == 1){
  if (digitalRead(giam) == LOW){
      delay(200);
  conter = conter - 1;}}
  a = conter; 
  if (a > 0){
lc.setDigit(0,0,a,false);
 }
 if (a < 0){
  conter = 9;
  a = 9;
lc.setDigit(0,0,a,false);
 }

 
  if (buttonPushCounter %4 == 2){
  if (digitalRead(giam) == LOW){
      delay(200);
  conter2 = conter2 - 1;}}
  b = conter2; 
  if (b > 0){
lc.setDigit(0,1,b,false);
 }
 if (b < 0){
  conter2 = 9;
  b = 9;
lc.setDigit(0,1,b,false);
 }
  if (buttonPushCounter %4 == 3){
  if (digitalRead(giam) == LOW){
      delay(200);
  conter3 = conter3 - 1;}}
  c = conter3; 
  if (c > 0){
lc.setDigit(0,2,c,false);
 }
 if (c < 0){
  conter3 = 9;
  c = 9;
lc.setDigit(0,2,c,false);
 }
// SAN LƯỢNG
  if (digitalRead(sen)== LOW || digitalRead(nut) == LOW){
      delay(500);
  conter4 = conter4 + 1;}
  d = conter4; 
  if (d < 10){
lc.setDigit(0,7,d,false);
 }
 if (d > 9){
  d = 0;
lc.setDigit(0,7,d,false);
 } 

 
 if (conter4 > 9){
  conter5 = conter5 + 1;
  e = conter5;
  if (e < 10){
  lc.setDigit(0,6,e,false);}
  if (e > 9){
  e = 0;
lc.setDigit(0,6,e,false);}
  conter4 = 0;
  d = conter4;
  }
 if (conter5 > 9){
  conter6 = conter6 + 1;
  f = conter6;
  if (f < 10){
  lc.setDigit(0,5,f,false);}
  if (f > 9){
  f = 0;
lc.setDigit(0,5,f,false);}
  conter5 = 0;
  e = conter5;}
  if (conter4 > 9 && conter5 > 9 && conter6 > 9){
  conter4 = 0;
  d = conter4;
  conter5 = 0;
  e = conter5;
  conter6 = 0;
  f = conter6;}
  k = c*100 + b*10 +a;
  s = f*100 + e*10 + d;
}


void logoConsole(void) {
  Serial.printf("----------------------\\\\\n");
  Serial.printf("|| EPCBTechEPCBTechEPCB ||\n");
  Serial.printf("|| P                  T ||\n");
  Serial.printf("|| C      .*.         e ||\n");
  Serial.printf("|| B      * *  .*.    c ||\n");
  Serial.printf("|| T***.  * *  * `****h ||\n");
  Serial.printf("|| e   `**' *  *      E ||\n");
  Serial.printf("|| c        `**'      P ||\n");
  Serial.printf("|| h                  C ||\n");
  Serial.printf("|| EPCBTechEPCBTechEPCB ||\n");
  Serial.printf("----------------------//\n");
  Serial.printf("//---------------------------------------------------------------------------------\\\\\n");
  Serial.printf("||   __ _                            _   _  _             _ _                          ||\n");
  Serial.printf("||  / __| |_   _ _ _ _  _ _   ___| | |  \\/  | __  _ _ () |_ _  _ __                   ||\n");
  Serial.printf("|| | |   | '_ \\ / ` | ' \\| '_ \\ / _ \\ | | |\\/| |/ _ \\| '_ \\| | __/ _ \\| '__|   ||\n");
  Serial.printf("|| | |___| | | | (| | | | | | | |  __/ | | |  | | () | | | | | || (_) | | \            ||\n");
  Serial.printf("||  \\____|_| |_|\\__,_|_| |_|_| |_|\\___|_| |_|  |_|\\___/|_| |_|_|\\__\\___/|_|      ||\n");
  Serial.printf("\\\\---------------------------------------------------------------------------------//  \n");
}
