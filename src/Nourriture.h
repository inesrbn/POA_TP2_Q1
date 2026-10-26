#include "raylib.h"

class Nourriture {
    public:
        static const double DUREE_FRAICHEUR;  // durée de vie en secondes
        
        Nourriture(Vector2 pos);

        bool estFraiche(double maintenant) const;  // vrai si la nourriture est encore fraîche
        int getId() const;  // retourne l'id de la nourriture
        Vector2 getPosition() const;  // retourne la position de la nourriture
        double getHeureCreation() const;  // retourne l'heure de création de la nourriture

    private:
        static int compteur;  // compteur de nourriture créée (pour donner un id unique)
        
        int id;
        Vector2 position;
        double heureCreation;
        
    
};