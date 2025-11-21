WorkCare IoT – Estação de Bem-Estar no Trabalho
================================================

### João Victor Soares Rodrigues
### RM551410

### Link Wokwi https://wokwi.com/projects/447550636336239617


1. Introdução
-------------

O avanço da automação, da Internet das Coisas (IoT) e dos modelos de trabalho híbridos e remotos está transformando profundamente a forma como as pessoas exercem suas atividades profissionais. Se, por um lado, essas mudanças ampliam a flexibilidade e a produtividade, por outro, trazem novos desafios relacionados à saúde, ao bem-estar e à qualidade do ambiente de trabalho.

Em cenários de home office ou escritórios com forte presença de tecnologia, é comum que profissionais permaneçam longos períodos em frente a telas, em ambientes nem sempre adequados em termos de conforto térmico, ergonomia e pausas regulares. Muitas vezes, a gestão do próprio bem-estar fica restrita à percepção subjetiva do trabalhador, que tende a negligenciar sinais de fadiga, estresse e desconforto.

Nesse contexto, o projeto **WorkCare IoT – Estação de Bem-Estar no Trabalho** propõe uma solução tecnológica simples, mas representativa, que utiliza conceitos de IoT para monitorar condições ambientais e o tempo de trabalho contínuo, auxiliando na promoção de hábitos mais saudáveis e na melhoria da qualidade de vida no ambiente profissional.

2. Problema de Pesquisa
-----------------------

O problema central abordado pelo projeto pode ser resumido da seguinte forma:

> Como apoiar, de forma simples e automatizada, a saúde e o bem-estar de trabalhadores em ambientes digitais, por meio do monitoramento contínuo de condições ambientais e de tempo de trabalho, utilizando tecnologias acessíveis de Internet das Coisas?

A questão envolve dois aspectos principais:

1. **Falta de monitoramento objetivo do ambiente de trabalho**  
   Em muitos contextos, especialmente no trabalho remoto, não há um sistema estruturado para acompanhar variáveis como temperatura e umidade. Ambientes muito quentes, frios ou abafados podem impactar diretamente a concentração, o conforto físico e o desempenho do profissional.

2. **Ausência de mecanismos de alerta para pausas**  
   Mesmo existindo recomendações sobre pausas periódicas, a decisão de interromper a atividade normalmente depende apenas da disciplina individual. Em situações de alta demanda, é comum que o trabalhador ultrapasse limites saudáveis de tempo contínuo em frente ao computador, aumentando o risco de fadiga e problemas de saúde.

Dessa forma, há uma lacuna entre o conhecimento sobre boas práticas de bem-estar no trabalho e a existência de ferramentas tecnológicas que ajudem, na prática, a implementar e reforçar esses cuidados no dia a dia.

3. Proposta do Projeto
----------------------

O projeto WorkCare IoT propõe o desenvolvimento de uma **estação de bem-estar** baseada em um microcontrolador ESP32, capaz de integrar três elementos principais:

1. **Monitoramento ambiental**  
   Utilização de um sensor de temperatura e umidade para acompanhar, em tempo real, as condições do ambiente em que o trabalhador está inserido. Esses dados permitem identificar situações de desconforto térmico, como calor excessivo, que podem afetar a saúde e a produtividade.

2. **Monitoramento do tempo de trabalho contínuo**  
   O sistema registra o tempo decorrido desde o início de um período de trabalho, simulando a rotina de uso do computador ou de permanência em atividade sem pausas. A partir de um limite pré-definido (por exemplo, 50 minutos em um cenário real), o sistema passa a considerar que há risco aumentado de fadiga e necessidade de descanso.

3. **Geração de alertas e envio de dados via IoT**  
   Com base na combinação entre condições ambientais e tempo de trabalho, o sistema classifica o estado do trabalhador em uma situação “normal” ou de “alerta”. Essa classificação é comunicada por meio de um atuador simples (como um LED), que serve como lembrete visual de que é necessário fazer uma pausa ou ajustar o ambiente. Paralelamente, os dados são enviados a um broker MQTT, permitindo que aplicações externas (dashboards, sistemas de análise, etc.) acompanhem o histórico de condições e alertas.

Em síntese, o projeto não se limita a medir variáveis isoladas, mas procura **integrar monitoramento, tomada de decisão automática e comunicação em rede**, caracterizando uma aplicação coerente com os princípios da Internet das Coisas no contexto do Futuro do Trabalho.

4. Objetivos
------------

### 4.1 Objetivo Geral

Desenvolver uma solução baseada em ESP32 e IoT que contribua para a promoção de saúde e bem-estar no ambiente de trabalho, por meio do monitoramento de condições ambientais e de tempo de trabalho contínuo, com geração de alertas e disponibilização dos dados em um canal de comunicação MQTT.

### 4.2 Objetivos Específicos

- Identificar fatores relacionados ao conforto e ao bem-estar no ambiente de trabalho que podem ser monitorados com sensores simples (como temperatura e umidade).
- Modelar uma lógica de decisão que considere, de forma combinada, as condições ambientais e o tempo de trabalho contínuo, identificando estados de normalidade e de alerta.
- Implementar uma solução embarcada capaz de:
  - ler dados de sensores ambientais;
  - acompanhar o tempo de trabalho;
  - acionar um mecanismo de alerta para o usuário;
  - enviar os dados coletados para um broker MQTT.
