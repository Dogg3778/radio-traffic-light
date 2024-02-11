/*
Победа над nRF24L01: на три шага ближе, приемник
https://habr.com/ru/post/476716/
*/
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 10); // порты D9, D10: CSN CE

const uint32_t pipe = 111156789; // адрес рабочей трубы;
byte data[1];
int scn;  //счетчик циклов прослушивания эфира
int sg;  //счетчик числа принятых пакетов с передатчика

void setup() {
  Serial.begin(9600);

  radio.begin();  // инициализация
  delay(2000);
  radio.setDataRate(RF24_1MBPS); // скорость обмена данными RF24_1MBPS или RF24_2MBPS
  radio.setCRCLength(RF24_CRC_8); // размер контрольной суммы 8 bit или 16 bit
  radio.setChannel(0x6f);         // установка канала
  radio.setAutoAck(false);       // автоответ
  radio.openReadingPipe(1, pipe); // открыть трубу на приём
  radio.startListening();        // приём
}

void loop() {
  radio.read(data, 1);
  if (data[0] > 0){
    Serial.println(String(data[0]));
  }
}