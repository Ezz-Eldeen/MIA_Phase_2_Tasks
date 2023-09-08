const int rotaryPinA = 2;  // Encoder signal A connected to digital pin 2
const int rotaryPinB = 3;  // Encoder signal B connected to digital pin 3

volatile int encoderCount = 0;  // Variable to store the encoder count
volatile int encoderLastA, encoderLastB;  // Variables to store the last encoder state
volatile int rotations = 0;

void setup() {
  pinMode(rotaryPinA, INPUT);
  pinMode(rotaryPinB, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(rotaryPinA), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rotaryPinB), encoderISR, CHANGE);
  //ISR stands for Interrupt Service Routine which is basically just a function that gets called
  // when a pin's state is changed from high to low or low to high
  Serial.begin(9600);
}

void loop() {
  // Print the encoder count and number of rotations in the clockwise direction
  Serial.print("Count: ");
  Serial.print(encoderCount);
  Serial.print("\tRotations: ");
  Serial.println(rotations);
  
  delay(500);  
}

// Interrupt service routine for the encoder
void encoderISR() {
  int encoderNewA = digitalRead(rotaryPinA);
  int encoderNewB = digitalRead(rotaryPinB);
  
  if (encoderNewA != encoderLastA || encoderNewB != encoderLastB) {
    // Checking the direction of the rotation by seeing which pin get's updated first
    if (encoderNewA == HIGH && encoderNewB == LOW && encoderLastA == LOW) {
    
      encoderCount++;
    }
    
    encoderLastA = encoderNewA;
    encoderLastB = encoderNewB;
  }
  
  // Check if the encoder has completed a full rotation in the clockwise direction
  if (encoderCount >= 540) {
    rotations++;  
    encoderCount = 0;  
  }
}
//only problem with this code is the ISR which will add 1 if for the first time I rotate counter clockwise since it doesn't have the previous pin state(or atleast that's what I think)


// Getting the cutoff frequency for the low pass filter:

// since we know the robot's wheel is 0.2 in radius therefore the circumference of the wheel
// is 1.256 which is one revolution in meters or 540 pulses. since we know the maximum speed is 0.5 m/s
// therefor the we can divide 0.5 / by the circumference to see approx. how many revolutions it would do in a second
// which turns out to be 0.002 Hz (v/circumference)
