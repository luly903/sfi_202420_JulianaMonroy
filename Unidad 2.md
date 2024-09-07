## Ejercicio 1
```
void setup() {
  Serial.begin(115200);
}

void loop() {
if(Serial.available()){
if(Serial.read() == '1'){
      Serial.print("Hello from Raspberry Pi Pico");
    }
  }
}
```
Prueba la aplicación con ScriptCommunicator. ¿Cómo funciona?

**R\:** Basicamente lo que hace el codigo es que si se escribe por consola el número 1 va a parecer en la pantalla el mensaje "Hello from Raspberry Pi Pico"

Crea un nuevo C# Script y un Game Object. Añade el Script al GameObject. Ve al menu Assets y luego selecciona Open C# Project.

```csharp
using UnityEngine;
using System.IO.Ports;
public class Serial : MonoBehaviour
{
private SerialPort _serialPort =new SerialPort();
private byte[] buffer =new byte[32];

void Start()
    {
        _serialPort.PortName = "COM3";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable =true;
        _serialPort.Open();
        Debug.Log("Open Serial Port");
    }

void Update()
    {

				if (Input.GetKeyDown(KeyCode.A))
        {
            byte[] data = {0x31};// or byte[] data = {'1'};            
						_serialPort.Write(data,0,1);
            Debug.Log("Send Data");
        }

				if (Input.GetKeyDown(KeyCode.B))
        {
						if (_serialPort.BytesToRead >= 16)
            {
                _serialPort.Read(buffer, 0, 20);
                Debug.Log("Receive Data");
                Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
            }
        }

    }
}
```

Analiza:

- ¿Por qué es importante considerar las propiedades *PortName* y *BaudRate*?
  
**R\:** Son importantes dado que PortName es la función que le da el nombre al puerto, en otras palabras es la función que le indica al programa que puerto es el que se va a usar.Por otro lado, BaudRate basicamente cumple la función de indicar la velocidad con la que se va a hacer la trsnamisión de datos

- ¿Qué relación tienen las propiedades anteriores con el controlador?

**R\:** Como se enciono anteriormente PortName sirve para indicar en que puesto se encuentra conectado el controlador y BaudRate es quien indica la velocidad quen tendra la transmisión de datos entre el controlador y el computador.

## Ejercicio 2

