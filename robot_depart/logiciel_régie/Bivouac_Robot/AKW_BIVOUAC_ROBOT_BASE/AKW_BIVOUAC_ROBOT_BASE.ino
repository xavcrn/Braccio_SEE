
#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
#include <Servo.h>
//#include <OSCMessage.h>
int status = WL_IDLE_STATUS;

//___________________________CONFIGURATION WIFI & COMMUNICATION____________
//the Arduino's IP
IPAddress static_ip(192, 168, 1, 10);
unsigned int localPort = 2626;      // local port to listen on
//destination IP
IPAddress outIp(192, 168, 1, 2);  // madmappers'IP
const unsigned int outPort = 2628;


char ssid[] = "BIVOUAC_CTL";        // SSID du réseau
char pass[] = "akwariom2022";    // mot de passe


char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back

boolean debug = false; // mettre "true" en cas de probleme de connection pour vérifier ce qui se passe dans le serial monitor

char head;
long value;


WiFiUDP Udp;

//___________________________CONFIGURATION MOTEUR____________

int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;     //M1 Direction Control
int M2 = 7;     //M1 Direction Control
int counter = 0;


void setup() {

  if (debug) Serial.begin(19200);
  wifiSetup();
  Udp.begin(localPort);

  analogWrite(E1, 0);
  analogWrite(E2, 0);
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    readPacket();
    if (debug) printMessageInfo(packetSize);

    head = packetBuffer[0];
    value = 1000 * (packetBuffer[1] - '0') + 100 * (packetBuffer[2] - '0') + 10 * (packetBuffer[3] - '0') + (packetBuffer[4] - '0');
    value = value - 255;
    if (head == 'l') //left
    {
      if (value < 0) digitalWrite(M1, LOW);
      else digitalWrite(M1, HIGH);
      analogWrite(E1, abs(value));
      
    }
    if (head == 'r') //left
    {
      if (value < 0) digitalWrite(M2, LOW);
      else digitalWrite(M2, HIGH);
      analogWrite(E2, abs(value));

    }

    //sendReply();
  }
}
