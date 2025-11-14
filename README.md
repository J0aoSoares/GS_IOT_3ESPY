# WorkCare IoT – Estação de Bem-Estar no Trabalho

### João Victor Soares Rodrigues
### RM551410

## 1. Introdução

O avanço da automação, da Internet das Coisas (IoT) e do trabalho remoto está transformando profundamente a forma como as pessoas exercem suas atividades profissionais. Nesse contexto, aspectos como **saúde**, **bem-estar** e **qualidade do ambiente de trabalho** tornam-se cada vez mais relevantes para garantir produtividade e sustentabilidade no “Futuro do Trabalho”.

Este projeto apresenta uma **estação de bem-estar** baseada em ESP32, capaz de monitorar variáveis ambientais (temperatura e umidade) e o tempo de trabalho contínuo, emitindo alertas visuais quando condições de desconforto ou possível fadiga são identificadas. Além disso, os dados são enviados via **MQTT**, caracterizando uma aplicação prática de IoT alinhada ao tema proposto pela disciplina.

## 2. Objetivos

### 2.1 Objetivo Geral

Desenvolver uma solução simples e de baixo custo, utilizando ESP32, sensor DHT22 e um LED, que monitore o ambiente de trabalho e o tempo de uso, fornecendo alertas e enviando dados via MQTT, como exemplo de aplicação do conceito de IoT no contexto do Futuro do Trabalho.

### 2.2 Objetivos Específicos

- Monitorar temperatura e umidade do ambiente em tempo real por meio do sensor DHT22.
- Controlar um LED de alerta com base em condições pré-definidas de conforto térmico e tempo de trabalho contínuo.
- Enviar os dados coletados (temperatura, umidade, tempo de trabalho e estado de alerta) para um broker MQTT.
- Simular o funcionamento do sistema no ambiente Wokwi, demonstrando a integração entre hardware, software e comunicação IoT.
- Discutir o impacto da solução na promoção de saúde e bem-estar no ambiente de trabalho.

## 3. Fundamentação Teórica (Resumo)

### 3.1 Internet das Coisas (IoT)

A Internet das Coisas (IoT) consiste na conexão de dispositivos físicos à internet, permitindo a coleta, o envio e o processamento de dados de forma automatizada. No contexto do trabalho, a IoT possibilita a criação de **ambientes inteligentes**, capazes de monitorar condições, reagir a eventos e apoiar decisões relacionadas à produtividade e bem-estar.

### 3.2 ESP32

O **ESP32** é um microcontrolador com recursos de Wi-Fi e Bluetooth integrados, amplamente utilizado em projetos de IoT por seu baixo custo, flexibilidade e facilidade de programação por meio da IDE Arduino ou plataformas similares. Neste projeto, o ESP32 é responsável por:

- Ler os dados do sensor DHT22;
- Processar a lógica de decisão (alertas);
- Acionar o LED;
- Conectar-se ao Wi-Fi;
- Enviar dados ao broker MQTT.

### 3.3 Sensor DHT22

O **DHT22** é um sensor digital de temperatura e umidade. Ele fornece leituras razoavelmente precisas para aplicações didáticas, sendo amplamente utilizado em projetos de monitoramento ambiental. No Wokwi, o DHT22 é conectado ao ESP32 por meio do pino de dados (SDA).

### 3.4 Protocolo MQTT

O **MQTT (Message Queuing Telemetry Transport)** é um protocolo leve de comunicação voltado para IoT, baseado no modelo **publicador/assinante (pub/sub)**. No projeto, o ESP32 atua como **publicador**, enviando mensagens em formato JSON para um tópico em um broker MQTT público. Essas mensagens podem ser consumidas por dashboards, aplicações web ou outros dispositivos.

## 4. Materiais e Métodos

### 4.1 Componentes Utilizados (Simulação Wokwi)

