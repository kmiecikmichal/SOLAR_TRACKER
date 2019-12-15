# SOLAR_TRACKER

### Project description

The main goal of the project is to build a solar tracker with two operating modes:

- The first mode uses four photoresistors, which in special directional tubes measure the intensity of light at selected points. A miniature photovoltaic cell mounted on two servos rotates depending on the location of the photoresistor showing the strongest light intensity (use on cloudy days).
- The second mode uses the accelerometer built into KL05. We will use the algorithm indicating current predicted position of the sun followed by our tracker (use on sunny days).

### Problem analysis

The accelerometer checks the current position of the KL05 board attached to the movable stand with mini photovoltaic panel allowing it to be positioned in an optimal position in relation to the position of the sun. Data from the accelerometer will be sent using the I2C bus. Servomechanisms setting the stand in the right position will be controlled by PWM. The distribution of several photoresistors will allow for directional measurement of light intensity in order to determine its strongest source

### Implementation plan

The components we use are FRDM-KL05 evaluation board equipped with accelerometer, mini photovoltaic cell, two servos and four photoresistors.

![DL Schemat blokowy](https://user-images.githubusercontent.com/48928449/70871392-276df480-1f9f-11ea-8708-1818eb22f4f7.jpg)
