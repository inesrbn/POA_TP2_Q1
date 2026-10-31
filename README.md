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

## Ce qui se passe à l'écran

- **Graine verte** : fraîche pendant 5 secondes. Les pigeons se dirigent vers la plus récente
  et la mangent ; si plusieurs pigeons la touchent en même temps, un seul la mange.
- **Graine marron** : plus fraîche (de 5 à 10 secondes). Les pigeons l'ignorent.
- **Après 10 secondes** : la graine disparaît.
- **Pigeons** : à compléter (sommeil sans nourriture, déplacement, effarouchement).

## Organisation du code

| Fichier | Rôle |
| --- | --- |
| `src/main.cpp` | Fenêtre, boucle principale, clic, dessin |
| `src/Nourriture.h/.cpp` | Une graine : position, id unique, fraîcheur |
| `src/Scene.h/.cpp` | Toute la nourriture, protégée par un mutex |
| `src/Pigeon.h/.cpp` | Un pigeon et son thread |
