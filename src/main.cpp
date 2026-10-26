// main.cpp : point d'entrée du programme.
// Pour l'instant : une fenêtre raylib vide avec la boucle de jeu.
// Les classes Nourriture, Scene et Pigeon viendront se brancher ici.

#include "raylib.h"

#include <exception>
#include <iostream>

// Constantes de la fenêtre : on les regroupe ici pour les changer facilement.
namespace config {
constexpr int LARGEUR = 1000;
constexpr int HAUTEUR = 700;
constexpr int FPS = 60;
constexpr const char* TITRE = "Nourrir les pigeons";
}  // namespace config

int main() {
    try {
        InitWindow(config::LARGEUR, config::HAUTEUR, config::TITRE);
        if (!IsWindowReady()) {
            std::cerr << "Erreur : impossible d'ouvrir la fenêtre.\n";
            return 1;
        }
        SetTargetFPS(config::FPS);

        // TODO (partie 4) : créer la Scene et les pigeons ici.

        // Boucle de jeu : un tour = une image affichée.
        // On sort quand l'utilisateur ferme la fenêtre ou appuie sur Échap.
        while (!WindowShouldClose()) {
            // 1. Entrées utilisateur
            // TODO (partie 4) : si clic gauche -> ajouter de la nourriture.

            // 2. Dessin (uniquement dans le thread principal !)
            BeginDrawing();
            ClearBackground(Color{200, 200, 190, 255});  // couleur "pavés"

            // TODO (partie 4) : dessiner la nourriture puis les pigeons.

            DrawText("Clique pour lancer des graines", 10, 10, 20, DARKGRAY);
            DrawFPS(config::LARGEUR - 90, 10);
            EndDrawing();
        }

        // TODO : arrêter proprement les threads des pigeons AVANT de fermer.

        CloseWindow();
    } catch (const std::exception& e) {
        std::cerr << "Erreur inattendue : " << e.what() << '\n';
        if (IsWindowReady()) CloseWindow();
        return 1;
    } catch (...) {
        std::cerr << "Erreur inconnue.\n";
        if (IsWindowReady()) CloseWindow();
        return 1;
    }
    return 0;
}
