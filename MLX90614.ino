/********************************************************************************
   Descripción: Ejemplo para el sensor de temperatura  por infrarrojos MLX90614.
                El ejemplo también usa una pantalla OLED de 96 x 39 pixeles con
                un controlador I2C SSD1306.
                
   Placa Arduino: UNO
   Arduino IDE: 1.8.9

   www.firtec.com.ar
**********************************************************************************/
#include <SPI.h>
#include "oled.h"
#include <Wire.h>
#include <Adafruit_MLX90614.h>
 
#define OLED_CS         10
#define OLED_DC         6
#define OLED_RST        A3

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const char cartel_1 [] = {"TEMP."};
const char cartel_3 [] = {"AMBIENTE:"};
const char cartel_2 [] = {"OBJETO:"};
char buffer[10]=" ";
uint8_t _x, _y;
uint8_t _sx=1, _sy=1; 

 
void setup() {  
  SPI.begin();
  pinMode(OLED_CS, OUTPUT);
  pinMode(OLED_DC, OUTPUT);
  pinMode(OLED_RST, OUTPUT);
  OLED_Initialize();        // Configuración de la pantalla OLED
  delay(100);
  OLED_Clear();             // Borrado inicial de pantalla
  OLED_SetScale(1, 1);      // Letras en tamaño pequeño
  OLED_Puts(0, 1, cartel_2);// Muestras carteles iniciales
  OLED_Puts(0, 4, cartel_3);
  mlx.begin();              // Inicia el sensor MLX90614
}
 
void loop() {
  dtostrf(mlx.readObjectTempC(), 2, 1, buffer); // Temperatur del objeto pasada a ASCII
  OLED_SetScale(1, 3);                          // Cambia tamaño de letras
  OLED_Puts(60, 0, buffer);                     // Muestra la temperatura del objeto frente al sensor.
  OLED_SetScale(1, 1);                          // Cambia a letra pequeña
  dtostrf(mlx.readAmbientTempC(), 2, 1, buffer);// Lee y convierte a ASCII la tempertura ambiente
  OLED_Puts(65, 4, buffer);                     // Muesra la temperatura
  delay(500);
 
}
 
//------------ Funciones para la pantallas OLED -----------------
 
void OLED_Command(uint8_t temp){
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(OLED_CS,LOW);
  digitalWrite(OLED_DC,LOW);
  SPI.transfer(temp);
  digitalWrite(OLED_CS,HIGH);
  SPI.endTransaction();
}
 
void OLED_Data(uint8_t temp){
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(OLED_CS,LOW);
  digitalWrite(OLED_DC,HIGH);
  SPI.transfer(temp);
  digitalWrite(OLED_CS,HIGH);
  SPI.endTransaction();
}
 
void OLED_Initialize(void)
{
    digitalWrite(OLED_RST,LOW);
    delay(1000);
    digitalWrite(OLED_RST,HIGH);
    delay(1000);
    OLED_Command(SSD1306_DISPLAYOFF);             //0xAE  Set OLED Display Off
    OLED_Command(SSD1306_SETDISPLAYCLOCKDIV);     //0xD5  Set Display Clock Divide Ratio/Oscillator Frequency
    OLED_Command(0x80);
    OLED_Command(SSD1306_SETMULTIPLEX);           //0xA8  Set Multiplex Ratio
    OLED_Command(39);
 
    OLED_Command(SSD1306_SETSEGMENTREMAP);        //0xA1  Set Segment Remap Inv
    OLED_Command(SSD1306_COMSCANDEC);             //0xC8  Set COM Output Scan Inv
 
    OLED_Command(SSD1306_SETDISPLAYOFFSET);       //0xD3  Set Display Offset
    OLED_Command(0x00);
    OLED_Command(SSD1306_CHARGEPUMP);             //0x8D  Set Charge Pump
    OLED_Command(0x14);                           //0x14  Enable Charge Pump
    OLED_Command(SSD1306_SETSTARTLINE);           //0x40  Set Display Start Line
    OLED_Command(SSD1306_SETCOMPINS);             //0xDA  Set COM Pins Hardware Configuration
    OLED_Command(0x12);
    OLED_Command(SSD1306_SETCONTRAST);            //0x81   Set Contrast Control
    OLED_Command(0xAF);
    OLED_Command(SSD1306_SETPRECHARGE);           //0xD9   Set Pre-Charge Period
    OLED_Command(0x25);
    OLED_Command(SSD1306_SETVCOMDETECT);          //0xDB   Set VCOMH Deselect Level
    OLED_Command(0x20);
    OLED_Command(SSD1306_DISPLAYALLON_RESUME);    //0xA4   Set Entire Display On/Off
    OLED_Command(SSD1306_NORMALDISPLAY);          //0xA6   Set Normal/Inverse Display
    OLED_Command(SSD1306_DISPLAYON);              //0xAF   Set OLED Display On
} 
 
void OLED_SetRow(uint8_t add)
{
    add = 0xB0 | add;
    OLED_Command(add);
}
 
void OLED_SetColumn(uint8_t add)
{
    add += 32;
    OLED_Command((SSD1306_SETHIGHCOLUMN | (add >> 4))); // SET_HIGH_COLUMN
    OLED_Command((0x0f & add));                         // SET LOW_COLUMN
}
 
void OLED_PutPicture(const uint8_t *pic)
{
    unsigned char i,j;
    for(i=0; i<5; i++) 
    {
        OLED_SetRow(i);
        OLED_SetColumn(0);
        for(j=0; j<96; j++) 
        {
            OLED_Data(*pic++);
        }
    }
}
 
void OLED_SetContrast(uint8_t temp)
{
    OLED_Command(SSD1306_SETCONTRAST);
    OLED_Command(temp);                  
}
 
void OLED_SetScale(uint8_t sx, uint8_t sy){
    _sx = sx; _sy = sy;
}
 
void OLED_Clear(void)
{
    unsigned char i,j;
    for(i=0; i<5; i++) 
    {
        OLED_SetRow(i);
        OLED_SetColumn(0);
        for(j=0; j<96; j++)  OLED_Data(0);
    }
    _x = 0; _y = 0;
    OLED_SetRow(0);
    OLED_SetColumn(0);
}

void OLED_Putchar(char ch)
{
    uint8_t i, j, k, byte;
    const uint8_t *f = &font[(ch-' ')*5];
    const uint8_t mask[]={1, 3, 7, 0xf };
 
    for(i=0; i<6; i++) {
        uint32_t word;
        byte = *f++ << 1;
        if (i==5) byte = 0;
        for(j=0; j<8; j++) { 
            word <<= _sy;
            if (byte & 0x80) word |= mask[_sy-1];
            byte <<= 1;
        }
        for(j=0; j<_sy; j++){ 
            OLED_SetRow(_y+j) ;
            OLED_SetColumn(_x+i*_sx);
            for(k=0; k<_sx; k++){ 
                OLED_Data(word);
            }
            word >>= 8;
        }
    }
 
    _x+= 6 * _sx;
    if (_x >= OLED_WIDTH) { 
        _x = 0; OLED_SetColumn(0);
        _y += _sy;
        if (_y >= 5-_sy) { 
            _y = 0;
        }
        OLED_SetRow(_y);
    }
}
 
void OLED_Puts(char x, char y, char *s)
{
    _y = y; _x = x;
    OLED_SetRow(_y);
    OLED_SetColumn(_x);
    while(*s) {
        OLED_Putchar(*s++);
        _x++;
    }
}
