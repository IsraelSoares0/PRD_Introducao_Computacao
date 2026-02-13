# Cada Segundo Custa — Busca Eficiente em Sistema Embarcado

## Descrição do Problema

Este projeto implementa uma solução para um sistema embarcado responsável por determinar rapidamente o local de pouso de um módulo lunar.

O sistema recebe:

- Um **vetor de inteiros** contendo os IDs de possíveis pontos de pouso;
- Um **ID alvo**, correspondente ao ponto de pouso selecionado.

Os IDs:

- São **únicos**;
- Estão **desordenados**;
- Devem ser processados sob **restrição de tempo crítico**.

O objetivo é retornar o **índice do ID alvo no vetor** da forma mais eficiente possível.

---

## Estratégia Adotada

Como o vetor de entrada está desordenado, não é possível aplicar diretamente algoritmos de busca binária sem ordenação prévia.

Para atender ao requisito de tempo crítico, foi adotada a seguinte estratégia:

### Uso de Estrutura de Dispersão (Tabela Hash)

1. Percorrer o vetor uma única vez.
2. Inserir cada elemento em uma `unordered_map`, associando:
   - **Chave** → ID do ponto de pouso  
   - **Valor** → Índice correspondente no vetor
3. Realizar a busca do ID alvo diretamente na tabela hash.

---

## Justificativa da Escolha

A estrutura `unordered_map` em C++ utiliza **tabela de dispersão (hash table)**, oferecendo:

- Complexidade média de inserção: O(1)
- Complexidade média de busca:  O(1)

Assim:

- Construção da estrutura → O(n)
- Busca do elemento → O(1)
- Complexidade total → O(n)

---

## Comparação com Outras Abordagens

### Busca Linear

- Complexidade: O(n)
- Não exige memória adicional.
- Pode ser suficiente para vetores pequenos.
- Porém, em cenário crítico, o pior caso é ineficiente.

### Ordenação + Busca Binária

- Ordenação: O(n log n)
- Busca: O(log n)
- Complexidade total: O(n log n)

Não é ideal quando se deseja resposta imediata e não há necessidade de manter os dados ordenados.

### Tabela Hash (Escolhida)

- Pré-processamento linear
- Busca praticamente constante
- Melhor desempenho médio em tempo crítico

---

## Implementação Conceitual

Etapas do algoritmo:

1. Ler o vetor de IDs.
2. Construir a tabela hash associando ID → índice.
3. Verificar se o ID alvo está presente:
 - Se estiver → retornar índice.
 - Caso contrário → retornar indicação de não encontrado.
