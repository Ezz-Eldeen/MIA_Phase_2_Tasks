Q: If the Sensor is surrounded by a noisy environment, what type of
filter could used and what is the recommended cutoff frequency
depending on the sensor datasheet?

###Answer:
> We can use a Low Pass Filter (LPF) to only allow low frequencies while blocking higher frequencies that may be caused by external noise


# MPU6050 Yaw Angle Measurement

This Arduino sketch demonstrates how to measure the yaw angle using the MPU6050 gyroscope sensor.


1- This checks to see if the 2byte data from the sensor was send and it receives it to then proceed to process the data in the following lines.
```c
Wire.requestFrom(MPU6050Address, 2);  // Takes 2 byte data from the sensor
  if (Wire.available() >= 2)
```


2- This shift the high bits eight spaces to the left and then fits the 8 low bits beside them to get the final 
16 bit reading.
```c
    yawAngle = (highByte << 8) | lowByte;
```

3- converts the reading from the gyroscope to degrees per second, the number 131 was chosen according to matching the datasheet with the used sensor
 
```c
float angularVelocity = yawAngle /131;
```


4- this adds the angle calculated from the integration to the previous angle since the angle is constantly changing we keep adding the change happening
```c
  totalAngle += IntegrationDtheta;
```