- Discutir de que forma soluções semelhantes podem ser ampliadas e integradas a ambientes corporativos, plataformas de monitoramento de bem-estar e políticas de saúde ocupacional.

5. Justificativa
----------------

O projeto se justifica tanto do ponto de vista tecnológico quanto do ponto de vista social.

Do ponto de vista tecnológico, a proposta evidencia o potencial de plataformas embarcadas (como o ESP32) e de protocolos de IoT (como o MQTT) para a construção de soluções voltadas ao cotidiano do trabalhador. Ao utilizar componentes acessíveis e uma arquitetura relativamente simples, o projeto se posiciona como uma **porta de entrada pedagógica** para temas como automação, computação em nuvem e análise de dados.

Do ponto de vista social, a iniciativa dialoga diretamente com a necessidade de **promover ambientes de trabalho mais saudáveis**, em um contexto em que as fronteiras entre vida pessoal e profissional se tornam menos nítidas, especialmente no home office. Ferramentas que auxiliem na organização do tempo, no respeito a pausas e na manutenção de condições ambientais adequadas tornam-se importantes aliadas na prevenção de problemas físicos e emocionais.

Além disso, o projeto está alinhado ao tema interdisciplinar “O Futuro do Trabalho”, ao demonstrar que a tecnologia pode ser utilizada não apenas para aumentar a produtividade, mas também para **cuidar do bem-estar humano**, promovendo um equilíbrio mais saudável entre desempenho e qualidade de vida.

6. Metodologia em Alto Nível
----------------------------

A metodologia adotada pode ser descrita de forma resumida em três etapas principais:

1. **Análise do problema e definição de requisitos**  
   Nesta etapa, foram identificados os principais fatores de bem-estar no ambiente de trabalho que poderiam ser abordados com uma solução de baixo custo. Definiram-se, então, os requisitos básicos do sistema: monitorar temperatura, umidade e tempo de trabalho, emitir alertas locais e enviar dados a um canal de comunicação IoT.

2. **Modelagem conceitual da solução**  
   A partir dos requisitos, foi elaborado um modelo conceitual no qual um dispositivo embarcado realiza as leituras de sensores, processa regras de decisão (limites de temperatura e de tempo de trabalho) e aciona alertas. Em paralelo, o dispositivo atua como nó de uma rede IoT, publicando periodicamente os dados coletados em um tópico MQTT. O foco dessa etapa é garantir que a solução proposta seja coerente com o cenário do Futuro do Trabalho, privilegiando simplicidade, baixo custo e potencial de expansão.

3. **Implementação e validação em ambiente simulado**  
   A solução foi implementada utilizando um ESP32 e simulada em ambiente virtual. Foram realizados testes para verificar se:
   - as leituras ambientais eram atualizadas corretamente;
   - o sistema detectava adequadamente as condições de alerta;
   - os dados eram enviados ao broker MQTT conforme o esperado.
   A validação permitiu confirmar a viabilidade da proposta e fornecer base para discussões sobre possíveis extensões.

7. Resultados Esperados e Relevância
------------------------------------

Embora o projeto não tenha como objetivo substituir sistemas complexos de gestão de saúde ocupacional, ele demonstra, na prática, que **pequenas soluções de IoT podem ter impacto significativo no dia a dia do trabalhador**. Entre os resultados esperados, destacam-se:

- Sensibilização sobre a importância de monitorar não apenas a produtividade, mas também as condições de trabalho e o bem-estar individual.
- Ilustração de como tecnologias simples podem ser combinadas para apoiar decisões relacionadas à saúde, por meio de alertas e registros de dados.
- Estímulo à reflexão sobre como empresas, escolas e instituições podem adotar ferramentas semelhantes para promover ambientes mais saudáveis e inteligentes.

Em termos de relevância, o projeto reforça a ideia de que o Futuro do Trabalho envolve, necessariamente, a integração entre **tecnologia, dados e cuidado com as pessoas**. Ao propor uma estação de bem-estar baseada em IoT, o WorkCare IoT contribui para o debate sobre como construir ambientes de trabalho mais humanizados em meio à crescente digitalização das atividades profissionais.

8. Considerações Finais
-----------------------

O projeto WorkCare IoT sintetiza, em uma solução compacta, diversos conceitos trabalhados em disciplinas de tecnologia, como sistemas embarcados, redes, IoT e comunicação de dados, aplicados a um problema concreto e atual: a promoção da saúde e do bem-estar no ambiente de trabalho.

Mais do que entregar um protótipo funcional, a proposta busca evidenciar que o desenvolvimento tecnológico pode – e deve – estar ao serviço da qualidade de vida. Em um cenário em que o Futuro do Trabalho tende a ser cada vez mais digital, automatizado e conectado, iniciativas como esta apontam para um caminho em que **a tecnologia atua como parceira do trabalhador**, ajudando a equilibrar desempenho, saúde e bem-estar.

Como desdobramentos futuros, a solução pode ser expandida para incluir novos tipos de sensores (como luminosidade e ruído), mecanismos de interação com o usuário (aplicativos, notificações em dispositivos móveis) e integração com plataformas de análise de dados, potencializando ainda mais sua aplicabilidade em contextos reais.
