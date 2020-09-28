////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Arquivo:   ESP32_DHT11.ino
//Tipo:      Codigo-fonte para utilizar no ESP32 atraves da IDE do Arduino
//Autor:     Jackson Roberio - Idéias Eletrônicas Avançadas (IEA) 
//Descricao: Medidor de Temperatura e Umidade - Ler dados de sensores de umidade e temperatura (DHT11, DHT22 ou DHT21), 
//           enviando os dados através de comunicação bluetooth para comunicação com o app Medidor de Temperatura - IEA.
//Git:       https://github.com/IdeiasEletronicasAplicadas/medidor-de-temperatura
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "DHT.h"

/*
Equivalencia das saidas Digitais entre NodeMCU e ESP8266 (na IDE do Arduino)
NodeMCU - ESP8266
D0 = 16;
D1 = 5;
D2 = 4;
D3 = 0;
D4 = 2;
D5 = 14;
D6 = 12;
D7 = 13;
D8 = 15;
D9 = 3;
D10 = 1;
*/
#define DHTPIN D3

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)


DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  // Aguarde alguns segundos entre as medições, o DHT11 foi projetado para trabalhar em intervalo mínimo de ...
  delay(2000);

  // A leitura da temperatura ou umidade leva cerca de 250 milissegundos!
  // As leituras do sensor também podem ter até 2 segundos de idade (é um sensor muito lento)
  float h = dht.readHumidity();
  
  // Ler a temperatura como Celsius (o padrão)
  float t = dht.readTemperature();
  
  // Ler a temperatura como Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Verifique se alguma leitura falhou e saia mais cedo (para tentar novamente).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Calcula o Índice de calor em Fahrenheit (o padrão)
  float hif = dht.computeHeatIndex(f, h);
  
  // Calcule o índice de aquecimento em Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}
