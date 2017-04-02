#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    m_layoutPrincipal = new QHBoxLayout(this);
    m_canvas = new canvas(this);

    m_layoutDroite = new QVBoxLayout;
    m_recommencer = new QPushButton("Recommencer");


    m_layoutPrincipal->addWidget(m_canvas);
    m_layoutPrincipal->addLayout(m_layoutDroite);

    m_layoutDroite->addWidget(m_recommencer);

    this->setLayout(m_layoutPrincipal);

    jeu = new Jeu(this);

    connect(m_canvas, SIGNAL(click(int)), jeu, SLOT(actualiserGrille(int))); // Actualise la grille dans la classe Jeu si on clic sur une case

    connect(jeu, SIGNAL(changementGrille(vector<char>&)), m_canvas, SLOT(updateGrille(vector<char>&))); // Actualise la grille dans la classe Canvas si la grille à changer

    // Affiche une message box avec le vainqueur
    connect(jeu, SIGNAL(signalVictoire(char)), this, SLOT(indiquerVainqueur(char)));

    // Recommence la partie quand on appuie sur le bouton
    connect(m_recommencer, SIGNAL(clicked(bool)), jeu, SLOT(recommencer()));
}

MainWindow::~MainWindow()
{
    delete m_recommencer;
    delete m_layoutDroite;

    delete m_canvas;
    delete m_layoutPrincipal;

    delete jeu;
}

void MainWindow::indiquerVainqueur(char vainqueur)
{
    if(vainqueur == JOUEUR1)
        QMessageBox::information(this, "Fin de la partie !", "Le joueur 1 a remporter la partie !");
    else
        QMessageBox::information(this, "Fin de la partie !", "Le joueur 2 a remporter la partie !");
}
