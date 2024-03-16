#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"                     // подключение библиотек

RF24 radio(9, 10);                    // порты D9, D10: CSN CE
const uint32_t pipe = 111156789;      // адрес рабочей трубы;
byte data[1];                         // переменная для записи принимаемых данных
String prev = "";                     // предыдущее значение
int time = 0;

void setup() {
  Serial.begin(9600);                 // настройка COM-порта
  radio.begin();                      // инициализация
  delay(2000);                        // ожидание стабилизации работы радиомодуля
  radio.setDataRate(RF24_1MBPS);      // скорость обмена данными
  radio.setCRCLength(RF24_CRC_8);     // размер контрольной суммы
  radio.setChannel(0x6f);             // установка канала
  radio.setAutoAck(false);            // отключение автоответф
  radio.openReadingPipe(1, pipe);     // открыть трубу на приём
  radio.startListening();             // приём
  pinMode(3, OUTPUT);                 // перевод 3го пина в режим вывода
}

void loop() {
  radio.read(data, 1);                                // чтение эфира
  if ((data[0] > 0)&&(String(data[0]) != prev)){      // проверка: пришёл ли новый сигнал
    Serial.println(String(data[0]));                  // отправка в COM-порт принятых радиосигналов
    prev = String(data[0]);                           // запись предыдущего сигнала в переменную
    time = millis();                                  // установка точки отсчета времени
  }
  if ((millis()<time+200)){                           // таймер на 200мс для пищалки
    analogWrite(3, 100);                              // подача сигнала на пищалку
  } else {
    analogWrite(3, 0);                                // отключение пищалки
  }
}
