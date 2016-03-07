#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SchedulerLCD.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SchedulerLCD<LiquidCrystal_I2C> schedule(&lcd);

String mystring;
float temp = 30.5;

void setup()
{
  lcd.begin();
  lcd.backlight();


  // è possibile saltare questa chiamata
  // di default viene settato un timer di 2000 millisecondi cioè 2 secondi
  schedule.setTimer(1000); // tempo tra una print e la successiva in milliSecondi
}

void loop()
{
  mystring = "Temp: " + (String)temp;

  schedule.print("Rilevata", mystring.c_str(), "\0");
  schedule.print("Prima riga", "\0");
  schedule.print("", "Seconda riga", "\0");
  schedule.print("AreaCom", "SchedulerLCD", "\0");
  schedule.print("Hello", "World!", "\0");

  schedule.reset();
}
