/***********************************************************************************************

qwiic_buzzer.c

QMK C library for the SparkFun I2C Qwiic Buzzer BOB-24474. Adapted by Michael Watson from the
SparkFun_Qwiic_Buzzer_Arduino_Library found below 
https://github.com/sparkfun/SparkFun_Qwiic_Buzzer_Arduino_Library
SparkFun code, firmware, and software is released under the MIT License.

Usage Example:
    I2C_qwiic_buzzer_config(NOTE_E6, 500, 3); //Configure: Frequency, Duration(ms), Volume(1-4)
    I2C_qwiic_buzzer_on();                    //Turn on buzzer
    wait_ms(500);                             //play buzzer for Duration(ms)
    I2C_qwiic_buzzer_off();                   //Turn off buzzer

***********************************************************************************************/

#include <stdio.h>
#include <math.h>
#include <i2c_master.h>
#include "qwiic_buzzer.h"


bool I2C_qwiic_buzzer_connected(void) {                         // check if qwiic_buzzer returns the proper ID
    uint8_t data = 0;
    I2C_read_register(REG_ADR_ID, &data);
    if (data == ID)
       return true;                                             // true = connected
    else
       return false;                                            // false = not connected
}


void I2C_scan(void) {						// scan i2c addresses using i2c_ping_address and if sucess then return address
    uint8_t nDevices = 0;
    uprintf("Scanning for I2C devices...\n");
    for (uint8_t address = 1; address < 127; address++) {
        i2c_status_t error = i2c_ping_address(address << 1, TIMEOUT);
        if (error == I2C_STATUS_SUCCESS) {
            uprintf("  I2C device found at address 0x%02X\n", address);
            nDevices++;
        } 
    }
    if (nDevices == 0)
        uprintf("No I2C devices found\n");
    else
        uprintf("I2C device scanning done!\n");
}


void I2C_write_register(uint8_t reg, uint8_t data) {		// write to i2c register
    if (i2c_write_register(I2C_ADDR << 1, reg, &data, 1, TIMEOUT) == I2C_STATUS_SUCCESS) {
       uprintf("Wrote i2c data: 0x%02X\n", data);
    }
}


void I2C_read_register(uint8_t reg, uint8_t *data) {		// read from i2c register and return data 
    if (i2c_read_register(I2C_ADDR << 1, reg, data, 1, TIMEOUT) == I2C_STATUS_SUCCESS) {
       uprintf("Read i2c data\n");
    }
}


void I2C_qwiic_buzzer_config(uint16_t frequency, uint16_t duration, uint8_t volume) {

     uprintf("buzzer_config - Freq: %u Duration: %u\n", frequency, duration);


     uint8_t frequencyMSB = ((frequency & 0xFF00) >> 8);	// extract MSBs and LSBs 
     uint8_t frequencyLSB = (frequency & 0x00FF);
     uint8_t durationMSB = ((duration & 0xFF00) >> 8);
     uint8_t durationLSB = (duration & 0x00FF);
     size_t dataLength = 5;
     uint8_t data[dataLength];
     data[0] = frequencyMSB; 					// _REG_ADR_FREQ_MSB
     data[1] = frequencyLSB; 					// _REG_ADR_FREQ_LSB
     data[2] = volume;          				// _REG_ADR_VOL
     data[3] = durationMSB;     				// _REG_ADR_DUR_MSB
     data[4] = durationLSB;     				// _REG_ADR_DUR_LSB
     if (i2c_write_register(I2C_ADDR << 1, REG_ADR_FREQ_MSB, data, dataLength, TIMEOUT) == I2C_STATUS_SUCCESS) {
       uprintf("Wrote i2c configuration data\n");
     }
}


void I2C_qwiic_buzzer_on(void) {
    I2C_write_register(REG_ADR_ACTIVE, 0x01);
}


void I2C_qwiic_buzzer_off(void) {
    I2C_write_register(REG_ADR_ACTIVE, 0x00);
}


void soundFX1(float amplitude, float period, uint8_t volume) {	// sound FX
    int uDelay=2+amplitude+amplitude*sin(timer_read()/period);
    for(int i=0;i<5;i++){
      I2C_qwiic_buzzer_on();
      wait_us(uDelay);
      I2C_qwiic_buzzer_off();
      wait_us(uDelay);
    }
}


