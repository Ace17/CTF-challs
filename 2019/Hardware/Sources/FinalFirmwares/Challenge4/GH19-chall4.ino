//lib for PCA9535
#include <FaBoGPIO40_PCA9698-mod.h>
FaBoGPIO40 faboGPIO;

//
// Small Simple OLED library demo for AVR platform,
// without line drawing function (saving of 1K RAM)
//
// add large fonts only on challenge 4 (save ~850 bytes)
#define OLED_FONT_STRETCHED
#include <ss_oled.h>
extern const uint8_t boom[1086] PROGMEM ;
extern const uint8_t GreHack[1086] PROGMEM ;

void setup() {

  faboGPIO.configuration();
  faboGPIO.portMode(0, OUTPUT);
  faboGPIO.portMode(1, OUTPUT);

  delay(100);   // time for OLED to init
  oledInit(OLED_128x64, 0, 0, -1, -1, 400000L);       // Standard HW I2C bus at 400Khz

  // hi-level text hidding
  /*Serial.begin(9600);
  uint8_t strClear[]="            Hum, good job! It looks like you deserve a flag! Here we are: GH19{DumpDumpGo}               "; // ln 105
  for (int i=0;i<strlen(strClear);i++)
    Serial.println(strClear[i]^0xFF,HEX);*/
}

int i;
uint16_t position=0;
uint8_t state=1;

void loop() {

  // clear 2 last LED
  faboGPIO.portWrite(0,0xFF);
  faboGPIO.portWrite(1,0xFF);

  for (i=0; i<2; i++)
  {
    oledLoadBMP(boom,0,1);
    delay(450);
    oledLoadBMP(boom,1,1);
    delay(450);
  }  

  oledFill(0, 1);
  oledLoadBMP(GreHack,0,1);

  for (i=0;i<1485;i++)
  {
    // light 2 LED, round
    faboGPIO.portWrite(0,1<<(i%8));
    faboGPIO.portWrite(1,1<<(7-(i-3)%8));
    uint8_t scrolltext[105] PROGMEM = {0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xB7,0x8A,0x92,0xD3,0xDF,0x98,0x90,0x90,0x9B,0xDF,0x95,0x90,0x9D,0xDE,0xDF,0xB6,0x8B,0xDF,0x93,0x90,0x90,0x94,0x8C,0xDF,0x93,0x96,0x94,0x9A,0xDF,0x86,0x90,0x8A,0xDF,0x9B,0x9A,0x8C,0x9A,0x8D,0x89,0x9A,0xDF,0x9E,0xDF,0x99,0x93,0x9E,0x98,0xDE,0xDF,0xB7,0x9A,0x8D,0x9A,0xDF,0x88,0x9A,0xDF,0x9E,0x8D,0x9A,0xC5,0xDF,0xB8,0xB7,0xCE,0xC6,0x84,0xBB,0x8A,0x92,0x8F,0xBB,0x8A,0x92,0x8F,0xB8,0x90,0x82,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF};
    if (scrolltext[0] == 0xDF)
        for (int j=0;j<101;j++)
          scrolltext[j]^=0xFF;
    oledWriteString(i, 0, 6,(char *)scrolltext, FONT_STRETCHED, 0, 1);
    delay(20);
  }

}

