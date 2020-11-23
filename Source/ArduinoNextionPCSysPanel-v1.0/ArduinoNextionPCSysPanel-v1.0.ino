/*  Arduino & Nextion PC System Control Panel
 *  Copyright (C) 2020  by Taylor Jones / www.github.com/t-jones14

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include <EasyNextionLibrary.h> // include library
#include <trigger.h>            // include library

EasyNex myNex(Serial);          // Create an object of EasyNex class

// CUSTOMIZABLE VARIABLES
const int POWER_SW = 5;         // BJT1 - Check Schematic
const int RESET_SW = 6;         // BJT2 - Check Schematic
const int MB_CHECK = A7;        // +5V From Motherboard System Panel Connector

const int FORCE_TIME = 4000;     // Amount of time to hold POWER_SW closed to force system shutdown
// NOTE: Consult your motherboard user manual for the time required for forced shutdown.

// FIXED VARIABLES
// Do not edit these unless you know what you're doing.
// ====================================================
// State Management Variables
int mbState = 0;                  // This variable will hold the state of the motherboard. 0:Off/1:On
int interval = 1000;              // Rate (in millis) to run our custom loop

// Time Variables
unsigned long refresh_timer = millis();  // timer for refreshing Nextion's page
long currentMillis = millis();           // This will store the current time
unsigned long previousMillis = 0; // This will store the last time we looped
long sysStartTime = 0;            // This will store the time (in millis) when the MB was powered on
// TODO: long sysStopTime = 0;    // NOT IMPLEMENTED: This will store the time (in millis) when the MB was powered off last
long currentUptime = (sysStartTime - currentMillis);  // This will store our current system uptime
String rUptime = "";              // This var holds the readable uptime thats written to nextion display

//Nextion Variables to Write
String vHr = "";                  // Hours
String vMin = "";                 // Minutes
String vSec = "";                 // Seconds

// setup() runs when the Arduino is powered on or software reset (RST)
void setup() {

  myNex.begin(9600); // Begin serial communication with Nextion

  // Set the Output and Input pins
  pinMode(POWER_SW, OUTPUT);
  pinMode(RESET_SW, OUTPUT);
  pinMode(MB_CHECK, INPUT);

  // When the arduino is first powered on we need to figure out what state we need to be in.
  // We will accomplish this by first checking if the motherboard is powered on or not.
  float mbVoltage = getMbVoltage(); // get motherboard voltage via getMbVoltage() helper function

  // Now, let's get the current page Nextion is showing
  int currentPage = getCurrentPage();

  // if motherboard voltage is greater-than 1V
  if (mbVoltage > 1) {
    mbState = 1;              // set the motherboard state to 1:ON
    sysStartTime = millis();   // set the system start time
    if (currentPage != 1) {

      myNex.writeStr("page 1"); // Since motherboard is on, go to page 1
      loop();  // Now our arduino and nextion are in-sync and on the proper pages. Let's head to the loop();

    }
  } else {
    mbState = 0; // set the motherboard state to 0:OFF
    if (currentPage != 0) {
      myNex.writeStr("page 0"); // Since motherboard is off, go to page 0
      loop();  // Now our arduino and nextion are in-sync and on the proper pages. Let's head to the loop();
    }
  }

}

void loop() {

  // Our loop is pretty simple... we just need to listen for trigger events from the display
  // and write the system uptime to the display if the system is powered on.

  // lets start by checking what state we're in
  // lets get the current page just to make sure we're in-sync
  int currentPage = getCurrentPage();
  if (mbState == 1 && currentPage == 1) {
    // we're going to use a built-in "delay" so we're not sending needless writes to the nextion display
    if ((millis() - refresh_timer) > interval) {
      // since the motherboard is on and we're on page1 lets update the displayed uptime
      getUptime(); // update our time variables
      myNex.writeStr("tHr.txt", vHr); // write system hours uptime
      myNex.writeStr("tMin.txt", vMin); // write system minutes uptime
      myNex.writeStr("tSec.txt", vSec); // write system seconds uptime
      refresh_timer = millis();  // Set the timer equal to millis, create a time stamp to start over the "delay"
    }
  } else if (mbState == 1 && currentPage == 0) {

    // since motherboard is on, but we're on page0 lets get to page1
    // NOTE: currentPage!=1 is not used here because of page2 (shutdown options)
    myNex.writeStr("page 1"); // force page1

  }
  myNex.NextionListen(); // This function listens for Nextion events
}

// When the "page3 > Normal" OR "page0 > Power" option is selected
void trigger1() {

  int currentPage = getCurrentPage(); // get the current page Nextion is displaying

  // lets figure out which page we're on so we can perform the proper sequence
  if (currentPage == 0) {
    // since we're on page0 that means the system is off and we're booting it up
    sysStartTime = millis(); // set the system start time
    mbState = 1; // set mbState to 1 since we're turning on the PC
  } else if (currentPage == 2) {
    // since we're on page 2 (shutdown options)
    mbState = 0; // set mbState to 0 since we're turning off the PC
    myNex.writeStr("tHr.txt", "00"); // write system hours to 00
    myNex.writeStr("tMin.txt", "00"); // write system minutes to 00
    myNex.writeStr("tSec.txt", "00"); // write system seconds to 00
    //TO-DO:  Implement last total uptime
  }

  // trigger the switch
  digitalWrite(POWER_SW, HIGH);   // apply voltage to the BJT Base
  delay(500);                     // keep switch closed for 1/2 second
  digitalWrite(POWER_SW, LOW);    // Remove voltage from the BJT Base
}

// When the "page3 > Force" option is selected
void trigger2() {
  // trigger the switch
  digitalWrite(POWER_SW, HIGH);   // apply voltage to the BJT Base
  delay(FORCE_TIME);              // how long to hold closed for forced shutdown
  mbState = 0;                    // set mbState to 0 since we're turning off the PC
  digitalWrite(POWER_SW, LOW);    // Remove voltage from the BJT Base
}

// When the "page3 > Reset" option is selected
void trigger3() {
  // triger the switch
  digitalWrite(RESET_SW, HIGH);   // apply voltage to the BJT Base
  delay(500);                     // keep closed for 1/2 second
  digitalWrite(RESET_SW, LOW);    // Remove voltage from the BJT Base
}

// This helper function reads the voltage on the MB_CHECK pin and returns a float voltage value (X.XX)
float getMbVoltage() {
  // read the MB_CHECK pin voltage
  int sv = analogRead(MB_CHECK);

  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
  float mbV = sv * (5.0 / 1023.0);

  // return the value
  return mbV;
}

int getCurrentPage() {
  int pageId = myNex.currentPageId; // store the current page id eg. 0,1,2,3 etc...
  return pageId;
}

// This helper function pads our string time values with a leading zero if the number is less than 10.
String padding( int number, byte width ) {
  int currentMax = 10;
  for (byte i = 1; i < width; i++) {
    if (number < currentMax) {
      return String("0" + String(number));
    }
    currentMax *= 10;
  }
  return String(number);
}

// This helper function calculates our system uptime and puts it into a human-readable string
// Based on UPTIME by limbo at https://forum.arduino.cc/index.php?topic=8774.0
void getUptime() {
  currentUptime = (millis() - sysStartTime); // This will store our current system uptime
      long days = 0;
      long hours = 0;
      long mins = 0;
      long secs = 0;
      secs = currentUptime / 1000;          //convert milliseconds to seconds
      mins = secs / 60;                     //convert seconds to minutes
      hours = mins / 60;                    //convert minutes to hours
      days = hours / 24;                    //convert hours to days
      secs = secs - (mins * 60);            //subtract the coverted seconds to minutes in order to display 59 secs max
      mins = mins - (hours * 60);           //subtract the coverted minutes to hours in order to display 59 minutes max
      hours = hours - (days * 24);          //subtract the coverted hours to days in order to display 23 hours max
      String fHours = String(padding(hours, 2));    //format hours with leading zero if <10 and convert to string
      String fMins = String(padding(mins, 2));      //format minutes with leading zero if <10 and convert to string
      String fSecs = String(padding(secs, 2));      //format seconds with leading zero if <10 and convert to string
      //String uptime = fHours + ":" + fMins + ":" + fSecs; // Set the uptime var
      vHr = fHours;
      vMin = fMins;
      vSec = fSecs;
}
