#include <SPI.h>
#include <RF24.h>
//#include <LiquidCrystal.h>                        // задел на будущее
#include<time.h>                                  // подключение библиотек
RF24 radio(9, 10);                                // порты D9, D10: CSN CE
const uint32_t pipe = 111156789;                  // адрес рабочей трубы
byte data;                                        // переменная, отправляемая в эфир
//LiquidCrystal lcd(0, 1, 5, 6, 7, 8);              //=lcd(13, 12, 11, 10, 9, 8) задел на будущее

void setup() {
  //Serial.begin(115200);                           // (отладка) настройка COM-порта
  //Serial.println("Transmitter ON");               // (отладка) отправка сообщения о запуске в COM-порт

  radio.begin();                                  // инициализация
  delay(2000);                                    // ожидание стабилизации работы радиомодуля
  radio.setDataRate(RF24_1MBPS);                  // скорость обмена данными
  radio.setCRCLength(RF24_CRC_8);                 // размер контрольной суммы
  radio.setPALevel(RF24_PA_MIN);                  // уровень питания усилителя
  radio.setChannel(0x6f);                         // установка канала
  radio.setAutoAck(false);                        // отключение автоответа
  radio.powerUp();                                // включение
  radio.stopListening();                          // переход в режим передачи
  radio.openWritingPipe(pipe);                    // открыть трубу на отправку
  pinMode(2, OUTPUT);                             // красный диод
  pinMode(3, OUTPUT);                             // желтый диод
  pinMode(4, OUTPUT);                             // зеленый диод
  digitalWrite(2, 0);
  digitalWrite(3, 0);
  digitalWrite(4, 0);
  //lcd.begin(16,2);                                // задел на будущее
  //lcd.print("TEST");                              // задел на будущее
}

void loop() {
  for(int i {1}; i<4; i++){                       // цикл с перебором i от 1 до 3 (1 - красный, 2 - желтый, 3 - зеленый)
    unsigned long t = millis();                   // замер текущего времени
    data = i;                                     // присвоение текущего сигнала переменной отправки
    while (millis() < t+5000){                    // проверка: прошло ли 5 секунд с момента замера времени, если нет - отправка значения, если да - значение меняется
      radio.write(&data, 1);                      // отправка значения в эфир
      digitalWrite(i+1, 1);                       // включение светодиода
      //Serial.println(String(data));               // (отладка) отправка значения в COM-порт
    };
    digitalWrite(i+1, 0);                         // отключение светодиода
  };
}
