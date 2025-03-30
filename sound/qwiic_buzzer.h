/***********************************************************************************************

qwiic_buzzer.h

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

#pragma once

#define I2C_ADDR 0x34                           // <------------------------------- define default Qwiic Buzzer I2C address
#define ID 0x5E
#define TIMEOUT 50
#define REG_ADR_ID 0x00
#define REG_ADR_FW_MIN 0x01
#define REG_ADR_FW_MAJ 0x02
#define REG_ADR_FREQ_MSB 0x03
#define REG_ADR_FREQ_LSB 0x04
#define REG_ADR_VOL 0x05
#define REG_ADR_DUR_MSB 0x06
#define REG_ADR_DUR_LSB 0x07
#define REG_ADR_ACTIVE 0x08
#define REG_ADR_SAVE 0x09
#define REG_ADR_I2C_ADD 0x0A

#define RESONANT_FREQUENCY 2730
#define VOLUME_MIN 1
#define VOLUME_LOW 2
#define VOLUME_MID 3
#define VOLUME_MAX 4

#define NOTE_REST 0
#define NOTE_B0   31
#define NOTE_C1   33
#define NOTE_CS1  35
#define NOTE_D1   37
#define NOTE_DS1  39
#define NOTE_E1   41
#define NOTE_F1   44
#define NOTE_FS1  46
#define NOTE_G1   49
#define NOTE_GS1  52
#define NOTE_A1   55
#define NOTE_AS1  58
#define NOTE_B1   62
#define NOTE_C2   65
#define NOTE_CS2  69
#define NOTE_D2   73
#define NOTE_DS2  78
#define NOTE_E2   82
#define NOTE_F2   87
#define NOTE_FS2  93
#define NOTE_G2   98
#define NOTE_GS2  104
#define NOTE_A2   110
#define NOTE_AS2  117
#define NOTE_B2   123
#define NOTE_C3   131
#define NOTE_CS3  139
#define NOTE_D3   147
#define NOTE_DS3  156
#define NOTE_E3   165
#define NOTE_F3   175
#define NOTE_FS3  185
#define NOTE_G3   196
#define NOTE_GS3  208
#define NOTE_A3   220
#define NOTE_AS3  233
#define NOTE_B3   247
#define NOTE_C4   262
#define NOTE_CS4  277
#define NOTE_D4   294
#define NOTE_DS4  311
#define NOTE_E4   330
#define NOTE_F4   349
#define NOTE_FS4  370
#define NOTE_G4   392
#define NOTE_GS4  415
#define NOTE_A4   440
#define NOTE_AS4  466
#define NOTE_B4   494
#define NOTE_C5   523
#define NOTE_CS5  554
#define NOTE_D5   587
#define NOTE_DS5  622
#define NOTE_E5   659
#define NOTE_F5   698
#define NOTE_FS5  740
#define NOTE_G5   784
#define NOTE_GS5  831
#define NOTE_A5   880
#define NOTE_AS5  932
#define NOTE_B5   988
#define NOTE_C6   1047
#define NOTE_CS6  1109
#define NOTE_D6   1175
#define NOTE_DS6  1245
#define NOTE_E6   1319
#define NOTE_F6   1397
#define NOTE_FS6  1480
#define NOTE_G6   1568
#define NOTE_GS6  1661
#define NOTE_A6   1760
#define NOTE_AS6  1865
#define NOTE_B6   1976
#define NOTE_C7   2093
#define NOTE_CS7  2217
#define NOTE_D7   2349
#define NOTE_DS7  2489
#define NOTE_E7   2637
#define NOTE_F7   2794
#define NOTE_FS7  2960
#define NOTE_G7   3136
#define NOTE_GS7  3322
#define NOTE_A7   3520
#define NOTE_AS7  3729
#define NOTE_B7   3951
#define NOTE_C8   4186
#define NOTE_CS8  4435
#define NOTE_D8   4699
#define NOTE_DS8  4978

void I2C_scan(void);
void I2C_write_register(uint8_t reg, uint8_t data);
void I2C_read_register(uint8_t reg, uint8_t *data);
bool I2C_qwiic_buzzer_connected(void);
void I2C_qwiic_buzzer_config(uint16_t frequency, uint16_t duration, uint8_t volume);
void I2C_qwiic_buzzer_on(void);
void I2C_qwiic_buzzer_off(void);
void soundFX1(float amplitude, float period, uint8_t volume);
void soundFX2(int maximum, uint8_t volume);
void sound_effect_0(uint8_t volume);
void sound_effect_1(uint8_t volume);
void sound_effect_2(uint8_t volume);
void sound_effect_3(uint8_t volume);
void sound_effect_4(uint8_t volume);
void sound_effect_5(uint8_t volume);
void sound_effect_6(uint8_t volume);
void sound_effect_7(uint8_t volume);
void sound_effect_8(uint8_t volume);
void sound_effect_9(uint8_t volume);
void sound_effect_10(uint8_t volume);
void sound_effect_11(uint8_t volume);
void take_on_me(void);
void sound_demo(void);
