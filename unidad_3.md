## 1. ¿Cómo se ve un protocolo binario?
el protocolo binario es una comunicacion que se realiza entre el host(microcontrolador) y el reader(dispositivo receptor) en bytes de 8 bits que consisten de ceros y unos, es decir, codigo binario.

### ¿Puedes describir las partes de un mensaje?
- cada mensaje esta compuesto por 6 partes:  Len, Adr, Cmd, Data[], LSB-CRC16 Y MSB-CRC16, cada una de estas, excepto por el Data[] pesa 1 byte, el peso de Data[]  puede variar dependiendo del mensaje.

### ¿Para qué sirve cada parte del mensaje?
len: determina la longitud de la cadena de caracteres (de Data[]) en el protocolo.

adr: identifica el dispositivo receptor.

cmd: comando que se usa para interactuar con el sistema en el protocolo binario.

Data[]: conjunto de datos que se transmitiran en el protocolo binario, si no hay datos, el peso del data[] sera 0.

 LSB-CRC16  Y MSB-CRC16: confirman que el mensaje no tenga errores al moento de enviarse.


### 4. ¿En qué *endian* estamos transmitiendo el número? Y si queremos transmitir en el *endian* contrario, ¿Cómo se modifica el código?

estamos transmitiendo el numero en little endian, es decir, empezando por el byte de menor peso, si quisieramos transmitir el numero en big endian lo que habria que hacer seria que el programa leyera el array en el que se guardo el numero comenzando por la ultima posicion del array hasta el primero.

### 5. 
```
void setup() {
    Serial.begin(115200);
}

void loop() {
    float num1 = 4206.9023;
    float num2 = 3450;
    

    uint8_t arr1[4] = {0};
    uint8_t arr2[4] = {0};


    memcpy(arr1, (uint8_t *)&num1, 4);
    memcpy(arr2, (uint8_t *)&num2, 4);


    if(Serial.available())
    {
      if(Serial.read() == 'l')
      {
       Serial.println("Little-endian:");
          for (int i = 0; i < 4; i++) 
          {
              Serial.write(arr1[i]);
          }
        Serial.println();
       for (int i = 0; i < 4; i++) 
       {
           Serial.write(arr2[i]);
       }
       Serial.println();
      }
      else
      if(Serial.read() == 'b')
      {
           Serial.println("Big-endian:");
             for (int i = 3; i >= 0; i--) 
             {
              Serial.print(arr1[i]);
             }
           Serial.println();
             for (int i = 3; i >= 0; i--) 
             {
              Serial.print(arr2[i]);
             }
       Serial.println();
      }



    }

}
```
