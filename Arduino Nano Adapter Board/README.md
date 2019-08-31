SNES to CDi Arduino Nano Board
------------------------------

This version of the SNES to CDi is based on a board that you can have built at a board prototyping company and combine with an Arduino Nano to have an adapter to allow you to connect your CD-i to a SNES controller or compatible third party controller.  Using an 8Bitdo wireless SNES controller is a great way to enjoy a high quality wireless controller with your CD-i.  This is a great way to make your Arduino SNES to CD-i adapter permanant!

Code Changes from the Base Arduino Version
------------------------------------------

The board layout was simplified by using different pins than Laurent used in the original sketch.  Otherwise the code is the same.

However, and this may just be my player, but the adapter does not work from the rear controller port unless I reduce the firstId delay to under 100, in fact closer to 1.  The rear port is preferable in order to have the adapter plugged in to the console all the time and not be in the way.  The ATtiny85 version of the board does not have this issue.

The sketch in this directory has the correct pins set for this board, but the differences are as follows:
1. SNESpad uses 11, 10, and 12 for latch, clock, and data, instead of 5, 6, and 7
2. SoftwareSerial uses 8 and 9 for RX and TX instead of 9 and 10
3. RTSpin remains the same

How to make your own adapter
----------------------------

If you wish to create your own board, a schematic that this code is compatible with is provided here.

If you wish to just use the board I designed, you can use the supplied gerber files to submit for a board order from a prototyping service such as OSH Park or JLCPCB.  Keep in mind that OSH Park has a minimmum order size of 3 boards, and JLCPCB has a minimum order size of 5 boards.  So when you buy the components to make one, feel free to buy a couple more sets and either have multiple adapters or give one to a friend!

This board has 3 seperate components (From left to right):

1. An 8 pin mini din connector (Connects to the CD-i)
2. An Arduino Nano (Optionally socketed)
3. A JST XH connector.  (Optionally you can solder the SNES extension cable directly to these holes)

You'll need to provide an 8 pin mini din cable to connect the CD-i to this adapter, and you will also need a SNES extension cable that will be cut and soldered or crimped to a connector to provide a SNES controller interface to this board.

All parts are through hole components, so it should be easy soldering.

I bought a JST XH crimper and a big box of JST XH pins, adapters, and plugs on amazon for cheap.  The rest of the components I ordered from digikey.

For the complete bill of materials for the board:
1. 8 pin mini din connector - Digikey part number: CP-5080-ND, Manufacturer part number: MD-80SG
2. 5 pin JST XH Adapter - Digikey part number: 455-2270-ND, Manufacturer part number: B5B-XH-A(LF)(SN)
3. 5 pin JST XH Housing - Digikey part number: 455-2268-ND, Manufacturer part number: XHP-5
4. 5x JST XH Pin Connector - Digikey part number: 455-2261-1-ND, Manufacturer part nubmer: SXH-002T-P0.6
5. Arduino Nano (And headers if not pre-soldered)
6. SNES Extension Cable
7. 8 pin mini din to 8 pin mini din cable
8. (Optional) 2x 15 pin header - Digikey part number: S7048-ND, Manufacturer part number: PPPC151LFBN-RC

When assembling the board, solder the smallest to largest components in order.

I usually do it in this order:
1. JST XH Adapter
2. Arduino Socket Headers
3. 8 pin mini din connector

It is important to note that if you are using the case below, that the Arduino Nano will block the top cover from closing if you are using the socket headers AND you have the 2x3 pin ISP header attached to the rear of the Arduino Nano.  You can either desolder the ISP header, or you can use regular 2.45mm pin headers to attach the arduino to the board permanantly.

The case this board goes into:
1. BUD Industries PT-11664 Style H Plastic Box, 6" Length x 4" Width x 1-7/64" Height, Black
2. You will also need 4x #4-24 Thread 1/4" length screws (Sold Seperately)

After screwing the board into the case, you'll want to use a pair of snips or a knife to cut the plastic of the case so you can plug the connectors in.
I don't have a great way of mounting the SNES connector, so I made the hole in the case the size of the thinner part of the SNES connector, so that when the controller mates to the adapter you can push them together as you see in the pictures.

Some parts must be facing the correct orientation.

Part Orientation:
1. 8 pin mini din: Only goes in one way
3. Header Pins: Any orientation
4. Arduino Nano: Must be orientated so the usb connector matches the small box on the outline
5. JST XH Adapter: The side with cut outs for the XH housing to mate with must be facing the outside of the board

The completed adatper will look like this when screwed into the case:
![The Assembled SNES to CD-i Adapter](https://github.com/larryerb/SNEStoCDi/blob/master/Arduino%20Nano%20Adapter%20Board/images/Completed_Adapter.jpg)

Create the SNES adapter cable:
1. Take the SNES extension cable and cut the end that the controller plugs into around 6 to 8 inches (15 to 20 centimeters) from the connector
2. Strip the outer insulation back by a couple centimeters, and then strip the ends of each of the smaller wires by 5 or 6 milimeters
3. Using a multimeter in continuity mode, confirm which wire goes to which pin on the connector, and write down the color of the wire and which pin it connects to
   The SNES controller pinout goes like this:
    `(+5V)(CLOCK)(LATCH)(DATA) | (NC)(NC)(GND)`
   The connections on the board are labeled in the same order.
4. Either crimp the pin connectors on each of the wires from the adapter and insert them into the XH housing in the correct order, or solder the wires directly into the correct holes

The crimped cable should look something like this:
![Crimped Cable](https://github.com/larryerb/SNEStoCDi/blob/master/Arduino%20Nano%20Adapter%20Board/images/Crimped_Connector.jpg)

How to build and flash the code
-------------------------------

Follow Laurent's instructions from the base Arduino Adapter, but select Arduino Nano as the target board

The completed adapter hooked up to an 8Bitdo wireless snes controller looks like this:
![The completed SNES to CD-i Adapter](https://github.com/larryerb/SNEStoCDi/blob/master/Arduino%20Nano%20Adapter%20Board/images/Adapter_In_Action.jpg)

Future Improvements
-------------------

This board is cool but way bigger than it needs to be.  The massive ground planes on the top and bottom make soldering more complicated than it needs to be.  I started creating the ATtiny85 version shortly after finishing this version just to try and make something smaller and cheaper.  However, since this board actually has a case and works perfectly good enough, it ended up being the version I use day to day, and probably will be the one that most people would choose to make for themselves.

It would be nice to redesign the board to be a little smaller while still fitting into the case, and also it would be nice to have a way to firmly secure the SNES adapter to the case so you could swap controllers without having to unscrew the case.