# Tartarus Mod
A handwired custom keyboard mod using Dwarfkingkili Mod Kit

To flash to ProMicro with pre compiled code
1. Download .hex file from pre_compiled_hex folder
2. Download QMK Toolbox from https://qmk.fm/toolbox
3. Launch QMK Toolbox
4. Select ATmega32U4 in the MCU drop down
5. Press Open and locate the .hex file you downloaded and select it
6. Select Auto-Flash and jump RST and GND pins on your ProMicro to enter bootloader mode and auto flash the firmware
7. Note: after the initial flash you will no longer need to jump GND and RST to load the firmware as that will be bound to a key. (Press and hold Encoder Wheel Down and press Top Left Key to enter bootloader mode)

To Remap in Via
1. Go to usevia.app
2. Go to Settings and Enable Show Design tab
3. Go to Design tab and load the tartarus_mod_via.json that you can download from the via_json folder
4. If it doesn't ask you to pair your keyboard already, go to the Configure tab and Authorize your device (Tartarus Mod)
5. Remap keys as you like, there are 4 total layers to remap if needed.
6. Note: WASD mode is enabled by default and you can switch it off in via but Joystick mode requires a virtual controller to be mapped like XOutput (https://github.com/csutorasa/XOutput)

Here is the key layout:

<img width="586" height="325" alt="via_keymap_desc" src="https://github.com/user-attachments/assets/2df94dbd-6a05-4116-8ea4-827e82cde72b" />

This is what the remapping screen will look like in VIA:
<img width="2552" height="1392" alt="via_keymap" src="https://github.com/user-attachments/assets/53b0245e-a2bf-4475-bccf-b50bc996f287" />

Here is the WASD mode toggle and sensitivity slider menu:
<img width="2553" height="1381" alt="via_wasd_toggle" src="https://github.com/user-attachments/assets/5addbefd-2843-47b2-bf99-3d9d56615d51" />

If you want to make changes to the code and compile yourself here are the steps

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
