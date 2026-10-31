#include <vector>
#include <mutex>
#include "raylib.h"
#include "Nourriture.h"

class Scene{
    public:
        static const int DELAI_DISPARITION = 10;
        
        void ajouterNourriture(Vector2 pos);  // ajoute une nouvelle nourriture à la scène
        bool plusFraiche(int& id, Vector2& pos) const;  // trouve la nourriture la plus fraîche
        bool essayerManger(int id);  // essaie de manger la nourriture avec l'id donné
        bool aDeLaNourritureFraiche() const;  // vrai si la scène contient de la nourriture fraîche
        void nettoyer();  // supprime les nourritures périmées de la scène
        void dessinerNourriture() const;  // dessine toutes les nourritures de la scène

    private:
        std::vector<Nourriture> nourritures;  // vecteur de nourriture
        mutable std::mutex verrou;  // mutex pour protéger l'accès au vecteur de nourriture

};