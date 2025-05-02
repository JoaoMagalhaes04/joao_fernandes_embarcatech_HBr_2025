Arquitetura Modular

📚 Objetivo

Este repositório apresenta a implementação de uma arquitetura modular para leitura e conversão de valores analógicos do ADC interno do Raspberry Pi Pico W. O projeto inclui a conversão de valores lidos do sensor interno de temperatura em graus Celsius, além de testes unitários utilizando a biblioteca Unity.

📂 Estrutura do Repositório

/arquitetura_modular
│── /src            # Código-fonte principal (ex: temperature.c)
│── /include        # Cabeçalhos (.h)
│── /tests          # Testes unitários com Unity
│── /Unity          # Biblioteca Unity para testes
│   └── /src        # Arquivos unity.c e unity.h
│── Makefile        # Compilação dos testes
│── README.md       # Documentação do projeto

🧪 Testes

O projeto utiliza a biblioteca Unity para realizar testes unitários simples em C. O teste principal verifica se a conversão de ADC para temperatura está correta, com margem de erro aceitável.

Para rodar os testes:

make
./test_temperature

👤 Autor

João Fernandes – Hbr Campinas

Se tiver dúvidas, sugestões ou quiser contribuir, fique à vontade para abrir uma issue ou enviar um pull request. 🚀