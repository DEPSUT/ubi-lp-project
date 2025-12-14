@mainpage Projeto de Laboratórios de Programação

# Introdução
Esta é documentação técnica do programa desenvolvido, aqui encontrará todos os detalhes técnicos que digam respeito à explicação e implementação da lógica deste programa.

Este trabalho foi desenvolvido no âmbito da Unidade Curricular de **Laboratório de Programação** do curso de Engenharia Informática da **Universidade da Beira Interior (UBI)**.

<!-- O objetivo principal é a demonstração de competências avançadas em linguagem C, nomeadamente:
* **Gestão Dinâmica de Memória (Heap):** Uso correto de `malloc`, `realloc` e `free`.
* **Tipos Abstratos de Dados (TDA):** Encapsulamento de vetores e matrizes.
* **Compilação Separada:** Organização modular do código.
* **Algoritmos Numéricos:** Implementação da Eliminação de Gauss com Pivotagem Parcial. -->

---

# Arquitetura e Estrutura de Ficheiros

O projeto segue uma arquitetura por camadas, separando claramente a lógica de apresentação, a lógica de negócio e as estruturas de dados fundamentais.

## Organização do Código Fonte

Abaixo descreve-se a responsabilidade de cada módulo do sistema:

### 1. Núcleo (_Linear Algebra_)
* **`lialg.h` / `lialg.c`:**
    * Contém a definição dos Tipos Abstratos de Dados `vector` e `matrix`.
    * Implementa toda a lógica matemática pesada (Eliminação de _Gauss_, Multiplicação de Matrizes, Ordenação).
    * Gere a alocação e libertação de memória dinâmica (`malloc`/`free`).

### 2. Controlador
* **`menu_functions.h` / `menu_functions.c`:**
    * Age como intermediário entre o utilizador e o núcleo matemático.
    * Implementa a **Tabela de Despacho** (*_Dispatch Table_*) que mapeia opções do menu a funções específicas.
    * Gere estados internos temporários (ex: a matriz estática gerada na opção 10).

### 3. Utilitários e Infraestrutura
* **`functions.h` / `functions.c`:**
    * Biblioteca auxiliar de baixo nível para _Input/Output_.
    * Gere a formatação segura de `strings` e a limpeza inteligente do ecrã (contagem de linhas).
* **`config.h`:**
    * Ficheiro de configuração global.
    * Define constantes como tamanho de vetores, limites numéricos e _flags_ de _debug_.

### 4. Ponto de Entrada
* **`main.c`:**
    * Responsável apenas pelo ciclo de vida da aplicação (Inicialização -> Loop Principal -> Conclusão).
    * Não contém lógica matemática complexa, delegando-a para os módulos apropriados.

---

# Compilação e Execução

Para compilar o projeto, utilize o `Makefile` fornecido na raiz do projeto:

```bash
make          # Compila o projeto e gera a pasta build/
make execute  # Compila (se necessário) e executa o programa
make clean    # Remove os ficheiros binários e objetos
```