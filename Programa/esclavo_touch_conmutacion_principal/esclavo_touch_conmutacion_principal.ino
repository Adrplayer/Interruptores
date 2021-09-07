const int En_WrRd_RS485 = 2;
const int Led_1 = 3;
const int touchIn = 9;
boolean touchState;
char id='E';// UPCASE
char VarChar = ' ';
String BufferIn = "";
boolean StringCompleta = false;

// Set up
void setup(){
  Serial.begin (9600);
  pinMode (En_WrRd_RS485, OUTPUT);
  pinMode (Led_1, OUTPUT);
  pinMode (touchIn, INPUT);
  digitalWrite (En_WrRd_RS485, LOW);
  digitalWrite (Led_1, LOW);
  touchState = false;
}

//loop
void loop(){
  if(digitalRead(touchIn)){
    touchState = !(touchState);
    digitalWrite(Led_1,touchState);
    digitalWrite(En_WrRd_RS485, HIGH);
    delay(360);
    send();delay(50);send();
  }

  if(StringCompleta){
    if(BufferIn.indexOf(id) >= 0 ){
      touchState = !(touchState);
      digitalWrite(Led_1,touchState);
      //send();delay(50);send();
    }
    StringCompleta = false;
    BufferIn = "";
  }
}

void serialEvent(){
  while (Serial.available()){
    VarChar = (char)Serial.read();
    BufferIn += VarChar;
    if (VarChar =='#') {StringCompleta = true;}
  }
}
void send(){
  digitalWrite(En_WrRd_RS485, HIGH);
  delay(5);
  Serial.print(tolower(id));
  Serial.print(touchState); 
  Serial.print ("#");
  Serial.flush();
  digitalWrite(En_WrRd_RS485, LOW);
}
