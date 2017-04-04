#ifndef CONST_H
#define CONST_H

using namespace std;

#include <QApplication>
#include <QObject>

#include <QWidget>

#include <QPainter>
#include <QPaintEvent>
#include <QPen>

#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QComboBox>
#include <QLineEdit>
#include <QFileDialog>

#include <QMessageBox>

#include <QTime>

#include <vector>
#include <ctime>
#include <fstream>

enum {TRAIN_AGAINST_RANDOM};
enum {HIDDEN, ENTREE, SORTIE};
enum {NUL = -2, VIDE = -1, JOUEUR1 = 0, JOUEUR2 = 1, VICTOIRE_JOUEUR1 = 2, VICTOIRE_JOUEUR2 = 3};
enum {AUCUNE_IA = -1, RANDOM_IA = 0, MIN_MAX_IA = 1};

#define TAILLE_CASE 100
#define NB_CASE_HORIZONTAL 3
#define NB_CASE_VERTICAL 3

#define TAILLE_VERTICAL TAILLE_CASE * NB_CASE_VERTICAL
#define TAILLE_HORIZONTAL TAILLE_CASE * NB_CASE_HORIZONTAL

#define TAILLE_ESPACE 5

#define INFINI 1000

#define NB_VALEUR_POID 100


#endif // CONST_H
