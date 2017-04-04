#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "const.h"
#include "canvas.h"
#include "jeu.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    canvas *m_canvas;
    QHBoxLayout *m_layoutPrincipal;

    QVBoxLayout *m_layoutDroite;
    QPushButton *m_recommencer;

    QGroupBox *m_groupBox;
    QRadioButton *m_avecIa;
    QRadioButton *m_sansIa;

    QGroupBox *m_commence;
    QRadioButton *m_playerCommence;
    QRadioButton *m_iaCommence;

    QComboBox *m_choixIA;

    Jeu *jeu;

public slots:
    void indiquerVainqueur(char vainqueur);
    void recommencer();
};

#endif // MAINWINDOW_H
