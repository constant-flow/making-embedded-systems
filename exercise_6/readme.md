# Project Report - Audio Locator (Draft)

![[Maybe the picture from here](https://github.com/constant-flow/making-embedded-systems/raw/main/exercise_1/explanation.svg)](https://github.com/constant-flow/making-embedded-systems/raw/main/exercise_1/explanation.svg)
`TODO add nice image explaining the concept`

## Application description
The Audio-Locator can calculate a 3 dimensional direction towards an audio signal (voice, clap, beep). The device will point with a displayed graphic (2D-mode: compass needle, 3D-Mode: 2D bubble) on an LCD towards the origin of the most recent loud sound.

## Hardware description
The device uses up to three MEMS microphones to locate the loudest sound in hearable proximity

- Fast Processor (STM32F469)
- 3 MEMS Microphones
- Display
- Buttons for mode switching (Hemisphere selection, 2D/3D mode)
- USB port to power

## Software description
With DSP-functions (correlation) the recoded audio signals are compared with each other. A distinct sound, e.g. a clap, should create a similar signal for each microphone, with a slight time delay. Based on these time delays the direction can be calculated via trilateration. 
The threshold for a sound to be detected can be set via commandline interface

### Limitations
The system is based on up to 3 microphones, it can calculate the position of the audio source in 3D space, though it can't differenciate between directions above and below the microphone-plane, this would require a fourth microphone which is placed above or below this plane. As the microphones are highly directional, this project will focus on the frontal hemisphere.

## Architecture
`TODO Add graphs from here` [Link](https://github.com/constant-flow/making-embedded-systems/tree/main/exercise_1)

![https://github.com/constant-flow/making-embedded-systems/raw/main/exercise_1/diag-block.svg](https://github.com/constant-flow/making-embedded-systems/raw/main/exercise_1/diag-block.svg)

![https://github.com/constant-flow/making-embedded-systems/raw/main/exercise_1/diag-hoc.svg](https://github.com/constant-flow/making-embedded-systems/raw/main/exercise_1/diag-hoc.svg)

![https://github.com/constant-flow/making-embedded-systems/raw/main/exercise_1/diag-layered.svg](https://github.com/constant-flow/making-embedded-systems/raw/main/exercise_1/diag-layered.svg)
## Build instructions
### How to build
#### Hardware
The required hardware is already available on the [STM32F469I-Discovery Board](https://www.st.com/en/evaluation-tools/32f469idiscovery.html) to enable all 3 microphones at the same time it requires an addional wire soldered from `TODO ` to pin `TODO` as seen in this picture.

```
TODO picture of hacked board with additional wire
```

The board can be connected via Mini-USB (ST-LINK port) to the programming computer.

#### Software
The project is created with the stmCubeMX-IDE as a Makefile project and can be edited with any code editor and compiled with `make` from terminal.

Suggested IDE is **Visual Studio Code** IDE has a has useful extentions that help to build and debug the project
- `stm32-for-vscode` `TODO check name add link`
- `platformio`

After installation of these building and flashing can be triggered via `CMD+SHIFT+B`

**Mark portions of code i did**

### How to power and debug
- The discovery board comes with a ST-LINK coprocessor (Mini-USB) when connected to host computer, the USB provides power and a link to debug.

VSCodes provides debugging break points (click next to linenumber) and a handy interface to step through the code.

## Future
### Get ready for production
This functionality is planned to be packed into a small library so either a small Cortex-M coprocessor can output directional data via I2C / UART or used alongside on the main processor.
A small dev-kit with such a coprocessor and external microphones will be developed so developers can easily test this system

This library needs to be encapsulated and documented, so it is easy for other developers to get directional tracking into their project.

The minimal requirements for such a coprocessor need to be calculated and varyfied.

### Applications and features
This software and hardware solution (dev-kit) has a lot of potential for human-computer interactions
- Device awareness and feedback (similar Amazon Echo)
- Robot interaction, e.g. home assistent robots locating and differentiating users, learning locations

But also locating and tracking of objects and animals is a potential field of application
- bird locator
- gas leak finder

Possible future features:
- Background noise removal in audio calls with moving participants
- 3D-USB microphone with streaming of tracked sound locations
- Multi object location tracking

### Licenses
[TODO add all used tools/libs licenses]

---

<!-- # Troubles
## Tasks to complete
## Blocking items -->
