#ifndef COUCHENEURONNES_H
#define COUCHENEURONNES_H

#include  "const.h"

class CoucheNeurones : public QObject
{
    Q_OBJECT
public:
    explicit CoucheNeurones(short numberNeurones, char typeCouche);

    void initializeRandom(short nb_neuronesSuiv);

    inline vector<float>& getResult() {return result;}
    inline short getNbNeurones() {return nb_neurones;}

    inline vector<vector<float> >& getPoids() {return poids;}

    vector<float>& calculResult(vector<float> &pred);

private:
    short nb_neurones;
    vector<vector<float> > poids;
    vector<float> result;
    char type;

    void fonctionActivation(vector<float> &pred);

signals:

public slots:
};

#endif // COUCHENEURONNES_H
