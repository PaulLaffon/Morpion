#include "coucheneurones.h"

// Constructeur qui initialise de façon aléatoire
CoucheNeurones::CoucheNeurones(const short numberNeurones, const short neuronesCoucheSuiv)
    :nb_neurones(numberNeurones)
{
    // Tableau du résultat du calcul a partir de la matrice de poids
    result.resize(neuronesCoucheSuiv, -1);

    poids.resize(nb_neurones);

    for(int i = 0; i < nb_neurones; i++)
        poids[i].resize(neuronesCoucheSuiv);

    // On affecte une valeur aléatoire a chaque poids
    for(int i = 0; i < nb_neurones; i++)
    {
        for(int j = 0; j < neuronesCoucheSuiv; j++)
        {
            float value = ((rand() % NB_VALEUR_POID) - NB_VALEUR_POID / 2) / (double)NB_VALEUR_POID * 10.0;
            poids[i][j] = value;
        }
    }
}

// Constructeur avec tableau passé en entrée
CoucheNeurones::CoucheNeurones(const vector<vector<float> > &p) :nb_neurones(p.size())
{
    // On copie le vecteur poids
    poids = p;

    // Le résultat est le nombre de colonne de la matrice de poids
    result.resize(poids[0].size());
}

CoucheNeurones::CoucheNeurones(const CoucheNeurones &parent1, const CoucheNeurones &parent2)
{
    // On cherche le point de cross over, c'est le point au on va changer de parent
    int x = rand() % parent1.getNbNeurones();
    int y = rand() % parent1.getSuivNeurones();

    poids = parent1.getPoids();

    for(int i = x; i < parent1.getNbNeurones(); i++)
    {
        for(int j = y; j < parent1.getSuivNeurones(); j++)
        {
            poids[i][j] = parent2.getPoids()[i][j];
        }
    }

    // Le résultat est le nombre de colonne de la matrice de poids
    result.resize(poids[0].size(), -1);
    nb_neurones = poids.size();
}

void CoucheNeurones::fonctionActivation(vector<float> &pred)
{
    for(unsigned int i = 0; i < pred.size(); i++)
    {
        if(pred[i] < 1)
            pred[i] = 0.0;
    }
}

// Le booléen indique si il faut utiliser la fonction d'activation
vector<float>& CoucheNeurones::calculResult(vector<float> &pred, bool activationFunction)
{
    if(activationFunction)
        fonctionActivation(pred);

    // On fait la multiplication matricielle du vecteur ligne PRED avec la matrice POIDS pour obtenir le vecteur ligne result
    for(unsigned int col = 0; col < result.size(); col++)
    {
        float sum = 0;
        for(int lig = 0; lig < nb_neurones; lig++)
        {
            sum += (pred[lig] * poids[lig][col]);
        }
        result[col] = sum;
    }

    return result;
}
