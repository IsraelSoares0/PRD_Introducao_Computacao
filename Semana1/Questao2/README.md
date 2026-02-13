# Amanhecer — Filtragem e Análise de Estabilidade de Dados do Satélite Zarya

## Descrição do Problema

Este projeto implementa um procedimento de filtragem e análise de estabilidade aplicado a séries temporais provenientes do módulo **Zarya (Functional Cargo Block – FGB)** da Estação Espacial Internacional.

Devido à presença de ruído nos sensores, as medições apresentam pequenas flutuações aleatórias. O objetivo é suavizar os dados por meio de um filtro recursivo e, posteriormente, avaliar a estabilidade de cada variável monitorada.

As variáveis analisadas são:

- Altitude  
- Velocidade  
- Temperatura  
- Potência  

Cada coluna é processada de forma independente.

---

## Modelo Matemático do Filtro

O filtro aplicado é definido pela equação recursiva:

$$
\begin{cases}
y[n] = \frac{x[n] + y[n-1]}{2} \\
y[0] = x[0]
\end{cases}
$$


Onde:

- `x[n]` representa a medição original no instante `n`;
- `y[n]` representa o valor filtrado no instante `n`;
- `y[0]` é inicializado com o primeiro valor da série.

Esse filtro corresponde a uma suavização exponencial simples com fator de ponderação fixo de 0,5, reduzindo variações abruptas e atenuando ruídos de alta frequência.

---

## Etapas da Solução

### 1. Leitura do Conjunto de Dados

O programa realiza:

- Carregamento do arquivo CSV contendo as medições;
- Separação das colunas numéricas correspondentes às variáveis físicas;
- Armazenamento dos dados em estruturas adequadas para processamento sequencial.

---

### 2. Aplicação do Filtro

Para cada coluna (altitude, velocidade, temperatura e potência):

- O filtro recursivo é aplicado sequencialmente;
- Cada série é processada independentemente;
- O vetor filtrado substitui ou complementa os valores originais.

---

### 3. Análise de Estabilidade

Após a suavização, cada série filtrada é avaliada quanto à estabilidade.

Define-se:

- **Salto instantâneo** como a diferença absoluta entre dois valores consecutivos:

$\left| y[n] - y[n-1] \right|$


- **Limiar de estabilidade** como um valor máximo aceitável para essa variação.

Critério adotado:

- **Estável** → se nenhum salto ultrapassa o limiar definido;
- **Instável** → se ao menos um salto excede o limite.

O limiar pode ser definido com base em critérios experimentais ou estatísticos (por exemplo, valor fixo ou proporcional à variância da série).

---

## Saídas do Programa

O programa exibe:

- Séries filtradas para cada variável;
- Avaliação final de cada coluna:
  - `Estável`
  - `Instável`

O resultado fornece um diagnóstico simplificado da qualidade e regularidade das medições após a aplicação do filtro.

---

## Estratégia Utilizada

A abordagem combina:

- Processamento de arquivos CSV;
- Filtragem recursiva de séries temporais;
- Análise de variação incremental;
- Classificação baseada em limiar.