void readPacket(){
   int len = Udp.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len] = 0;
   if(debug) Serial.println("Contents:");
    if(debug) Serial.println(packetBuffer);
}

void sendReply(){
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
}

void printMessageInfo(int _packetSize) {
  Serial.print("Received packet of size ");
  Serial.println(_packetSize);
  Serial.print("From ");
  IPAddress remoteIp = Udp.remoteIP();
  Serial.print(remoteIp);
  Serial.print(", port ");
  Serial.println(Udp.remotePort());
}
