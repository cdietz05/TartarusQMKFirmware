/*
Copyright 2026 Chris Dietz
GPL-2.0-or-later
*/

#include "quantum.h"
#include "analog.h" 
#include "joystick.h"
#include "via.h"
#include "eeconfig.h"
#include <avr/eeprom.h>

#define id_custom_channel   0
#define id_custom_set_value 0x07  // VIA standard 'Set'
#define id_custom_get_value 0x08  // VIA standard 'Get'
#define id_custom_save      0x09  // VIA standard 'Save'
#define id_unhandled        0xFF

#define ID_DEADZONE_CONFIG 1
#define ID_WASD_TOGGLE     2
#define JOYSTICK_EEPROM_ADDR (void*)EECONFIG_USER_DATA

void user_joystick_config_set_value(uint8_t *data);
void user_joystick_config_get_value(uint8_t *data);
void user_joystick_config_save(void);

typedef struct
{
    uint8_t  magic;
    bool     wasd_mode;
    uint8_t deadzone;
} user_joystick_config_t;

user_joystick_config_t joystick_config;

// Define the Custom Matrix Array
matrix_row_t matrix[MATRIX_ROWS];
matrix_row_t raw_matrix[MATRIX_ROWS];

// Define Your Pin for keyboard, thumb button, and joystick press
// Keyboard Rows: B6, B2, B3, B1
pin_t row_pins[4] = { B6, B2, B3, B1 };
// Keyboard Cols: B5, B4, E6, D7, C6
pin_t col_pins[5] = { B5, B4, E6, D7, C6 };
// Thumb Buttons: F7, F6
pin_t thumb_pins[2] = { F7, F6 };

// Set delay to wait for full key changes
void matrix_io_delay(void) 
{
    _delay_us(30);
}

// Initialize keyboard matrix
void matrix_init(void) 
{
    // Initialize Row Pins (Outputs)
    for (int i = 0; i < 4; i++) 
    {
        setPinOutput(row_pins[i]);
        writePinHigh(row_pins[i]);
    }

    // Initialize Col Pins (Inputs)
    for (int i = 0; i < 5; i++) 
    {
        setPinInputHigh(col_pins[i]);
    }

    // Initialize Thumb Pins (Inputs)
    setPinInputHigh(thumb_pins[0]);
    setPinInputHigh(thumb_pins[1]);

    // Clear Matrix
    for (uint8_t i=0; i < MATRIX_ROWS; i++) 
    {
        matrix[i] = 0;
        raw_matrix[i] = 0;
    }

    eeprom_read_block(&joystick_config, JOYSTICK_EEPROM_ADDR, sizeof(user_joystick_config_t));

    if (joystick_config.magic != 0x42)
    {
        joystick_config.magic = 0x42;
        joystick_config.wasd_mode = 1;
        joystick_config.deadzone = 150;
        eeprom_update_block(&joystick_config, JOYSTICK_EEPROM_ADDR, sizeof(user_joystick_config_t));
    }

}

void update_thumb_stick(void) 
{
    int16_t x_raw = analogReadPin(F5);
    int16_t y_raw = analogReadPin(F4);
    int16_t center = 512;     

    // Clear matrix bits for digital WASD keys
    raw_matrix[3] &= ~(1UL << 8);
    raw_matrix[4] &= ~((1UL << 7) | (1UL << 8) | (1UL << 9));

    if (joystick_config.wasd_mode) 
    {
        // --- WASD MODE ---
        
        if (y_raw < (center - joystick_config.deadzone)) 
        { 
            raw_matrix[3] |= (1UL << 8); // UP
        } 
        if (y_raw > (center + joystick_config.deadzone)) 
        { 
            raw_matrix[4] |= (1UL << 8); // DOWN
        } 
        if (x_raw < (center - joystick_config.deadzone)) 
        { 
            raw_matrix[4] |= (1UL << 9); // LEFT
        } 
        if (x_raw > (center + joystick_config.deadzone)) 
        { 
            raw_matrix[4] |= (1UL << 7); // RIGHT
        } 

        // Set joystick axes to center
        joystick_set_axis(0, 0);
        joystick_set_axis(1, 0);
    } 
    else 
    {
        // --- ANALOG MODE ---

        // this will set the joystic output to xbox scale
        // if using Hall Effect stick set to 3 or 3.5
        // if using Analog stick set to 4
        int speed_scale = 3;

        int16_t x_val = (center - x_raw) / speed_scale;
        int16_t y_val = (y_raw - center) / speed_scale;

        // Clamp sticks to prevent snapping back
        if (x_val > 127) 
        {   
            x_val = 127;
        }
        if (x_val < -127) 
        {
            x_val = -127;
        }
        if (y_val > 127) 
        {
            y_val = 127;
        }
        if (y_val < -127) 
        {
            y_val = -127;
        }

        joystick_set_axis(0, (int8_t)x_val);
        joystick_set_axis(1, (int8_t)y_val);
    }
}

