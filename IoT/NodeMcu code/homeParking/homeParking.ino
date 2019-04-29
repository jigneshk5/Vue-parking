#include <FirebaseArduino.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;
// Set these to run example.
#define FIREBASE_HOST "smartparking-62de8.firebaseio.com"
#define FIREBASE_AUTH "r4IE5XR8AJAXPIeqAcLmjOKJYaa0t4YKKsYHztTy"

const int trigPin = D0;
const int echoPin = D1;
const int echoPin1 = D2;

const int red1 = D3;     //Parking status
const int blue1 = D4;    //Booking status
const int red2 = D5;   
const int blue2 = D6;

// defines variables
long duration;
double distance;
bool space1 = false;
bool space2 = false;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  delay(10);
  pinMode(trigPin, OUTPUT);  
  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  pinMode(echoPin1, INPUT); 

  pinMode(red1,OUTPUT);
  pinMode(blue1,OUTPUT);
  pinMode(red2,OUTPUT);
  pinMode(blue2,OUTPUT);
  
  setupWiFi();
}
void setupWiFi(){
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("123456", "12345678");
  WiFiMulti.addAP("obd_jignesh", "jigneshkumar");
  WiFiMulti.addAP("silver lions zone", "science@123");
  
  Serial.print("connecting");
  while(WiFiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
      delay(100);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  BeginFirebase(); 
  }
void BeginFirebase(){
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.setString("Ultrasonic sensor 1", "0");
Firebase.setString("Ultrasonic sensor 2", "0");

 if(Firebase.success()){
    Serial.print("Firebase write success!");
  } else {
      Serial.print("Firebase write failed!");
      Serial.println("");
      Serial.print(Firebase.error());
  }
  Serial.println("");
}

void loop() {  
  if(Firebase.success()){
  String val = Firebase.getString("Ultrasonic sensor 1");
  if(val=="1"){
   digitalWrite(blue1,HIGH);
   int x = analogRead(A0);   // read the input on analog pin 0
    if(x<100){
     distance = triggerRadar(trigPin,echoPin);
      if(distance<=3){
        Firebase.setBool("space/space1",true);
        digitalWrite(red1,HIGH);
      }
      else{
        Firebase.setBool("space/space1",false);  
        digitalWrite(red1,LOW);
            }  
    }
  }
  String val1 = Firebase.getString("Ultrasonic sensor 2");
  if(val1=="1"){
    digitalWrite(blue2,HIGH);
    distance = triggerRadar(trigPin,echoPin1);
    if(distance<=3){
      Firebase.setBool("space/space2",true);
      digitalWrite(red2,HIGH);
    }
    else{
      Firebase.setBool("space/space2",false);
      digitalWrite(red2,LOW); 
          }  
    }
  if(val=="0"){
    digitalWrite(blue1,LOW);   //Booking finishes
  }
  if(val1=="0"){
    digitalWrite(blue2,LOW);
    //Firebase.setBool("space/space2",false);
  } 
//      Serial.println(analogRead(A0));
//      delay(100);
  }
    if (Firebase.failed())
    {
    Serial.println("Connecting again in 3sec");
    delay(3000);
    setupWiFi();
    }
}
double triggerRadar(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  double d = duration*0.0343/2;
  return d;
}
