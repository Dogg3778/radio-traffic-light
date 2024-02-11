import processing.serial.*;
Serial serial;
int buff, h, w;
String buff1;

void setup() {
  serial = new Serial(this, "COM3", 9600);
  serial.clear();
  size(200,600);
  smooth();
};

void draw() {
  background(0,0,0);
  ellipseMode(CENTER);
  fill(255,0,0,50);
  ellipse(width/2,height/6,height/3,height/3);
  fill(255,240,0,50);
  ellipse(width/2,height/2,height/3,height/3);
  fill(0,255,0,50);
  ellipse(width/2,height/1.2,height/3,height/3);
  
  
  buff1 = serial.readString();
  
  if (buff1 != null){
    buff1 = buff1.replaceAll("[^0-9]", "");
  };
  
  if((buff1 != null)&&(buff1 != "")){
    try{buff1 = buff1.substring(1, 2);}
    catch(StringIndexOutOfBoundsException nfe){};
    buff = Integer.parseInt(buff1);
  };


  if (buff==1) {
    fill(255,0,0);
    ellipse(width/2,height/6,height/3,height/3);
  } else if (buff==2) {
    fill(255,240,0);
    ellipse(width/2,height/2,height/3,height/3);
  } else if (buff==3) {
    fill(0,255,0);
    ellipse(width/2,height/1.2,height/3,height/3);
  };
  
  
};
