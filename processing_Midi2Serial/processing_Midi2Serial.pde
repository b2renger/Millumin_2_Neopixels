import themidibus.*; //Import the library
import processing.serial.*;

Serial myPort;

MidiBus myBus; // The MidiBus

void setup() {
  size(400, 100);
  background(0);

  MidiBus.list(); // List all available Midi devices on STDOUT. This will show each device's index and name.
  myBus = new MidiBus(this, 0, -1); // Create a new MidiBus with no input device and the default Java Sound Synthesizer as the output device.

  println(Serial.list());
  String portName = Serial.list()[4]; // be careful to use the correct port
  myPort = new Serial(this, portName, 9600);
}

int r0 = 0;
int g0 = 0;
int b0 = 0;
int r1 = 0;
int g1 = 0;
int b1 = 0;
int r2 = 0;
int g2 = 0;
int b2 = 0;
int r3 = 0;
int g3 = 0;
int b3 = 0;



void draw() {
  fill(r0, g0, b0);
  rect(0, 0, 100, 100);

  fill(r1, g1, b1);
  rect(100, 0, 100, 100);

  fill(r2, g2, b2);
  rect(200, 0, 100, 100);

  fill(r3, g3, b3);
  rect(300, 0, 100, 100);

  String s = r0+","+g0+","+b0+","+r1+","+g1+","+b1+","+r2+","+g2+","+b2+","+r3+","+g3+","+b3+";\n";
  println(s);
  myPort.write(s);
}


void controllerChange(int channel, int number, int value) {
  // Receive a controllerChange
  /*
  println();
   println("Controller Change:");
   println("--------");
   println("Channel:"+channel);
   println("Number:"+number);
   println("Value:"+value);*/

  if (channel == 0 ) {
    if (number == 1) {
      r0 = value;
    }
    if (number == 2) {
      g0 = value;
    }
    if (number == 3) {
      b0 = value;
    }

    if (number == 4) {
      r1 = value;
    }
    if (number == 5) {
      g1 = value;
    }
    if (number == 6) {
      b1 = value;
    }

    if (number == 7) {
      r2 = value;
    }
    if (number == 8) {
      g2 = value;
    }
    if (number == 9) {
      b2 = value;
    }

    if (number == 10) {
      r3 = value;
    }
    if (number == 11) {
      g3 = value;
    }
    if (number == 12) {
      b3 = value;
    }
  }
}
