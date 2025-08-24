Entrega de trabalho para graduação em ADS
Feito por Gustavo Teixeira Louro

# Desafio Cartas de Cidades – Nível Aventureiro 🏅

## 📋 Descrição
No Nível Aventureiro, o sistema expande o nível Novato:
- Cadastro de **duas cartas** (estado, código, cidade, população, área, PIB e pontos turísticos).
- **Menu interativo** (`switch`) para escolher o atributo de comparação.
- **Comparação aninhada** (múltiplos atributos em sequência como critério de desempate).

## 🚩 Funcionalidades
- **Cadastro interativo** das cartas via terminal (scanf).
- **Opções de comparação**:
  1. População (**maior vence**)
  2. Área (**maior vence**)
  3. PIB (**maior vence**)
  4. Pontos turísticos (**maior vence**)
  5. Densidade populacional (**menor vence**)
  6. **Comparação aninhada** (prioridade: População → Área → PIB → Densidade → Pontos)
- **Saída clara**:
  - Exibe os dados das cartas
  - Mostra o critério escolhido
  - Indica a carta vencedora ou empate

## 📤 Exemplo de execução
```
=== Cadastro da Carta 1 ===
Estado (UF, ex: SP): SP
Código da carta: C01
Nome da cidade: São Paulo
População (habitantes): 12000000
Área (km^2): 1521
PIB: 699.28
Pontos turísticos: 50

=== Cadastro da Carta 2 ===
Estado (UF, ex: RJ): RJ
Código da carta: C02
Nome da cidade: Rio de Janeiro
População (habitantes): 6700000
Área (km^2): 1200
PIB: 400.50
Pontos turísticos: 70

===== MENU DE COMPARAÇÃO =====
1) População (maior vence)
2) Área (maior vence)
3) PIB (maior vence)
4) Pontos turísticos (maior vence)
5) Densidade populacional (menor vence)
6) Comparação aninhada (múltiplos atributos)
Selecione uma opção: 1

>>> Critério escolhido: População (maior vence)

Resultado: Carta 1 VENCEU segundo o critério selecionado.
```

## 🛠️ Requisitos atendidos
- Uso de `switch` para **menu interativo**.
- **Comparação aninhada** com múltiplos atributos.
- Entrada via terminal (`scanf`) e **saídas organizadas**.
