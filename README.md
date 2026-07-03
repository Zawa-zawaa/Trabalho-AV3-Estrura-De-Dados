# 📘 README — Trabalhos da Disciplina (Estrutura de dados) AV3

> Repositório contendo os Trabalhos A, B e C de Estrutura de dados.

---

# 👥 Integrantes

| Nome | Matrícula |
|------|-----------|
| Ivan Ramos De Oliveira Mourao | 2250104079 |
| Gustavo Gomes Ferraz | 2250205363 |

|------|-----------|
| Vídeo de apresentação | https://youtu.be/Omz7vC7pDB8 |


**Turma:** A

---

# 📂 Organização do Repositório

```text
.
├── TrabalhoA/
│   ├── main.c
│   ├── triagem.c
│   ├── dados_a.csv
│   ├── triagem.h
│   └── README.md
│
├── TrabalhoB/
│   ├── main.c
│   ├── emergencia.c
│   ├── dados_b.csv
│   ├── emergencia.h
│   └── README.md
│
├── TrabalhoC/
│   ├── main.c
│   ├── fila.c
│   ├── dados_c.csv
│   ├── fila.h
│   └── README.md
│
└── README.md
```

---

# 🅰️ Trabalho A

## Tema

**Tema escolhido:** *Listas Simples - Tema A3 - Triagem Hospitalar*

## Descrição

A ideia é simular uma lista de pacientes em uma triagem hospitalar.

Cada paciente deve possuir, no mínimo:

senha;
nome;
idade;
gravidade.
Pontos importantes:

a senha deve ser única;
a gravidade deve ser validada entre 1 e 4;
gravidade 1 representa maior prioridade;
a lista deve ficar ordenada pela gravidade;
em caso de empate na gravidade, deve ser considerada a menor senha.

### Compilação

```bash
cd TrabalhoA
```

ou

```bash
gcc *.c -o programa
```

### Execução

```bash
./programa
```
---

# 🅱️ Trabalho B

## Tema

**Tema escolhido:** *Pilhas Simples - Tema B2 — Chamadas de Emergência*

## Descrição

A ideia é simular uma pilha de chamadas de emergência.

A última chamada registrada será a primeira chamada atendida, respeitando a lógica LIFO.

Cada chamada deve possuir, no mínimo:

protocolo;
local;
tipo da ocorrência;
horário.
Pontos importantes:

o protocolo deve ser único;
registrar chamada corresponde a empilhar;
atender chamada corresponde a desempilhar;
consultar a última chamada corresponde a verificar o topo da pilha.

### Compilação

```bash
cd TrabalhoB
```

ou

```bash
gcc *.c -o programa
```

### Execução

```bash
./programa
```

### Observações

- 5 dados ja Pre-Cadastrados


---

# 🅲 Trabalho C

## Tema

**Tema escolhido:** *Filas Simples - Tema C2 — Fila de Impressão*

## Descrição

A ideia é simular uma fila de impressão com trabalhos normais e prioritários.

Trabalhos prioritários devem ser processados antes dos trabalhos normais.

Cada trabalho de impressão deve possuir, no mínimo:

ID;
nome do arquivo;
quantidade de páginas;
tipo, sendo N para normal ou P para prioritário.
Pontos importantes:

o programa deve ter uma fila normal simples;
o programa deve ter uma fila circular simples para trabalhos prioritários;
se existir trabalho prioritário, ele deve ser processado primeiro;
se não houver trabalho prioritário, o próximo trabalho normal deve ser processado;
deve ser possível buscar, listar e cancelar trabalhos.

### Compilação

```bash
cd TrabalhoC
```

ou

```bash
gcc *.c -o programa
```

### Execução

```bash
./programa
```
