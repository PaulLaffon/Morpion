#include "reseauneurone.h"

// Constructeur d'un réseau de neurones aléatoire
ReseauNeurone::ReseauNeurone(string file_name, int nbCouches, vector<int>& neuroneParCouche) : QObject()
{
    filename = file_name;

    if(nbCouches < 2)
    {
        qDebug("Pas possible de faire un réseau de neurones avec moins de 2 couches");
        return;
    }
    if(nbCouches != (int)neuroneParCouche.size())
    {
        qDebug("La taille du nombre de neurones par couche ne corresponds pas à celle du nombre de couches");
        return;
    }

    // On alloue le bon nombre de couches
    reseau.resize(nbCouches);
    reseau[0] = new CoucheNeurones(neuroneParCouche[0], ENTREE);
    // On alloue les couches caches
    for(int i = 1; i < nbCouches - 1; i++)
    {
        reseau[i] = new CoucheNeurones(neuroneParCouche[i], HIDDEN);
    }
    // On alloue la couche de sortie
    reseau.back() = new CoucheNeurones(neuroneParCouche.back(), SORTIE);

    // On initialize nos couches avec des poids aléatoire (sauf la dernière ou on ne se sert pas de ses poids)
    for(int i = 0; i < nbCouches - 1; i++)
    {
        reseau[i]->initializeRandom(reseau[i+1]->getNbNeurones());
    }

    // On sauvegarde le nouveau réseau fraichement créé de façon aléatoire
    save(filename);
}

// Constructeur d'un réseau de neurones qui charge le fichier contenant le réseau de neurones
ReseauNeurone::ReseauNeurone(string file_name)
{
    filename = file_name;

    load(file_name);
}

ReseauNeurone::~ReseauNeurone()
{
    save(filename);

    for(unsigned int i = 0; i < reseau.size(); i++)
        delete reseau[i];
}

void ReseauNeurone::save(string &file_name)
{
    ofstream file;
    file.open(file_name);

    // Nombre de couche
    file << reseau.size() << endl;

    // Neurones par couches
    for(unsigned int i = 0; i < reseau.size(); i++)
    {
        file << reseau[i]->getNbNeurones() << " ";
    }

    file << endl;

    // Pour chaque couche sauf la dernière on sauvegarde les poids
    for(unsigned int i = 0; i < reseau.size() - 1; i++)
    {
        // On affiche les dimension de la matrice
        file << reseau[i]->getPoids().size() << " " << reseau[i]->getPoids().at(0).size() << endl;

        // On affiche tout les poids
        for(unsigned int j = 0; j < reseau[i]->getPoids().size() ; j++)
        {
            for(unsigned int k = 0; k < reseau[i]->getPoids().at(j).size(); k++)
            {
                file << reseau[i]->getPoids()[j][k] << " ";
            }
            file << endl;
        }
    }

    file.close();
}


void ReseauNeurone::load(string& file_name)
{
    ifstream file;
    file.open(file_name);

    // On recupère le nombre de couche du reseau
    unsigned int size;
    file >> size;
    reseau.resize(size);

    // On recupere le nombre de neuronne par couche
    for(unsigned int i = 0; i < size; i++)
    {
        short nb;
        file >> nb;

        if(i == 0)
            reseau[i] = new CoucheNeurones(nb, ENTREE);
        else if(i == size - 1)
            reseau[i] = new CoucheNeurones(nb, SORTIE);
        else
            reseau[i] = new CoucheNeurones(nb, HIDDEN);
    }

    // On recupere le poids de chacune des couches
    for(unsigned int i = 0; i < size - 1; i++)
    {
        // On recupère la taille
        int x, y;
        file >> x >> y;

        // On redimentionne bien la matrice de poids
        reseau[i]->getPoids().resize(x);

        // On recupère la valeur de chacun des poids
        for(int j = 0; j < x; j++)
        {
            for(int k = 0; k < y; k++)
            {
                float p;
                file >> p;

                reseau[i]->getPoids()[j].push_back(p);
            }
        }
    }

    // On alloue de l'espace pour le résultat du calcul intermédiaire sur chaque couche
    // Le résultat est proportionelle a la taille de la couche suivante (multiplication matrice)
    for(unsigned int i = 0; i < size - 1; i++)
        reseau[i]->getResult().resize(reseau[i+1]->getNbNeurones());
}



vector<float>& ReseauNeurone::calculResult(vector<float>& entree)
{
    // On calcul (matrice) pour la couche d'entree vers la premiere couche cachee
    reseau[0]->calculResult(entree);

    // On calcule le resultat pour toute les couches cachés
    // Le resultat précédents sert à la couche suivant pour calculé le résultats
    for(unsigned int i = 1; i < reseau.size() - 1; i++)
    {
        reseau[i]->calculResult(reseau[i-1]->getResult());
    }

    return reseau[reseau.size() - 2]->getResult();
}









