# StringArtWeaver
This project is complemetary to [Algorithmic String Art]() where the machine instruction from the latter is used as input for physically weaving threads on predefined canvas.
## Setup
The system consist of electronic and physical setup. The user is expected to loop thread on the desired edge. The stepper motor will rotate 
the canvas to the desired nail/node based on the machine instruction.

### Physical setup 
Video of a working [example](https://www.youtube.com/watch?v=2l4N4f_ActE) for reference
- A canvas with nails on the edge
- Stepper motor attached to the center of canvas
- Thread source
- Needle 

### Electronic setup
- [Teensy LC](https://www.pjrc.com/teensy/teensyLC.html)
- [Stepper Motor](https://www.pololu.com/product/1208)
- [Stepper Motor Driver](https://www.pololu.com/product/1182)
- Power supply
- 100 microF capacitor
- Wires

## Installation Guide
1. [Install Arduino ](https://www.arduino.cc/en/main/software) *Note*: Windows App version doesn't work!
2. [Install Teensyduino](https://www.pjrc.com/teensy/td_download.html)
3. Flash the code as normal ".ino" file
4. Make sure the circuit is built as shown 
   - ![](https://github.com/Chitiiran/StringArtWeaver/blob/master/Electronics/WeaverCircuitDiagram.png)
5. Insert the thread into the eye of the needle.
6. The code will notify you where is the starting node. Tie the thread to that nail/node. Make sure the needle is between the
nail/node and thread source. 
7. Press 'n' and enter in Arduino command line (ctrl-shift-m) and the stepper will rotate the canvas to bring the next 
nail/node to the needle location. Press 'p' to go back to previous nail/node.
8. When the sequence is exhausted you will be notified.

## Notes
- The circuit diagram uses Teensy 3.1 instead of Teensy LC. The only difference is when you hookup the electronics
MS3 pin is attached to pin 15 of LC. For more information check the pin assignments in the ".ino" file.
- I used a pen that is fixed onto the setup to indicate the needle location. Since I move around, I labelled the nails 
on the canvas and looped the desired nail/node as displayed in Arduino command line. 

## Observations and Future work
The thread is currently looped around the nail manually using a a threaded needle. The next iteration shall have automated looping. However, 
several key observation for upgrade are
- When the thread is stuck the canvas rotates imprecisely. 
- Having a foldable needle would allow the needle to fold in the direction of canvas spin which allows the thread to 
extend freely.
- A mechanism that brings the folded needle to initial position after the canvas spin is necessary to loop onto the right nail.
- The loop mechanism have to loop start looping from top/bottom and end at top/bottom. Which means there are 4 desired state depending on the case.

## Author

* **Chitiiran** - *Initial work* - [Chitiiran](https://github.com/Chitiiran)

## Acknowledgments

* Inspiration [Instagram post](https://www.instagram.com/p/B2CY3ymgPPP/?utm_source=ig_web_copy_link)
* [Petros Vrellis](https://www.saatchiart.com/vrellis)

  