// 3. The Scanner Function
uint8_t matrix_scan(void) 
{
    bool changed = false;

    // Call update_thumb_stick to output thumbstick data
    update_thumb_stick();
   
    for (int i = 0; i < 4; i++) 
    {
        writePinLow(row_pins[i]);
        matrix_io_delay();

        matrix_row_t current_row_data = 0;
        for (int j = 0; j < 5; j++) 
        {
            if (!readPin(col_pins[j])) 
            { 
                current_row_data |= (1 << j);
            }
        }
        
        // Preserve joystick up to write later when in WASD mode cus key goes brrrrrrrrr
        if (i == 3 && joystick_config.wasd_mode)
        {
            current_row_data |= (raw_matrix[3] & (1UL << 8));
        }

        // Unselect Row
        writePinHigh(row_pins[i]);
        matrix_io_delay();

        // Update Row
        if (raw_matrix[i] != current_row_data)
        {
            raw_matrix[i] = current_row_data;
            changed = true;
        }
    }

    // Read Thumb 1
    if (!readPin(thumb_pins[0])) 
    {
        raw_matrix[3] |= (1 << 5); 
    } 
    else 
    {
        raw_matrix[3] &= ~(1 << 5);
    }

    // Read Thumb 2
    if (!readPin(thumb_pins[1])) 
    {
        raw_matrix[4] |= (1 << 5);
    } else 
    {
        raw_matrix[4] &= ~(1 << 5);
    }

    // Check for matrix changes and do final sync
    for (int i = 0; i < MATRIX_ROWS; i++) 
    {
        if (matrix[i] != raw_matrix[i]) 
        {
            matrix[i] = raw_matrix[i];
            changed = true;
        }
    }    
    
    return changed;
}

// Required Helper Function
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

// Required Helper Function
void matrix_print(void) {}

#ifdef VIA_ENABLE
void via_custom_value_command_kb(uint8_t *data, uint8_t length) 
{
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel)
    {
        switch (*command_id)
        {
            case id_custom_set_value:
            {
                user_joystick_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                user_joystick_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                user_joystick_config_save();
                break;
            }
        }

        return;
    }

    *command_id = id_unhandled;
}
#endif

void user_joystick_config_set_value(uint8_t *data)
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id)
    {
        case ID_WASD_TOGGLE:
        {
            joystick_config.wasd_mode = *value_data;
            break;
        }
        case ID_DEADZONE_CONFIG:
        {
            joystick_config.deadzone = *value_data;
            break;
        }
    }
}

void user_joystick_config_get_value(uint8_t *data)
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id)
    {
        case ID_WASD_TOGGLE:
        {
            *value_data = joystick_config.wasd_mode;
            break;
        }
        case ID_DEADZONE_CONFIG:
        {
            *value_data = joystick_config.deadzone;
            break;
        }
    }
}

void user_joystick_config_save(void)
{
    eeprom_update_block(&joystick_config, JOYSTICK_EEPROM_ADDR, sizeof(user_joystick_config_t));
}