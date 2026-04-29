# Interface de Controle de Braço Robótico – TCC (UNESP/CTIG)

Este software foi desenvolvido como parte do **Trabalho de Conclusão de Curso** de Automação Industrial no  
**Colégio Técnico Industrial de Guaratinguetá Professor Carlos Augusto Patrício Amorim – UNESP**, com o objetivo de criar uma interface para controle de um braço robótico utilizando um **Arduino**.

A interface permite o controle manual e automático do braço, registrando posições e permitindo repetição de movimentos.

---

## Funcionalidades Principais

- Interface gráfica desenvolvida com **PyQt5**
- Comunicação serial com **Arduino**
- Controle manual do braço robótico
- Registro de posições via encoder
- Execução automática de movimentos gravados

---

## Tecnologias Utilizadas

- **Python 3.12**
- **PyQt5** – Interface gráfica
- **PySerial** – Comunicação USB
- **Arduino** – Controle de hardware

---

## Código do Arduino

O funcionamento do sistema depende de um código embarcado no Arduino.

O arquivo está disponível na pasta "src/" e deve ser carregado na placa utilizando a Arduino IDE.

Certifique-se de que a porta serial e a taxa de comunicação estejam configuradas corretamente.

---

## Estrutura do Projeto

SoftwareTCCv1.2/
│
├── src/                          # Código-fonte completo do projeto
│   ├── InterfaceTCC1.7.py           # Código principal da aplicação
│   ├── uiInterfaceTCCCores.py       # Interface gerada pelo Qt Designer
│   ├── interfaceTCC2.ui         # Arquivo editável no Qt Designer
│   ├── (__pycache__/...)         # Arquivos automáticos do Python
│   ├── Arduino
│   └── TCCFinalFinalFinal2.ino
│
├── dist/                         # Pasta gerada pelo PyInstaller
│   ├── InterfaceTCC1.7.exe        # Executável final
│   ├── LICENSE                   # Licença GPLv3 (obrigatória no dist)
│   ├── README.md                 # Instruções para o usuário
│   └── registro de movimento     # Gerado automaticamente pelo software
│
├── build/                        # Arquivos temporários do PyInstaller
│   └── (gerados automaticamente)
│
├── InterfaceTCC1.7.spec             # Arquivo de configuração do PyInstaller
│
├── LICENSE                       # Licença completa (cópia principal)
└── README.md 

## Instalação das Dependências

Antes de rodar o sistema, instale as bibliotecas necessárias:

pip install pyqt5 pyserial

## Como executar

Na pasta do projeto, execute:

cd src python InterfaceTCC1.7.py
A interface será aberta imediatamente.

## Geração de Relatórios

Ao final de cada processo, o software automaticamente:

- Salva um arquivo .txt com todos os valores medidos

- Gera um PDF contendo:

 - Gráfico de tensão ao longo do tempo
 - Dados definidos pelo usuário
 - Dados finais medidos
 - Tensão, corrente, potência, pressão e temperatura

## Importação e exportação de parâmetros

A interface permite:

- Salvar os parâmetros digitados em um arquivo .txt
- Carregar arquivos salvos anteriormente

Ideal para testes repetitivos e calibrações.

## Licenciamento

Este projeto utiliza PyQt5, que é distribuída sob a GNU General Public License versão 3 (GPLv3).
Portanto, todo o projeto é distribuído sob a mesma licença GPLv3.

Isso garante:

- Acesso total ao código-fonte
- Direito de estudar, modificar e redistribuir
- Obrigação de manter a mesma licença em trabalhos derivados

O texto integral da GPLv3 encontra-se no arquivo LICENSE.

## Autores

- Caio Vianna Guimarães Galvão  
- Clara Fernandes de Oliveira  
- Davi Nascimento Gomes  
- João Pedro Soares Pereira  
- João Luis Garufe Coelho  

Trabalho de Conclusão de Curso – 2025
Colégio Técnico Industrial de Guaratinguetá – UNESP

## Orientação

- **Orientador:** Prof. Daniel Quintas Perez  
- **Coorientador:** Prof. Cléber Duarte Ferreira  
- **Coordenador:** Prof. Leandro Pimenta de Carvalho  

---

## Citação

Se usar este software em trabalhos acadêmicos, cite:

Galvão, C. V. G.; Oliveira, C. F.; Gomes, D. N.; Pereira, J. P. S.; Coelho, J. L. G. (2025).  
*Interface de Controle do Braço Robótico – TCC*.  
Colégio Técnico Industrial de Guaratinguetá – UNESP.