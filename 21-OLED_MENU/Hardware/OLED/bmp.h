#ifndef __BMP_H
#define __BMP_H

//?ź?
unsigned char Signal_11x8[] = 
{
    0x03,0x05,0x09,0xFF,0x09,0xC5,0x03,0xF0,0x00,0xFC,0x00
};

//????
unsigned char Bluetooth_9x9[] = 
{
    0x00,0x00,0x44,0x28,0xFF,0x11,0xAA,0x44,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00
};

//????
unsigned char BAT_8x16[] =
{
    0x3C,0x24,0xFF,0x81,0xBD,0xBD,0xBD,0x81,0xBD,0xBD,0xBD,0x81,0xBD,0xBD,0xBD,0xFF
};

//?˵?
unsigned char Menu_16x16[] =
{
    0x00,0x00,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x00,0x00,
    0x00,0x00,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x00,0x00
};

//??
unsigned char Lock_16x16[] =
{
    0x00,0x00,0xC0,0xF0,0xF8,0xCC,0xC4,0xC4,0xC4,0xC4,0xCC,0xF8,0xF0,0xC0,0x00,0x00,
    0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00,0x00
};


// ????ͷ
unsigned char Left_16x16[] =
{
    0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

// ?Ҽ?ͷ
unsigned char Right_16x16[] =
{
    0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xF8,0xF0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00
};

//ȷ??
unsigned char Ok_16x16[] =
{
    0x00,0x00,0x00,0xC0,0xC0,0x80,0x00,0x00,0x00,0x80,0xC0,0xE0,0x70,0x38,0x18,0x00,
    0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0E,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00
};

//????
unsigned char Back_16x16[] = 
{
    0x00,0x00,0x00,0x60,0xF0,0xF8,0x60,0x60,0x60,0x60,0x60,0xE0,0xE0,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x18,0x19,0x18,0x18,0x18,0x18,0x18,0x1F,0x1F,0x00,0x00,0x00
};

//????48*48
unsigned char BT_32x32[] = 
{
    0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0xF8,0xF8,0xFE,0xFE,0xFE,0xFE,0xFF,0xFF,0xFF,
    0x0F,0x1F,0x3F,0x7E,0xFE,0xFE,0xFE,0xFC,0xF8,0xF8,0xC0,0x80,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xF3,0xC7,0x8F,0x9F,0x3F,
    0x00,0x3F,0x9E,0xCE,0xE0,0xF1,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x9F,0x8F,0xC7,0xF3,0xF9,0xF8,
    0x00,0xF8,0xF9,0x73,0x07,0x8F,0x9F,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x03,0x07,0x1F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xE0,0xF8,0xF8,0xFE,0xFE,0xFF,0x7F,0x3F,0x3F,0x1F,0x03,0x01,0x00,0x00,0x00,0x00
};

unsigned char Wifi_48x48[] = 
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xE0,0xF0,0xF0,0xF8,0xF8,0xF8,0xFC,
    0xFC,0xFC,0xFC,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFC,0xFC,0xFC,
    0xFC,0xF8,0xF8,0xF8,0xF0,0xF0,0xE0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x02,0x07,0x0F,0x1F,0x3F,0x3F,0x1F,0x0F,0x8F,0x87,0xC3,0xE3,0xE1,
    0xF1,0xF1,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF0,0xF1,0xF1,
    0xE1,0xE3,0xC3,0x87,0x8F,0x0F,0x1F,0x3F,0x3F,0x1F,0x0F,0x07,0x02,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x07,0x0F,0x1F,0x3F,0x1F,
    0x0F,0x0F,0x87,0x87,0xC3,0xC3,0xC3,0xC3,0xE3,0xC3,0xC3,0xC3,0x87,0x87,0x0F,0x0F,
    0x1F,0x3F,0x1F,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

};
unsigned char Setting_32x32[] = 
{
    0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xE0,0xE0,0xC0,0x80,0x80,0xF8,0xF8,0xFC,
    0xFC,0xFC,0xF8,0xE0,0x80,0xC0,0xE0,0xE0,0xE0,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xC0,0xE0,0xE0,0xE3,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x1F,0x1F,
    0x1F,0x1F,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE3,0xE1,0xE0,0xE0,0x00,0x00,
    0x00,0x00,0x03,0x07,0x07,0xCF,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF8,0xF8,
    0xF8,0xF8,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0x8F,0x07,0x07,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x07,0x07,0x03,0x03,0x03,0x3F,0x3F,0x3F,
    0x3F,0x3F,0x3F,0x0F,0x03,0x03,0x07,0x0F,0x07,0x07,0x03,0x00,0x00,0x00,0x00,0x00,
};

unsigned char Info_32x32[] = 
{
    0x00,0x00,0xC0,0xC0,0xC0,0xE0,0xFC,0x7C,0x7C,0x7C,0x7E,0x1E,0x1E,0x1F,0x0F,0x0F,
    0xCF,0xCF,0xDF,0xDE,0x1E,0x3E,0x7C,0x7C,0x7C,0xFC,0xF8,0xC0,0xC0,0xC0,0x00,0x00,
    0xE0,0xFC,0xFF,0xFF,0x3F,0x07,0x07,0x00,0x00,0x00,0x00,0x00,0xC0,0x40,0xE0,0xE0,
    0xF3,0xF7,0xE7,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x3F,0xFF,0xFF,0xFF,0xE0,
    0x07,0x3F,0xFF,0xFF,0xFC,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x40,0xF8,0xFF,0x7F,
    0x4F,0x47,0x61,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xFC,0xFF,0xFF,0xFF,0x07,
    0x00,0x00,0x03,0x07,0x07,0x07,0x3F,0x3E,0x7C,0x7C,0x7C,0x78,0x78,0xF8,0xF0,0xF0,
    0xF0,0xF0,0xF8,0x78,0x78,0x7C,0x7C,0x7C,0x3E,0x3F,0x1F,0x07,0x07,0x03,0x00,0x00
};




#endif


