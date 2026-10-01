# Sistema de Controle Acadêmico

Sistema acadêmico em **C** para cadastro e gerenciamento de alunos, disciplinas, notas e situação acadêmica.

Projeto de portfólio desenvolvido para praticar estruturas, funções, vetores, arquivos e organização de código em C.

## Funcionalidades
- Cadastrar alunos
- Listar alunos
- Buscar aluno por matrícula
- Cadastrar disciplinas
- Registrar notas
- Calcular média
- Exibir situação: aprovado, recuperação ou reprovado
- Remover registros
- Persistir dados em arquivos binários

## Tecnologias
- C11
- GCC
- Structs
- Vetores
- Funções e protótipos
- Manipulação de arquivos
- CRUD em terminal

## Estrutura
src/main.c
data/alunos.dat

## Compilação
```bash
gcc -Wall -Wextra -std=c11 src/main.c -o sistema-academico
./sistema-academico
```

O arquivo de dados é criado automaticamente quando o programa é executado.

## Autor
**Luis Fillipe Backer Faria**
GitHub: https://github.com/lfillipebf-ai
