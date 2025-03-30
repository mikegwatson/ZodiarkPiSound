# ZodiarkPi/QMK I<sup>2</sup>C Keyboard Sound
Add Sound To Your ZodiarkPi Keyboard Using [SparkFun Qwiic Buzzer BOB-24474](https://www.sparkfun.com/sparkfun-qwiic-buzzer.html)

&nbsp;

### Sound Demo
https://github.com/user-attachments/assets/96be4976-08ce-485e-ae0a-f66f3da4de4b

&nbsp;

### Prerequisites
***Note*** You can _not_ use a dual axis encoder with this setup, since it uses the extra I<sup>2</sup>C pins

&nbsp;

### Wiring
Wire SparkFun Qwiic Buzzer As Shown:<br>
<img src="https://github.com/user-attachments/assets/e8fe0486-fe48-446f-a433-ebbc0ed86099" alt="ZodiarkPiQwiicBuzzer1" width="378" height="504">

Prepare To Hide The Buzzer:<br>
<img src="https://github.com/user-attachments/assets/f68df095-2718-4d6e-a544-9b7926785d68" alt="ZodiarkPiQwiicBuzzer2" width="378" height="504">

Hidden Buzzer:<br>
<img src="https://github.com/user-attachments/assets/a4206b62-00a4-41c0-b92e-fb1d38929b1d" alt="ZodiarkPiQwiicBuzzer3" width="378" height="504">

&nbsp;

### QMK Code
1. Copy github ```sound``` directory to ```qmk_firmware/keyboards/aleblazer/zodiarkpi/```

2. Edit ```qmk_firmware/keyboards/aleblazer/zodiarkpi/config.h```      (add or uncomment the below lines to set RP2040 I<sup>2</sup>C pins)
```
#define I2C_DRIVER I2CD0
#define I2C1_SCL_PIN GP17                                        //Pin 22 SET I2C1 HERE FOR I2C0
#define I2C1_SDA_PIN GP16                                        //Pin 21 SET I2C1 HERE FOR I2C0
```

3. Edit ```qmk_firmware/keyboards/aleblazer/zodiarkpi/halconf.h```     (add or uncomment the below line to enable I<sup>2</sup>C in HAL)
```
#define HAL_USE_I2C TRUE
```

4. Edit ```qmk_firmware/keyboards/aleblazer/zodiarkpi/mcuconf.h```     (add or uncomment the below lines to use IC20)
```
#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE

#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 FALSE
```

5. Edit ```qmk_firmware/keyboards/aleblazer/zodiarkpi/rules.mk```      (add or uncomment the below line to enable the I<sup>2</sup>C driver)
```
I2C_DRIVER_REQUIRED = yes
```

6. Edit ```qmk_firmware/keyboards/aleblazer/zodiarkpi/zodiarkpi.c```   (add the below lines to the top of the file)
```
#include "sound/qwiic_buzzer.c"
```

7. Edit ```qmk_firmware/keyboards/aleblazer/zodiarkpi/zodiarkpi.c```   (add below lines to ```void keyboard_post_init_kb(void)```)
```
i2c_init();                                                      //initialize the I2C bus
if (I2C_qwiic_buzzer_connected()) {
  uprintf("I2C qwiick buzzer found at: 0x%02X\n", I2C_ADDR);     //use 'qmk console' on PC to see if buzzer found
}
```

8. Edit ```qmk_firmware/keyboards/aleblazer/zodiarkpi/keymaps/default/keymap.c``` (add the below line to the top of the file)
```
#include "../../sound/qwiic_buzzer.h"
```

9. Edit ```qmk_firmware/keyboards/aleblazer/zodiarkpi/keymaps/default/keymap.c``` (play a sound every time a key is pressed)
```
bool process_record_user(uint16_t keycode, keyrecord_t *record) {  
  sound_effect_2(VOLUME_MAX)
}
``` 
