 //misc
//#define clockPin 8
//#define clearCounter 7
//#define minusVRef 10
//#define vIn 9
 
//the value between 0-255 being read in
#define inPinA 3
#define inPinB 4
#define inPinC 5
#define inPinD 6

//these are used to output to the 7 seg decoder
#define dataPinA 14
#define dataPinB 15
#define dataPinC 16
#define dataPinD 17

//these are used to multiplex the 7 segs
#define switchPinA 11
#define switchPinB 12
#define switchPinC 18

int displayArr[3];
int analogConversion{};

void setup() {
  for(int i = 3; i <= 6; i++){
	pinMode(i, INPUT);
  }
  for(int i = 14; i <= 18){
	pinMode(i, OUTPUT);
	digitalWrite(i, 0);
  }

  pinMode(11, OUTPUT);
  digitalWrite(11, 0);
  pinMode(12, OUTPUT);
  digitalWrite(12, 0);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  readInput();
  
  for(int i = 0; i < 250; i++){
      displayNum();
  }
}

void inputSelect(int s){
  switch(s){
    case 0:
      digitalWrite(vIn, 1);
      digitalWrite(minusVRef, 0);

    case 1:
      digitalWrite(vIn, 0);
      digitalWrite(minusVRef, 1);
  }
}

void clk(int t){
  for(int i = 0; i < t; i++){
      digitalWrite(clockPin, 1);
      delay(5);
      digitalWrite(clockPin, 0);
      delay(5);
  }
}

void clearC(){
   digitalWrite(clearCounter, 1);
   delay(5);
   digitalWrite(clearCounter, 0);
   delay(5);
  
}

void readInput(){
  int a = digitalRead(inPinA);
  int b = digitalRead(inPinB) << 1;
  int c = digitalRead(inPinC) << 2;
  int d = digitalRead(inPinD) << 3;
  analogConversion = a+b+c+d;
}

void arrayFiller(int num, int arr[]){
  int decade = 100;
  int temp{};
  for(int i = 0; i < 3; i++){
    arr[i] = num / decade;
    temp = arr[i] * decade; 
    num -= temp;
    decade /= 10;
  }
}
void binaryOut(int num){
  digitalWrite(dataPinA, (num & 0x01));
  digitalWrite(dataPinB, (num & 0x02) >> 1);
  digitalWrite(dataPinC, (num & 0x04) >> 2);
  digitalWrite(dataPinD, (num & 0x08) >> 3);
   
}

void segSelect(int seg){
  switch(seg){
    //the drivers for each 7 seg will be a inverter pulling it low to activate it
    case 0:
    digitalWrite(switchPinA, 1);
    digitalWrite(switchPinB, 0);
    digitalWrite(switchPinC, 0);
    break;

    case 1:
    digitalWrite(switchPinA, 0);
    digitalWrite(switchPinB, 1);
    digitalWrite(switchPinC, 0);
    break;

    case 2:
    digitalWrite(switchPinA, 0);
    digitalWrite(switchPinB, 0);
    digitalWrite(switchPinC, 1);
    break;

  }
}

void displayNum(){
  for(int i = 0; i < 3; i++){
    segSelect(i);
    binaryOut(displayArr[i]);
    delayMicroseconds(4500);
  }
}
