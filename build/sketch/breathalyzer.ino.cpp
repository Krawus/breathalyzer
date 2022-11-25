#include <Arduino.h>
#line 1 "d:\\Arduino_projects\\breathalyzer\\breathalyzer.ino"
//Arduino Nano
// SDA pin - A4
// SCL pin - A5

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "beer_frames.h"

#define SCREEN_WIDTH 128 //pixels
#define SCREEN_HEIGHT 32 //pixels
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
#define sensor_pin 6
#define button 12

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#line 20 "d:\\Arduino_projects\\breathalyzer\\breathalyzer.ino"
void setup();
#line 33 "d:\\Arduino_projects\\breathalyzer\\breathalyzer.ino"
void loop();
#line 51 "d:\\Arduino_projects\\breathalyzer\\breathalyzer.ino"
void warmup_screen(uint32_t duration);
#line 84 "d:\\Arduino_projects\\breathalyzer\\breathalyzer.ino"
void print_in_centre(String to_print, uint8_t line_num);
#line 99 "d:\\Arduino_projects\\breathalyzer\\breathalyzer.ino"
void print_reading(uint16_t sensor_reading);
#line 20 "d:\\Arduino_projects\\breathalyzer\\breathalyzer.ino"
void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS); 
  display.setTextColor(WHITE);        
  display.clearDisplay();
  warmup_screen(20000);
  display.display();
}

unsigned long act_time;
unsigned long timestamp = 0;
uint16_t sensor_read;

void loop()
{
  act_time = millis();

  if(act_time - timestamp >= 500)
  {
    display.clearDisplay();
    sensor_read = analogRead(sensor_pin);
    print_reading(sensor_read);
    
    display.display();

    timestamp = act_time;
  }
}

//~~~~~ FUNCTIONS

void warmup_screen(uint32_t duration)
{
  unsigned long act_time = millis();
  unsigned long measured_time = 0;
  unsigned long loop_enter_time = act_time;
  uint8_t frame_per = 20;
  display.invertDisplay(1);
  uint8_t frame_index=0;
  
  while(act_time - loop_enter_time < duration)
    {
      act_time = millis();

      if(act_time - measured_time >= frame_per)
      {
        display.clearDisplay();
      
        if(frame_index >18)
          frame_index = 0;

        display.drawBitmap(0,0, beer_frames[frame_index], SCREEN_WIDTH, SCREEN_HEIGHT, 1);
      
        display.display();
        measured_time = act_time;
        frame_index++;  
      }
    }
    
    display.invertDisplay(0);
    display.clearDisplay();
}


void print_in_centre(String to_print, uint8_t line_num)
{
  if(line_num > 7)
    line_num = 7;
  else if(line_num < 0)
    line_num = 0;

  int16_t x_bound, y_bound;
  uint16_t width, height;

  display.getTextBounds(to_print, 0, 0, &x_bound, &y_bound, &width, &height);
  display.setCursor((SCREEN_WIDTH - width)/2, line_num*4);
  display.println(to_print);
}

void print_reading(uint16_t sensor_reading)
{
  display.setTextSize(3);

    print_in_centre(String(sensor_read), 0);

    display.setTextSize(1);

    if(sensor_read <= 550)
      print_in_centre("you're pretty sober", 6);

    if((sensor_read > 550) && (sensor_read <= 650))
      print_in_centre("I smeel a beer", 6);

    if((sensor_read > 650) && (sensor_read <= 750) )
      print_in_centre("someone been drinkin'", 6);

    if((sensor_read > 750) && (sensor_read <= 900))
      print_in_centre("you drunk AF", 6);

    if(sensor_read > 900)
      print_in_centre("WASTED", 6);
}
