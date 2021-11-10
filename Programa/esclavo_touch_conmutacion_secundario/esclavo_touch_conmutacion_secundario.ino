const int En_WrRd_RS485 = 2;
const int Rele    = 3;
const int led1    = 4;
const int touchIn = 9;
const int t     =  90;

String    id    = "D";// UPCASE
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
      delay(60);
    }
  }
void send(){
  digitalWrite(En_WrRd_RS485, HIGH);
  /* blink(); */
  delay(5);
  Serial.println( id + "#");
  Serial.flush();
  digitalWrite(En_WrRd_RS485, LOW);
}

void blink(){
  digitalWrite(led1,HIGH);
  delay(t);
  digitalWrite(led1,LOW);
  delay(t);
  digitalWrite(led1,HIGH);
  delay(t);
  digitalWrite(led1,LOW);
  delay(t);
  digitalWrite(led1,HIGH);
  delay(t);
  digitalWrite(led1,LOW);
}

