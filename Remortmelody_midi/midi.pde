import processing.serial.*;
import themidibus.*;
MidiBus bus;
Serial myport;
int num;
int x;

void setup(){
myport = new Serial(this,"COM4",9600);
MidiBus.list();
bus= new MidiBus(this,0,1);

}
void draw(){
bus.sendMessage(0xC0,0,1,0);
//bus.sendNoteOn(0,num,150);
println(num);
}

void serialEvent(Serial p){
 x =p.read();
 if(x==0){
 bus.sendNoteOff(0,num,126);
 num=0;
 }
 if(p.read()==x){
 draw();
 }
 if(x==50) num=60;//c4
 if(x==51) num=61;//cs
 if(x==52) num=62;//d
 if(x==53) num=63;//ds
 if(x==54) num=64;//e
 if(x==55) num=65;//f
 if(x==56) num=66;//fs
 if(x==57) num=67;//g
 if(x==58) num=68;//gs
 if(x==59) num=69;//a
 if(x==60) num=70;//as
 if(x==61) num=71;//b
 if(x==62) num=72;//c5
 if(x==63) num=73;//cs
 println(x);
 bus.sendNoteOn(0,num,126);

}