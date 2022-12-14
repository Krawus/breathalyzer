#line 1 "d:\\Arduino_projects\\breathalyzer\\README.md"
# breathalyzer - work in progress...
## Components
- Arduino nano
- 0.91" OLED with I2C interface
- MQ-3 alcohol sensor
- power source - 9V battery

## Electrical diagram

![circut](images/schematic.png)



## Wiring the prototype
To start programming I firstly built a prototype using breadboard. (I skipped the switch which cut the power off, because during programming I am powering whole device via USB)

![components](images/components.jpg)
![wired_breadboard](images/wired_prototype.jpg)

## Programming

According to datasheet first important thing is preheat the sensor, so I set the preheat time to 2minutes (after 2 minutes sensor reading has stopped decreasing).
For the preheat time I proggramed a fancy animated loading screen.

![warming_gif](images/warming_screen.gif)

After this I used simple analog read to read the value from sensor every 500ms. I am using millis() function to measure time between program loops - thanks to this I won't stop whole program using delay() function (multithreading 😎).

To print every text horizontally centered I created the `print_in_centre()` function.

![printed_in_centre](images/printed_text.png)

Everything printed on the screen is managed by `print_reading()` function.

It's really hard to calibrate properly this sensor - so it could show per mille value. By now I just calibrated it as good as I am able to in my home conditions. I designed housing in such a way that I will be able to calibrate it in the future if needed.

