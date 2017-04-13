#include "reseauneurone.h"

ReseauNeurone::ReseauNeurone(const vector<int> &neuroneParCouche)
{
    // On ajoute n - 1 couche car la dernière ne fait que office de résultat
    // Or le résultat est stocké dans l'avant dernière couche, donc on a pas besoin de la dernière
    for(int i = 0; i < (int)neuroneParCouche.size() - 1; i++)
    {
        // On appelle le constructeur random de la couche
        reseau.push_back(CoucheNeurones(neuroneParCouche[i], neuroneParCouche[i+1]));
    }
}



// Constructeur d'un réseau de neurones qui charge le fichier contenant le réseau de neurones
ReseauNeurone::ReseauNeurone(const string& file_name)
{
    load(file_name);
}

ReseauNeurone::ReseauNeurone(ifstream &file)
{
    load(file);
}

ReseauNeurone::ReseauNeurone(const ReseauNeurone &parent1, const ReseauNeurone &parent2)
{
    for(unsigned int i = 0; i < parent1.getNbCouche(); i++)
    {
        reseau.push_back(CoucheNeurones(parent1.getCouche(i), parent2.getCouche(i)));
    }
}

ReseauNeurone::~ReseauNeurone()
{

}

void ReseauNeurone::save(ofstream &file)
{
    // Nombre de couche
    file << reseau.size() << endl;

    file << endl;

    // POur chaque couche du réseau de neurones (il y a n-1 couches)
    for(unsigned int i = 0; i < reseau.size(); i++)
    {
        // On affiche les dimension de la matrice
        file << reseau[i].getNbNeurones() << " " << reseau[i].getSuivNeurones() << endl;

        // On affiche tout les poids
        for(int j = 0; j < reseau[i].getNbNeurones() ; j++)
        {
            for(int k = 0; k < reseau[i].getSuivNeurones(); k++)
            {
                file << reseau[i].getPoids()[j][k] << " ";
            }
            file << endl;
        }
    }

}

void ReseauNeurone::save(const string &file_name)
{
    ofstream file;
    file.open(file_name);

    save(file);

    file.close();
}

void ReseauNeurone::load(ifstream &file)
{
    // On recupère le nombre de couche du reseau
    unsigned int size;
    file >> size;

    // On recupere le poids de chacune des couches
    for(unsigned int i = 0; i < size; i++)
    {
        // On recupère la taille
        int x, y;
        file >> x >> y;

        // Matrice qui va servir a stocker les poids, ensuite elle va être copié
        vector<vector<float> > poids;

        poids.resize(x);

        // On recupère la valeur de chacun des poids
        for(int j = 0; j < x; j++)
        {
            for(int k = 0; k < y; k++)
            {
                float p;
                file >> p;

                // On stocke chaque poids dans la matrice
                poids[j].push_back(p);
            }
        }
        // On alloue chaque couche grâce au constructeur qui prend une matrice de poids
        reseau.push_back(CoucheNeurones(poids));
    }
}

void ReseauNeurone::load(const string& file_name)
{
    ifstream file;
    file.open(file_name);

    load(file);

    file.close();
}



const vector<float> &ReseauNeurone::calculResult(vector<float>& entree)
{   

    // On calcul (matrice) pour la couche d'entree vers la premiere couche cachee
    reseau[0].calculResult(entree, false);

    // On calcule le resultat pour toute les couches cachés
    // Le resultat précédents sert à la couche suivant pour calculé le résultats
    for(unsigned int i = 1; i < reseau.size(); i++)
    {
        reseau[i].calculResult(reseau[i-1].getResult(), true);
    }

    return reseau.back().getResult();
}









