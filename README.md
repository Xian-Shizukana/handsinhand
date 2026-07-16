# Hands in Hand

Hands in Hand is a turn-based, console-based card battler written in C++. The game combines the classic Rock-Paper-Scissors mechanic with deck building, card drafting, and roguelike progression. Players build a deck, choose a hand before each battle, arrange the order of their cards, defeat increasingly difficult enemies, and purchase upgrades between fights.

---

## Features

- Rock-Paper-Scissors based combat
- Deck building and card purchasing
- Healing and damage cards
- Shop system with upgrades
- Automatic save/load system
- Progressive difficulty scaling
- ASCII card display with colored terminal output

---

## Gameplay

Each run consists of several phases.

### 1. Picking Phase

Choose **5 cards** from your deck to bring into battle.

### 2. Arrangement Phase

Arrange the order in which your cards will be played.

Since combat is automatic after this phase, the order of your cards is an important strategic decision.

### 3. Battle Phase

Cards are revealed one by one.

Each card has:

- a type (Rock, Paper, or Scissors)
- a value (damage or healing amount)
- an optional special effect

The winner of each matchup is determined using normal Rock-Paper-Scissors rules:

- Rock defeats Scissors
- Paper defeats Rock
- Scissors defeats Paper

If both cards are the same type, the higher card value wins.

### 4. Shop Phase

After defeating an enemy, players receive gold which can be spent on:

- New cards
- Maximum HP upgrades
- Full heal

Each completed level increases the game's difficulty.

---

## Card Format

Internally, cards are stored as strings.

Example:

```
rn7
```

Meaning:

| Character | Meaning |
|-----------|---------|
| `r` | Rock |
| `n` | Normal card |
| `7` | Deals 7 damage |

Another example:

```
ph10
```

Means:

- Paper card
- Healing effect
- Restores 10 HP

---

## Enemy Scaling

Enemies become stronger every level.

The game scales:

- Enemy HP
- Card strength
- Healing card frequency
- Gold rewards

This creates progressively more difficult encounters.

---

## Save System

The game automatically saves after each completed battle.

Save data is stored in:

```
hihSave.txt
```

The save file contains:

- Score
- Current level
- Player HP
- Maximum HP
- Gold
- Deck

If the player dies, the save file is automatically deleted.

---

## Project Structure

Major functions include:

| Function | Purpose |
|----------|---------|
| `generateNewGame()` | Initializes a new run |
| `pickingPhase()` | Select battle cards |
| `arrangingPhase()` | Arrange card order |
| `battlingPhase()` | Handles combat |
| `shoppingPhase()` | Shop between battles |
| `generateCard()` | Random card generation |
| `generateNewEnemy()` | Creates scaled enemies |
| `autoSave()` | Saves current progress |
| `validateLoadFile()` | Loads previous save |

---

## Requirements

- C++17 or newer
- Terminal with ANSI color support
- `<filesystem>` support

---

## Compilation

Using g++:

```bash
g++ main.cpp -std=c++17 -o HandsInHand
```

Run:

```bash
./HandsInHand
```

Windows:

```bash
HandsInHand.exe
```

---

## Future Improvements

Possible future additions include:

- More card effects
- Boss encounters
- Relics/passive abilities
- Better save encryption
- Improved UI

---

## Authors

- Calaoagan, Sean Jefferson M.
- Cordero, Hexel A.
- Juanico, Joaquin Paul

Developed as a C++ project for our finals in Data Structures & Algorithms.
