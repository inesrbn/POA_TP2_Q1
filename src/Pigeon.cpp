#include "Pigeon.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>
#include <stdexcept>

using namespace std::chrono_literals;

// Constructeur du pigeon
Pigeon::Pigeon(Scene& scene, Vector2 positionInitiale, float vitesse, float largeurFenetre, float hauteurFenetre)
    : scene(scene),
      position(positionInitiale),
      cibleEffrayement(positionInitiale),
      vitesse(vitesse),
      largeurFenetre(largeurFenetre),
      hauteurFenetre(hauteurFenetre) {

    if (vitesse <= 0 || largeurFenetre <= 0 || hauteurFenetre <= 0) {
        throw std::invalid_argument("Parametres du pigeon invalides");
    }
}

// Destructeur du pigeon
Pigeon::~Pigeon() {
    arreter();
}

// Démarre le thread du pigeon
void Pigeon::demarrer() {
    // Check si le thread est déjà en cours d'exécution
    if (threadPigeon.joinable()) {
        return;
    }

    // Le demarre sinon
    actif.store(true);

    try {
        threadPigeon = std::thread(&Pigeon::boucle, this);
    } catch (...) {
        actif.store(false);
        throw;
    }
}

// Attend que le thread du pigeon se termine pour le fermer
void Pigeon::arreter() {
    actif.store(false);

    if (threadPigeon.joinable()) {
        threadPigeon.join();
    }
}

Vector2 Pigeon::getPosition() const {
    std::lock_guard<std::mutex> verrou(mutex);
    return position;
}

Pigeon::Etat Pigeon::getEtat() const {
    std::lock_guard<std::mutex> verrou(mutex);
    return etat;
}

void Pigeon::deplacerVers(Vector2 destination, float deltaTemps) {
    std::lock_guard<std::mutex> verrou(mutex);

    float dx = destination.x - position.x;
    float dy = destination.y - position.y;

    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < 0.001f) {
        return;
    }

    float pas = std::min(vitesse * deltaTemps, distance);

    position.x += (dx / distance) * pas;
    position.y += (dy / distance) * pas;

    position.x = std::clamp(position.x, 0.0f, largeurFenetre);
    position.y = std::clamp(position.y, 0.0f, hauteurFenetre);
}

void Pigeon::effrayer() {
    thread_local std::mt19937 generateur(std::random_device{}());

    std::uniform_real_distribution<float> distributionX(0.0f, largeurFenetre);

    std::uniform_real_distribution<float> distributionY(0.0f, hauteurFenetre);

    std::lock_guard<std::mutex> verrou(mutex);

    cibleEffrayement = {
        distributionX(generateur),
        distributionY(generateur)
    };

    etat = Etat::EFFRAYE;
}

void Pigeon::boucle() {
    thread_local std::mt19937 generateur(std::random_device{}());

    std::uniform_real_distribution<float> probabilite(0.0f, 1.0f);

    constexpr float deltaTemps = 0.02f;

    while (actif.load()) {
        try {
            std::optional<Vector2> nourriture;
            int id;
            Vector2 positionNourriture;

            if (scene.aDeLaNourritureFraiche()) {
                scene.plusFraiche(id, positionNourriture);
                nourriture = positionNourriture;
            }

            // Une probabilite differente est tiree a chaque tour.
            float probabiliteEffrayement = std::uniform_real_distribution<float>(0.0f, 0.005f)(generateur);

            bool doitEffrayer = probabilite(generateur) < probabiliteEffrayement; 

            if (nourriture.has_value()) {
                {
                    std::lock_guard<std::mutex> verrou(mutex);
                    etat = Etat::SE_DEPLACE;
                }

                deplacerVers(*nourriture, deltaTemps);

                Vector2 positionActuelle = getPosition();

                float dx = nourriture->x - positionActuelle.x;
                float dy = nourriture->y - positionActuelle.y;

                // Distance de contact avec la nourriture.
                if (dx * dx + dy * dy <= 100.0f) {
                    scene.essayerManger(id);
                }
            }
            else if (doitEffrayer) {
                effrayer();
            }

            Etat etatActuel = getEtat();

            if (etatActuel == Etat::EFFRAYE) {
                Vector2 destination;

                {
                    std::lock_guard<std::mutex> verrou(mutex);
                    destination = cibleEffrayement;
                }

                deplacerVers(destination, deltaTemps);

                Vector2 actuelle = getPosition();

                float dx = destination.x - actuelle.x;
                float dy = destination.y - actuelle.y;

                if (dx * dx + dy * dy <= 4.0f) {
                    std::lock_guard<std::mutex> verrou(mutex);
                    etat = Etat::ENDORMI;
                }
            }
            else if (!nourriture.has_value()) {
                std::lock_guard<std::mutex> verrou(mutex);
                etat = Etat::ENDORMI;
            }

        } catch (...) {
            std::lock_guard<std::mutex> verrou(mutex);
            etat = Etat::ENDORMI;
        }

        std::this_thread::sleep_for(20ms);
    }
}

void Pigeon::dessiner() const {
    Vector2 positionActuelle = getPosition();
    Etat etatActuel = getEtat();

    Color couleur = GRAY;

    switch (etatActuel) {
        case Etat::ENDORMI:
            couleur = DARKGRAY;
            break;

        case Etat::SE_DEPLACE:
            couleur = GRAY;
            break;

        case Etat::EFFRAYE:
            couleur = RED;
            break;
    }

    DrawCircleV(positionActuelle, 12.0f, couleur);
    DrawCircle(
        static_cast<int>(positionActuelle.x + 5),
        static_cast<int>(positionActuelle.y - 4),
        3.0f,
        BLACK
    );
}