/*
 * Archivo: oled.h
*/
 
#define OLED_WIDTH             96
#define OLED_HEIGHT            39
 
#define SSD1306_DISPLAYOFF          0xAE
#define SSD1306_SETDISPLAYCLOCKDIV  0xD5
#define SSD1306_SETMULTIPLEX        0xA8
#define SSD1306_SETDISPLAYOFFSET    0xD3
#define SSD1306_SETSTARTLINE        0x40
#define SSD1306_CHARGEPUMP          0x8D
 
#define SSD1306_SETSEGMENTREMAP     0xA1
#define SSD1306_SEGREMAP            0xA0
 
#define SSD1306_COMSCANDEC          0xC8
#define SSD1306_SETCOMPINS          0xDA
#define SSD1306_SETCONTRAST         0x81
#define SSD1306_SETPRECHARGE        0xD9
#define SSD1306_SETVCOMDETECT       0xDB
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_NORMALDISPLAY       0xA6
#define SSD1306_DISPLAYON           0xAF
 
#define SSD1306_DISPLAYALLON        0xA5
#define SSD1306_INVERTDISPLAY       0xA7
#define SSD1306_SETLOWCOLUMN        0x00
#define SSD1306_SETHIGHCOLUMN       0x10
#define SSD1306_MEMORYMODE          0x20
#define SSD1306_COLUMNADDR          0x21
#define SSD1306_PAGEADDR            0x22
#define SSD1306_COMSCANINC          0xC0
#define SSD1306_SEGREMAP            0xA0
#define SSD1306_EXTERNALVCC         0x1
#define SSD1306_SWITCHCAPVCC        0x2
 
#define SSD1306_ACTIVATE_SCROLL                         0x2F
#define SSD1306_DEACTIVATE_SCROLL                       0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA                0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL                 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL                  0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL    0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL     0x2A
 
const uint8_t font[] = { // compact 5x8 font
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,0x00,0x00,0x00,0x07,0x00,0x07,0x00, //  'sp,!,"
    0x14,0x7F,0x14,0x7F,0x14, // #
    0x24,0x2A,0x7F,0x2A,0x12,0x23,0x13,0x08,0x64,0x62,0x36,0x49,0x56,0x20,0x50, //  '$,%,&
    0x00,0x08,0x07,0x03,0x00,0x00,0x1C,0x22,0x41,0x00,0x00,0x41,0x22,0x1C,0x00, //  '',(,)
    0x2A,0x1C,0x7F,0x1C,0x2A,0x08,0x08,0x3E,0x08,0x08,0x00,0x00,0x70,0x30,0x00, //  '*,+,,
    0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x60,0x60,0x00,0x20,0x10,0x08,0x04,0x02, //  '-,.,/
    0x3E,0x51,0x49,0x45,0x3E,0x00,0x42,0x7F,0x40,0x00,0x72,0x49,0x49,0x49,0x46, //  '0,1,2
    0x21,0x41,0x49,0x4D,0x33,0x18,0x14,0x12,0x7F,0x10,0x27,0x45,0x45,0x45,0x39, //  '3,4,5
    0x3C,0x4A,0x49,0x49,0x31,0x41,0x21,0x11,0x09,0x07,0x36,0x49,0x49,0x49,0x36, //  '6,7,8
    0x46,0x49,0x49,0x29,0x1E,0x00,0x00,0x14,0x00,0x00,0x00,0x40,0x34,0x00,0x00, //  '9,:,;
    0x00,0x08,0x14,0x22,0x41,0x14,0x14,0x14,0x14,0x14,0x00,0x41,0x22,0x14,0x08, //  '<,=,>
    0x02,0x01,0x59,0x09,0x06,0x3E,0x41,0x5D,0x59,0x4E,                          //  '?,@
    0x7C,0x12,0x11,0x12,0x7C,                                                   //  'A
    0x7F,0x49,0x49,0x49,0x36,0x3E,0x41,0x41,0x41,0x22,0x7F,0x41,0x41,0x41,0x3E, //  'B,C,D
    0x7F,0x49,0x49,0x49,0x41,0x7F,0x09,0x09,0x09,0x01,0x3E,0x41,0x41,0x51,0x73, //  'E,F,G
    0x7F,0x08,0x08,0x08,0x7F,0x00,0x41,0x7F,0x41,0x00,0x20,0x40,0x41,0x3F,0x01, //  'H,I,J
    0x7F,0x08,0x14,0x22,0x41,0x7F,0x40,0x40,0x40,0x40,0x7F,0x02,0x1C,0x02,0x7F, //  'K,L,M
    0x7F,0x04,0x08,0x10,0x7F,0x3E,0x41,0x41,0x41,0x3E,0x7F,0x09,0x09,0x09,0x06, //  'N,O,P
    0x3E,0x41,0x51,0x21,0x5E,0x7F,0x09,0x19,0x29,0x46,0x26,0x49,0x49,0x49,0x32, //  'Q,R,S
    0x03,0x01,0x7F,0x01,0x03,0x3F,0x40,0x40,0x40,0x3F,0x1F,0x20,0x40,0x20,0x1F, //  'T,U,V
    0x3F,0x40,0x38,0x40,0x3F,0x63,0x14,0x08,0x14,0x63,0x03,0x04,0x78,0x04,0x03, //  'W,X,Y
    0x61,0x59,0x49,0x4D,0x43,                                                   //  'Z
    0x00,0x7F,0x41,0x41,0x41,0x02,0x04,0x08,0x10,0x20,                          //  '[,\
    0x00,0x41,0x41,0x41,0x7F,0x04,0x02,0x01,0x02,0x04,0x40,0x40,0x40,0x40,0x40, //  '],^,_
    0x00,0x03,0x07,0x08,0x00,0x20,0x54,0x54,0x38,0x40,0x7F,0x28,0x44,0x44,0x38, //  '`,a,b
    0x38,0x44,0x44,0x44,0x28,0x38,0x44,0x44,0x28,0x7F,0x38,0x54,0x54,0x54,0x18, //  'c,d,e
    0x00,0x08,0x7E,0x09,0x02,0x0C,0x52,0x52,0x4A,0x3C,0x7F,0x08,0x04,0x04,0x78, //  'f,g,h
    0x00,0x44,0x7D,0x40,0x00,0x20,0x40,0x40,0x3D,0x00,0x7F,0x10,0x28,0x44,0x00, //  'i,j,k
    0x00,0x41,0x7F,0x40,0x00,0x7C,0x04,0x78,0x04,0x78,0x7C,0x08,0x04,0x04,0x78, //  'l,m,n
    0x38,0x44,0x44,0x44,0x38,0x7C,0x18,0x24,0x24,0x18,0x18,0x24,0x24,0x18,0x7C, //  'o,p,q
    0x7C,0x08,0x04,0x04,0x08,0x48,0x54,0x54,0x54,0x24,0x04,0x04,0x3F,0x44,0x24, //  'r,s,t
    0x3C,0x40,0x40,0x20,0x7C,0x1C,0x20,0x40,0x20,0x1C,0x3C,0x40,0x30,0x40,0x3C, //  'u,v,w
    0x44,0x28,0x10,0x28,0x44,0x4C,0x50,0x50,0x50,0x3C,0x44,0x64,0x54,0x4C,0x44, //  'x,y,z
    0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x77,0x00,0x00,0x00,0x41,0x36,0x08,0x00, //  '{,|,}
    0x02,0x01,0x02,0x04,0x02                                                    //  '~
    };
