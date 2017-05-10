#include <Wire.h>
/*
Identifiering             = 0x10,
Placering_relativt_objekt = 0x11,
Placering_relativt_lada   = 0x12,
Maxhastighet              = 0x13,
Lyckat_lyft               = 0x14,
Misslyckat_lyft           = 0x15,
Lyckad_avlamning          = 0x16,
Misslyckad_avlamning      = 0x17,
Justera_position          = 0x18,
Avbryt_justering          = 0x19,
Uppstart_pabyggnad        = 0x20,
Lyft_kloss                = 0x21,
Lyft_glas                 = 0x22,
Lyft_strumpa              = 0x23,
Avbryt_lyft               = 0x24,
Lamna_av_objekt           = 0x25,
Position_av_lada          = 0x30,
Aktuell_position_robot    = 0x31,
Start_position_strumpa    = 0x32,
Start_position_kloss      = 0x33,
Start_position_glas       = 0x34,
Uppstart_Position         = 0x40
*/

//Pabyggnads nummert för att identifiering 
uint8_t id_nummer =  37;
//Avståndet til objektet, första talet är avståndet i cm och andra vinkeln roboten behöver vara i. 
uint8_t avstand_objekt[] = {10,5};
//Avståndet roboten måsta stanna till från kanten till lådan, 1: Avståndet till lådan, 2: Vinkeln till lådan
uint8_t avstand_lada[] = {11,6};
//Hastigheten som roboten kan röra sig med objektet i ett lyft ? 
uint8_t max_hastighet = 15;
//Justering av position, om roboten behöver åka fram eller bakåt för att kunna ta upp objektet.
int position_justering = 0;
//Status på om lyftet är klart eller inte
uint8_t lyft_status = 0;

uint8_t data_packet[2];
uint8_t twi_state = 0,request_state = 0;

/**
 * Setup
 */
void setup() {
  Wire.begin(2);                  //Startar upp TWI bibliotektet och sätter adressen till 2.
  Wire.onRequest(requestEvent);   //Sätter ihop ett avbrott för när mastern vill att slaven skall skicka information.
  Wire.onReceive(receiveEvent);   //Sätter ihop ett avbrott för när slaven skall ta imot information.
  Serial.begin(9600);             
}
/**
 *  Main loop
 */
void loop() {
  delay(100);
}

/**
 * Metod som kallas då mastern vill att slaven skall skicka information
 * till sig, detta sker över I2C.
 */
void requestEvent(){
  switch(twi_state){
    case 0x10:                              //Identifiering skickar information om roboten vilket id pabyggnaden har
        data_packet[0] = twi_state;   
        data_packet[1] = id_nummer;         //idnummert
        Wire.write(data_packet,2);          //Skriver till slaven
      break;
    case 0x11:                              //Placering_relativt_objekt (Avståndet som roboten måste stanna innan objektet)
        data_packet[0] = twi_state;
        data_packet[1] = avstand_objekt[0]; // Avståndet mellan robot och objekt
        data_packet[2] = avstand_objekt[1]; // Vinkel mellan robot och objekt
        Wire.write(data_packet,3);
      break;
    case 0x12:                              //Placering_relativt_lada  (Avståndet som roboten måste stanna innan lådan)
        data_packet[0] = twi_state;
        data_packet[1] = avstand_lada[0];   // Avståndet mellan robot och lådan
        data_packet[2] = avstand_lada[1];   // Vinkeln mellan robot och lådan
        Wire.write(data_packet,3);
      break;
    case 0x13:                              //Maxhastighet som påbyggnaden klarar av
        data_packet[0] = twi_state;
        data_packet[1] = max_hastighet;     //Maxhastighet
        Wire.write(data_packet,2);
      break;
    case 0x14:                              //Lyckat lyft om roboten har lyckats lyfta objekte
        data_packet[0] = twi_state;
        data_packet[1] = lyft_status;       //3 = lyckat lyft, 4 = misslyckat lyft
        Wire.write(data_packet,2); 
      break;
    case 0x15:                              //Misslyckat lyft, om roboten har misslyckat med att lyfta objektet
        data_packet[0] = twi_state;         
        Wire.write(data_packet,1);
      break;
    case 0x16:
        data_packet[0] = twi_state;
        Wire.write(data_packet,1);
      break;
    case 0x17:
    
      break;
    case 0x18:
    
      break;
    case 0x19:
    
      break;
  }
  
}
/**
 * Slaven tar emot information från mastern, detta sker genom ett avbrott
 * som mastern bestämmer när den vill skicka information till slaven.
 *  @param howMany Hur många bitar som packetet är på
 */
void receiveEvent(int howMany){
  while(Wire.available()){
     twi_state = Wire.read(); // Läser in medelandet.
  }
  switch(twi_state){
    case 0x10:
        
      break;
    case 0x11:
    
      break;
    case 0x12:
    
      break;
    case 0x13:
    
      break;
    case 0x14:
    
      break;
    case 0x15:
    
      break;
    case 0x16:
    
      break;
    case 0x17:
    
      break;
    case 0x18:
    
      break;
    case 0x19:
    
      break;
    case 0x20:
    
      break;
    case 0x21:
    
      break;
    case 0x22:
    
      break;
    case 0x23:
    
      break;
    case 0x24:
      
      break;
    case 0x25:
    
      break;
  }
  Serial.println();
}



