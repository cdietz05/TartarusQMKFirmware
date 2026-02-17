MCU = atmega32u4
BOOTLOADER = caterina
ARCH = AVR

# --- JOYSTICK ---
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog

# --- FEATURES ---
ENCODER_ENABLE = yes
MOUSEKEY_ENABLE = no

# --- CUSTOM MATRIX ---
CUSTOM_MATRIX = yes
SRC += tartarus_mod_custom_matrix.c

# --- DISABLE EXTRAS ---
CONSOLE_ENABLE = no
NKRO_ENABLE = no