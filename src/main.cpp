
#include "raylib.h"
#include "Scene.h"
#include "Pigeon.h"
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
        // Initilisation des éléments du jeu
        // Initialisation du contexte graphique
        InitWindow(config::LARGEUR, config::HAUTEUR, config::TITRE);
        if (!IsWindowReady()) {
            std::cerr << "Erreur : impossible d'ouvrir la fenêtre.\n";
            return 1;
        }
        SetTargetFPS(config::FPS);
        Scene scene;

        //Initilisation de la logique
        Pigeon pigeon(scene, {200.0f, 200.0f}, 100.0f, config::LARGEUR, config::HAUTEUR);
        pigeon.demarrer();

        Pigeon pigeon2(scene, {300.0f, 300.0f}, 100.0f, config::LARGEUR, config::HAUTEUR);
        pigeon2.demarrer();


        // Boucle de jeu : un tour = une image affichée.
        // On sort quand l'utilisateur ferme la fenêtre ou appuie sur Échap.
        while (!WindowShouldClose()) {
            // Si clic gauche -> ajouter de la nourriture.
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                //ajouter de la nourriture à la scène.
                scene.ajouterNourriture(GetMousePosition());
            }

            scene.nettoyer();  // supprime les nourritures périmées
            
            /*//test de manger la nourriture la plus fraiche si on appuie sur espace
            if (IsKeyPressed(KEY_SPACE)) {
                int id;
                Vector2 pos;
                if (scene.plusFraiche(id, pos)) {
                    bool premier = scene.essayerManger(id);  // doit valoir true : la graine est mangée
                    bool second  = scene.essayerManger(id);  // doit valoir false : elle n'existe plus
                    std::cout << std::boolalpha              // affiche true/false au lieu de 1/0
                            << "Graine " << id
                            << " -> 1er essai : " << premier
                            << ", 2e essai : " << second << '\n';
                } else {
                    std::cout << "Aucune graine fraiche a manger\n";
                }
            }//--------------------------------------*/

            // Dessin
            // Dessin de la scène
            BeginDrawing();
            ClearBackground(Color{200, 200, 190, 255});  // couleur "pavés"

            // Dessin du "gameplay"
            scene.dessinerNourriture();
            // dessiner les pigeons.
            pigeon.dessiner();
            pigeon2.dessiner();
            EndDrawing();
        }

        pigeon.arreter();
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
