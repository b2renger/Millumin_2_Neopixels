
import processing.serial.*;

Serial myPort;


import oscP5.*;
import netP5.*;

OscP5 oscP5;

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


void setup() {
  size(400, 100);
  frameRate(10);
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this, 1234);


  println(Serial.list());
  String portName = Serial.list()[4]; // be careful to use the correct port
  myPort = new Serial(this, portName, 9600);
}


void draw() {
  fill(r0, g0, b0);
  rect(0, 0, 100, 100);

  fill(r1, g1, b1);
  rect(100, 0, 100, 100);

  fill(r2, g2, b2);
  rect(200, 0, 100, 100);

  fill(r3, g3, b3);
  rect(300, 0, 100, 100);
}



/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  try {
    if (theOscMessage.checkAddrPattern("/r0")==true) {
      r0 = int(theOscMessage.get(0).floatValue());
    }
    if (theOscMessage.checkAddrPattern("/g0")==true) {
      g0 = int(theOscMessage.get(0).floatValue());
    }
    if (theOscMessage.checkAddrPattern("/b0")==true) {
      b0 = int(theOscMessage.get(0).floatValue());
    }

    if (theOscMessage.checkAddrPattern("/r1")==true) {
      r1 = int(theOscMessage.get(0).floatValue());
    }
    if (theOscMessage.checkAddrPattern("/g1")==true) {
      g1 = int(theOscMessage.get(0).floatValue());
    }
    if (theOscMessage.checkAddrPattern("/b1")==true) {
      b1 = int(theOscMessage.get(0).floatValue());
    }

    if (theOscMessage.checkAddrPattern("/r2")==true) {
      r2 = int(theOscMessage.get(0).floatValue());
    }
    if (theOscMessage.checkAddrPattern("/g2")==true) {
      g2 = int(theOscMessage.get(0).floatValue());
    }
    if (theOscMessage.checkAddrPattern("/b2")==true) {
      b2 = int(theOscMessage.get(0).floatValue());
    }

    if (theOscMessage.checkAddrPattern("/r3")==true) {
      r3 = int(theOscMessage.get(0).floatValue());
    }
    if (theOscMessage.checkAddrPattern("/g3")==true) {
      g3 = int(theOscMessage.get(0).floatValue());
    }
    if (theOscMessage.checkAddrPattern("/b3")==true) {
      b3 = int(theOscMessage.get(0).floatValue());
    }

    String s = r0+","+g0+","+b0+","+r1+","+g1+","+b1+","+r2+","+g2+","+b2+","+r3+","+g3+","+b3+";\n";
    println(s);
    myPort.write(s);
  }
  catch (Exception e) {
  }
}
