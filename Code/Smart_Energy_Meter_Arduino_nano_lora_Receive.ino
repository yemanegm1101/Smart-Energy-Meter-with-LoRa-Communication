#include <SPI.h>
#include <LoRa.h>

// LoRa status LEDs
const int LED_RED    = 5;
const int LED_GREEN   = 6;


void setup() {
  Serial.begin(9600);
  while (!Serial);

  // ---- LoRa init ----
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);


  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    digitalWrite(LED_GREEN, HIGH);
    while (1);
  }
  Serial.println("LoRa Receiver Ready");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    String packet = "";
    while (LoRa.available()) {
      packet += (char)LoRa.read();
    }
    digitalWrite(LED_RED, HIGH);
    delay(100);
    digitalWrite(LED_RED, LOW);

    // packet is "Vrms,Irms,P,Wh"
    Serial.print("Recv: ");
    Serial.println(packet);

    // simple parsing demo
    float V, I, P, E;
    int idx1 = packet.indexOf(',');
    int idx2 = packet.indexOf(',', idx1+1);
    int idx3 = packet.indexOf(',', idx2+1);

    V = packet.substring(0, idx1).toFloat();
    I = packet.substring(idx1+1, idx2).toFloat();
    P = packet.substring(idx2+1, idx3).toFloat();
    E = packet.substring(idx3+1).toFloat();

    Serial.print(" Voltage: "); Serial.print(V); Serial.println(" V");
    Serial.print(" Current: "); Serial.print(I); Serial.println(" A");
    Serial.print(" Power:   "); Serial.print(P); Serial.println(" W");
    Serial.print(" Energy:  "); Serial.print(E); Serial.println(" Wh");
    Serial.println();
  }
}
