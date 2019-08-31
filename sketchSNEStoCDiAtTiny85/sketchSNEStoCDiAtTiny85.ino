
/*******************************
 *
 *  File: sketchSNEStoCDiAtTiny85.ino
 *  Description: software for the AtTiny85 based SNEStoCDi gamepad converter (allows to use a Nintendo SNES/SFC gamepad on a Philips CDi)
 *  Author: Lawrence Erb
 *  Date: 07-01-2019
 *  Version: 1.0
 *  Thanks: Laurent Berta (Original sketchSNEStoCDi code and arduino schematics), Rob Duarte (SNESpad library), Paul Hackmann (documentation about the CDi pointing devices)
 *  License: CC-BY 4.0 ( http://creativecommons.org/licenses/by/4.0/legalcode )
 *
 ******************************/

#include <SendOnlySoftwareSerial.h>
#include <SNESpad.h>
#include <EEPROM.h>

SNESpad pad = SNESpad(1, 2, 0); // Create a SNESpad instance, change the pin values to match your wiring (latch, clock, data)
SendOnlySoftwareSerial vSerial(4, true); // TX, inverse_logic. No RX needed as the CDi only communicates via the RTS line.  Connects to the RXD pin on the console.
const int RTSpin = 3; // the number of the analog pin used to receive the RTS signal from the CDi

const int RTSthreshold = 328; // threshold for the CDi RTS analog detection
uint16_t btns;
bool btnRpressed = false;
int padbyte0, padbyte1, padbyte2, oldpadbyte0, oldpadbyte1, oldpadbyte2, x, y;
byte spd;
bool firstId = true;
bool btnLpressed = false;
bool btnSEpressed = false;
bool standardMapping = true;

// init
void setup()
{
  oldpadbyte0 = 0;
  oldpadbyte1 = 0;
  oldpadbyte2 = 0;

  byte eepromData = EEPROM.read(0); // retrieve speed setting from the Arduino's EEPROM
  if(eepromData >= 1 && eepromData <= 5) spd = eepromData;
  else spd = 3;
  
  vSerial.begin(1200); // open serial interface to send data to the CDi
}

// main
void loop()
{
  if(analogRead(RTSpin) < RTSthreshold) {
    while(analogRead(RTSpin) < RTSthreshold) { } // wait for CDi to assert the RTS line
    if(firstId) delay(100);
    else delay(1);
    firstId = false;
    vSerial.write(0b11001010); // send device id ("maneuvering device")
  }

  // Get the state of the SNES pad buttons
  btns = pad.buttons();

  // manage speed control
  if(btns & SNES_R) {
    if(!btnRpressed) changeSpeed(spd+1); // speed : up
    btnRpressed = true;
  }
  else btnRpressed = false;
  if(btns & SNES_L) {
    if(!btnLpressed) changeSpeed(spd-1); // speed : down
    btnLpressed = true;
  }
  else btnLpressed = false;
  if(btns & SNES_START) changeSpeed(3); // speed : default (3)

  padbyte0 = 0b11000000;  //initialize data bytes
  padbyte1 = 0b10000000;
  padbyte2 = 0b10000000;

  // Dpad X axis
  x = 127;
  if(btns & SNES_LEFT) {
    switch (spd) {
      case 5:
        x = 254;
        break;
      case 4:
        x = 170;
        break;
      case 3:
        x = 149;
        break;
      case 2:
        x = 139;
        break;
      case 1:
        x = 130;
        break;
    }
  }
  if(btns & SNES_RIGHT) {
    switch (spd) {
      case 5:
        x = 1;
        break;
      case 4:
        x = 85;
        break;
      case 3:
        x = 106;
        break;
      case 2:
        x = 116;
        break;
      case 1:
        x = 125;
        break;
    }
  }
  
  if(x<127) // right
  {
    x = x ^ 0b01111111;
    x = x + 1;
    padbyte1 = padbyte1 | x;
    padbyte1 = padbyte1 & 0b10111111;
    if((x & 0b01000000) != 0)
      padbyte0 = padbyte0 | 0b00000001;
  }
  else if(x>127) // left
  {
    x = x ^ 0b01111111;
    x = x + 1;
    padbyte1 = padbyte1 | x;
    padbyte1 = padbyte1 & 0b10111111;
    if((x & 0b01000000) != 0)
      padbyte0 = padbyte0 | 0b00000011;
    else
      padbyte0 = padbyte0 | 0b00000010; 
  }

  // Dpad Y axis
  y = 127;
  if((btns & SNES_UP) || (btns & SNES_A)) { make A button also trigger dpad up to make games where up is jump a little more fun
    switch (spd) {
      case 5:
        y = 254;
        break;
      case 4:
        y = 170;
        break;
      case 3:
        y = 149;
        break;
      case 2:
        y = 139;
        break;
      case 1:
        y = 130;
        break;
    }
  }
  if(btns & SNES_DOWN) {
    switch (spd) {
      case 5:
        y = 1;
        break;
      case 4:
        y = 85;
        break;
      case 3:
        y = 106;
        break;
      case 2:
        y = 116;
        break;
      case 1:
        y = 125;
        break;
    }
  }

  if(y<127) // down
  {
    y = y ^ 0b01111111;
    y = y + 1;
    padbyte2 = padbyte2 | y;
    padbyte2 = padbyte2 & 0b10111111;
    if((y & 0b01000000) != 0)
      padbyte0 = padbyte0 | 0b00000100;
  }
  else if(y>127) // up
  {
    y = y ^ 0b01111111;
    y = y + 1;
    padbyte2 = padbyte2 | y;
    padbyte2 = padbyte2 & 0b10111111;
    if((y & 0b01000000) != 0)
      padbyte0 = padbyte0 | 0b00001100;
    else
      padbyte0 = padbyte0 | 0b00001000;
  }

  // buttons
  if(btns & SNES_SELECT) {
    if(!btnSEpressed) standardMapping = !standardMapping; // mapping change : invert buttons 1 & 2 (Y & B)
    btnSEpressed = true;
  }
  else btnSEpressed = false;
  if(standardMapping) {
    if(btns & SNES_Y) padbyte0 = padbyte0 | 0b00100000;  //button 1 (Y)
    if(btns & SNES_B) padbyte0 = padbyte0 | 0b00010000;  //button 2 (B)
  }
  else {
    if(btns & SNES_B) padbyte0 = padbyte0 | 0b00100000;  //button 1 (B)
    if(btns & SNES_Y) padbyte0 = padbyte0 | 0b00010000;  //button 2 (Y)
  }
  if(btns & SNES_X) padbyte0 = padbyte0 | 0b00110000; // button 3 (X)

  if((padbyte0 != oldpadbyte0) || (padbyte1 != 0b10000000) || (padbyte2 != 0b10000000) || ((padbyte0 & 0b00001111) != 0))  // see if state has changed
  {     
    if(analogRead(RTSpin) > RTSthreshold) vSerial.write(padbyte0);
    if(analogRead(RTSpin) > RTSthreshold) vSerial.write(padbyte1);
    if(analogRead(RTSpin) > RTSthreshold) vSerial.write(padbyte2);
  }

  // save state
  oldpadbyte0 = padbyte0; 
  oldpadbyte1 = padbyte1;
  oldpadbyte2 = padbyte2;
}

// change speed setting and save it to the EEPROM
void changeSpeed(byte newspeed)
{
  if(newspeed<1) newspeed=1;
  else if(newspeed>5) newspeed=5;
  
  spd=newspeed;
  EEPROM.write(0, spd);
}
