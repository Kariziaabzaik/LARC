# Projeto de Controle com ESP32: ADC, PWM e Timer

Este repositório documenta a implementação de um sistema embarcado utilizando ESP32. O projeto foi desenvolvido em etapas incrementais (versões 0.1 a 1.0).

## 🗂️ Versões do Projeto

O código foi dividido para validar cada conceito isoladamente antes da integração final:

### v0.1 - Leitura de ADC
* **Descrição:** Implementação da leitura de sensores (como potenciômetros) através das portas analógicas do ESP32. O foco desta versão é garantir a aquisição correta dos dados de entrada.
* **Código-Fonte:** [**`v0.1_Leitura_de_ADC.ino`**](./v0.1_Leitura_de_ADC.ino)
* **Simulação Wokwi:** [![Wokwi](https://img.shields.io/badge/Wokwi-Simulação_Serial-blue?logo=wokwi&logoColor=white)](https://wokwi.com/projects/449264190995390465)

### v0.2 - Interrupção Temporizada
* **Descrição:** Configuração do hardware timer para gerar eventos periódicos precisos. O código demonstra como contar segundos em segundo plano sem bloquear o `void loop`, utilizando interrupções e flags de controle.
* **Código-Fonte:** [**`v0.2_Interrupcao_Temporizada.ino`**](./v0.2_Interrupcao_Temporizada.ino)
* **Simulação Wokwi:** [![Wokwi](https://img.shields.io/badge/Wokwi-Simulação_Serial-blue?logo=wokwi&logoColor=white)](https://wokwi.com/projects/449264024976435201)
---

1.  Clique no link de "Código-Fonte" para ver o script `.ino` usado.
2.  Clique no "badge" da simulação para abrir o projeto no Wokwi.
3.  No Wokwi, clique no botão de **Play** verde para iniciar a simulação.

*Projeto desenvolvido pela LARC (Liga Acadêmica de Robótica e Controle) - 2025.2*
