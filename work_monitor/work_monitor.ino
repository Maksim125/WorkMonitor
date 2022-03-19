String dataLabel1 = "Photoresistor";
int sensor1 = A1;
float threshold = 500;

int digit1 = 6; //Left most digit
int digit2 = 9; //2nd from the left
int digit3 = 10; //2nd from the right
int digit4 = 11; //Right most digit

#define DIGIT_ON LOW
#define DIGIT_OFF HIGH
#define DISPLAY_BRIGHTNESS 500

int segA = 2;
int segB = 3;
int segC = 4;
int segD = 5;
int segE = A0;
int segF = 7;
int segG = 8;
int segDP = 12;

unsigned long ledCounter = 0; //In units of seconds, what time you want to start the clock with
unsigned long sleepThreshold = 10; //Seconds to wait after the light is off before reset of clock
unsigned long startMillis;
unsigned long startRefreshMillis;
unsigned long currentMillis;
const unsigned long period = 1000;

const unsigned long refreshDigit = 5; //How fast to refresh the display
int currDigit = 0;
bool ledOn;
int ledTimer[] = {0,0,0,0}; //Hour tens, hour ones . Second tens, Second ones
unsigned long sleepTimer = 0;


void setup() {
  //Open the serial port communication
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  //Set the pin to measure the sensor voltage
  pinMode(sensor1, INPUT);

  //Setup the pins for the eight segment display
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);

  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(segDP, OUTPUT);

  //Start the timer
  startMillis = millis();
  startRefreshMillis = millis();
}

void loop() {
  currentMillis = millis();
  unsigned long brightness = analogRead(sensor1);

  //Every second, check if the led is on, and if it is, append an extra second to the time
  if(currentMillis - startMillis >= period) {
    startMillis = currentMillis;
    //If LED is on, reset the sleep timer
    if (brightness > threshold) {
      ledCounter++;
      sleepTimer = 0;
    }
    //If the timer timed out, send the number of seconds it had been on to the serial port
    if (sleepTimer >= sleepThreshold && ledCounter > 0) {
      sendLEDOnSeconds(ledCounter);
      ledCounter = 0;
    }
    
    //If LED is off, accumulate an extra second to the sleep timer if it hasn't timed out already
    if (brightness < threshold && sleepTimer < sleepThreshold) {
      sleepTimer++;
    }
    
    //Get the number of hours and minutes
    unsigned long hours = ledCounter / 3600;
    unsigned long minutes = (ledCounter - (hours * 3600)) / 60;
    unsigned long seconds = (ledCounter - (hours * 3600) - (minutes * 60));

    //If no hours yet, display minutes and seconds
    if (hours == 0) {
      ledTimer[0] = (minutes /10) % 10;
      ledTimer[1] = minutes % 10;

      ledTimer[2] = (seconds /10);
      ledTimer[3] = seconds % 10;
    }
    //If at least one hour passed, display hours and minutes
    if (hours >= 1) {
      ledTimer[0] = (hours /10) % 10;
      ledTimer[1] = hours % 10;

      ledTimer[2] = (minutes /10);
      ledTimer[3] = minutes % 10;
    }
  }

  //Refresh the display and write the number in each place
  if (currentMillis - startRefreshMillis > refreshDigit) {
    //Dim the display using the default case of writenumber for non-single digit integer input
    writeNumber(1000, false);

    //If the sleep timer hasn't been exceeded, light up the display to show the current timer
    if (sleepTimer < sleepThreshold) {
      currDigit++;
      currDigit = currDigit % 4;
      digitOn(currDigit);
      if (currDigit == 1) {
        writeNumber(ledTimer[currDigit],true);
      }
      else {
        writeNumber(ledTimer[currDigit],false);
      }
    }
  }
}

/*
 * Sends the number of seconds that have passed for this session to the
 * serial port
 */
void sendLEDOnSeconds(int seconds) {
  Serial.println(seconds);
}

/*
 * Turns on the digit at the specific index
 * 
 * @param digitIndex which digit to turn on
 */
void digitOn(int digitIndex) {
  if (digitIndex == 0) {
    digitalWrite(digit1, DIGIT_ON);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
  }
  if (digitIndex == 1) {
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_ON);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
  }
  if (digitIndex == 2) {
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_ON);
    digitalWrite(digit4, DIGIT_OFF);
  }
  if (digitIndex == 3) {
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_ON);
  }
}

/*
 * Write number to selected digit for the 8 segment display
 * 
 * @param num the digit to write
 * @param dot whether or not to display the period in the display
 */
void writeNumber(int num, bool dot) {
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segDP, LOW);

  if (dot) {
    digitalWrite(segDP, HIGH);
  }
  switch(num) {
    case 0:
      digitalWrite(segB,HIGH);
      digitalWrite(segC,HIGH);
      digitalWrite(segF,HIGH);
      digitalWrite(segE,HIGH);
      digitalWrite(segA,HIGH);
      digitalWrite(segD,HIGH);
      break;
    case 1:
      digitalWrite(segB,HIGH);
      digitalWrite(segC,HIGH);
      break;
    case 2:
      digitalWrite(segA,HIGH);
      digitalWrite(segB,HIGH);
      digitalWrite(segG,HIGH);
      digitalWrite(segE,HIGH);
      digitalWrite(segD,HIGH);
      break;
    case 3:
      digitalWrite(segA,HIGH);
      digitalWrite(segB,HIGH);
      digitalWrite(segG,HIGH);
      digitalWrite(segC,HIGH);
      digitalWrite(segD,HIGH);
      break;
    case 4:
      digitalWrite(segF,HIGH);
      digitalWrite(segG,HIGH);
      digitalWrite(segB,HIGH);
      digitalWrite(segC,HIGH);
      break;
    case 5:
      digitalWrite(segA,HIGH);
      digitalWrite(segF,HIGH);
      digitalWrite(segG,HIGH);
      digitalWrite(segC,HIGH);
      digitalWrite(segD,HIGH);
      break;
    case 6:
      digitalWrite(segA,HIGH);
      digitalWrite(segF,HIGH);
      digitalWrite(segG,HIGH);
      digitalWrite(segC,HIGH);
      digitalWrite(segD,HIGH);
      digitalWrite(segE,HIGH);
      break;
    case 7:
      digitalWrite(segB,HIGH);
      digitalWrite(segC,HIGH);
      digitalWrite(segA,HIGH);
      break;
    case 8:
      digitalWrite(segB,HIGH);
      digitalWrite(segC,HIGH);
      digitalWrite(segF,HIGH);
      digitalWrite(segE,HIGH);
      digitalWrite(segA,HIGH);
      digitalWrite(segD,HIGH);
      digitalWrite(segG,HIGH);
      break;
    case 9:
      digitalWrite(segB,HIGH);
      digitalWrite(segC,HIGH);
      digitalWrite(segF,HIGH);
      digitalWrite(segA,HIGH);
      digitalWrite(segG,HIGH);
      break; 
  }
}
