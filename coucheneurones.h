#ifndef COUCHENEURONNES_H
#define COUCHENEURONNES_H

#include  "const.h"

class CoucheNeurones
{

public:
    CoucheNeurones(const short numberNeurones, const short neuronesCoucheSuiv); // Constructeur aléatoire
    CoucheNeurones(const vector<vector<float> >& p); // Constructeur avec poids

    // Constructeur a partir des parents
    CoucheNeurones(const CoucheNeurones& parent1, const CoucheNeurones& parent2);



    inline vector<float>& getResult() {return result;}

    inline short getNbNeurones() const {return nb_neurones;}
    inline short getSuivNeurones() const {return poids[0].size();}

    inline const vector<vector<float> >& getPoids() const {return poids;}

    // Retourne le résultat qui va être calculé par la couche suivante
    vector<float>& calculResult(vector<float> &pred, bool activationFunction);

private:
    short nb_neurones;
    vector<vector<float> > poids;
    vector<float> result;

    void fonctionActivation(vector<float> &pred);


};

#endif // COUCHENEURONNES_H