- 1x ESP32 DevKit (ESP32 Dev Module)
- 1x Sensor DHT22 (temperatura e umidade)
- 1x LED (qualquer cor)
- 1x Resistor de 220 Ω (para o LED)
- Fios de conexão virtuais (no ambiente Wokwi)

### 4.2 Ferramentas de Software

- Simulador **Wokwi** (projeto ESP32)
- IDE Arduino (ou editor de código do próprio Wokwi)
- Broker MQTT público (ex.: `broker.hivemq.com`)
- Cliente MQTT opcional (ex.: MQTT Explorer) para visualizar mensagens

### 4.3 Ligações no Wokwi

**Sensor DHT22:**

- VCC → 3V3 do ESP32
- SDA (dados) → GPIO 15 do ESP32
- NC → não conectado
- GND → GND do ESP32

**LED de Alerta:**

- Anodo (perna maior) → resistor de 220 Ω → GPIO 2 do ESP32
- Catodo (perna menor) → GND do ESP32

### 4.4 Estrutura do Repositório

Sugestão de estrutura de pastas para o repositório GitHub:

```text
WorkCare-IoT/
├─ src/
│  └─ workcare_iot.ino      # Código-fonte principal do ESP32
└─ README.md                # Documentação do projeto (este arquivo)
```

## 5. Desenvolvimento do Projeto

### 5.1 Lógica de Funcionamento

1. Na inicialização, o ESP32 configura o sensor DHT22, o LED e estabelece conexão Wi-Fi com a rede do simulador Wokwi.
2. Em seguida, o ESP32 se conecta ao broker MQTT público.
3. Um temporizador registra o momento de início do “período de trabalho”.
4. Em intervalos regulares (por exemplo, a cada 5 segundos), o sistema:
   - Lê temperatura e umidade do DHT22;
   - Calcula o tempo de trabalho contínuo desde o início;
   - Verifica se a temperatura ultrapassa um limiar de conforto (ex.: 28 °C);
   - Verifica se o tempo de trabalho excede um limite pré-definido (por exemplo, 50 minutos em um cenário real, ou um valor menor em simulação);
   - Caso alguma condição de desconforto seja detectada, o LED é aceso e o estado é marcado como “alerta”;
   - Caso contrário, o LED permanece apagado e o estado é “normal”.
5. Após processar a lógica, o ESP32 monta um **payload JSON** com os dados lidos e o estado de alerta e o publica em um tópico MQTT.

### 5.2 Trecho Resumido do Código

Abaixo, um trecho ilustrativo (resumido) do código utilizado no ESP32:

```cpp
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

const int DHT_PIN = 15;
const int LED_PIN = 2;

DHTesp dht;
WiFiClient espClient;
PubSubClient client(espClient);

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqttServer = "broker.hivemq.com";
const int   mqttPort   = 1883;

unsigned long inicioTrabalho = 0;
// Exemplo: 50 minutos em milissegundos
const unsigned long LIMITE_TRABALHO_MS = 50UL * 60UL * 1000UL;

void setup() {
  Serial.begin(115200);
  dht.setup(DHT_PIN, DHTesp::DHT22);
  pinMode(LED_PIN, OUTPUT);
  // Conexão Wi-Fi e MQTT (funções auxiliares omitidas)
  inicioTrabalho = millis();
}

void loop() {
  // Verificações de conexão Wi-Fi/MQTT (omitidas)
  unsigned long agora = millis();
  TempAndHumidity data = dht.getTempAndHumidity();

  float temperatura = data.temperature;
  float umidade = data.humidity;
  unsigned long tempoTrabalho = agora - inicioTrabalho;

  bool ambienteRuim   = (temperatura > 28.0);
  bool tempoExcedido  = (tempoTrabalho > LIMITE_TRABALHO_MS);
  bool alerta         = ambienteRuim || tempoExcedido;

  digitalWrite(LED_PIN, alerta ? HIGH : LOW);

  // Montagem e publicação do payload MQTT (omitidos neste trecho)
}
```

