uint8_t sendBuffer[8];
String respBuffer[25];
float V,C,P,E,F,pf,Alarm;
int idx = 0;


void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial.println("Starting.......");

}

void loop() {
  sendBuffer[0]=0x01;
  sendBuffer[1]=0x04;
  sendBuffer[2]=0x00;
  sendBuffer[3]=0x00;
  sendBuffer[4]=0x00;
  sendBuffer[5]=0x0A;
  sendBuffer[6]=0x70;
  sendBuffer[7]=0x0D;
  Serial.println("");
  Serial.println("sendCMD done!");
  Serial3.write(sendBuffer,8);
  


  

    while(Serial3.available()){ // wait for a character

   
    int incomingByte = Serial3.read();
    if(idx==25){idx=0;}
    respBuffer[idx] = String(incomingByte, HEX);   
    Serial.print(incomingByte,HEX);
    Serial.print(' ');
    idx=idx+1;
   
    
    }
    
  
    Serial.println("");
     

  V=findOut(3, 4)/10;
  Serial.print("Voltage: "); 
  Serial.print(V);
  Serial.println(" V");


  C=findOut(5, 6)/1000;
  Serial.print("Current: "); 
  Serial.print(C);
  Serial.println(" A" );


  P=findOut(9, 10)/10;
  Serial.print("Power: "); 
  Serial.print(P);
  Serial.println(" W");


  E=findOut(5, 6)/1000;
  Serial.print("Energy: "); 
  Serial.print(E);
  Serial.println(" kWh");

  
  F=findOut(17, 18)/10;
  Serial.print("Frequency: "); 
  Serial.print(F);
  Serial.println(" Hz");


  pf=findOut(19, 20)/100;
  Serial.print("pf: "); 
  Serial.println(pf);


     
 delay (9000);
}


   float findOut(int start_byte_position, int end_byte_position){
    
   int   H_byte,L_byte;
   String addH_L;
   
    if (end_byte_position == start_byte_position+1){
       H_byte=start_byte_position;
       L_byte=end_byte_position;
      
       addH_L= respBuffer[H_byte]+respBuffer[L_byte];
      }
    else if(end_byte_position > start_byte_position+1){
       H_byte=start_byte_position;
       L_byte=end_byte_position;
      
       addH_L= respBuffer[H_byte]+respBuffer[H_byte+1]+respBuffer[L_byte-1]+respBuffer[L_byte];
      }

      
   //Serial.print("String formated hex: ");Serial.println(addH_L);
   char char_array[addH_L.length() + 1];
   addH_L.toCharArray(char_array, (addH_L.length() + 1));

 
   float num = (int)strtol(char_array, NULL, 16);
   return num;
  }
  
