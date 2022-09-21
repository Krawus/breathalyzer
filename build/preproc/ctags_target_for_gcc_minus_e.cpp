# 1 "d:\\alkomat\\breathalyzer\\breathalyzer.ino"
//Arduino Nano
// SDA pin - A4
// SCL pin - A5

# 6 "d:\\alkomat\\breathalyzer\\breathalyzer.ino" 2
# 7 "d:\\alkomat\\breathalyzer\\breathalyzer.ino" 2
# 8 "d:\\alkomat\\breathalyzer\\breathalyzer.ino" 2
# 9 "d:\\alkomat\\breathalyzer\\breathalyzer.ino" 2
# 10 "d:\\alkomat\\breathalyzer\\breathalyzer.ino" 2
# 18 "d:\\alkomat\\breathalyzer\\breathalyzer.ino"
Adafruit_SSD1306 display(128 /*pixels*/, 32 /*pixels*/, &Wire, -1);

void setup()
{
  display.begin(0x02 /*|< Gen. display voltage from 3.3V*/, 0x3C);
  display.setTextColor(1 /*|< Draw 'on' pixels*/ /*|< Draw 'on' pixels*/);
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
    sensor_read = analogRead(6);
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

        display.drawBitmap(0,0, beer_frames[frame_index], 128 /*pixels*/, 32 /*pixels*/, 1);

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
  display.setCursor((128 /*pixels*/ - width)/2, line_num*4);
  display.println(to_print);
}
