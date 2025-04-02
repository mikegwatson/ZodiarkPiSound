# ZodiarkPi / QMK I<sup>2</sup>C Keyboard Sound
A QMK sound driver for a [ZodiarkPi](https://www.splitlogic.xyz/shop/splitlogic/p/zodiarkpi) keyboard, or [QMK](https://github.com/qmk/qmk_firmware) keyboard, using the [SparkFun I<sup>2</sup>C Qwiic Buzzer - BOB-24474](https://www.sparkfun.com/sparkfun-qwiic-buzzer.html) 

&nbsp;

### Sound Demo
https://github.com/user-attachments/assets/96be4976-08ce-485e-ae0a-f66f3da4de4b

&nbsp;

### Achtung!
***Note*** You can _**not**_ use a dual axis encoder with the ZodiarkPi and this buzzer, since it uses the extra I<sup>2</sup>C pins

&nbsp;

### Wiring
Wire SparkFun Qwiic Buzzer As Shown:<br>
<img src="https://github.com/user-attachments/assets/e8fe0486-fe48-446f-a433-ebbc0ed86099" alt="ZodiarkPiQwiicBuzzer1" width="378" height="504">

Prepare To Hide The Buzzer (put eletrical tape on the back of the buzzer to prevent shorts):<br>
<img src="https://github.com/user-attachments/assets/f68df095-2718-4d6e-a544-9b7926785d68" alt="ZodiarkPiQwiicBuzzer2" width="378" height="504">

Hidden Buzzer:<br>
<img src="https://github.com/user-attachments/assets/a4206b62-00a4-41c0-b92e-fb1d38929b1d" alt="ZodiarkPiQwiicBuzzer3" width="378" height="504">

&nbsp;

### QMK ZodiarkPi Environment Setup 
#### This is how I did it with Debian Linux, but there may be a better way to do this:
1. ```git clone https://github.com/Aleblazer/qmk_firmware.git```       (clone QMK)
   
2. ```cd qmk_firmware```                                               (goto QMK directory)

3. ```git branch -v -a```                                              (list branches)

4. ```git switch zodiarkpi```                                          (switch branch to zodiarkpi)

5. ```ls ~/Documents/qmk_firmware/keyboards/aleblazer```               (should now see zodiarkpi directory)

6. ```make git-submodule```                                            (download submodules)

7. ```nano keyboards/aleblazer/zodiarkpi/zodiarkpi.c```                (comment/uncomment to match your display & encoders)

8. ```qmk flash -kb aleblazer/zodiarkpi -km gc9a01cirque```            (make sure you can compile & flash - gc9a01cirque in this case)   

&nbsp;

### QMK Sound Code
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

4. Edit ```qmk_firmware/keyboards/aleblazer/zodiarkpi/mcuconf.h```     (add the below lines to use IC20)
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

7. Edit ```qmk_firmware/keyboards/aleblazer/zodiarkpi/zodiarkpi.c```   (add below lines to ```void keyboard_post_init_kb(void)``` function)
```
i2c_init();                                                      //initialize the I2C bus
if (I2C_qwiic_buzzer_connected()) {
  uprintf("I2C qwiick buzzer found at: 0x%02X\n", I2C_ADDR);     //use 'qmk console' on PC to see if buzzer found
}
sound_effect_0(VOLUME_MID);                                      //play startup sound when the keyboard boots     
```

8. Edit ```qmk_firmware/keyboards/aleblazer/zodiarkpi/keymaps/default/keymap.c``` (add the below line to the top of the file)
```
#include "../../sound/qwiic_buzzer.h"
```

9. Recompile / Flash the new code for your Zodiark Pi and if all worked properly you should hear a sound on bootup of your keyboard.
   You can add additional code to your keymap file, so that every time a key is pressed you can play a sound by calling the below function:
```
bool process_record_user(uint16_t keycode, keyrecord_t *record) 
``` 

&nbsp;

### Need Help
Visit the [Discord server](https://discord.gg/BCSbXwskVt) #zodiarkpi channel or open a bug here.
