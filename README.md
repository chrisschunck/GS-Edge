Projeto ESP32 + Node‑RED Dashboard
🔎 Visão Geral
Este projeto conecta um ESP32 rodando sensores (DHT22 e LDR) a um broker MQTT, e usa o Node‑RED para receber os dados e exibi‑los em tempo real em um dashboard web com gauges.
---
⚙️ Componentes Utilizados
• ESP32 (simulado no Wokwi ou físico)
• Sensor DHT22 (temperatura e umidade)
• Sensor LDR (luminosidade)
• Broker MQTT (IP: 100.28.226.153, porta: 1883)
• Node‑RED (rodando localmente no Mac)
• Node‑RED Dashboard (interface web em http://localhost:1880/ui)
---
📡 Fluxo de Dados

ESP32 coleta dados dos sensores:

Temperatura (°C
Umidade (%)
Luminosidade (0–4095)

Publica via MQTT no tópico:
futuro_trabalho/sensores

com payload JSON:
{"temperatura":24.0,"umidade":40.0,"luminosidade":1001}

Node‑RED recebe a mensagem:
Nó mqtt in → recebe do broker
Nó json → transforma em objeto
Nós function → extraem cada campo
Nós gauge → exibem os valores no dashboard

🛠️ Configuração do Node‑RED
MQTT In Node
Server: 100.28.226.153
Port: 1883
Topic: futuro_trabalho/sensores

Function Nodes
Temperatura:
msg.payload = msg.payload.temperatura;
return msg;
Umidade:
msg.payload = msg.payload.umidade;
return msg;
Luminosidade:
msg.payload = msg.payload.luminosidade;
return msg;


Como Rodar
Inicie o Node‑RED:
node-red
Abra o editor em:
http://localhost:1880
Importe o fluxo e clique em Deploy.
http://localhost:1880/ui
Rode o código no ESP32 (Wokwi ou físico).
Veja os gauges atualizando em tempo real.

🎯 Funcionalidades Extras
• LED no ESP32 acende se temperatura > 28 °C.
• Possibilidade de adicionar charts para histórico de dados.
• Fácil expansão para novos sensores ou alarmes.
