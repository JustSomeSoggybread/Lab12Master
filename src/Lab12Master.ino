SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

bool expectData = false;
void setup() {
  //init pin
  pinMode(D5,OUTPUT);
  
  //serial monitor
  //set up SPI
  SPI.begin(SPI_MODE_MASTER,D5);
  SPI.setClockSpeed(1,MHZ);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  
}
void loop() {
  char rx[1];
  char tx[1];

  if (expectData == true){
    tx[0] = '*';
    digitalWrite(D5,LOW);
    SPI.transfer(tx,rx,1,NULL);
    digitalWrite(D5,HIGH);
    if ((rx[0] != 0) && (rx[0] != 255)){
      Serial.println(rx[0]);
      expectData = false;
    }
  }
  else{
    while(!Serial.isConnected());

    while (!Serial.available());
    char x = Serial.read();
    
    tx[0] = x;

    //write to slave 
    digitalWrite(D5,LOW);
    SPI.transfer(tx,rx,1,NULL);
    digitalWrite(D5,HIGH);

    if (x == '?')
    {
      expectData = true;
    }
  }
}