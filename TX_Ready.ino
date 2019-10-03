//Tx

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

//-------- system config -----------------
byte mac[] = {0x2A, 0x00, 0x22, 0x22, 0x22, 0x22};
IPAddress ip(169, 254, 240, 200);
const unsigned int localPort = 9631;
char remote_IP[] = "169.254.240.100";
int remote_Port = 1369;
char UDP_TX_Buffer[80]; // For future use...
char recvdBuffer[UDP_TX_PACKET_MAX_SIZE + 1];
//char UDP_RX_Buffer[80]; // For future use...
EthernetUDP Udp;
//-----------------------------------------

void setup()
{
  Ethernet.begin(mac, ip);  // Set up the Ethernet Shield
  Udp.begin(localPort);     // Open a socket for this port
  Serial.begin(9600);       // Set up serial monitor with PC
  //pinMode(13, OUTPUT);
  //analogReference(INTERNAL);
   delay(50);
}

void loop()
{
int recvdSize = Udp.parsePacket();
int tempC = analogRead(A1);
Serial.println(tempC);
delay(50);

 itoa(tempC, UDP_TX_Buffer, 10); 

   Udp.beginPacket(remote_IP, remote_Port);
   Udp.write(UDP_TX_Buffer);
   Udp.endPacket();
   strcpy(UDP_TX_Buffer,"");
   delay(50);
}
