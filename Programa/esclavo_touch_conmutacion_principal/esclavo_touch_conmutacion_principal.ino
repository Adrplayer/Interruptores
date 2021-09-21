const int En_WrRd_RS485 = 2;
const int Rele    = 3;
const int led1    = 4;
const int touchIn = 9;
const int t     = 100;

String    id    = "E";// UPCASE
String    _id   = "e";//DOWNCASE
String    inputString;

boolean    touchState;
boolean    completeString;

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
  completeString = false;
}

//loop
void loop(){
  serialEvent();
  touchEvent();
}

void serialEvent(){
  while(Serial.available()){
    digitalWrite(led1,HIGH);
    char inputChar = Serial.read();
    inputString += inputChar;
    if(inputChar == '#'){
      completeString = true;
      continue;
    }
  }
  digitalWrite(led1,LOW);
  delay(200);
  if (completeString){
    if(inputString.indexOf(id)>=0){
      touchState = !(touchState);
      digitalWrite(Rele,touchState);
      send();
    }
  }
  inputString = "";
  completeString = false;
}

void touchEvent(){
    if(digitalRead(touchIn)){
      touchState = !(touchState);
      digitalWrite(Rele,touchState);
      delay(360);
      send();
    }
  }
void send(){
  digitalWrite(En_WrRd_RS485, HIGH);
  blink();
  delay(5);
  Serial.println( _id + String(touchState) + "#");
  Serial.flush();
  digitalWrite(En_WrRd_RS485, LOW);
  blink();
}

void blink(){
  digitalWrite(led1,HIGH);
  delay(t);
  digitalWrite(led1,LOW);
  delay(t);
  digitalWrite(led1,HIGH);
  delay(t);
  digitalWrite(led1,LOW);
}

