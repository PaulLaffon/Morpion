#ifndef RESEAUNEURONE_H
#define RESEAUNEURONE_H

#include "const.h"
#include "coucheneurones.h"

class ReseauNeurone : public QObject
{
    Q_OBJECT
public:
    ReseauNeurone(string file_name);
    ReseauNeurone(string file_name, int nbCouches, vector<int>& neuroneParCouche);
    ~ReseauNeurone();

    void save(string& file_name);
    void load(string& file_name);

    vector<float>& calculResult(vector<float>& entree);

    inline int getNbCouche() {return reseau.size();}
    inline int getCoucheSize(int i) {return reseau[i]->getNbNeurones();}
    inline float& getPoids(int couche, int i, int j) {return reseau[couche]->getPoids()[i][j];}

    inline string& getFileName() {return filename;}

private:
    vector<CoucheNeurones*> reseau;
    string filename;

signals:

public slots:
};

#endif // RESEAUNEURONE_H
