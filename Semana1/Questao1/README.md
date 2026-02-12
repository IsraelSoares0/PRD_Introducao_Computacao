# Expansão do Metrô de Tbilisi

## Descrição do Problema

Este projeto implementa uma solução para o planejamento de expansão do Metrô de Tbilisi, considerando critérios estruturais, geográficos e de demanda populacional.

O objetivo é identificar linhas metroviárias viáveis a partir de um conjunto de 20 bairros, levando em conta:

- **Viabilidade estrutural do bairro** (pontuação entre 0 e 100);
- **Distâncias entre bairros** (matriz de adjacência);
- **Fluxo de deslocamento desejado** (preferências dos moradores).

A decisão final sobre a construção de uma linha é baseada em uma métrica quantitativa que relaciona demanda, viabilidade média e custo total da linha.

---

## Modelagem do Problema

O problema foi modelado como um **grafo não direcionado ponderado**, onde:

- **Vértices** representam bairros;
- **Arestas** representam conexões possíveis entre bairros;
- **Pesos das arestas** representam as distâncias entre bairros;
- Informações adicionais associadas aos vértices incluem:
  - Pontuação de viabilidade;
  - Lista de destinos mais desejados.

---

## Etapas da Solução

### 1. Filtragem de Bairros Viáveis

São considerados apenas bairros com **viabilidade** >= 70

Esse conjunto define o subconjunto de vértices elegíveis para construção de estações.

---

### 2. Construção das Conexões Válidas

Entre os bairros viáveis, uma conexão é considerada válida se:

- A distância entre eles for ≤ 10;
- Houver fluxo relevante (um bairro deseja se deslocar ao outro, ou vice-versa).

Isso gera um subgrafo contendo apenas conexões justificáveis tanto geograficamente quanto em termos de demanda.

---

### 3. Geração das Linhas Possíveis

As linhas são modeladas como **caminhos simples contínuos** no grafo, obedecendo às seguintes regras:

- Devem conter pelo menos 3 bairros;
- Não podem repetir bairros;
- Devem utilizar apenas conexões válidas.

A geração das linhas é feita por meio de busca em profundidade (DFS), explorando todas as combinações possíveis que satisfaçam os critérios.

---

### 4. Cálculo das Métricas de Cada Linha

Para cada linha encontrada, são calculadas as seguintes métricas:

- **Tamanho da linha** (número de bairros);
- **Soma das viabilidades**;
- **Média de viabilidade**;
- **Demanda atendida** (fluxos internos presentes na linha);
- **Custo total** (soma das distâncias entre bairros consecutivos).

---

### 5. Critério de Aprovação

Uma linha é aprovada para construção se satisfizer o critério obrigatório:

$$
\frac{\text{Demanda Total} \times \text{Média de Viabilidade}}{\text{Custo Total}} \geq 10
$$

---

## Saídas do Programa

O programa exibe:

- Lista de bairros viáveis;
- Conexões recomendadas;
- Todas as linhas possíveis;
- Linhas aprovadas para construção;
- Métricas gerais da expansão.

---

## Estratégia Utilizada

A abordagem combina:

- Filtragem baseada em restrições;
- Modelagem por grafos;
- Busca em profundidade (DFS) para enumeração de caminhos;
- Avaliação multicritério para decisão final.

O método garante que apenas linhas estruturalmente viáveis, geograficamente justificáveis e socialmente relevantes sejam aprovadas.