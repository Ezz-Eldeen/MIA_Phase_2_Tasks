# Getting the cutoff frequency for the low pass filter:

 since we know the robot's wheel is 0.2 in radius therefore the circumference of the wheel  

 
 is 1.256 which is one revolution in meters or 540 pulses. since we know the maximum speed is 0.5 m/s  

 
therefore can divide 0.5 / by the circumference to see approx. how many revolutions it would do in a second  


 which turns out to be:
 >0.002 Hz (v/circumference)

--------------
# Code documentation
1- listening for a change in pin A or pin B and invoking an interrupt service routine that is defined later
```c
  attachInterrupt(digitalPinToInterrupt(rotaryPinA), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rotaryPinB), encoderISR, CHANGE);
```

2- This is the interrupt service routine which is invoked once a pin is changed which then checks whether it is rotating clockwise or anticlockwise
and then increases the counter if it is CW
```c
void encoderISR()
```

3- resets encoder count at 540 and increments the rotation variable to keep count of the numnber of full revolutions
```c
if (encoderCount >= 540)
```