void soundFX2(int maximum, uint8_t volume) {              // space gun
    for(int i=0; i<maximum; i++){
       I2C_qwiic_buzzer_on();
       wait_us(i);
       I2C_qwiic_buzzer_off();
       wait_us(i);
    }
       I2C_qwiic_buzzer_off();
}


void sound_effect_0(uint8_t volume) {				// siren
    for(int i = 0; i < 3; i++){
      I2C_qwiic_buzzer_config(NOTE_G4, 70, volume);
      I2C_qwiic_buzzer_on();
      I2C_qwiic_buzzer_off();
      wait_ms(70);
      I2C_qwiic_buzzer_config(NOTE_G5, 70, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(70);
      I2C_qwiic_buzzer_off();
      I2C_qwiic_buzzer_config(NOTE_G6, 70, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(70);
      I2C_qwiic_buzzer_off();
     }
}


void sound_effect_1(uint8_t volume) {                           // fast sirens
    for (uint8_t i = 0; i < 4; i++) {
        for (int note = 150; note < 4000; note += 150) {
          I2C_qwiic_buzzer_config(note, 0, volume);
          I2C_qwiic_buzzer_on();
          wait_ms(2);
        }
        for (int note = 4000; note > 150; note -= 150) {
          I2C_qwiic_buzzer_config(note, 0, volume);
          I2C_qwiic_buzzer_on();
          wait_ms(2);
        }
    }
    I2C_qwiic_buzzer_off();
}


void sound_effect_2(uint8_t volume) { 				// robot yes
    for (int note = 150; note < 4000; note += 150) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(40);
    }
    I2C_qwiic_buzzer_off();
}


void sound_effect_3(uint8_t volume) {                           // robot fast yes
    for (int note = 150; note < 4000; note += 150) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(10);
    }
    I2C_qwiic_buzzer_off();
}


void sound_effect_4(uint8_t volume) {                           // robot no
    for (int note = 4000; note > 150; note -= 150) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(40);
    }
    I2C_qwiic_buzzer_off();
}


void sound_effect_5(uint8_t volume) {                           // robot fast no 
    for (int note = 4000; note > 150; note -= 150) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(10);
    }
    I2C_qwiic_buzzer_off();
}


void sound_effect_6(uint8_t volume) {                           // robot laughing
    float laugh_delay = 0.4;
    uint8_t laugh_step = 10;
    for (int note = 1538; note < 1905; note += laugh_step) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(10);
    }
    I2C_qwiic_buzzer_off();
    wait_ms(laugh_delay);
    for (int note = 1250; note < 1515; note += laugh_step) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(10);
    }
    I2C_qwiic_buzzer_off();
    wait_ms(laugh_delay);
    for (int note = 1111; note < 1342; note += laugh_step) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(10);
    }
    I2C_qwiic_buzzer_off();
    wait_ms(laugh_delay);
   for (int note = 1010; note < 1176; note += laugh_step) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(10);
    }
    I2C_qwiic_buzzer_off();
}


void sound_effect_7(uint8_t volume) {                           // robot crying
    float cry_delay = 0.5;
    int cry_step = -10;
    for (int note = 2000; note > 1429; note += cry_step) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(10);
    }
    I2C_qwiic_buzzer_off();
    wait_ms(cry_delay);
    for (int note = 1667; note > 1250; note += cry_step) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(10);
    }
    I2C_qwiic_buzzer_off();
    wait_ms(cry_delay);
    for (int note = 1429; note > 1053; note += cry_step) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(10);
    }
    I2C_qwiic_buzzer_off();
}


void sound_effect_8(uint8_t volume) {                           // robot fast crying
    float laugh_delay = 0.2;
    int laugh_step = -20;
    for (int note = 2000; note < 1429; note += laugh_step) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(10);
    }
    I2C_qwiic_buzzer_off();
    wait_ms(laugh_delay);
    for (int note = 1667; note < 1250; note += laugh_step) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(10);
    }
    I2C_qwiic_buzzer_off();
    wait_ms(laugh_delay);
    for (int note = 1429; note < 1053; note += laugh_step) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(10);
    }
    I2C_qwiic_buzzer_off();
    wait_ms(300);
}


