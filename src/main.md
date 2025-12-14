@mainpage Projeto de Laboratórios de Programação

# Introdução
Esta é documentação técnica do programa desenvolvido, aqui encontrará todos os detalhes técnicos que dizem respeito à explicação e implementação da lógica deste programa.

Este trabalho foi desenvolvido no âmbito da Unidade Curricular de **Laboratório de Programação** do curso de Engenharia Informática da **Universidade da Beira Interior (UBI)**.

---

# Estrutura dos Ficheiros

O programa é separado em vários ficheiros para facilitar a leitura e o desenvolvimento, são separadas a lógica e a apresentação através de um intermediário (`menu_functions.c`) que os conecta.

## Organização do Código Fonte

Abaixo descreve-se a responsabilidade de cada módulo do sistema:

### 1. Matemática (_Linear Algebra_)
* **`lialg.h` / `lialg.c`:**
    * Contém a definição dos Tipos Abstratos de Dados `vector` e `matrix`.
    * Implementa toda a lógica matemática pesada (Eliminação de _Gauss_, Multiplicação de Matrizes, Ordenação).
    * Gere a alocação e libertação de memória dinâmica (`malloc`/`free`).

### 2. Controlador
* **`menu_functions.h` / `menu_functions.c`:**
    * Age como intermediário entre o utilizador a lógica interna do programa.
    * Implementa a **Tabela de Despacho** (*_Dispatch Table_*) que mapeia opções do menu a funções específicas.
    * Gere estados internos temporários (ex: a matriz estática gerada na opção 10).

### 3. Utilitários e Infraestrutura
* **`functions.h` / `functions.c`:**
    * Biblioteca auxiliar para _Input/Output_ e outras ajudas.
    * Gere a formatação segura de `strings` e a limpeza inteligente do ecrã (contagem de linhas).
* **`config.h`:**
    * Ficheiro de configuração global.
    * Define constantes como tamanho de vetores, limites numéricos e _flags_ de _debug_.

### 4. Ponto de Entrada
* **`main.c`:**
    * Responsável pelo ciclo de vida da aplicação (Inicialização -> Loop Principal -> Conclusão).
    * Não contém lógica matemática complexa, age apenas como inicializador.

---

# Compilação e Execução

Para compilar o projeto, utilize o `Makefile` na raiz do projeto:

```bash
make          # Compila o projeto e gera a pasta build/
make execute  # Compila (se necessário) e executa o programa
make clean    # Remove os ficheiros binários e objetos
```