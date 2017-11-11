# Ultimate Fox Deterrent

> Flashes LEDs and makes noise when a fox is near

## Parts list

- Arduino Uno
- DS3231 for time keeping
- HC-SR501 for motion sensing x4
- 5V 5050 LED strip
- Solar panel
- Battery
- USB / DC / Solar Lithium Ion/Polymer charger - v2 - [here](https://www.adafruit.com/product/390)

# Power Calculations
## Charge

### Best case sunny day

Medium solar panel - 6V 2W = 333.3 mA

Huge solar panel - 6V 6W = 1000 mA

## Arduino

Arduino Uno 16Hz Sleep enabled - 3.14 mA

Arduino Uno 16Hz No Sleep - 19.9 mA

## Battery
2500 mAh

### Time for full charge

#### Medium Solar Panel

2500 mAh / 333.3 * 1.2 (for inefficiency) = 9 hours

#### Huge Solar Panel

2500 mAh / 1000 * 1.2 (for inefficiency) = 3 hours

## How long will it last

### No Solar
#### No Sleep

2500 mAh / 19.9 mA * 0.7 (For inefficiency) = 87.9 hours

#### Sleep

2500 mAh / 3.14 mA * 0.7 (For inefficiency) = 557.3 hours

## Conclusion

If the rate of charge exceeds the rate of usage, it should be fine?

# Sources

http://www.home-automation-community.com/arduino-low-power-how-to-run-atmega328p-for-a-year-on-coin-cell-battery/

https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-battery-life

https://www.convertunits.com/from/watt/volt/to/mA

http://www.csgnetwork.com/batterychgcalc.html
