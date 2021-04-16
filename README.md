# Millumin_2_Neopixels
Sample code to work with millumin timeline and send osc data to processing to control neopixels leds via arduino.
Warning OSC in millumin overflows easily, MIDI may be a good option but you'll probably see the steps.


## How does it work ?

MILLUMIN =========> PROCESSING =========> ARDUINO
            osc                 serial
          or MIDI

In the millumin project each track is used for one color component (r, g and b)
Processing receives osc, display the color, and send the data to arduino via serial
The arduino program parses the incomming data and lights up a led strip (connected to D9)


## How to get started

- Open up the millumin project
- Use the timeline to create some keys
- Open up the processing program
- Install the OSCP5 library (which is used for communication : through the "Sketch" menu -> "Import Library" -> "Add Library" -> search "OSCP5' -> click install) or TheMidiBus for Midi
- Connect an arduino with a led strip on it (D6 or D9 / D10 / D11)
- Flash the arduino program on your board (tested with uno)
- Launch the processing program

-> if it doesn't work right away check the port on line 24, this should point to a valid arduino board :)


