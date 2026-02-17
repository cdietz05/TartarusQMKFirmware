# Tartarus Mod
A handwired custom keyboard mod using Dwarfkingkili Mod Kit

To compile code 
1. Download Zip file of code
2. Download QMK Firmware from https://qmk.fm
3. Unzip files and past tartarus_mod folder into qmk_firmware handwired folder (C:\Users\<your user>\qmk_firmware\keyboards\handwired)
4. Launch QMK MSYS and run the following command: qmk compile -kb handwired/tartarus_mod -km via

To flash to ProMicro
1. Download QMK Toolbox from https://qmk.fm/toolbox
2. Launch QMK Toolbox
3. Select ATmega32U4 MCU
4. Select Open and select your compiled code (C:\Users\<your user>\qmk_firmware\handwired_tartarus_mod_via.hex)
5. Select Auto-Flash and jump reset and ground on your ProMicro to auto flash the firmware
6. Note: after the initial flash you will no longer need to jump GND and RST to load the firmware as that will be bound to a key. (Press and hold Encoder Wheel Down and press Top Left Key to enter bootloader mode)

To Remap in Via
1. Go to usevia.app
2. Go to Settings and Enable Show Design tab
3. Go to Design tab and load the tartarus_mod_via.json
4. If it doesn't ask you to pair your keyboard already, go to the Configure tab and Authorize your device (Tartarus Mod)
5. Remap keys as you like, there are 4 total layers to remap if needed.
6. Note: WASD mode is enabled by default and you can switch it off in via but Joystick mode requires a virtual controller to be mapped like XOutput (https://github.com/csutorasa/XOutput)