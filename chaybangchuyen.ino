// defines pins numbers
//import processing.serial.*; //Thư viện
//Serial myPort; 
const int stepPin = 5; //clk+   
const int dirPin = 2; //cw+ 
const int enPin = 8; 
int sensor = 6;
int sanphamloi=0;
int sanphamdat=0;
int sen1 = 9;
int chuphinh=0;
int dung =0;
int dungbangchuyen=1;
int period = 2000;
int count = 0;
long botles[100];
int demchai=0;
int trangthaiin=0;
int demphantu=0; // phan tu dem vi tri can lay trong mang
// create array push botles


unsigned long time_now = 0;
bool  start = 1;
int stepPin1 = 11;
int dirPin1 = 12;
void setup() {
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  pinMode(sensor,INPUT);
  pinMode(sen1,INPUT);
  pinMode(stepPin1,OUTPUT);
  pinMode(dirPin1,OUTPUT);
  Serial.begin(9600);
}
  void motor()
  { 
     if (millis()> time_now + period)
      time_now = millis (); 
    digitalWrite(dirPin1,LOW); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 1200; x++) {
    digitalWrite(stepPin1,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin1,LOW); 
    delayMicroseconds(500);
    digitalWrite(stepPin1,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin1,LOW); 
    delayMicroseconds(500);
    digitalWrite(stepPin1,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin1,LOW); 
    delayMicroseconds(500); 
      digitalWrite(stepPin1,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin1,LOW); 
    delayMicroseconds(500);
  }
  delay(500); // One second delay
  digitalWrite(dirPin1,HIGH); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 1200; x++) {
    digitalWrite(stepPin1,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1,LOW);
    delayMicroseconds(500);
    digitalWrite(stepPin1,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin1,LOW); 
    delayMicroseconds(500);
    digitalWrite(stepPin1,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin1,LOW); 
    delayMicroseconds(500);
     digitalWrite(stepPin1,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin1,LOW); 
    delayMicroseconds(200);
  }
  delay(1000);
}
  void chay()
   {
  digitalWrite(dirPin,LOW);
  for(int x = 0; x < 120; x++) 
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(600); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(600); 
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(100); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(100);
   } 
  void ngung()
 { 
  digitalWrite(dirPin,LOW);
  for(int x = 0; x < 900; x++) 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(400); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(400); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(400); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(100);
}
void loop() 
{
  
  if(Serial.available() > 0) //Nếu có tín hiệu gửi đến Serial
  {
    char read = Serial.read(); //Đọc giá trị gửi
    if(read == '1') //Nếu gửi '1'
    {
      
      botles[demchai]=1;
    //  Serial.println("san pham dat");
      demchai++;
      
      
    }
    if(read == '0') //Nếu gửi '0'
    {
      botles[demchai]=0;
    //  Serial.println("san pham ko dat");
      demchai++;
    }
             if(read == '3') //Nếu gửi '1'
            {
      
              dungbangchuyen=1;
              
     //         Serial.println("chay bang chuyen");
      
      
            }
        if(read == '4') //Nếu gửi '1'
        {
      
       dungbangchuyen=0;
       trangthaiin=1;
    //   Serial.println("dung bang chuyen");
      
      
    } 
  }
  while(dungbangchuyen==0){
      ngung();
    if(Serial.available() > 0) //Nếu có tín hiệu gửi đến Serial
      {
        char read = Serial.read(); //Đọc giá trị gửi
         if(read == '3') //Nếu gửi '1'
            {
      
              dungbangchuyen=1;
      //        Serial.println("chay bang chuyen");
      
      
            }
        if(read == '4') //Nếu gửi '1'
        {
      
       dungbangchuyen=0;
       trangthaiin=1;
    //   Serial.println("dung bang chuyen");
      
      
    }
    }
    if(trangthaiin==1){
   //   Serial.print("so san pham loi: ");
    //  Serial.println(sanphamloi);
    //  Serial.print("so san pham dat: ");
    //  Serial.println(sanphamdat);
      trangthaiin=0;
      }
    if(dungbangchuyen == 1){
        break;
        }
    }
/////////////thoat ra////////////////
  sensor = digitalRead(6);
   if (sensor==1 && chuphinh==0)
   {
    chay();
    chuphinh=1;
   }
   else if(sensor !=1 && chuphinh==1){
 
    Serial.println("c");
    chuphinh=0;
    }
   else
   {
    ngung();
    chay();//chay cham lai (cam bien 1)

   }
    sen1=digitalRead(9);// doc sensor co tin hieu hay ko?
    if(demphantu ==10000)
    demphantu =0;

    ///////////////
    if (sen1==0 && botles[demphantu] == 0)
    { chay();
      
      demphantu=demphantu+1;
      sanphamloi++;
      motor();
      }
      else if(sen1==0 && botles[demphantu] == 1){
        chay();
        sanphamdat++;
        while(true){
           sen1=digitalRead(9);
           chay();
          if(sen1!=0){
            demphantu=demphantu+1;
            break;
            }
          
        }
        }
        else{
          chay();
          return;
          }

      
      }
