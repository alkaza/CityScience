## Program Discription
### Geting Started
#### Get Source Code
```
git clone https://github.com/alkaza/CityScience.git
```
#### Enter Source Directory
```
cd CityScience/src
```
#### Compile
```
make all
```
#### Run
```
sudo ./control
```
#### Terminate
```
Ctrl-C
```

### Working Principles
#### DC Motor Driver
| State |  EnA  |  In1  |  In2  |  In3  |  In4  |  EnB  |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| Front |   1   |   1   |   0   |   1   |   0   |   1   |
| Back  |   1   |   0   |   1   |   0   |   1   |   1   |
| Right |   1   |   1   |   0   |   1   |   0   |   1   |
| Left  |   1   |   1   |   0   |   0   |   1   |   1   |
| Brake |   1   |   0   |   1   |   1   |   0   |   1   |
| Brake |   1   |   1   |   1   |   1   |   1   |   1   |
| Stop  |   0   |   X   |   X   |   X   |   X   |   0   |
#### Ultrasonic Sensor

## Wiring Raspberry Pi 3 Model B V1.2
### DC Motor Driver L296N
|DC Motor Driver | Raspberry Pi 3 | WiringPi | Remark |
| :------------: | :------------: | :------: | :----: |
| EnA            | Physical Pin12 | Pin1     | PWM0   |
| In1            | Physical Pin13 | Pin2     |        |
| In2            | Physical Pin15 | Pin3     |        |
| EnB            | Physical Pin33 | Pin23    | PWM1   |
| In3            | Physical Pin21 | Pin22    |        |
| In4            | Physical Pin29 | Pin21    |        |
| Gnd            | Physical Pin39 |          | Ground |

#### Important
|DC Motor Driver | Connection            ||
| :------------: | :---: | :------------: |
| Vcc            | Vcc   | Battery Holder |
| Gnd            | Gnd   | Battery Holder |
| Gnd            | Gnd   | Raspberry Pi 3 |


### Ultrasonic Sensor HC-SR04
| Ultrasonic Sensor | Raspberry Pi 3 | WiringPi | Remark    |
| :---------------: | :------------: | :------: | :-------: |
| Vcc               | Physical Pin2  |          | 3v3 Power |
| Trig              | Physical Pin16 | Pin4     |           |
| Echo              | Physical Pin18 | Pin5     |           |
| Gnd               | Physical Pin20 |          | Ground    |


## Power Supplies
### Raspberry Pi 3
#### Power Bank
- Capacity : 5200mAh 
- Output : 5V 2A

### DC Motor Driver
#### AAx6 Battery Holder
- Capacity : 1.5V x 6 = 9V
