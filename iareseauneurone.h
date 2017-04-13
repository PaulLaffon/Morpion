#ifndef IARESEAUNEURONE_H
#define IARESEAUNEURONE_H

#include "const.h"
#include "ia.h"
#include "reseauneurone.h"


class IAReseauNeurone : public IA
{
    Q_OBJECT
public:
    IAReseauNeurone(); // Constructeur aléatiore
    IAReseauNeurone(const string& filename); // Constructeur avec fichier
    IAReseauNeurone(ifstream &file); // Constructeur avec flux

    // Constructeur pour l'algo génétique avec les parents, qui donne naissance à un fils
    IAReseauNeurone(const IAReseauNeurone &parent1, const IAReseauNeurone &parent2);
    ~IAReseauNeurone();

    virtual int play();

    inline void save(ofstream& file) {m_reseau->save(file);}
    inline void save(const string& filename) {m_reseau->save(filename);}

    inline void load(ifstream& file) {m_reseau->load(file);}
    inline void load(const string& filename) {m_reseau->load(filename);}

    inline int getScore() const{return score;}
    inline void setScore(int s) {score = s;}
    inline void scoreWin() {score += 1;}
    inline void scoreLose() {score -= 2;}
    inline void resetScore() {score = 0;}

    inline const ReseauNeurone& getReseau() const {return *m_reseau;}

private:
    ReseauNeurone *m_reseau;
    int score;

signals:

public slots:
};

#endif // IARESEAUNEURONE_H
