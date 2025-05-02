Arquitetura Modular

📚 Objetivo

Este repositório apresenta um exemplo de projeto modular em C para o Raspberry Pi Pico W, com foco em organização por camadas (HAL, drivers e aplicação). O projeto pode ser facilmente expandido para incluir sensores, atuadores e periféricos, mantendo separação clara entre hardware e lógica de aplicação.

📂 Estrutura do Repositório

/ARQUITETURA_MODULAR
│── /app               # Código da aplicação principal (main.c, lógica de uso)
│── /build             # Diretório de build (gerado pelo CMake)
│── /drivers           # Módulos de drivers (ex: sensores, botões, joystick)
│── /hal               # Camada de abstração de hardware (ex: ADC, GPIO)
│── /include           # Arquivos de cabeçalho compartilhados
│── .vscode            # Configurações de ambiente do VS Code
│── CMakeLists.txt     # Configuração do projeto para CMake
│── pico_sdk_import.cmake # Inclusão do SDK do Raspberry Pi Pico
│── blink.pio          # Código PIO gerado ou incluído (opcional)
│── .gitignore         # Arquivos ignorados pelo Git
│── README.md          # Documentação do projeto

⚙️ Sobre a Arquitetura

O projeto segue a seguinte divisão modular:

    HAL (Hardware Abstraction Layer): encapsula o acesso direto ao hardware, como leitura de ADC ou controle de pinos.

    Drivers: implementa a lógica de dispositivos específicos, como sensores ou atuadores, usando a HAL.

    App: contém o fluxo principal da aplicação, utilizando os drivers de forma abstrata.

🛠️ Compilação

Este projeto é configurado para ser compilado com o CMake e o SDK da Raspberry Pi Pico.
Exemplo de compilação:

mkdir build
cd build
cmake ..
make

👤 Autor

João Fernandes – Hbr Campinas

Contribuições, dúvidas ou sugestões são muito bem-vindas! Abra uma issue ou envie um PR 🚀