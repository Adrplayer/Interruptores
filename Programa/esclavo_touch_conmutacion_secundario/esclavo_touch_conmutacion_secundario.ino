/*
TODO

[x] Remove blink funct
[x] Remove t variable

*/


const int En_WrRd_RS485 = 2;
const int Rele    = 3;
const int led1    = 4;
const int touchIn = 9;

String    id    = "C";// UPCASE
String    inputString;

boolean    touchState;

// Set up
void setup(){
  // Serial init
  Serial.begin(9600);

  // Pin setup
  pinMode(En_WrRd_RS485, OUTPUT);
  pinMode(Rele, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(touchIn, INPUT);

  // Pin init
  digitalWrite(En_WrRd_RS485, LOW);
  digitalWrite(Rele, LOW);
  digitalWrite(led1, LOW);

  // touchState
  touchState = false;
}

//loop
void loop(){
  touchEvent();
}


void touchEvent(){
    if(digitalRead(touchIn)){
      touchState = !(touchState);
      digitalWrite(Rele,touchState);
      send();
      delay(600);
    }
  }
void send(){
  digitalWrite(En_WrRd_RS485, HIGH);
  /* digitalWrite(led1,HIGH); */
  delay(10);
  Serial.println( id + "#");
  Serial.flush();
  /* digitalWrite(led1,LOW); */
  digitalWrite(En_WrRd_RS485, LOW);
}
