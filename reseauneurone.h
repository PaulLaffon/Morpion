#ifndef RESEAUNEURONE_H
#define RESEAUNEURONE_H

#include "const.h"
#include "coucheneurones.h"

class ReseauNeurone : public QObject
{
    Q_OBJECT
public:
    ReseauNeurone(const string& file_name); // Constructeur avec fichier
    ReseauNeurone(ifstream &file); // Constructeur avec flux de fichier
    ReseauNeurone(const vector<int>& neuroneParCouche); // Construcrteur aléatoire

    // Constructeur pour l'algo génétique qui donne naissance a un fils
    ReseauNeurone(const ReseauNeurone& parent1, const ReseauNeurone& parent2);
    ~ReseauNeurone();

    void save(const string& file_name);
    void save(ofstream& file);

    void load(const string& file_name);
    void load(ifstream &file);

    const vector<float>& calculResult(vector<float>& entree);

    inline const CoucheNeurones& getCouche(int i) const {return reseau[i];}

    inline int getNbCouche() const {return reseau.size();}
    inline int getCoucheSize(int i) const {return reseau[i].getNbNeurones();}
    //inline float& getPoids(int couche, int i, int j) {return reseau[couche].getPoids()[i][j];}

private:
    vector<CoucheNeurones> reseau;

signals:

public slots:
};

#endif // RESEAUNEURONE_H
