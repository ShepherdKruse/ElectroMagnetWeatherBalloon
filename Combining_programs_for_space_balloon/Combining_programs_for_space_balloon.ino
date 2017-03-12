#include<dht.h>
#include <stdint.h>
#include <SparkFunBME280.h>
#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
File myFile;
int pinCS = 53; // Pin 10 on arduino
BME280 mySensor;
dht DHT;
#define DHT11_PIN 6
RTC_DS3231 rtc;

void setup()

{
  
  Serial.begin(9600); 
  pinMode(pinCS, OUTPUT);
if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  
  // Create/Open file 
  myFile = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Writing to file...");
    // Write to file
    myFile.println("Testing text 1, 2 ,3...");
    myFile.close(); // close the file
    Serial.println("Done.");
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
  // Reading the file
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("Read:");
    // Reading the whole file
    while (myFile.available()) {
      Serial.write(myFile.read());
   }
    myFile.close();
  }
  else {
    Serial.println("error opening test.txt");
  }
  
  
  {
    //Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
   //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
   //rtc.adjust(DateTime(2017, 3, 11, 15, 26, 30 ));
}
  {
  
  mySensor.settings.commInterface = I2C_MODE;
  mySensor.settings.I2CAddress = 0x76;
  mySensor.settings.runMode = 3; //Normal mode
  mySensor.settings.tStandby = 0;
  mySensor.settings.filter = 0;
  mySensor.settings.tempOverSample = 1;
  mySensor.settings.pressOverSample = 1;
  mySensor.settings.humidOverSample = 1;

  //Calling .begin() causes the settings to be loaded
  delay(10);  //Make sure sensor had enough time to turn on. BME280 requires 2ms to start up.
  Serial.print(mySensor.begin(), HEX);
  Serial.print(mySensor.readRegister(BME280_CHIP_ID_REG), HEX);
  Serial.print(mySensor.readRegister(BME280_RST_REG), HEX);
  Serial.print(mySensor.readRegister(BME280_CTRL_MEAS_REG), HEX);
  Serial.print(mySensor.readRegister(BME280_CTRL_HUMIDITY_REG), HEX);
  uint8_t memCounter = 0x80;
  uint8_t tempReadData;
  for(int rowi = 8; rowi < 16; rowi++ )
  {
   
    Serial.print(rowi, HEX);
    for(int coli = 0; coli < 16; coli++ )
    {
      tempReadData = mySensor.readRegister(memCounter);
      Serial.print((tempReadData >> 4) & 0x0F, HEX);//Print first hex nibble
      Serial.print(tempReadData & 0x0F, HEX);//Print second hex nibble
      memCounter++;
    }
 
  }
  Serial.print(mySensor.calibration.dig_T1);
  Serial.print(mySensor.calibration.dig_T2);
  Serial.print(mySensor.calibration.dig_T3);
  Serial.print(mySensor.calibration.dig_P1);
  Serial.print(mySensor.calibration.dig_P2);
  Serial.print(mySensor.calibration.dig_P3);
  Serial.print(mySensor.calibration.dig_P4);
  Serial.print(mySensor.calibration.dig_P5);
  Serial.print(mySensor.calibration.dig_P6);
  Serial.print(mySensor.calibration.dig_P7);
  Serial.print(mySensor.calibration.dig_P8);
  Serial.print(mySensor.calibration.dig_P9);
  Serial.print(mySensor.calibration.dig_H1);
  Serial.print(mySensor.calibration.dig_H2);
  Serial.print(mySensor.calibration.dig_H3);
  Serial.print(mySensor.calibration.dig_H4);
  Serial.print(mySensor.calibration.dig_H5);
  Serial.print(mySensor.calibration.dig_H6);
  Serial.print("");
}
lcd.begin(16,2);
  for(int i = 0; i< 3; i++)
  {
  
  lcd.println("DHT11");
  delay(5000);
  lcd.clear();
    int chk = DHT.read11(DHT11_PIN);
    lcd.setCursor(0,0);
    lcd.println("Temperature:");
    lcd.setCursor(0,1);
    lcd.println(DHT.temperature, 1);
    delay(2000);
    lcd.clear();
    lcd.println("Humidity)
    
  }

    }
  
void loop()
{
  

  DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print("  ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.print("   ");
    delay(100);
  Serial.print("Temperature: ");
  Serial.print(mySensor.readTempF(), 2);
  Serial.print(" degrees F  ");
  Serial.print("Pressure: ");
  Serial.print(mySensor.readFloatPressure(), 2);
  Serial.print(" Pa  ");
  Serial.print("Altitude: ");
  Serial.print(mySensor.readFloatAltitudeFeet(), 2);
  Serial.print(" ft  "); 
  delay(100);
  int chk = DHT.read11(DHT11_PIN);
Serial.print(DHT.humidity, 1);
Serial.print("%  ");
Serial.print(DHT.temperature, 1);
Serial.println("C ");
delay(10000);


  }







