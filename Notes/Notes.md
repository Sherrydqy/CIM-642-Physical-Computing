# 2019.01.24
### positive(+) and Negative(-)
-put the led on the ground -> Negative????

### Electricity will always follow the path of least resistance

creating a loop between + and - -> electrical circuit

- each band on a resistor represents a digit
- Current in an LED can only flows from the positive to the Negative
- How to tell the difference between Anode and Cathode in an LED?
1. positive: longer leg
2. ? [not sure] positive has ?flag piece cutout on it

### Serial Cable
like a USB, it sends serial message between the computer and the device

###Pins
- pin13-2: digital input/output pins. on/off
## Never connect anything to pin 1 and 0
pins 1,0 are communication pins. They have connections to different part of the board.
They also have connection to the USB serial portal. So if they are blocked, you cannot connect to a computer.

# 2019.01.31
- electricity circuit in pin 13 is specifically for LED

When you set a pin to voltage   pin13 can give a positive voltage

pin has two functions: 1. outlet plug  2. giving voltage

- Parallel circuit
- Series circuit: one down, all down <- downside
- Switch (btn) has two sides connection
- led 2 20 om resistor
- switch 10k om resistor

# 2019.02.07
### How do we dim a light using Arduino?
If you have duty cycle of 75%

5v   usually is power for switch, sensor, etc

* PW pin: ~pin#.
if not a PW pin, if you are over a specific value, it's gonna be considered as on, verse visa.

* potentiometer
 two pins at the top, one pin at the bottom.
 the pin at the bottom is linked to an analog pins
 two pins at the top. could be either + / -. so power / ground

 It can generate a gradual change. It's an analog sensor, it should be connected to pin A0-A5.
 It constantly ask arduino??1:13:14

 * pinMode(pin#, INPUT) is only for digital INPUT

 Here, to dim a light gradually, 其实是在用小矩形做近似，无限小的时候，模拟正弦函数的弧度

 * map的时候注意range，超出或者变成负数，都可能出现相反的结果

# 2019.02.14
phototransistor
photoresistor: no threshold
![](http://www.rfwireless-world.com/Terminology/Photoresistor-vs-Phototransistor.html)

### Whenever you are doing something with a sensor, always start with a baseline test to get an idea of what the current environment light/sound/temperature range is

* if you use delay(2000);
delay will stop the microcontroller for 2 secs, it stops everything. It stops to sense the input as well.

instead, you use millis()
* println() also slows down the Arduino

# 2019.02.21
- the maximum of the value the analogWrite() can go is 255

# 2019.02.28
knock Lock - solution: numberOfKnocks = 0;//add it to the last line

- music fountain, e.g Las Vegas Fountain, there's sensor? / engage and disengage?

# 2019.03.28

* HW
  * Finish the tutorials
  * design something used that sheet, the one from the top and another one from the bottom.
  * 3D print it

For 3D printer, you need to measure in MM (millimeters)
For CLC and the other machine in 1018, you need to measure an object in inches

Inner dimension claws (Top)
Outer dimension claws (Bottom)

cap for a button

*"3.4, give or take"*
*tolerance concept*

Solid works (a 3D printer software)

Parametric modeling (参数模型) - one measurement changes, it can automatically adjust the whole model

Top view is used in 3D printing.
So you should select sketch on the top plane - Because a 3D printer print things from the bottom to the top

constraints = anchor points telling whether they are intersect.

You never want use the exact measurement for 3D printing.
Because of thermal dynamic extension and stuff,
You need to add a tolerance
How do you do that? Set the caliper at the measurement that kind of bigger than the actual size, and put your button, for example, between the claws to see if it fits.

* Cura
try to print from angles, like you can use gravity towards your favor.
Profiles: choose 'fast'

**Support:** 如果你要打印一些悬空的东西
**Build Plate Adhesion:**
* Build Plate Adhesion Type:
  * Brim: 四周的
  * Skirt:

Manage Printer: connect. You can remote print to it if the 3D Printer has a wifi connectivity
