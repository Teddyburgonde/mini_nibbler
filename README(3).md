# MiniNibbler-DynGUI

Projet pédagogique pour apprendre à créer un Snake en C++ avec une interface graphique dynamique, chargée à l'exécution via `dlopen`.

---

## 🎯 Objectifs

❌ Comprendre la séparation logique / interface graphique  
❌ Apprendre à charger dynamiquement une bibliothèque `.so`  
❌ Créer une interface `IGui` et la faire implémenter dans une GUI  
❌ Contrôler la boucle de jeu depuis le `main` uniquement  

---

## 🗺️ Feuille de route (étapes numérotées)

### ✅ 1. 🧱 Structure initiale du projet
✅ Créer les dossiers suivants :  
✅ `core/` : logique du jeu (Snake, Game)  
✅ `includes/` : headers partagés (`IGui.hpp`, `GameState.hpp`)  
✅ `gui_ncurses/` : interface Ncurses  
✅ `main.cpp` à la racine  
✅ `Makefile`  

---

### ✅ 2. 🧠 Implémentation de la logique du Snake
✅ Créer la classe `Snake` avec :  
✅ position  
✅ direction  
✅ méthode `move()`, `grow()`, `checkCollision()`  

✅ Créer la classe `Game` avec :  
✅ boucle de jeu (`loop()`)  
✅ placement de la nourriture  
✅ test de fin de partie  

---

### ❌ 3. 📦 Création des types partagés
❌ Créer `GameState.hpp` avec les infos à afficher dans la GUI (snake, food, score…)  
❌ Créer `Input.hpp` avec l’enum `Input` (UP, DOWN, LEFT, RIGHT, EXIT, NONE)  

---

### ❌ 4. 🧩 Création de l’interface IGui
❌ Créer le fichier `IGui.hpp` avec les méthodes :
```cpp
class IGui {
public:
    virtual void init(int width, int height) = 0;
    virtual void render(const GameState&) = 0;
    virtual Input getInput() = 0;
    virtual void cleanup() = 0;
    virtual ~IGui() {}
};
```

---

### ❌ 5. 🎨 Implémentation de la GUI `Ncurses`
❌ Implémenter la classe `GuiNcurses` dans `gui_ncurses/` :  
❌ utiliser `ncurses` pour dessiner le snake  
❌ récupérer les entrées clavier  

❌ Ajouter une fonction C visible :
```cpp
extern "C" IGui* createGui();
```

---

### ❌ 6. 🔗 Chargement dynamique de la GUI
❌ Dans `main.cpp`, utiliser :  
❌ `dlopen()` pour ouvrir la GUI  
❌ `dlsym()` pour charger `createGui()`  
❌ `dlerror()` pour gérer les erreurs  
❌ `dlclose()` à la fin  

---

### ❌ 7. 🕹️ Intégration de la boucle de jeu
❌ Dans le `main` :  
❌ initialiser le jeu  
❌ charger la GUI  
❌ faire une boucle `while` avec :  
❌ lecture des entrées (`gui->getInput()`)  
❌ mise à jour du jeu (`game.update()`)  
❌ rendu (`gui->render()`)  

---

### ❌ 8. Tests et validation
❌ Lancer le projet et tester :  
❌ snake se déplace bien  
❌ GUI affiche correctement  
❌ ESC quitte le jeu proprement  

---

## Bonus possibles (facultatifs)

❌ Ajouter les GUI `SDL2` et `SFML`  
❌ Changer de GUI avec 1, 2, 3 à chaud  
❌ Ajouter des obstacles ou un score  

---

## 🛠️ Compilation

```bash
make
./mininibbler 20 20
```

---

## 📌 Rappel important

❌ Ne rien afficher directement depuis le `core`  
❌ Ne jamais faire de `#include <ncurses.h>` dans le `main`  
❌ Tout passe par l’interface `IGui`