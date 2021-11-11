/*
TODO
[x] reorder send and delay in touch event (ln 34,35)
[x] led_1 rename to Rele
[x] remove the tolower funct and replace with _id character
[x] Change ln 65-66 , add _id into the send string
[ ] Code organize
[ ] Comments
[ ] Docs

*/

const int En_WrRd_RS485 = 2;
const int Rele = 3;
const int led1 = 4;
const int touchIn = 9 ;
boolean touchState;
String id= "B"; // UPCASE
String _id="b"; // downcase
char VarChar = ' ';
String BufferIn = "";
boolean StringCompleta = false;

// Set up
void setup(){
  Serial.begin (9600);
  pinMode (En_WrRd_RS485, OUTPUT);
  pinMode (Rele, OUTPUT);
  pinMode (led1, OUTPUT);
  pinMode (touchIn, INPUT);
  digitalWrite (En_WrRd_RS485, LOW);
  digitalWrite (Rele, LOW);
  touchState = false;
}

//loop
void loop(){
  if(digitalRead(touchIn)){
    touchState = !(touchState);
    digitalWrite(Rele,touchState);
    send();
    delay(360);
  }
  serialEvent();
  if(StringCompleta){
    if(BufferIn.indexOf(id) >= 0 ){
      touchState = !(touchState);
      digitalWrite(Rele,touchState);
      delay(10);
      send();
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
  Serial.print(_id);
  Serial.print(String(touchState));
  Serial.println("#");
  Serial.flush();
  digitalWrite(En_WrRd_RS485, LOW);
}