const uint8_t boom[1086] PROGMEM = {
  0x42, 0x4D, 0x3E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00,
  0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x00,
  0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
  0x00, 0x00, 0xC3, 0x0E, 0x00, 0x00, 0xC3, 0x0E, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x01, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0xF8, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0xFC, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x00, 0xF0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xF0, 0xE0, 0x00,
  0x00, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F,
  0xFF, 0xF3, 0xF0, 0x00, 0x00, 0x00, 0x1F, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1F, 0xFF, 0xCF, 0xF8, 0x04, 0x00, 0x00, 0xFF, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0x1F, 0xF8, 0x0E,
  0x00, 0x03, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
  0xFE, 0x3F, 0xFC, 0x0F, 0xFC, 0x1F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1F, 0xFE, 0x7F, 0xFE, 0x0F, 0xF8, 0x7F, 0xF8, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0x7F, 0xFC, 0x7F,
  0xF3, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x1C,
  0x1F, 0x7F, 0xF1, 0xFF, 0xF3, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0F, 0xE0, 0x00, 0x00, 0x03, 0x7F, 0xFE, 0x3F, 0xFB, 0xFF, 0xE0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0xFC, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xCF,
  0xF9, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xC0, 0x00,
  0x0F, 0x7F, 0xFF, 0xCF, 0x3D, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x07, 0xFF, 0xFC, 0x00, 0x3F, 0xFF, 0xFF, 0xEE, 0x60, 0xFF, 0xE0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xC1, 0xFF, 0xFF, 0xFF, 0xE1,
  0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xE3, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xF8, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x0F, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x0F,
  0xFF, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x03,
  0xC0, 0x00, 0x00, 0x1F, 0xFF, 0xFC, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xEF, 0xFF, 0xCE, 0x0F, 0xCF, 0x00, 0x10, 0x1F, 0xFF, 0xFE, 0x3F, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0x8F, 0xE7, 0xCF, 0x9F, 0x8F, 0xF0, 0x1F, 0x1F,
  0xFF, 0xFF, 0x10, 0x00, 0xFF, 0xFE, 0x07, 0xFE, 0x27, 0xC1, 0xCF, 0xCE,
  0x0F, 0x80, 0x03, 0x3F, 0xC0, 0xFF, 0x8F, 0xFF, 0x1F, 0xE1, 0xF8, 0x38,
  0xF3, 0x88, 0xCF, 0xE0, 0x04, 0x00, 0x00, 0x3F, 0xCE, 0x7F, 0x9F, 0xFF,
  0xC7, 0x8F, 0xFF, 0x83, 0xF1, 0x9E, 0x1F, 0xE0, 0x20, 0x00, 0x00, 0x7F,
  0x8E, 0x3F, 0x3F, 0xFF, 0xF3, 0x3F, 0xFF, 0xE7, 0xF8, 0x3F, 0x1F, 0xE3,
  0xF0, 0x00, 0x00, 0x7F, 0xC0, 0x7E, 0x7F, 0x07, 0xF8, 0x7F, 0xFF, 0xF3,
  0xFC, 0x7F, 0x9F, 0xE3, 0xF8, 0x00, 0x00, 0xFF, 0xFD, 0xFC, 0xFC, 0xF1,
  0xFC, 0x7E, 0x07, 0xF3, 0xFE, 0xFF, 0xFF, 0xE3, 0xF8, 0x00, 0x00, 0xFF,
  0xFF, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF9, 0xF9, 0xFF, 0xFF, 0xFF, 0xE3,
  0xFC, 0x00, 0x00, 0xFF, 0x1F, 0xFC, 0xFD, 0xFE, 0xFC, 0xFD, 0xFC, 0xF8,
  0xFF, 0xFF, 0xFF, 0xC1, 0xFC, 0x00, 0x01, 0xFF, 0x07, 0xE0, 0xFC, 0xFE,
  0x7C, 0xFD, 0xFE, 0x7C, 0xFF, 0xFF, 0xFF, 0xC9, 0xFE, 0x00, 0x01, 0xFF,
  0x23, 0xE0, 0xFC, 0xFE, 0x7C, 0xFC, 0xFE, 0x7E, 0x7F, 0xFF, 0xFF, 0xCC,
  0xFF, 0x00, 0x03, 0xFF, 0x03, 0xF0, 0xFE, 0x3E, 0xFC, 0xFE, 0x7E, 0x7E,
  0x3F, 0xFD, 0xFF, 0x8C, 0xFF, 0x00, 0x03, 0xFF, 0xC7, 0xF8, 0x7F, 0x81,
  0xFE, 0x7F, 0x1C, 0xFF, 0x3F, 0xF8, 0x7F, 0x9E, 0x7F, 0x80, 0x03, 0xFF,
  0xFF, 0xF8, 0x3F, 0xFF, 0xFE, 0x3F, 0xC1, 0xFF, 0x1F, 0xF1, 0x1F, 0x9E,
  0x7F, 0x80, 0x00, 0xFF, 0xFF, 0xF8, 0x9F, 0xFF, 0xFE, 0x1F, 0xFF, 0xFE,
  0x0F, 0xE3, 0xC3, 0x1F, 0x3F, 0xC0, 0x00, 0x0F, 0xFF, 0xF9, 0xE7, 0xFF,
  0xFC, 0xCF, 0xFF, 0xFE, 0x47, 0xCF, 0xF8, 0x3F, 0x38, 0x00, 0x07, 0xC0,
  0xFF, 0xE3, 0xF8, 0xFF, 0xF1, 0xE3, 0xFF, 0xF8, 0xE7, 0x9F, 0xFE, 0x00,
  0x00, 0x00, 0x1F, 0xF8, 0x00, 0x07, 0xFE, 0x1F, 0x87, 0xFC, 0x7F, 0xE3,
  0xF3, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xF0,
  0x7F, 0xFF, 0x80, 0x1F, 0xF8, 0x7F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xFF, 0xF8, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFD, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF,
  0xFF, 0xFF, 0xFF, 0xF0, 0x03, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0xFF, 0xE0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
  0x00, 0x3F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x03, 0xFF,
  0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x07, 0xF0, 0x00, 0x01, 0x98, 0x00, 0x01,
  0xFC, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x01, 0xF8, 0x00,
  0x01, 0xF8, 0x00, 0x1F, 0xFF, 0x80, 0x03, 0xFF, 0xFF, 0xFF, 0xFC, 0x00,
  0x00, 0x00, 0x7C, 0x00, 0x01, 0xF8, 0x00, 0x07, 0xFF, 0x00, 0x01, 0xFF,
  0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x07, 0xFE, 0x00, 0x03,
  0xFE, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x03, 0x00,
  0x00, 0xF0, 0x00, 0x03, 0xFE, 0x00, 0x01, 0xFF, 0x00, 0x1F, 0xF0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x03, 0xFE, 0x00, 0x00, 0xFC,
  0x00, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
  0x06, 0x00, 0x00, 0xF0, 0x00, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0,
  0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t GreHack[1086] PROGMEM = {
  0x42, 0x4D, 0x3E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00,
  0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x00,
  0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
  0x00, 0x00, 0xC2, 0x0E, 0x00, 0x00, 0xC2, 0x0E, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF,
  0x07, 0xC1, 0xE1, 0xFF, 0xC1, 0xE0, 0xF8, 0xF8, 0x1F, 0x07, 0xFE, 0x07,
  0xC1, 0xF0, 0x0F, 0xFF, 0x07, 0xC3, 0xE1, 0xFF, 0xC1, 0xE0, 0xF8, 0x78,
  0x1E, 0x0F, 0xFF, 0x07, 0xC1, 0xF0, 0x0F, 0xFF, 0x87, 0xC3, 0xC1, 0xFF,
  0xC1, 0xE0, 0xF8, 0x78, 0x1E, 0x1F, 0xFF, 0x87, 0xC3, 0xE0, 0x1F, 0xFF,
  0x87, 0xC3, 0xC1, 0xFF, 0xC1, 0xE0, 0xF8, 0x78, 0x1E, 0x1F, 0xFF, 0x87,
  0xC3, 0xE0, 0x1F, 0x07, 0x87, 0xC3, 0xC1, 0xF0, 0x01, 0xE0, 0xF8, 0x78,
  0x1E, 0x1F, 0x07, 0x87, 0xC7, 0xC0, 0x1F, 0x07, 0x87, 0xC7, 0xC1, 0xF0,
  0x01, 0xE0, 0xF8, 0x7C, 0x3E, 0x1F, 0x07, 0x87, 0xC7, 0xC0, 0x1F, 0x07,
  0x87, 0xC7, 0xC1, 0xF0, 0x01, 0xE0, 0xF8, 0x7C, 0x3C, 0x1F, 0x07, 0x87,
  0xCF, 0x80, 0x1F, 0x07, 0x87, 0xC7, 0x81, 0xF0, 0x01, 0xE0, 0xF8, 0x3C,
  0x3C, 0x1F, 0x07, 0x87, 0xEF, 0x80, 0x1F, 0x07, 0x87, 0xC7, 0x81, 0xF0,
  0x01, 0xE0, 0xF8, 0x3F, 0xFC, 0x1F, 0x07, 0x87, 0xFF, 0x00, 0x1F, 0x07,
  0x87, 0xFF, 0x81, 0xF0, 0x01, 0xE0, 0xF8, 0x3F, 0xFC, 0x1F, 0x07, 0x87,
  0xFF, 0x00, 0x1F, 0x07, 0x87, 0xFF, 0xC1, 0xF0, 0x01, 0xF0, 0xF8, 0x3F,
  0xFC, 0x1F, 0x00, 0x07, 0xFE, 0x00, 0x1F, 0x07, 0x87, 0xFF, 0xE1, 0xFF,
  0x81, 0xF8, 0xF8, 0x3F, 0xFC, 0x1F, 0x00, 0x07, 0xFE, 0x00, 0x1F, 0x07,
  0x87, 0xFF, 0xE1, 0xFF, 0x81, 0xFC, 0xF8, 0x3E, 0x78, 0x1F, 0x00, 0x07,
  0xFC, 0x00, 0x1F, 0x07, 0x87, 0xC1, 0xE1, 0xFF, 0x81, 0xFE, 0xF8, 0x1E,
  0x78, 0x1F, 0x00, 0x07, 0xFC, 0x00, 0x1F, 0x07, 0x87, 0xC1, 0xE1, 0xFF,
  0x81, 0xFF, 0xF8, 0x1E, 0x78, 0x1F, 0x00, 0x07, 0xFC, 0x00, 0x1F, 0x07,
  0x87, 0xC1, 0xE1, 0xF0, 0x01, 0xFF, 0xF8, 0x1E, 0x78, 0x1F, 0x00, 0x07,
  0xFE, 0x00, 0x1F, 0x3F, 0x87, 0xC1, 0xE1, 0xF0, 0x01, 0xEF, 0xF8, 0x1E,
  0x78, 0x1F, 0x00, 0x07, 0xDF, 0x00, 0x1F, 0x3F, 0x87, 0xC1, 0xE1, 0xF0,
  0x01, 0xE7, 0xF8, 0x1E, 0x78, 0x1F, 0x07, 0x87, 0xDF, 0x00, 0x1F, 0x3F,
  0x87, 0xC1, 0xE1, 0xF0, 0x01, 0xE3, 0xF8, 0x1F, 0xF0, 0x1F, 0x07, 0x87,
  0xCF, 0x80, 0x1F, 0x00, 0x07, 0xC1, 0xE1, 0xF0, 0x01, 0xE1, 0xF8, 0x0F,
  0xF0, 0x1F, 0x07, 0x87, 0xCF, 0x80, 0x1F, 0x00, 0x07, 0xC1, 0xE1, 0xF0,
  0x01, 0xE0, 0xF8, 0x0F, 0xF0, 0x1F, 0x07, 0x87, 0xC7, 0xC0, 0x1F, 0x00,
  0x07, 0xC1, 0xE1, 0xF0, 0x01, 0xE0, 0xF8, 0x0F, 0xF0, 0x1F, 0x07, 0x87,
  0xC7, 0xC0, 0x1F, 0x00, 0x07, 0xC3, 0xE1, 0xF8, 0x01, 0xE0, 0xF8, 0x0F,
  0xF0, 0x1F, 0x0F, 0x87, 0xC3, 0xE0, 0x1F, 0x00, 0x07, 0xFF, 0xE1, 0xFF,
  0xC1, 0xE0, 0xF8, 0x0F, 0xF0, 0x1F, 0xFF, 0x87, 0xC3, 0xE0, 0x1F, 0x00,
  0x07, 0xFF, 0xE1, 0xFF, 0xC1, 0xE0, 0xF8, 0x07, 0xE0, 0x0F, 0xFF, 0x07,
  0xC1, 0xF0, 0x1F, 0x00, 0x07, 0xFF, 0xC1, 0xFF, 0xC1, 0xE0, 0xF8, 0x07,
  0xE0, 0x07, 0xFE, 0x07, 0xC1, 0xF0, 0x1F, 0x07, 0x80, 0x00, 0x00, 0x00,
  0x01, 0xE0, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x07,
  0x80, 0x00, 0x00, 0x00, 0x01, 0xE0, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x1F, 0x07, 0x80, 0x00, 0x00, 0x00, 0x01, 0xE0, 0xF8, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x07, 0x80, 0x00, 0x00, 0x00,
  0x01, 0xE0, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x07,
  0x80, 0x00, 0x00, 0x00, 0x01, 0xE0, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x1F, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x01, 0xE0, 0xF8, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0x80, 0x00, 0x00, 0x00,
  0x01, 0xE0, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xE0, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x01, 0xE0, 0xF8, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
