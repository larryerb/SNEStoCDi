SNES to CDi ATtiny85
--------------------

This version of the SNES to CDi is based on a small board that you can have built at a board prototyping company and combine with a few dollars in parts to can have a small adapter to allow you to connect your CD-i to a SNES controller or compatible third party controller.  Using an 8Bitdo wireless SNES controller is a great way to enjoy a high quality wireless controller with your CD-i.

How to make your own SNEStoCDiATtiny85 adapter
----------------------------------------------

If you wish to create your own board, a schematic that this code is compatible with is provided here.

If you wish to just use the board I designed, you can use the supplied gerber files to submit for a board order from a prototyping service such as OSH Park or JLCPCB.  Keep in mind that OSH Park has a minimmum order size of 3 boards, and JLCPCB has a minimum order size of 5 boards.  So when you buy the components to make one, feel free to buy a couple more sets and either have multiple adapters or give one to a friend!

This board has 5 seperate components (From left to right):

1. An 8 pin mini din connector (Connects to the CD-i)
2. A Microchip (Formely Atmel) ATtiny85 microcontroller (Optionally socketed)
3. A 100nf decoupling capacitor
4. A 6 pin AVR ISP header (So you can program the chip without removing it from the socket, or if you solder the microcontroller directly)
5. A JST XH connector.  (Optionally you can solder the SNES extension cable directly to these holes)

You'll need to provide an 8 pin mini din cable to connect the CD-i to this adapter, and you will also need a SNES extension cable that will be cut and soldered or crimped to a connector to provide a SNES controller interface to this board.

All parts are through hole components, so it should be easy soldering.

I bought a JST XH crimper and a big box of JST XH pins, adapters, and plugs on amazon for cheap.  The rest of the components I ordered from digikey.

For the complete bill of materials:
1. 8 pin mini din connector - Digikey part number: CP-5080-ND, Manufacturer part number: MD-80SG
2. ATtiny85 - Digikey part number: ATTINY85-20PU-ND, Manufacturer part number: ATTINY85-20PU
3. 5 pin JST XH Adapter - Digikey part number: 455-2270-ND, Manufacturer part number: B5B-XH-A(LF)(SN)
4. 5 pin JST XH Housing - Digikey part number: 455-2268-ND, Manufacturer part number: XHP-5
5. 5x JST XH Pin Connector - Digikey part number: 455-2261-1-ND, Manufacturer part nubmer: SXH-002T-P0.6
6. 100nf Through hole ceramic capicitor, lead spacing 0.200in / 5.08mm - Digikey part number: 399-9877-2-ND, Manufacturer part number: C322C104K5R5TA7301 
7. 2x3 Header pins, 2.54mm spacing - Digikey part number: 952-2121-ND, Manufacturer part number: M20-9980346
8. SNES Extension Cable
9. 8 pin mini din to 8 pin mini din cable
10. (Optional) 8 pin (2x4) chip socket - Digikey part number: ED90032-ND, Manufacturer part number: 110-43-308-41-001000

When assembling the board, solder the smallest to largest components in order.

I usually do it in this order:
1. Chip Socket
2. Decoupling capacitor
3. JST XH Adapter
4. Header Pins
5. 8 pin mini din connector

Some parts must be facing the correct orientation.

Part Orientation:
1. 8 pin mini din: Only goes in one way
2. Decoupling capacitor: Any orientation
3. Header Pins: Any orientation
4. ATtiny85: pin one 'dot' on the microcontroller must be facing the side of the chip outline that has the small "bite" out of it
5. JST XH Adapter: The side with cut outs for the XH housing to mate with must be facing the inside of the board

The completed adatper will look like this, next to an unpopulated board front and back for comparison:
![The Assembled SNES to CD-i Adapter](https://github.com/larryerb/SNEStoCDi/blob/master/sketchSNEStoCDiAtTiny85/Assembled.jpg)

Create the SNES adapter cable:
1. Take the SNES extension cable and cut the end that the controller plugs into around 6 to 8 inches (15 to 20 centimeters) from the connector
2. Strip the outer insulation back by a couple centimeters, and then strip the ends of each of the smaller wires by 5 or 6 milimeters
3. Using a multimeter in continuity mode, confirm which wire goes to which pin on the connector, and write down the color of the wire and which pin it connects to
   The SNES controller pinout goes (+5V)(CLOCK)(LATCH)(DATA) | (NC)(NC)(GND)
   The connections on the board are labeled in the same order.
4. Either crimp the pin connectors on each of the wires from the adapter and insert them into the XH housing in the correct order, or solder the wires directly into the correct holes

The crimped cable should look something like this:
![Crimped Cable](https://github.com/larryerb/SNEStoCDi/blob/master/sketchSNEStoCDiAtTiny85/Crimped_Connector.jpg)

How to build and flash the code
-------------------------------

You can use an arduino or a USB to AVR ISP programmer to flash this board.  You'll need the Arduino IDE to compile this sketch file and upload it to the ATtiny85.

I followed this guide to set up the Arduino IDE to program the ATtiny85:
https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829

With the Arduino IDE, if you are uploading the sketch to the ATtiny85 for the first time, you will have to ensure the clock speed is set to "16 MHz" and run "Burn Bootloader" before using the adapter for the first time.  Otherwise the adapter will run at 1 MHz and not work.

The arduino board flasher I built to program the adapter looks like this:
![Flashing the board](https://github.com/larryerb/SNEStoCDi/blob/master/sketchSNEStoCDiAtTiny85/Flashing.jpg)

The 6 pin ISP header cable and breadboard adapter were bought from Adafruit

The arduino board flasher I built to program the adapter looks like this:
![The completed SNES to CD-i Adapter](https://github.com/larryerb/SNEStoCDi/blob/master/sketchSNEStoCDiAtTiny85/Completed_Adapter.jpg)

Future Improvements
-------------------

This board is cool but it has no housing!  I'll see if I can't either find a housing and redo the board to match it or 3d print something.  If you are handy with a 3d printer and 