Te invito a ver antes unos videos cortos con la explicación de este experimento usando unas herramientas un poco diferentes, sin embargo, el principio es el mismo.  Te dejo [este](https://youtube.com/playlist?list=PLX4ZVWZsOgzST9kfU9_ohOUYp_oDo2z48) link).

Ahora realiza este experimento. Modifica la aplicación del PC así:

```
using UnityEngine;
using System.IO.Ports;
using TMPro;

public class Serial : MonoBehaviour
{
	private SerialPort _serialPort =new SerialPort();
	private byte[] buffer =new byte[32];

	public TextMeshProUGUI myText;

	private static int counter = 0;

	void Start()
    {
        _serialPort.PortName = "COM3";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable =true;
        _serialPort.Open();
        Debug.Log("Open Serial Port");
    }

void Update()
    {
        myText.text = counter.ToString();
        counter++;

				if (Input.GetKeyDown(KeyCode.A))
        {
            byte[] data = {0x31};// or byte[] data = {'1'};            
						_serialPort.Write(data,0,1);
            int numData = _serialPort.Read(buffer, 0, 20);
            Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
            Debug.Log("Bytes received: " + numData.ToString());
        }
    }
}
```

En tu sistema operativo debes averiguar en qué puerto está el controlador y cómo se llama. En Windows se usa COMx, donde x es el número del puerto serial asignado por el sistema operartivo a tu controlador.

A continuación, debes adicionar a la aplicación un elemento de GUI tipo *Text - TextMeshPro* y luego, arrastrar una referencia a este elemento a *myText* (si no sabes cómo hacerlo llama al profe).

Y la aplicación del controlador:

```
void setup()
{
		Serial.begin(115200);
}

void loop()
{
		if(Serial.available())
		{
				if(Serial.read() == '1')
				{
			      delay(3000);
			      Serial.print("Hello from Raspi");
				}
		}
}
```

Ejecuta la aplicación en Unity. Verás un número cambiar rápidamente en pantalla. Ahora presiona la tecla A (no olvides dar click en la pantalla *Game*). ¿Qué pasa? ¿Por qué crees que ocurra esto?

**R\:** El codigo inicia un contador que va muy pero muy rapido y cuando oprimimos la letra A este suma un byte, cada vez que pulsemos A se agregara un byte.

Prueba con el siguiente código. Luego, **ANALIZA CON DETENIMIENTO.** Una vez más, no olvides cambiar el puerto serial.

```csharp
using UnityEngine;
using System.IO.Ports;
using TMPro;

public class Serial : MonoBehaviour
{
		private SerialPort _serialPort =new SerialPort();
		private byte[] buffer =new byte[32];

		public TextMeshProUGUI myText;

		private static int counter = 0;

		void Start()
		{
		    _serialPort.PortName = "COM3";
		    _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable =true;
        _serialPort.Open();
        Debug.Log("Open Serial Port");
		}

		void Update()
		{
        myText.text = counter.ToString();
        counter++;

				if (Input.GetKeyDown(KeyCode.A))
				{
            byte[] data = {0x31};// or byte[] data = {'1'};
            _serialPort.Write(data,0,1);
        }
				if (_serialPort.BytesToRead > 0)
			  {
	          int numData = _serialPort.Read(buffer, 0, 20);
            Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
            Debug.Log("Bytes received: " + numData.ToString());
        }
		}

```

¿Funciona?
Por ejemplo, ¿Qué pasaría si al momento de ejecutar la instrucción `int numData = 
_serialPort.Read(buffer, 0, 20);` solo han llegado 10 de los 16 bytes del mensaje? ¿Cómo puede hacer tu programa para saber que ya tiene el mensaje completo? ¿Cómo se podría garantizar que antes de hacer la operación Read tenga los 16 bytes listos para ser leídos? Además, si los mensajes que envía el controlador tienen tamaños diferentes, ¿Cómo haces para saber que el mensaje enviado está completo o faltan bytes por recibir?

**R\:** El codigo si funciona, este basicamente va haciendo un conteo de los bytes que hay en el momento hasta llegar a 20. Cuando el sistema no llega a los 20 bytes lo que hace es contar hasta el número que haya, si hay 916 bytes cuenta hasta 16 bytes, si hay más contara más y si hay menos contara menos. En cuanto al buffer eso depende de como se programe se puede decidir que comience en 0 o 10 y que termine hasta en 50, depende de quien lo programe.

## Ejercicio 3

Nótese que en los dos ejercicios anteriores, el PC primero le pregunta al controlador por datos (le manda un 1). ¿Y si el PC no pregunta?

**R\:** Si no se le pregunta al PC no sucedera nada, dado que se necesita que el PC indique la instrucción para que se ejecute la función.

Realiza el siguiente experimento. Programa ambos códigos y analiza su funcionamiento.

```cpp
void task()
{
		enum class TaskStates
		{
				INIT,
				WAIT_INIT,
				SEND_EVENT
		};
		static TaskStates taskState = TaskStates::INIT;
		static uint32_t previous = 0;
		static u_int32_t counter = 0;

		switch (taskState)
		{
				case TaskStates::INIT:
				{
						Serial.begin(115200);
						taskState = TaskStates::WAIT_INIT;
						break;
				}
				case TaskStates::WAIT_INIT:
				{
						if (Serial.available() > 0)
						{
								if (Serial.read() == '1')
								{
										previous = 0; // Force to send the first value immediately
										taskState = TaskStates::SEND_EVENT;
								}
						}
						break;
				}
				case TaskStates::SEND_EVENT:
				{
						uint32_t current = millis();
						if ((current - previous) > 2000)
						{
								previous = current;
								Serial.print(counter);
								counter++;
						}
						if (Serial.available() > 0)
						{
							  if (Serial.read() == '2')
							  {
								    taskState = TaskStates::WAIT_INIT;
							  }
						}
						break;
				}
				default:
				{
						break;
				}
		}
}

void setup()
{
		task();
}

void loop()
{
		task();
}
```

```csharp
using UnityEngine;
using System.IO.Ports;
using TMPro;

enum TaskState
{
    INIT,
    WAIT_START,
    WAIT_EVENTS
}

public class Serial : MonoBehaviour
{
		private static TaskState taskState = TaskState.INIT;
		private SerialPort _serialPort;
		private byte[] buffer;
		public TextMeshProUGUI myText;
		private int counter = 0;

		void Start()
    {
        _serialPort =new SerialPort();
        _serialPort.PortName = "COM3";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable =true;
        _serialPort.Open();
        Debug.Log("Open Serial Port");
        buffer =new byte[128];
    }

void Update()
    {
        myText.text = counter.ToString();
        counter++;

				switch (taskState)
        {
						case TaskState.INIT:
		            taskState = TaskState.WAIT_START;
                Debug.Log("WAIT START");
								break;
						case TaskState.WAIT_START:
								if (Input.GetKeyDown(KeyCode.A))
                {
                    byte[] data = {0x31};// start
                    _serialPort.Write(data,0,1);
                    Debug.Log("WAIT EVENTS");
                    taskState = TaskState.WAIT_EVENTS;
                }
								break;
						case TaskState.WAIT_EVENTS:
								if (Input.GetKeyDown(KeyCode.B))
                {
                    byte[] data = {0x32};// stop
                    _serialPort.Write(data,0,1);
                    Debug.Log("WAIT START");
                    taskState = TaskState.WAIT_START;
                }
								if (_serialPort.BytesToRead > 0)
                {
                    int numData = _serialPort.Read(buffer, 0, 128);
                    Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
                }
								break;
						default:
                Debug.Log("State Error");
								break;
        }
    }
}
```

¿Recuerdas las preguntas presentadas en el experimento anterior? ¿Aquí nos pasa lo mismo?

Analicemos el asunto. Cuando preguntas `_serialPort.BytesToRead > 0` lo que puedes asegurar es que al MENOS tienes un byte del mensaje, pero no puedes saber si tienes todos los bytes que lo componen. Una idea para resolver esto, sería hacer que todos los mensajes tengan el mismo tamaño. De esta manera solo tendrías que preguntar `_serialPort.BytesToRead > SIZE`, donde SIZE sería el tamaño fijo; sin embargo, esto le resta flexibilidad al protocolo de comunicación. Nota que esto mismo ocurre en el caso del programa del controlador con `Serial.available() > 0`. ¿Cómo podrías solucionar este problema?

**R\:**  una manera de solucionar el problema seria restringiendo el tamaño del mensaje para que este dentro de un rango determinado de bytes, por ejemplo, escribir _serialPort.BytesToRead > minV && _serialPort.BytesToRead < maxV donde minV y maxV serian los valores que determinen el rango del tamaño de los mensajes, para que esten dentro de un rango o incluso un unico valor en especifico.

## Ejercicio 4

Ahora vas a analizar cómo puedes resolver el problema anterior. Puntualmente, analiza el siguiente programa del controlador:
String btnState(uint8_t btnState)
{
		if(btnState == HIGH)
		{
				return "OFF";
		}
		else
				return "ON";
}

void task()
{
		enum class TaskStates
		{
		    INIT,
		    WAIT_COMMANDS
	  };
		static TaskStates taskState = TaskStates::INIT;
		constexpr uint8_t led = 25;
		constexpr uint8_t button1Pin = 12;
		constexpr uint8_t button2Pin = 13;
		constexpr uint8_t button3Pin = 32;
		constexpr uint8_t button4Pin = 33;

		switch (taskState)
	  {
				case TaskStates::INIT:
				{
						Serial.begin(115200);
						pinMode(led, OUTPUT);
						digitalWrite(led, LOW);
						pinMode(button1Pin, INPUT_PULLUP);
						pinMode(button2Pin, INPUT_PULLUP);
						pinMode(button3Pin, INPUT_PULLUP);
						pinMode(button4Pin, INPUT_PULLUP);
						taskState = TaskStates::WAIT_COMMANDS;
						break;
				}
				case TaskStates::WAIT_COMMANDS:
				{
						if (Serial.available() > 0)
						{
								String command = Serial.readStringUntil('\n');
								if (command == "ledON")
								{
										digitalWrite(led, HIGH);
								}
								else if (command == "ledOFF")
								{
										digitalWrite(led, LOW);
								}
								else if (command == "readBUTTONS")
							  {
										Serial.print("btn1: ");
						        Serial.print(btnState(digitalRead(button1Pin)).c_str());
						        Serial.print(" btn2: ");
						        Serial.print(btnState(digitalRead(button2Pin)).c_str());
						        Serial.print(" btn3: ");
						        Serial.print(btnState(digitalRead(button3Pin)).c_str());
						        Serial.print(" btn4: ");
						        Serial.print(btnState(digitalRead(button4Pin)).c_str());
						        Serial.print('\n');
					      }
						}
						break;
				}
				default:
				{
						break;
			  }
		}
}

void setup()
{
  task();
}

void loop()
{
  task();
}
​
A continuación, analiza el siguiente programa del PC:
using UnityEngine;
using System.IO.Ports;
using TMPro;

enum TaskState
{
    INIT,
    WAIT_COMMANDS
}

public classSerial : MonoBehaviour
{
		private static TaskState taskState = TaskState.INIT;
		private SerialPort _serialPort;
		private byte[] buffer;
		public TextMeshProUGUI myText;
		private int counter = 0;

		void Start()
    {
				_serialPort =new SerialPort();
        _serialPort.PortName = "COM3";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable =true;
        _serialPort.NewLine = "\n";
        _serialPort.Open();
        Debug.Log("Open Serial Port");
        buffer =new byte[128];
    }

		void Update()
    {
        myText.text = counter.ToString();
        counter++;

				switch (taskState)
        {
						case TaskState.INIT:
		            taskState = TaskState.WAIT_COMMANDS;
                Debug.Log("WAIT COMMANDS");
								break;
						case TaskState.WAIT_COMMANDS:
								if (Input.GetKeyDown(KeyCode.A))
                {
		                _serialPort.Write("ledON\n");
                    Debug.Log("Send ledON");
                }
								if (Input.GetKeyDown(KeyCode.S))
                {
                    _serialPort.Write("ledOFF\n");
                    Debug.Log("Send ledOFF");
                }
								if (Input.GetKeyDown(KeyCode.R))
                {
                    _serialPort.Write("readBUTTONS\n");
                    Debug.Log("Send readBUTTONS");
                }
								if (_serialPort.BytesToRead > 0)
                {
                    string response = _serialPort.ReadLine();
                    Debug.Log(response);
                }
								break;
						default:
                Debug.Log("State Error");
								break;
        }
    }
}

**R\:** El programa nos perimite configurar un led y cuatro botones, dpendiendo del boton que presionemos nos mostrara un estado diferente el cula se mostrara en el puerto serial. Con la tecla A manda un mensaje de que el led esta encendido, con la tecla S manda un mensaje que muestra que el led esta apagado y con la tecla R manda el mensaje de leer botones.
