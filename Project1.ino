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

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
    
}

void loop() {
	readInput();
	arrayFiller(analogConversion, displayArr);

	for(int i = 0; i < 300; i++){
		displayNum();
	}

	analogConversion = 0;
}

void readInput(){
  analogConversion | inPinA;
  analogConversion | (inPinB << 1);
  analogConversion | (inPinC << 2);
  analogConversion | (inPinD << 3);
  analogConversion | (inPinE << 4);
  analogConversion | (inPinF << 5);
  analogConversion | (inPinG << 6);
  analogConversion | (inPinH << 7);  
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
