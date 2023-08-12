Custom board has been added to the local project files in boards and variants with the respective build flags added to the platformio.ini file, roughly following https://calinradoni.github.io/pages/210403-platformio-customstm32board.html
ToDo: 
1. Add specific instructions for doing this process since it's not well documented
2. Modify PeripheralPins.c and variant_ROCATV1.cpp and other files to reflect the pinout of the board irl

FreeRTOS is included as a local library since there is some weird linking stuff going on with the library meaning that it ignores a custom config file, recommend changing the default config in the STM32duino FreeRTOS for now. According to some GitHub issues its due to platformIO, and the Arduino IDE (which the library was made for) works fine, might be nice to modify it to work with platformIO and publish it.