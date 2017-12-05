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
            float value = rand() - RAND_MAX / 2;
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
    poids.resize(parent1.getNbNeurones());
    for(int i = 0; i < parent1.getNbNeurones(); i++)
    {
        poids[i].resize(parent1.getSuivNeurones());
        for(int j = 0; j < parent1.getSuivNeurones(); j++)
        {
            if(rand() % 2)
            {
                poids[i][j] = parent1.getPoids()[i][j];
            }
            else
            {
                poids[i][j] = parent2.getPoids()[i][j];
            }

            // Mutations
            if(rand() % 70 == 0)
            {
                poids[i][j] = rand() - RAND_MAX / 2;
            }
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
        if(pred[i] > 0)
            pred[i] *= 3;
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
