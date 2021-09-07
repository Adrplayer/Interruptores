const int En_WrRd_RS485 = 2;
const int Led_1 = 3;
const int touchIn = 9;
boolean touchState;
char id='J';// UPCASE
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
    delay(360);
    send();delay(50);
  }
}
void send(){
  delay(5);
  digitalWrite(En_WrRd_RS485, HIGH);
  Serial.print(id);
  Serial.print ('#');
  Serial.flush();
  digitalWrite(En_WrRd_RS485, LOW);
}
