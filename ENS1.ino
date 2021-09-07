//the value between 0-255 being read in
#define inPinA 3
#define inPinB 4
#define inPinC 5
#define inPinD 6
#define inPinE 7
#define inPinF 8
#define inPinG 9
#define inPinH 10

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
  for(int i = 3; i <= 10; i++){
    pinMode(i, INPUT);
  }

  for(int i = 14; i <= 17; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(18, OUTPUT);
    
}

void loop() {

}

void readInput(){
  analogConversion | inPinA;
  analogConversion | (inPinB << 1);
  analogConversion | (inPinC << 2);
  analogConversion | (inPinD << 3);
  analogConversion | (inPinE << 4);
  analogConversion | (inpinF << 5);
  analogConversion | (inpinG << 6);
  analogConversion | (inpinH << 7);  
}

void arrayFiller(){
  
}

void display(int arr[]){
  
}
