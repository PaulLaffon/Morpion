#include "coucheneurones.h"

CoucheNeurones::CoucheNeurones(short numberNeurones, char typeCouche)
    : QObject(), nb_neurones(numberNeurones), type(typeCouche)
{

}

void CoucheNeurones::initializeRandom(short nb_neuronesSuiv)
{
    // Tableau du résultat du calcul a partir de la matrice de poids
    result.resize(nb_neuronesSuiv);

    poids.resize(nb_neurones);

    for(int i = 0; i < nb_neurones; i++)
        poids[i].resize(nb_neuronesSuiv);

    // On affecte une valeur aléatoire a chaque poids
    for(int i = 0; i < nb_neurones; i++)
    {
        for(int j = 0; j < nb_neuronesSuiv; j++)
        {
            poids[i][j] = (rand() % NB_VALEUR_POID) / (double)NB_VALEUR_POID;
        }
    }
}

void CoucheNeurones::fonctionActivation(vector<float> &pred)
{
    for(unsigned int i = 0; i < pred.size(); i++)
    {
        if(pred[i] >= 1)
            pred[i] = 1;
        else
            pred[i] = 0;
    }
}

vector<float>& CoucheNeurones::calculResult(vector<float> &pred)
{
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
