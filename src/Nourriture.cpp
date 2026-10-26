#include "Nourriture.h" 

int Nourriture::compteur = 0;  // initialisation du compteur de nourriture
 
const double Nourriture::DUREE_FRAICHEUR = 5.0;

Nourriture::Nourriture(Vector2 pos) :id(++compteur), position(pos), heureCreation(GetTime()) {
    
}
bool Nourriture::estFraiche(double maintenant) const {
    return maintenant - heureCreation < DUREE_FRAICHEUR;
}

int Nourriture::getId() const {
    return id;
}

Vector2 Nourriture::getPosition() const {
    return position;
}

double Nourriture::getHeureCreation() const {
    return heureCreation;
}
