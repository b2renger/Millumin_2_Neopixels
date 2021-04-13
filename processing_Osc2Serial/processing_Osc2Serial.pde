
import processing.serial.*;

Serial myPort;  


import oscP5.*;
import netP5.*;

OscP5 oscP5;

float r = 255;
float g = 0;
float b = 0;

void setup() {
  size(100, 100);
  frameRate(25);
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this, 8000);


  println(Serial.list());
  String portName = Serial.list()[4]; // be careful to use the correct port
  myPort = new Serial(this, portName, 9600);
}


void draw() {
  background(r, g, b);
  
  
}



/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  if (theOscMessage.checkAddrPattern("/r")==true) {
    r = theOscMessage.get(0).floatValue()*255;
  }
  if (theOscMessage.checkAddrPattern("/g")==true) {
    g = theOscMessage.get(0).floatValue()*255;
  }
  if (theOscMessage.checkAddrPattern("/b")==true) {
    b = theOscMessage.get(0).floatValue()*255;
  }
  
  String s = r+","+g+","+b+";";
  println(s);
  myPort.write(s);
}
