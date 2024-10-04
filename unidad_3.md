### 1. - ¿Cómo se ve un protocolo binario?
- ¿Puedes describir las partes de un mensaje?
- ¿Para qué sirve cada parte del mensaje?

### 4. ¿En qué *endian* estamos transmitiendo el número? Y si queremos transmitir en el *endian* contrario, ¿Cómo se modifica el código?

estamos transmitiendo el numero en little endian, es decir, empezando por el byte de menor peso, si quisieramos transmitir el numero en big endian lo que habria que hacer seria que el programa leyera el array en el que se guardo el numero comenzando por la ultima posicion del array hasta el primero.
