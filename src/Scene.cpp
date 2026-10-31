#include "Scene.h"
#include <algorithm>

void Scene::ajouterNourriture(Vector2 pos) {
    std::lock_guard<std::mutex> lock(verrou);// verrouille le mutex pour protéger l'accès au vecteur
    nourritures.emplace_back(pos);// ajoute une nouvelle nourriture à la fin du vecteur
}

void Scene::dessinerNourriture() const {
    std::lock_guard<std::mutex> lock(verrou); 
    double maintenant = GetTime();// obtient le temps actuel
    for (const auto& nourriture : nourritures) {
        // vert si fraîche, marron sinon
        Color couleur = nourriture.estFraiche(maintenant) ? GREEN : BROWN;
        DrawCircleV(nourriture.getPosition(), 5, couleur);
    }
}

bool Scene::aDeLaNourritureFraiche() const {
    std::lock_guard<std::mutex> lock(verrou);
    double maintenant = GetTime();
    for (const auto& nourriture : nourritures) {
        if (nourriture.estFraiche(maintenant)) {//vérifie si la nourriture est fraîche
            return true;
        }
    }
    return false;
}

bool Scene::plusFraiche(int& id, Vector2& pos) const {
    std::lock_guard<std::mutex> lock(verrou);
    double maintenant = GetTime();
    double plusFraicheHeure = -1;  // initialise la variable pour stocker l'heure de la nourriture la plus fraîche
    bool trouve = false;

    for (const auto& nourriture : nourritures) {
        if (nourriture.estFraiche(maintenant)) {  // vérifie si la nourriture est fraîche
            if (!trouve || nourriture.getHeureCreation() > plusFraicheHeure) {  // compare les heures de création
                plusFraicheHeure = nourriture.getHeureCreation();  // met à jour l'heure de la nourriture la plus fraîche
                id = nourriture.getId();
                pos = nourriture.getPosition();
                trouve = true; 
            }
        }
    }
    return trouve;
}

bool Scene::essayerManger(int id) {
    std::lock_guard<std::mutex> lock(verrou);
    for (size_t i = 0; i < nourritures.size(); i++) {
        if (nourritures[i].getId() == id) {                // on a trouvé la graine
            nourritures.erase(nourritures.begin() + i);   // on la supprime
            return true;                                   // ce pigeon l'a mangée
        }
    }
    return false;  // pas trouvée
}

void Scene::nettoyer() {
    std::lock_guard<std::mutex> lock(verrou);
    double maintenant = GetTime();
    // on parcourt à l'envers : du dernier élément au premier
    for (int i = (int)nourritures.size() - 1; i >= 0; i--) {
        if (maintenant - nourritures[i].getHeureCreation() > DELAI_DISPARITION) {
            nourritures.erase(nourritures.begin() + i);
        }
    }
}


