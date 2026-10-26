# Nourrir les pigeons

Simulation multithreadée en C++ avec raylib : chaque pigeon est un thread, l'utilisateur lance de la nourriture d'un clic.

## Groupe

- ROBIN Inès
- CHARTIER Tristan

## Installation de raylib

- **Linux (Debian/Ubuntu)** : `sudo apt install libraylib-dev`
  (sinon, compiler raylib depuis https://github.com/raysan5/raylib)
- **macOS** : `brew install raylib`
- **Windows** : installeur officiel sur https://www.raylib.com (fournit MinGW)

## Compiler et lancer

```
make        # compile
make run    # compile et lance
make clean  # nettoie
```

## Comment jouer

- **Clic gauche** : lancer de la nourriture à l'endroit cliqué
- **Échap** ou fermer la fenêtre : quitter

À compléter : règles de fraîcheur, effarouchement, etc.