void sound_effect_9(uint8_t volume) { 				// SND_FX3
    I2C_qwiic_buzzer_config(100, 250, volume);
    I2C_qwiic_buzzer_on(); 
    wait_ms(200);
    I2C_qwiic_buzzer_config(50, 250, volume);
    I2C_qwiic_buzzer_on(); 
    wait_ms(400);
    I2C_qwiic_buzzer_off();
}


void sound_effect_10(uint8_t volume) { 				// SND_FX4
  for (int i=0; i < 3; i++) { 
    for (int j = 1; j < 100; j++) {
      I2C_qwiic_buzzer_config(j, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(1);
      I2C_qwiic_buzzer_off();
    }
    wait_ms(100);
    I2C_qwiic_buzzer_off();
  }
  for (int j = 0; j < 4; j++) {
    soundFX2(300, volume);
  }
}


void sound_effect_11(uint8_t volume) {				// Hello
    for (int note = 150; note < 4000; note += 150) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(10);
    }
    for (int note = 4000; note > 150; note -= 150) {
      I2C_qwiic_buzzer_config(note, 0, volume);
      I2C_qwiic_buzzer_on();
      wait_ms(10);
    }
    I2C_qwiic_buzzer_off();
}


void take_on_me(void) {			           		// more melodies at: https://github.com/robsoncouto/arduino-songs
  int tempo = 140;
  int melody[] = {
    // Take on me, by A-ha, Score available at https://musescore.com/user/27103612/scores/4834399, Arranged by Edward Truong
    NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, NOTE_REST,8, NOTE_B4,8, NOTE_REST,8, NOTE_E5,8,
    NOTE_REST,8, NOTE_E5,8, NOTE_REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
    NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, NOTE_REST,8, NOTE_D5,8, NOTE_REST,8, NOTE_FS5,8,
    NOTE_REST,8, NOTE_FS5,8, NOTE_REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
    NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, NOTE_REST,8, NOTE_B4,8, NOTE_REST,8, NOTE_E5,8,
    NOTE_REST,8, NOTE_E5,8, NOTE_REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
    NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, NOTE_REST,8, NOTE_D5,8, NOTE_REST,8, NOTE_FS5,8,
    NOTE_REST,8, NOTE_FS5,8, NOTE_REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
    NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, NOTE_REST,8, NOTE_B4,8, NOTE_REST,8, NOTE_E5,8,
    NOTE_REST,8, NOTE_E5,8, NOTE_REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
    NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, NOTE_REST,8, NOTE_D5,8, NOTE_REST,8, NOTE_FS5,8,
    NOTE_REST,8, NOTE_FS5,8, NOTE_REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  };
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  int wholenote = (60000 * 4) / tempo;				// whole note duration in ms
  int divider = 0, noteDuration = 0;
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = melody[thisNote + 1];				// duration of each note
    if (divider > 0) {
      noteDuration = (wholenote) / divider;			// regular note duration
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);		// dotted note shown with negative duration
      noteDuration *= 1.5; 					// increase duration by 1.5 for dotted notes
    }
    I2C_qwiic_buzzer_config(melody[thisNote], noteDuration * 0.9, 3);//90% duration with 10% pause
    I2C_qwiic_buzzer_on();
    wait_ms(noteDuration);					// wait duration before playing next note
    I2C_qwiic_buzzer_off();
  }
}


void sound_demo(void) {
    uint8_t volume = VOLUME_MID;
    sound_effect_0(volume);
    wait_ms(500);
    sound_effect_1(volume);
    wait_ms(500);
    sound_effect_2(volume);
    wait_ms(500);
    sound_effect_3(volume);
    wait_ms(500);
    sound_effect_4(volume);
    wait_ms(500);
    sound_effect_5(volume);
    wait_ms(500);
    sound_effect_6(volume);
    wait_ms(500);
    sound_effect_7(volume);
    wait_ms(500);
    sound_effect_8(volume);
    wait_ms(500);
    sound_effect_9(volume);
    wait_ms(500);
    sound_effect_10(volume);
    wait_ms(500);
    sound_effect_11(volume);
    wait_ms(500);
    take_on_me();
}
