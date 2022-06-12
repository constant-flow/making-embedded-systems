# Project Report - Audio Locator (Draft)

![[](doc_assets/Audio-locator-title.svg](doc_assets/Audio-locator-title.svg)

## Application description
The Audio-Locator can calculate a dimensional direction towards an audio signal (voice, clap, beep). The device will point with a displayed graphic (In-PCB-plane-mode: compass needle, In-Front-of-screen-mode: Line indicating direction out of the screen) on an LCD towards the origin of the most recent loud sound.

`TODO: ADD video`

## Hardware description
The device uses up to two MEMS microphones to locate the loudest sound in hearable proximity

- Fast Processor (STM32F469)
- 2 MEMS Microphones
- Display
- Buttons for mode switching
- USB port to power
- Audio Codec (cs43l22) + Headphone out

## Software description
With DSP-functions (correlation) the recorded audio signals (Mic 1 vs Mic 2) are compared with each other. A distinct sound, e.g. a clap, should create a similar signal for each microphone, with a slight time delay. Based on these time delays the direction can be calculated via trigonometric functions. 
The threshold for a sound to be detected can be set via commandline interface (`threshold 0-255`, smaller value = more detections). With a sampling rate of `16000 Hz` and a speed of sound of `343 m/s` having a phase delay of one sample means `2.14 cm` appart. With a microphone distance of `11.8 cm` means the soundwave arrives 5 samples later, if the sound came from the side of both microphones (β=180° or β=0°β).

- The `In-PCB-plane-mode` calculates direction of the sound within the plane that the PCB surface is in. The sound is expected below the display (towards headphone jack)
- The `In-Front-of-screen-Mode` calculates direction of the sound within the plane orthogonal to the screen which goes through both microphones. The sound is expected in front of the screen.

### Limitations
The system is based on 2 microphones, it can calculate the position of the audio source in 2D space, thus it can't differentiate if the sound came from one side or the other. To compansate for that the tracking mode defines the direction the sound is expected from and also the plane in were the sound must be create on.

## Architecture
![](doc_assets/diag-block.drawio.svg)

`TODO Update graph` ![https://github.com/constant-flow/making-embedded-systems/raw/main/exercise_1/diag-hoc.svg](https://github.com/constant-flow/making-embedded-systems/raw/main/exercise_1/diag-hoc.svg)

`TODO Update graph` ![https://github.com/constant-flow/making-embedded-systems/raw/main/exercise_1/diag-layered.svg](https://github.com/constant-flow/making-embedded-systems/raw/main/exercise_1/diag-layered.svg)
## Build instructions
### How to build
#### Hardware
The required hardware is already available on the [STM32F469I-Discovery Board](https://www.st.com/en/evaluation-tools/32f469idiscovery.html).

**IMPORTANT**
> To capture the correct microphone setup it is required to close the solder jumper `SB17` and to open solder jumper `SB18`. This enables capturing microphone `U1` and `U2`. ⚠️ If this is not performed two microphones (`U6` and `U2`) are used which are too close and not calibrated for the processing of the software.
> ![](doc_assets/hw_mods.jpg)

The board can be connected via Mini-USB (ST-LINK port) to the programming computer.

#### Software

TODO: describe code modules quickly

The project is created with the stmCubeMX-IDE as a Makefile project and can be edited with any code editor and compiled with `make` from terminal.

Suggested IDE is **Visual Studio Code** IDE has a has useful extentions that help to build and debug the project
- [`stm32-for-vscode` - build/debug ](https://marketplace.visualstudio.com/items?itemName=bmd.stm32-for-vscode)
- `picocom` – serial communication (install via homebrew, apt)

After installation of these building and flashing can be triggered via `CMD+SHIFT+B`

**IMPORTANT:**
> The board I used was a Rev-B board, this is setup in the `Makefile` via the `-DUSE_STM32469I_DISCO_REVB` flag make sure to match that flag to your board revision.

**Mark portions of code i did**

### How to power and debug
- The discovery board comes with a ST-LINK coprocessor (Mini-USB) when connected to host computer, the USB provides power and a link to debug.

- VSCodes provides debugging break points (click next to linenumber) and a handy interface to step through the code.

## Future
### Get ready for production
Adding more microphones reduces the need for setting a tracking mode, a 3rd microphone can track sounds in one 3D-hemisphere, by adding a 4th microphone (which is not in the same plane as the 3 other microphones) a full 3D sound direction can be calculated without specifing a tracking mode. Having further microphones with more distance could even calculate/estimate the position of a sound source (if reflections are low).

This functionality can bepacked into a small library so either a small Cortex-M coprocessor can output directional data via I2C / UART or used alongside on the main processor.
A small dev-kit with such a coprocessor and external microphones will be developed so developers can easily test this system.

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
This project is based on existing code libraries, when using this project please check and comply to the listed licenses.

- [BSP – BSD-3-Clause](Drivers/BSP/STM32469I-Discovery/LICENSE.txt)
- [CMSIS – Apache](Drivers/CMSIS/LICENSE.txt)
- [HAL – BSD-3-Clause](Drivers/STM32F4xx_HAL_Driver/LICENSE.txt)
- [Middleware – BSD-3-Clause & ST-SLA0044](https://www.st.com/content/ccc/resource/legal/legal_agreement/license_agreement/group0/59/57/63/12/cf/a6/47/65/SLA0044/files/SLA0044.txt/jcr:content/translations/en.SLA0044.txt)
- [PDM2PCM - ST-SLA0047](https://www.st.com/content/ccc/resource/legal/legal_agreement/license_agreement/group0/73/b4/79/b9/5a/e6/4a/9e/SLA0047/files/SLA0047.txt/jcr:content/translations/en.SLA0047.txt)

---

<!-- # Troubles
## Tasks to complete
## Blocking items -->
