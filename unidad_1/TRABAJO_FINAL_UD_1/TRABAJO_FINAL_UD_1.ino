void config() {


 enum class estadosConfig { Config, subirT, bajarT, iniciarT };


  static estadosConfig estado = estadosConfig::Config;

   static uint32_t contador = 5000;

   uint32_t *pcontador = &contador;

   static char boton;

   static bool dialog = false;

  switch (estado)
{
  case estadosConfig::Config:
  {
    if (Serial.available() > 0)
        {
          if (!dialog) {
 
    Serial.begin(115200);
    Serial.print("CONFIG");
    Serial.print('\n');
    Serial.print('\n');
    Serial.print("el contador puede durar hasta minimo 1 segundo y maximo 40 segundos");
    Serial.print('\n');
    Serial.print("el tiempo actual del contador es de ");
    Serial.print(contador/1000);
    Serial.print(" segundos");
        Serial.print('\n');
    Serial.print("presiona (S) para aumentar el tiempo del contador 1 segundo");
    Serial.print('\n');
    Serial.print("presiona (B) para disminuir el tiempo del contador 1 segundo");
    Serial.print('\n');
    Serial.print("presiona (J) para iniciar el contador");
    dialog = true;
        }
        }
    break;
  }
}
}





void setup() {
  // put your setup code here, to run once:
 config();
}


void loop() {
  // put your main code here, to run repeatedly:
 config();
}






