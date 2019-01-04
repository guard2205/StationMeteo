/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/
#include "SparkFunBME280.h"
#include "Wire.h"
#include "SPI.h"
//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

BME280 capteur;


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define SSD1306_LCDHEIGHT 64 // ligne ajoutée

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);
  
      //configuration du capteur
      capteur.settings.commInterface = I2C_MODE; 
      capteur.settings.I2CAddress = 0x76;
      capteur.settings.runMode = 3; 
      capteur.settings.tStandby = 0;
      capteur.settings.filter = 0;
      capteur.settings.tempOverSample = 1 ;
      capteur.settings.pressOverSample = 1;
      capteur.settings.humidOverSample = 1;
     
      delay(10);  // attente de la mise en route du capteur. 2 ms minimum
      // chargement de la configuration du capteur
      capteur.begin();
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  
}


void loop() {
  display.setTextSize(1);
  display.setTextColor(WHITE, WHITE);
  display.setCursor(0,0);
  display.print("P : ");

  display.print(capteur.readFloatPressure());
  display.println(" Pa");

  display.print("T : ");
  display.print(capteur.readTempC()/*, .2*/);
  display.println(" C");

  display.print("H : ");
  display.print(capteur.readFloatHumidity());
  display.println(" %");
  
  Serial.print(capteur.readFloatPressure());
  Serial.print(";");
  Serial.print(capteur.readTempC());
  Serial.print(";");
  Serial.print(capteur.readFloatHumidity());
    Serial.print(";");

  display.display();
  delay(1000);
  display.clearDisplay();
}


