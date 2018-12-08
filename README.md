# cmput 274 final project

The cmput 274 final project by Amir Hansen and Ralph Milford.

## Defualt Wiring Guide
| __Arduino Mega__ | __Lcd dispaly__ |
| :--------------- | :-------------- |
| GND              | GND             |
| 5V               | Vin             |
| Digital 52       | CLK             |
| Digital 50       | MISO            |
| Digital 51       | MOSI            |
| Digital 48       | CS              |
| Digital 49       | D/C             |
| Digital 53       | RST             |
| __Arduino Mega__ | __Joystick__    |
| GND              | GND             |
| 5V               | +5V             |
| Analog 1         | VRx             |
| Analog 0         | VRy             |
| Analog 2         | SW              |

## Installation instructions

To install using the provided make file, the UofA cmput274 virtual machine would be required as it has all dependicies installed.

## Running instruction

When the arduino is powered on a start screen should appear, if so then you have correctly wired and uploaded and simply click in the Analog stick to start playing.

## Game Rules

Collect apples to increase your score, length, and movement speed. Having your snake colour more closly match the apple colour will give you more points. 
* Points is calulated by `snakeLength*(rgbMax-rgbDelta)`


 
