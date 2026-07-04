# Fundamentos de Sistemas Operacionais

Repositório acadêmico da disciplina **FBX4052 - Fundamentos de Sistemas Operacionais**, contendo anotações, exercícios e projetos desenvolvidos em linguagem C, com foco em conceitos fundamentais de sistemas operacionais, programação em ambiente Linux, processos, threads, sincronização e análise de chamadas de sistema.

## Objetivo

O objetivo deste repositório é centralizar os estudos e implementações práticas da disciplina de Fundamentos de Sistemas Operacionais, permitindo acompanhar a evolução dos conteúdos trabalhados em aula e dos exercícios desenvolvidos ao longo do semestre.

Entre os principais temas abordados estão:

* criação e gerenciamento de processos;
* uso de threads com `pthreads`;
* sincronização com mutex, semáforos e barreiras;
* análise de chamadas de sistema;
* programação em C no Linux;
* organização de projetos com CMake e Makefile;
* projeto final de análise de dados utilizando múltiplas threads.

## Tecnologias utilizadas

* Linguagem C
* Linux
* GCC
* Make
* CMake
* POSIX Threads (`pthreads`)
* Shell/terminal Linux

## Estrutura do repositório

```text
fundamentos-OS/
├── Processos/
├── Threads/
├── Projeto/
├── exercicios/
│   └── analise-chamadas-sistema/
├── .gitignore
└── Fundamentos de Sistemas Operacionais.rar
```

## Diretórios principais

### `Processos/`

Contém materiais, anotações e atividades relacionadas ao estudo de processos em sistemas operacionais.

Esse conteúdo envolve conceitos como criação de processos, execução concorrente, chamadas de sistema e comportamento de programas em ambiente Linux.

### `Threads/`

Contém exemplos e exercícios sobre programação com threads.

Dentro desse diretório há exemplos envolvendo:

* barreiras;
* mutex;
* semáforos;
* variáveis de condição;
* testes com CMake;
* exercícios práticos de sincronização.

A pasta é voltada ao estudo de concorrência e paralelismo utilizando a biblioteca `pthread`.

### `Projeto/`

Contém arquivos relacionados ao projeto desenvolvido durante a disciplina.

O projeto trabalha conceitos de processamento concorrente/paralelo em C, com uso de `pthreads`, leitura de arquivos, processamento de dados e organização com CMake.

## Projeto principal

O projeto principal da disciplina está disponível em um repositório separado:

[fundamentos-OS-Projeto](https://github.com/JpEscobarM/fundamentos-OS-Projeto)

Esse projeto consiste em uma aplicação em C para análise de dados de sensoriamento, utilizando `pthreads` para processamento paralelo.

O programa processa arquivos JSON com medições de sensores e calcula estatísticas como:

* temperatura;
* umidade;
* pressão atmosférica;
* nível de bateria;
* spreading factors;
* logs de execução;
* tempo total de processamento.

## Anotações da disciplina

O arquivo:

```text
Fundamentos de Sistemas Operacionais.rar
```

contém anotações do material e exercícios resolvidos da disciplina.

Para visualizar esse conteúdo, siga os passos abaixo:

1. Crie uma conta no site [tldraw](https://www.tldraw.com/).
2. Descompacte o arquivo `.rar`.
3. Importe no tldraw o arquivo:

```text
Fundamentos de Sistemas Operacionais.tldr
```

Esse arquivo reúne anotações visuais feitas durante os estudos da disciplina.

## Exercícios

### `exercicios/analise-chamadas-sistema/`

Contém exercícios relacionados à análise de chamadas de sistema.

Essa pasta inclui exemplos simples em C e Python, além de um arquivo de análise documentando o comportamento observado durante a execução dos programas.

## Requisitos

Para compilar e executar os projetos em C, recomenda-se utilizar um ambiente Linux com os seguintes pacotes instalados:

```bash
gcc
make
cmake
```

Em distribuições baseadas em Debian/Ubuntu, é possível instalar com:

```bash
sudo apt update
sudo apt install build-essential cmake
```

## Como compilar projetos com CMake

Quando o exercício ou projeto possuir um arquivo `CMakeLists.txt`, o processo comum de compilação é:

```bash
mkdir build
cd build
cmake ..
make
```

Após a compilação, execute o binário gerado dentro da pasta `build`.

Exemplo:

```bash
./nome_do_executavel
```

## Observações sobre o build

A pasta `build/` não deve ser versionada no Git, pois contém arquivos gerados durante a compilação.

Sempre que novos arquivos `.c` forem adicionados a um projeto com CMake, o arquivo `CMakeLists.txt` deve ser atualizado para incluir esses arquivos na geração do executável.

Exemplo:

```cmake
add_executable(analise
    src/main.c
    src/arquivo_novo.c
)
```

Após alterar o `CMakeLists.txt`, execute novamente:

```bash
cmake ..
make
./analise
```

## Conceitos trabalhados

Este repositório reúne práticas relacionadas a diversos conceitos de Sistemas Operacionais, como:

* processos;
* threads;
* concorrência;
* paralelismo;
* sincronização;
* mutex;
* semáforos;
* barreiras;
* variáveis de condição;
* chamadas de sistema;
* gerenciamento de recursos;
* entrada e saída em arquivos;
* compilação de programas em C no Linux.

## Finalidade acadêmica

Este repositório foi desenvolvido para fins acadêmicos, como parte das atividades da disciplina de Fundamentos de Sistemas Operacionais.

O conteúdo aqui presente tem como objetivo apoiar o aprendizado prático de conceitos vistos em aula, principalmente por meio de implementação em C no ambiente Linux.
