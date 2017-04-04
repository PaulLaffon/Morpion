#ifndef IARESEAUNEURONE_H
#define IARESEAUNEURONE_H

#include "const.h"
#include "ia.h"
#include "reseauneurone.h"
#include "judge.h"

typedef struct
{
    short couche;
    short x, y;
    float ancienneValue;

}Modif;

class IAReseauNeurone : public IA
{
    Q_OBJECT
public:
    IAReseauNeurone(string filename);
    ~IAReseauNeurone();

    virtual int play();
    virtual pair<int, int> train(char typeMethode);

private:
    ReseauNeurone *m_reseau;


    vector<Modif> modifPoids();

signals:

public slots:
};

#endif // IARESEAUNEURONE_H
