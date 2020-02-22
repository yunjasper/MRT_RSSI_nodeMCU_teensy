# McGill Rocket Team Avionics 2020 - RSSI Receiver to nodeMCU v0.9 and Teensy 3.5

Contains the code to be run on the nodeMCU v0.9. Note that this code was developed using PlatformIO (hence all the folders).

Pinout of nodeMCU:

- D1 to LED (indicate whether nodeMCU is active)
- 3V to Teensy 3.5 pin 3.3V out
- RX to Teensy 3.5 pin 1 (TX1)
- TX to voltage divider (1 kOhm and 560 Ohm), then to Teensy 3.5 pin 0 (RX1)
- VIN to 4.40V power supply
- GND to GND
