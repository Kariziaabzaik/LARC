# Projeto de Controle com ESP32: ADC, PWM e Timer

Este repositório documenta a implementação de um sistema embarcado utilizando ESP32. O projeto foi desenvolvido em etapas incrementais (versões 0.1 a 1.0).

## 🗂️ Versões do Projeto

O código foi dividido para validar cada conceito isoladamente antes da integração final:

### 🔹 v0.1 - Leitura de ADC
* **Conceito:** Conversão Analógico-Digital.
* **Descrição:** Implementação da leitura de sensores (como potenciômetros) através das portas analógicas do ESP32. O foco desta versão é garantir a aquisição correta dos dados de entrada.
* **Arquivo:** `v0.1_Leitura_de_ADC.ino`
 
### 🔹 v0.2 - Interrupção Temporizada (Atual)
* **Foco:** Base de Tempo.
* **Descrição:** Configuração do hardware timer para gerar eventos periódicos precisos. O código demonstra como contar segundos em segundo plano sem bloquear o `void loop`, utilizando interrupções e flags de controle.
* **Arquivo:** `v0.2_Interrupcao_Temporizada.ino`
* 
---
*Projeto desenvolvido pela LARC (Liga Acadêmica de Robótica e Controle) - 2025.2*