*(No projeto completo, as funções de conexão Wi-Fi, reconexão MQTT e publicação do JSON são implementadas.)*

## 6. Demonstração e Testes

A validação do sistema foi realizada em duas etapas principais:

### 6.1 Teste de Lógica Local (Serial Monitor)

- O projeto foi executado no Wokwi, observando-se, no **Serial Monitor**, os valores de temperatura, umidade e tempo de trabalho.
- Foram verificados os momentos em que o LED era acionado, tanto por temperatura acima do limite quanto por estouro do tempo de trabalho configurado (em simulação, um tempo menor foi usado para facilitar a visualização).

### 6.2 Teste de Envio MQTT

- Com o ESP32 conectado ao broker `broker.hivemq.com`, o projeto publicou os dados no tópico:
  - `workcare/estacao1/sensores`
- Utilizando um cliente MQTT, foi possível se inscrever (`subscribe`) nesse tópico e visualizar as mensagens JSON, confirmando a comunicação IoT.

## 7. Resultados Esperados e Discussão

O projeto conseguiu integrar, de forma simples, conceitos importantes relacionados ao Futuro do Trabalho:

- **Automação e monitoramento contínuo:** o sistema monitora variáveis ambientais sem intervenção humana, reduzindo a dependência da percepção subjetiva do trabalhador.
- **Feedback em tempo real:** o LED funciona como um alerta imediato, sugerindo pausas ou ajustes no ambiente.
- **Uso de dados para tomada de decisão:** os dados enviados via MQTT podem ser armazenados e analisados por aplicações externas, permitindo visualizar padrões de conforto/desconforto e carga de trabalho.
- **Baixo custo e acessibilidade:** a solução utiliza componentes amplamente disponíveis, podendo ser adaptada para home offices, coworkings e pequenas empresas.

Além disso, o projeto reforça a importância de considerar o bem-estar do trabalhador em ambientes cada vez mais digitais e conectados, demonstrando que tecnologias simples podem gerar benefícios práticos no dia a dia.

## 8. Conclusão

A “Estação de Bem-Estar WorkCare IoT” demonstra, de forma didática, como a combinação de **ESP32**, **sensores ambientais**, **atuadores simples** (LED) e **comunicação MQTT** pode ser aplicada para promover saúde e qualidade de vida no ambiente de trabalho, alinhando-se ao tema do Futuro do Trabalho.

Mesmo com uma configuração mínima (um microcontrolador, um sensor e um LED), o sistema é capaz de:
- Monitorar o ambiente;
- Auxiliar na gestão de pausas;
- Enviar dados para a nuvem;
- Servir de base para soluções mais complexas.

Como trabalhos futuros, podem ser consideradas extensões como:
- Inclusão de um botão para registrar manualmente o início e o fim de pausas;
- Integração com um painel web ou dashboard (por exemplo, Node-RED, Grafana);
- Armazenamento histórico dos dados para análise a longo prazo;
- Uso de múltiplos sensores (luminosidade, ruído, presença) para enriquecer o monitoramento.

## 9. Como Executar o Projeto

1. Acessar o simulador Wokwi e criar um novo projeto com ESP32.
2. Adicionar o sensor DHT22 e o LED ao circuito, realizando as conexões conforme descrito na Seção 4.3.
3. Copiar o código-fonte completo para o arquivo `.ino` do projeto.
4. Executar o simulador e abrir o Serial Monitor para acompanhar as leituras.
5. (Opcional) Utilizar um cliente MQTT para se inscrever no tópico configurado e visualizar as mensagens publicadas.

---

**Observação:** este README foi elaborado em formato acadêmico, com seções de contextualização, objetivos, fundamentação teórica, materiais e métodos, desenvolvimento, resultados esperados e conclusão, podendo ser adaptado conforme as exigências específicas da disciplina ou instituição.
