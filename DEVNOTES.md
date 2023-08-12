Custom board has been added to the local project files in boards and variants with the respective build flags added to the platformio.ini file, roughly following https://calinradoni.github.io/pages/210403-platformio-customstm32board.html
ToDo: 
1. Add specific instructions for doing this process since it's not well documented
2. Modify PeripheralPins.c and variant_ROCATV1.cpp and other files to reflect the pinout of the board irl

FreeRTOS is included as a local library since there is some weird linking stuff going on with the library meaning that it ignores a custom config file, recommend changing the default config in the STM32duino FreeRTOS for now. According to some GitHub issues its due to platformIO, and the Arduino IDE (which the library was made for) works fine, might be nice to modify it to work with platformIO and publish it.

Currently using HSI clock and not the external one, seems to be some weird timing issues with it when using STM32CubeIDE's automatic config, not sure if its because of software or PCB design or something else, SystemClock_Config initializes the clock, right now its using the default F767ZI code. Going to continue using the HSI instead just to get through the work