#include <ClickEncoder.h>
#include <Arduino.h>
#include <FreqMeasure.h>
#include <TimerOne.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PID_v1.h>

#define FAN1PIN 10
#define RPMPIN 2

#define ENC_PIN_UP 3
#define ENC_PIN_DN 4
#define ENC_PIN_BTN 5


//number of seconds between LCD updates
#define UPDATE_SECS 0.5

//number of RPM measurments to average
#define RPM_AVG 5

//number of PID targets (one per temperature sensor)
#define TARGETS 3

//encoder setup
ClickEncoder *encoder;
int16_t last, value;

void timerIsr() {
  encoder->service();
}

// initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(LCD_PINS);
OneWire oneWire(4);
DallasTemperature sensors(&oneWire);

int numberOfDevices; // Number of temperature devices found

DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

int last_sec = 0;
int this_sec = 0;
int rpm_measurments [RPM_AVG];
unsigned short rpm = 0;
unsigned byte pos = 0;
double pid_targets[

void setup() {
  Timer1.initialize(40);  // 40 us = 25 kHz
  //HAVE THE FAN ON 100% TO BEGIN WITH
  Timer1.pwm(FAN1PIN, 1023);

  lcd.begin(20, 2);
  FreqMeasure.begin();
  sensors.begin();                    //Start Dallas 1 wire library
  tempSensors = sensors.getDeviceCount();

  encoder = new ClickEncoder(ENC_PIN_UP, ENC_PIN_DN, ENC_PIN_BTN);
}



void loop() {
  if (FreqMeasure.available()) {
    if(pos >= RPM_AVG)
      pos = 0
    rpm_measurments[pos] = FreqMeasure.read();
    pos++;
    //recalculate RPM
    rpm = 0;
    for(int i = 0; i < RPM_AVG; i++)
      rpm += rpm_measurments[i];
    rpm = rpm / RPM_AVG;
  }  
  
  
  //update the LCD once per second
  this_sec = millis/(1000 * UPDATE_SECS);
  if(this_sec != last_sec) {
    last_sec = this_sec;
  
    //print whatever we have to print
    //cursor is col,row
    lcd.setCursor(0, 0);
    lcd.print("RPM: ");
    lcd.print(rpm);
    lcd.setCursor(9,0);
    lcd.print(" TEMP: ");

    //each second print a different temperature. rotate based on how many sensors are connected
    lcd.print(sensors.getTempCByIndex(this_sec % number));
    lcd.print("°C");   

    //next row
    lcd.setCursor(0, 1);
    lcd.print("TRGT: ");
    lcd.print(










//junk
  
  sensors.requestTemperatures(); 
  
  //get temperatures
  for(int i=0;i<numberOfDevices; i++) {
    lcd.setCursor(0, 1);
    lcd.print(i);
    lcd.print(": ");
    lcd.print((int)(sensors.getTempCByIndex(i)));
    lcd.print("C");
    
  }
  //Print info to the LCD
    lcd.setCursor(0, 0);
    lcd.print("Fan: ");
    lcd.print(dutyCycle);
    lcd.print("%");
    lcd.setCursor(10, 0);
    lcd.print("RPM: ");
    lcd.print(half_revolutions);
    Timer1.pwm(FAN1PIN, (dutyCycle / 100) * 1023);
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print((int)(sensors.getTempFByIndex(0)));
    lcd.print("F");
  }
  
}
