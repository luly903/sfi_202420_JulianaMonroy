
uint32_t valor1=1;

uint32_t valor2=2;

uint32_t extra;

uint32_t *pvalor1 = &valor1;
uint32_t *pvalor2 = &valor2;

void cambio(uint32_t *valorA, uint32_t *valorB)
{

extra = *pvalor2;
valor2 = *pvalor1;
valor1 = extra;

  Serial.print("valores despues del intercambio:");
    Serial.print('\n');
  Serial.print(valor1);
    Serial.print('\n');
  Serial.print(valor2);

}

void principal()
{
  Serial.begin(115200);

  uint32_t valor1=1;

uint32_t valor2=2;

uint32_t *pvalor1 = &valor1;
uint32_t *pvalor2 = &valor2;

  Serial.print("valores antes del intercambio:");
    Serial.print('\n');
  Serial.print(valor1);
    Serial.print('\n');
  Serial.print(valor2);

cambio(&valor1, &valor2);

}

void setup() {
  // put your setup code here, to run once:
principal();
}

void loop() {
  // put your main code here, to run repeatedly:
principal();
}
