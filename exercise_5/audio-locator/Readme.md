# Audio Locator

## Commandline options
- `threshold [0-255]` to set detector value
- `mode [2-3]` to set to detect in 2D or 3D

## Toolchain
- generated a project with CubeMX-IDE
- includes all required files (thus huge)
- builds via `make` or better via VSCode `stm32-for-vscode`
- VSCode as IDE
- CMD+Shift+B to build in VSCode

### How to replicate for new project
- create a project via MX IDE, setup for makefile toolchain, tick box to copy *.c and *.h files into directory (code generator)
- in vscode install `stm32-for-vscode` extension
- open `stm32-for-vscode` panel hit **build**
- see it failing failing with `undefined reference to '__errno'`
- open generated file `STM32-for-VSCode.config.yaml` go to `linkerFlags:` and add line with `- -specs=rdimon.specs`
- hit **build** again and it should compile
- hit **Flash STM** and it should flash your connected device
