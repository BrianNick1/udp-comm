//Rx
#include <SPI.h>    // ( Net surf for SPI pins )
#include <Ethernet.h>
#include <EthernetUdp.h>
#include<Servo.h>

// -------- Do not change the section below -----------------
byte mac[] = { 0x2A, 0x00, 0x22, 0x22, 0x22, 0x44 }; //(Naming rules)
IPAddress ip(169, 254, 240, 100);                       //(IP rules according to subnet/gateway)
const unsigned int localPort = 1369;    // Process ID port (TCP/UDP Alternate port = 8888)
char remote_IP1[]="169.254.240.200";
int remote_Port1 = 9631;
char UDP_TX_Buffer[80];
char recvdBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; // Buffer for incoming data
EthernetUDP Udp;  //Class variable (Initiates process of UDP)
// ------------------------------------------------------------

Servo ESC;  //Newly added genius code
int temperature =atoi(recvdBuffer);

void setup()
{
  Ethernet.begin(mac, ip);   // Set up the Ethernet Shield
  Udp.begin(localPort);      // Open a socket for this port
  Serial.begin(9600);        // Set up serial monitor with PC4
  ESC.attach(2);
  delay(50);    
}

void loop()
{
  //transmit
int recvdSize = Udp.parsePacket();

 if (Udp.available()) 
 {
    IPAddress remote = Udp.remoteIP();
    Udp.read(recvdBuffer, UDP_TX_PACKET_MAX_SIZE);
    recvdBuffer[recvdSize] = '\0';
    recvdSize -= 8;               // Gets rid of the message header

    int temperature =atoi(recvdBuffer);
    Serial.println(temperature);
    
    temperature=map(temperature,0,1023,0,170);
    ESC.write(temperature);
 }
}
