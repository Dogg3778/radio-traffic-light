import processing.serial.*;                         // подключение библиотеки serial
Serial serial;                                      // создание COM-порта с именем serial (ага, оригинально)
int buff, h, w;                                     // целочисленные переменные: буффер числа, высота окна, ширина окна 
String buff1;                                       // буффер входящей строки

void setup() {
  serial = new Serial(this, "COM3", 9600);          // объявление COM-порта
  serial.clear();                                   // очистка буффера порта от мусора
  size(200,600);                                    // установка размеров окна
  smooth();                                         // сглаживание пикселей
};

void draw() {
  background(0,0,0);                                // черный фон
  ellipseMode(CENTER);                              // установка режима рисовки эллипсов
  fill(255,0,0,50);                                 // установка цвета заливки на полупрозрачный красный
  ellipse(width/2,height/6,height/3,height/3);      // отрисовка круга
  fill(255,240,0,50);                               // установка цвета заливки на полупрозрачный желтый
  ellipse(width/2,height/2,height/3,height/3);      // отрисовка круга
  fill(0,255,0,50);                                 // установка цвета заливки на полупрозрачный зеленый
  ellipse(width/2,height/1.2,height/3,height/3);    // отрисовка круга
  
  
  buff1 = serial.readString();                      // считываем строку из порта
  
  // фильтр
  if (buff1 != null){                               // проверка что строка не пустая
    buff1 = buff1.replaceAll("[^0-9]", "");         // удаление всех символов кроме цифр
  };
  
  if((buff1 != null)&&(buff1 != "")){               // проверка строки на пустоту после очистки
    try{buff1 = buff1.substring(1, 2);}             // проверка строки на пустоту после очистки
    catch(StringIndexOutOfBoundsException nfe){};   // проверка строки на пустоту после очистки
    buff = Integer.parseInt(buff1);                 // перевод в целое число
  };


  if (buff==1) {                                    // если единица...
    fill(255,0,0);                                  // красный цвет
    ellipse(width/2,height/6,height/3,height/3);    // отрисовка круга поверх предыдущего
  } else if (buff==2) {                             // если двойка...
    fill(255,240,0);                                // жетый цвет
    ellipse(width/2,height/2,height/3,height/3);    // отрисовка круга поверх предыдущего
  } else if (buff==3) {                             // если тройка...
    fill(0,255,0);                                  // зеленый цвет
    ellipse(width/2,height/1.2,height/3,height/3);  // отрисовка круга поверх предыдущего
  };
};
