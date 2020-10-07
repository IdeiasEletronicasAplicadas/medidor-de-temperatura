////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Arquivo:   ESP32_DHT11.ino
//Tipo:      Codigo-fonte para utilizar no ESP32 atraves da IDE do Arduino
//Autor:     Jackson Roberio - Idéias Eletrônicas Avançadas (IEA) 
//Descricao: Medidor de Temperatura e Umidade - Ler dados de sensores de umidade e temperatura (DHT11, DHT22 ou DHT21), 
//           enviando os dados através de comunicação bluetooth para comunicação com o app Medidor de Temperatura - IEA.
//Git:       https://github.com/IdeiasEletronicasAplicadas/medidor-de-temperatura
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "DHT.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;


//Altere GPIO preferencial do seu ESP32.
#define DHTPIN 17


// Remova o comentário de qualquer tipo que estiver usando!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)


DHT dht(DHTPIN, DHTTYPE);


String valorEnviadoBluethooth;

String humidade;
String temperatura;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32-IEA"); //Nome da rede bluethooth.
  dht.begin(); //Inicia a leitura do sensor de temperatura.

  //Usados apenas para facilitar o uso da memória e evitar repetição
  humidade = F("%, Humidade: ");
  temperatura = F("Temperatura: ");
}

void loop() {
  // Aguarde alguns segundos entre as medições, cada DHT foi projetado para trabalhar em intervalo mínimo de predeterminado.
  delay(3000);

  // A leitura da temperatura ou umidade leva cerca de 250 milissegundos!
  // As leituras do sensor também podem ter até 2 segundos de idade (é um sensor muito lento)
  float h = dht.readHumidity();
  
  // Ler a temperatura como Celsius (o padrão)
  float t = dht.readTemperature();
  

  // Verifique se alguma leitura falhou e envia mensagem de erro.
  if (!(isnan(h) || isnan(t))) {

    temperatura = F("Temperatura: ");
    humidade = F("ºC; Humidade: ");

    temperatura = temperatura + t;
    humidade = humidade + h;
  
    valorEnviadoBluethooth = temperatura + humidade + F("%");

    SerialBT.println(valorEnviadoBluethooth);
    
  } else {
    Serial.println(F("Falha ao ler sensor DHT!"));
    return;
 }

  Serial.println(valorEnviadoBluethooth);
}
