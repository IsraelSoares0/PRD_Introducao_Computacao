# Apostando Todas as Fichas — Simulação de Monte Carlo para Estimativa de Alcance

## Descrição do Problema

Este projeto implementa uma simulação de Monte Carlo para estimar a distribuição do alcance horizontal de um foguete, considerando incertezas nos parâmetros de lançamento.

Durante um lançamento real, pequenas variações na velocidade inicial e no ângulo podem gerar diferenças significativas no ponto de impacto. A simulação permite estimar probabilisticamente a região mais provável de queda, auxiliando na definição de zonas de segurança e recuperação.

O alcance horizontal é calculado pela fórmula:

$$
R = \frac{v^2 \sin(2\theta)}{g}
$$

onde:

- `v` é a velocidade inicial (m/s);
- `θ` é o ângulo de lançamento (radianos);
- `g = 9.8 m/s²` é a aceleração da gravidade.

---

## Modelagem da Incerteza

Os parâmetros variam de forma aleatória e uniforme nos intervalos:

$$
v \in [v_0 - \Delta v,\; v_0 + \Delta v]
$$

$$
\theta \in [\theta_0 - \Delta \theta,\; \theta_0 + \Delta \theta]
$$

onde:

- `v₀` é a velocidade nominal;
- `Δv` é a variação máxima da velocidade;
- `θ₀` é o ângulo nominal (em graus);
- `Δθ` é a variação máxima do ângulo (em graus).

A conversão de graus para radianos é aplicada antes do cálculo do alcance.

---

## Etapas da Solução

### 1. Geração das Simulações

O programa:

- Lê os parâmetros de entrada:
  - `N` → número de simulações
  - `v₀`, `Δv`
  - `θ₀`, `Δθ`
  - `K` → número de regiões
- Gera `N` pares aleatórios `(v, θ)` com distribuição uniforme;
- Calcula o alcance `R` para cada simulação;
- Armazena todos os valores de `R`.

---

### 2. Determinação do Intervalo de Alcance

Após as simulações:

- Determina-se: Rmin (Menor valor observado) e Rmax (Maior valor observado)

- Define-se o intervalo total: [Rmin, Rmax]

---

### 3. Divisão em Regiões

O intervalo é dividido em `K` regiões consecutivas de mesmo tamanho: $\text{largura} = \frac{R_{\max} - R_{\min}}{K}$

Cada região possui o formato: $\left[ R_{\min} + i \cdot \text{largura},\; R_{\min} + (i+1)\cdot \text{largura} \right)$

para `i = 0, 1, ..., K−1`.

---

### 4. Contagem e Estimativa de Probabilidade

Para cada região:

- Conta-se o número de lançamentos cujo alcance pertence ao intervalo;
- A probabilidade estimada;

---

## Saída do Programa

O programa apresenta, para cada região:

- Intervalo da região;
- Quantidade de lançamentos;
- Probabilidade estimada de queda (em percentual).

---

## Estratégia Utilizada

A solução utiliza:

- Geração de números pseudoaleatórios com distribuição uniforme;
- Avaliação direta da equação física do alcance;
- Estatística descritiva para estimativa de distribuição empírica.

A complexidade do algoritmo é:

$$
\text{Tempo: } \mathcal{O}(N + K)
$$

$$
\text{Espaço: } \mathcal{O}(N)
$$

A precisão da estimativa aumenta com o crescimento de `N`, conforme o princípio da Lei dos Grandes Números.

---

## Justificativa da Abordagem

O método de Monte Carlo foi escolhido porque:

- O sistema possui incertezas nos parâmetros de entrada;
- A propagação analítica da incerteza é complexa;
- A simulação permite estimar probabilidades de forma simples e escalável;
- A confiabilidade aumenta com o número de simulações.
