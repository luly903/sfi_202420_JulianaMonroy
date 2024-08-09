## ¿Cómo se ejecuta este programa?
El codigo lo que hace es funcionar como una especie de reloj que va aumentando los segundos (en forma de milisegundos) y mostrando la cuenta
en el monitor.

## Pudiste ver este mensaje: Serial.print("Task1States::WAIT_TIMEOUT\n");. 
## ¿Por qué crees que ocurre esto?
No, creo que esto pasa debido a que el mensaje probablemente se muestra por un momento bastante breve durante el conteo o bucle, lo cual lo hace
casi imposible de percibir una vez ejecutado el programa.

## ¿Cuántas veces se ejecuta el código en el caso Task1States::INIT?
Una vez, cuando se inicia el codigo, el cual inicia el estado INIT en task1 que empieza con el bucle de conteo, despues de ello pasa task1 al estado
Task1States::WAIT_TIIMEOUT
