# SousVide — Controlador IoT de Temperatura (ESP32)

> Controlador de temperatura baseado em ESP32 para um sistema de sous vide / aquecimento de baixa tensão, alimentado por uma resistência de imersão de 12V compatível com energia fotovoltaica.

[![Platform](https://img.shields.io/badge/platform-ESP32-blue)](https://www.espressif.com/en/products/socs/esp32)
[![Framework](https://img.shields.io/badge/framework-Arduino-00979D)](https://www.arduino.cc/)
[![Build](https://img.shields.io/badge/build-PlatformIO-orange)](https://platformio.org/)
[![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow)](#roadmap)
[![License](https://img.shields.io/badge/license-MIT-green)](#licença)

---

## 📖 Sobre o projeto

O **SousVide** é um projeto de hardware + firmware que transforma uma resistência de imersão de baixa tensão em um controlador de temperatura inteligente, pensado para funcionar de forma eficiente com fontes de **energia solar fotovoltaica (12V)**.

O objetivo é ler a temperatura da água/líquido em tempo real através de um sensor digital e, futuramente, acionar a resistência de forma controlada (via relé/MOSFET) para manter a temperatura dentro de uma faixa definida pelo usuário — abrindo caminho para features de IoT como monitoramento remoto, dashboard e automação.

> ⚠️ **Estágio atual:** projeto em desenvolvimento inicial (protótipo). A leitura de temperatura já está mapeada via PlatformIO; o algoritmo de controle (PID, liga/desliga, etc.) e a conectividade (WiFi/app/dashboard) ainda **não foram implementados** e fazem parte do roadmap.

---

## 🔧 Hardware

### Elemento de aquecimento

| Especificação | Valor |
|---|---|
| Material do tubo | Aço Inox 304 |
| Comprimento | 200 mm |
| Rosca | 1.1/4" BSP em Latão (padrão universal para aquecedores) |
| Potência | 120 W |
| Tensão | 12 V |
| Aplicação | Compatível com placas fotovoltaicas (baixa tensão) |
| Itens inclusos | 1x Resistência de imersão |

### Microcontrolador

- **Placa:** ESP32 (DOIT ESP32 DEVKIT V1)
- **Framework:** Arduino (via PlatformIO)
- **Sensor de temperatura:** DS18B20 (via barramento OneWire)

### Bibliotecas utilizadas

| Biblioteca | Versão | Função |
|---|---|---|
| [`milesburton/DallasTemperature`](https://github.com/milesburton/Arduino-Temperature-Control-Library) | ^3.11.0 | Leitura do sensor de temperatura DS18B20 |
| [`paulstoffregen/OneWire`](https://github.com/PaulStoffregen/OneWire) | ^2.3.8 | Comunicação com dispositivos OneWire |

---

## ✨ Funcionalidades

- [x] Leitura de temperatura via sensor digital DS18B20
- [ ] Algoritmo de controle de temperatura (PID / liga-desliga) — *em definição*
- [ ] Acionamento da resistência via relé/SSR
- [ ] Conectividade WiFi
- [ ] Dashboard / app para monitoramento e controle remoto
- [ ] Persistência de configurações (setpoint, histórico)

---

## 📁 Estrutura do projeto

```
SousVide/
├── .vscode/        # Configurações do editor (PlatformIO/VS Code)
├── docs/           # Documentação adicional do projeto
├── include/        # Headers (.h) do projeto
├── lib/            # Bibliotecas privadas/locais do projeto
├── src/            # Código-fonte principal (firmware)
├── test/           # Testes automatizados (PlatformIO Unit Testing)
├── platformio.ini  # Configuração de build, board e dependências
└── README.md
```

---

## 🚀 Como rodar o projeto

### Pré-requisitos

- [PlatformIO](https://platformio.org/install) (extensão para VS Code ou CLI)
- Placa ESP32 (DOIT DevKit V1) conectada via USB
- Sensor DS18B20 conectado ao pino OneWire configurado
- Driver serial da placa instalado (ex: CP2102/CH340, dependendo do modelo)

### Clonando o repositório

```bash
git clone https://github.com/newsantoryu/SousVide.git
cd SousVide
```

### Compilando e enviando o firmware

Com a extensão do PlatformIO no VS Code, basta abrir a pasta do projeto e usar os botões **Build** e **Upload**.

Ou, via linha de comando:

```bash
# Compilar o firmware
pio run

# Enviar (upload) para a placa
pio run --target upload

# Monitorar a saída serial
pio device monitor
```

> **Nota:** o `platformio.ini` está configurado com `monitor_port` e `upload_port` fixos (`/dev/ttyACM0`). Se a sua placa aparecer em outra porta, ajuste essas variáveis ou remova as linhas para deixar o PlatformIO detectar automaticamente.

### Parâmetros de conexão

| Parâmetro | Valor |
|---|---|
| Board | `esp32doit-devkit-v1` |
| Baud rate (monitor) | 115200 |
| Baud rate (upload) | 921600 |

---

## 🗺️ Roadmap

- [ ] Definir e implementar estratégia de controle de temperatura (PID ou liga/desliga)
- [ ] Adicionar acionamento seguro da resistência (relé/SSR + proteções)
- [ ] Implementar conectividade WiFi
- [ ] Criar dashboard/app de monitoramento remoto
- [ ] Adicionar testes automatizados no diretório `test/`
- [ ] Documentar esquema elétrico e diagrama de ligação

---

## 🤝 Contribuindo

Contribuições são bem-vindas! Sinta-se à vontade para abrir uma [issue](https://github.com/newsantoryu/SousVide/issues) ou enviar um pull request.

1. Faça um fork do projeto
2. Crie uma branch para sua feature (`git checkout -b feature/nova-feature`)
3. Commit suas mudanças (`git commit -m 'feat: adiciona nova feature'`)
4. Push para a branch (`git push origin feature/nova-feature`)
5. Abra um Pull Request

---

## ⚠️ Aviso de segurança

Este projeto envolve o controle de um elemento de aquecimento elétrico em contato com líquidos. Embora opere em baixa tensão (12V), cuidados básicos de segurança elétrica e isolamento devem ser observados durante a montagem e o uso. Use por sua conta e risco.

---

## 📄 Licença

Distribuído sob a licença MIT. Veja `LICENSE` para mais informações.

---

## 👤 Autor

**newsantoryu**
GitHub: [@newsantoryu](https://github.com/newsantoryu)
