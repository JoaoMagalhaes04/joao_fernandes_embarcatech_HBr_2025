Arquitetura Modular - Conversão ADC para Temperatura

📚 Objetivo

Este projeto demonstra uma arquitetura modular em C para leitura de valores do ADC interno do Raspberry Pi Pico W e conversão para temperatura em graus Celsius, com validação por testes unitários utilizando a biblioteca Unity.

📂 Estrutura do Repositório

/ADC_CONERSAO
│── /Unity               # Biblioteca Unity (src/unity.c e unity.h)
│── /build               # Diretório de build (gerado pela compilação)
│── /vscode              # Configurações do VS Code (opcional)
│── Makefile             # Script de compilação para testes
│── CMakeLists.txt       # Arquivo para compilação via CMake (não utilizado neste projeto)
│── pico_sdk_import.cmake# Inclusão do SDK do Raspberry Pi (reservado)
│── temperature.c        # Implementação da conversão ADC → °C
│── temperature.h        # Cabeçalho da função de conversão
│── test_temperature.c   # Teste unitário usando Unity
│── blink.pio            # Arquivo gerado pelo SDK (não usado neste projeto)
│── .gitignore           # Arquivos ignorados pelo Git

🧪 Testes

O projeto utiliza a biblioteca Unity para validar a conversão de valores do ADC em temperatura.
Para compilar e rodar os testes:

make
./test_temperature

🛠️ Compilação

O Makefile está configurado para compilar automaticamente temperature.c, test_temperature.c e Unity/src/unity.c. Verifique se os caminhos estão corretos no seu sistema.

👤 Autor

João Fernandes – Hbr Campinas

Contribuições são bem-vindas! Se tiver sugestões ou dúvidas, sinta-se à vontade para abrir uma issue. 🚀