# ZodiarkPi/QMK I2C Keyboard Sound
Add Sound To Your ZodiarkPi Keyboard Using [SparkFun Qwiic Buzzer BOB-24474](https://www.sparkfun.com/sparkfun-qwiic-buzzer.html)

### Sound Demo
https://github.com/user-attachments/assets/96be4976-08ce-485e-ae0a-f66f3da4de4b

### Prerequisites
***Note*** Can not use a dual axis encoder with this setup, since it uses the extra I2C pins

### Wiring
Wire SparkFun Qwiic Buzzer As follows:
![ZodiarkPiQwiicBuzzer1](https://github.com/user-attachments/assets/e8fe0486-fe48-446f-a433-ebbc0ed86099)

Prepare To Hide The Buzzer:
![ZodiarkPiQwiicBuzzer2](https://github.com/user-attachments/assets/f68df095-2718-4d6e-a544-9b7926785d68)

Hidden Buzzer:
![ZodiarkPiQwiicBuzzer3](https://github.com/user-attachments/assets/a4206b62-00a4-41c0-b92e-fb1d38929b1d)

### QMK Code
1. copy github ```sound``` directory to ```qmk_firmware/keyboards/aleblazer/zodiarkpi/```

2. edit ```qmk_firmware/keyboards/aleblazer/zodiarkpi/config.h```      //add or uncomment the below lines to set RP2040 I2C pins
```#define I2C_DRIVER I2CD0```                                 
```#define I2C1_SCL_PIN GP17```                                        //Pin 22  MUST USE I2C1 HERE EVEN WHEN REALLY USING I2C0
```#define I2C1_SDA_PIN GP16```                                        //Pin 21  MUST USE I2C1 HERE EVEN WHEN REALLY USING I2C0

3. edit qmk_firmware/keyboards/aleblazer/zodiarkpi/halconf.h     //add or uncomment the below line to enable I2C in HAL
```#define HAL_USE_I2C TRUE```

4. edit qmk_firmware/keyboards/aleblazer/zodiarkpi/mcuconf.h     //add or uncomment the below lines to use IC20 
```#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE

#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 FALSE
```

5. edit qmk_firmware/keyboards/aleblazer/zodiarkpi/rules.mk      //add or uncomment the below line to enable the I2C driver
```I2C_DRIVER_REQUIRED = yes```

6. edit qmk_firmware/keyboards/aleblazer/zodiarkpi/zodiarkpi.c   //add the below lines to the top of the file
```#include "sound/qwiic_buzzer.c"```                            

7. edit qmk_firmware/keyboards/aleblazer/zodiarkpi/zodiarkpi.c   //add the below lines to ```void keyboard_post_init_kb(void)``` function
 ```i2c_init();                                                  //initialize the I2C bus
    if (I2C_qwiic_buzzer_connected()) {
      uprintf("I2C qwick buzzer found at address 0x%02X\n", I2C_ADDR);
    }
```

8. edit qmk_firmware/keyboards/aleblazer/zodiarkpi/keymaps/default/keymap.c //add the below line to the top of the file
```#include "../../sound/qwiic_buzzer.h"```

9. edit qmk_firmware/keyboards/aleblazer/zodiarkpi/keymaps/default/keymap.c //play a sound every time a key is pressed
```bool process_record_user(uint16_t keycode, keyrecord_t *record) {  
sound_effect_2(VOLUME_MAX)
}
``` 
