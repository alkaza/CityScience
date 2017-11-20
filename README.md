## Wiring Raspberry Pi 3 Model B V1.2

### DC Motor Driver L296N
```
Raspberry Pi 3 - DC Motor Driver

Physical Pin12 - EnA (BCM Pin18, WiringPi Pin1, PWM0)
Physical Pin13 - In1 (BCM Pin27, WiringPi Pin2)
Physical Pin15 - In2 (BCM Pin22, WiringPi Pin3)

Physical Pin33 - EnB (BCM Pin13, WiringPi Pin23, PWM1)
Physical Pin21 - In3 (BCM Pin6,  WiringPi Pin22)
Physical Pin29 - In4 (BCM Pin5,  WiringPi Pin21)

Physical Pin39 - Gnd (Ground)
```

### Ultrasonic Sensor HC-SR04
```
Raspberry Pi 3 - Ultrasonic Sensor

Physical Pin2  - Vcc  (3v3 Power)
Physical Pin16 - Trig (BCM Pin23, WiringPi Pin4)
Physical Pin18 - Echo (BCM Pin24, WiringPi Pin5)
Physical Pin20 - Gnd  (Ground)
```

#### Note
- Physical - Number corresponding to the pin's physical location on the header
- WiringPi - Wiring Pi pin number (shown as a tooltip), for Gordon Henderson's Wiring Pi library
- BCM - Broadcom pin number, commonly called "GPIO", these are the ones you probably want to use with RPi.GPIO and GPIO Zero

#### Raspberry Pi Pinout
https://pinout.xyz/
