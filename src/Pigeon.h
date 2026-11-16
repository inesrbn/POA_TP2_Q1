#include "raylib.h"
#pragma once

#include "Scene.h"

#include <atomic>
#include <functional>
#include <mutex>
#include <optional>
#include <thread>

class Pigeon {
    public:
        enum class Etat {
            ENDORMI,
            SE_DEPLACE,
            EFFRAYE
        };

        using RechercheNourriture = std::function<std::optional<Vector2>()>;
        using MangerNourriture = std::function<bool(Vector2)>;

        Pigeon(Scene& scene, Vector2 positionInitiale, float vitesse, float largeurFenetre, float hauteurFenetre);
        
        ~Pigeon();

        Pigeon(const Pigeon&) = delete;
        Pigeon& operator=(const Pigeon&) = delete;

        void demarrer();
        void arreter();

        void dessiner() const;

        Vector2 getPosition() const;
        Etat getEtat() const;

    private:
        void boucle();
        void deplacerVers(Vector2 destination, float deltaTemps);
        void effrayer();

        mutable std::mutex mutex;

        Vector2 position;
        Vector2 cibleEffrayement;

        Scene& scene;
        float vitesse;
        float largeurFenetre;
        float hauteurFenetre;

        Etat etat = Etat::ENDORMI;

        std::thread threadPigeon;
        std::atomic<bool> actif{false};
};