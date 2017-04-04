#ifndef IAMINMAX_H
#define IAMINMAX_H

#include "const.h"
#include "ia.h"

class IAMinMax : public IA
{
Q_OBJECT

public:
    IAMinMax();
    //virtual void updateGrille(const vector<char> &g);
    virtual int play();

private:
    int evaluation();
    bool matchNul();

    int nbCaseVide();
    int maxi(int caseVides, int profondeur);
    int mini(int caseVides, int profondeur);

};

#endif // IAMINMAX_H
