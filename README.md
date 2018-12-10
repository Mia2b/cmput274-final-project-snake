# Snake
## Fall 2018 Cmput 274 Final Project
##### Amir Hansen id: 1523209 
##### Ralph Milford id: 1534131

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

* Collect apples to increase your score, length, and movement speed. Having your snake colour more closly match the apple colour will give you more points. 
   - Points is calulated by `snakeLength*(rgbMax-rgbDelta)`
* You may only turn 90 degree from your current direction
* The game will end if you collide with yourself or with the game board boundarys
* Only the top 10 high scores will be displayed on the start menue scores chart
   - Only the highest score will be displayed in the top right of the screen
   - The top left score is your current score

 
## Notes

In order for the game to be played the joystick accessory for the Arduino is required.  The joystick is divided into four directions, with the seperation being at 45 degrees angles.  The controls also will not allow the player to flip 180 degrees, instead limiting the directions to either a left or a right.  The game will end under two conditions.  If the snake collides with border of the playable screen or if the snake collides with a part of itself.  The position of these marked positions are created using the class `Map` found in `Map.h`.  The score and length of the snake increase by the snake landing on spaces that contain apples.  It checks to see if the snake has landed on a marked space in the `Map` created for the apples.  If the snake has, then the variable `score` will increase depending on `snakeLength*(rgbMax-rgbDelat)`.  It also increases the snakes length by using `snek.grow(3)`.  The top ten scores reached will be saved and display whenever the game starts.  It does this by saving that list to the Arduino itself and creates an integrity check to ensure it obtains the correct list.  If the integrity check fails a generic list of highscores is then created and writen onto the eeprom memory along with a check code.  Several variables in this game can be manual set in the `game_config.h` file.  This includes variables such as the size of the screen that the games is played in as well as the amount of apples that will be on the screen at any given time. Game controlles are set within the snake class for movement.
 
## Acknowledgments

The [Arduino](www.arduino.cc) documentation was used extensivly in making this project.  Primarily to use functions found the the arduino library.  We also used [EEPROM Write Anything](https://playground.arduino.cc/Code/EEPROMWriteAnything) as a reference point on how to use the AVR eeprom memory.