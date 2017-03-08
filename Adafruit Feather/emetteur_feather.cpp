// Feather9x_RX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (receiver)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example Feather9x_TX
 
#include <SPI.h>
#include <RH_RF95.h>
#include <time.h>
 
/* for feather32u4 */
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7
 
/* for feather m0  
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3
*/
 
/* for shield 
#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 7
*/
 
 
/* for ESP w/featherwing 
#define RFM95_CS  2    // "E"
#define RFM95_RST 16   // "D"
#define RFM95_INT 15   // "B"
*/
 
/* Feather 32u4 w/wing
#define RFM95_RST     11   // "A"
#define RFM95_CS      10   // "B"
#define RFM95_INT     2    // "SDA" (only SDA/SCL/RX/TX have IRQ!)
*/
 
/* Feather m0 w/wing 
#define RFM95_RST     11   // "A"
#define RFM95_CS      10   // "B"
#define RFM95_INT     6    // "D"
*/
 
/* Teensy 3.x w/wing 
#define RFM95_RST     9   // "A"
#define RFM95_CS      10   // "B"
#define RFM95_INT     4    // "C"
*/
 
// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 868.0
 
// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);
 
// Blinky on receipt
#define LED 13
 
void setup() 
{
  pinMode(LED, OUTPUT);     
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
 
  while (!Serial);
  Serial.begin(9600);
  delay(100);
 
  Serial.println("Feather LoRa RX Test!");
  
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
 
  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");
 
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
 
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
 
  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
  srand(time(NULL));
}
 
void loop()
{
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
      digitalWrite(LED, HIGH);
      delay(10);
      
      // Send 
      double temperature;
      double humidite;
      double numero;
      
      temperature = ((int)((rand()-0.5)*100.0));
      
      humidite = ((int)((rand()-0.5)*100.0));
      numero=1;
      
      uint8_t *data;
      data = reinterpret_cast<uint8_t*>(&temperature);
     // data = (uint8_t*)(&temperature);
      
      uint8_t *data2;
       data2 = reinterpret_cast<uint8_t*>(&humidite); 

      uint8_t *data3;
      data3 = reinterpret_cast<uint8_t*>(&numero);

      uint8_t fi[sizeof(double)*3 / sizeof(uint8_t)];
      int i; 
      for(i=0;i<4;i++){
      fi[i]=data[i];
      }
      for(i=4;i<8;i++){
      fi[i]=data2[i-4];
      }
      for(i=8;i<12;i++){
      fi[i]=data3[i-8];
      }
      
      rf95.send(fi, sizeof(double)*3);
      rf95.waitPacketSent();
      Serial.print("Temperature : " );
      Serial.print(temperature);
      Serial.print(" , Humidite : ");
      Serial.print(humidite);
      Serial.print("\n");
      digitalWrite(LED, LOW);
      delay(10000);
}