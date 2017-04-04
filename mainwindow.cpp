#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    srand(time(nullptr));


    // Toute la fenetre
    m_layoutPrincipal = new QHBoxLayout(this);
    m_canvas = new canvas(this); // La zone de jeu

    // Le menu avec ses différents éléments
    m_layoutDroite = new QVBoxLayout;
    m_recommencer = new QPushButton("Recommencer");

    // Groupe Box qui indique si on joue avec ou sans IA
    m_groupBox = new QGroupBox("IA");
    m_avecIa = new QRadioButton("Avec");
    m_sansIa = new QRadioButton("Sans");

    m_avecIa->setChecked(true);
    QHBoxLayout *layout_IA = new QHBoxLayout;
    layout_IA->addWidget(m_avecIa);
    layout_IA->addWidget(m_sansIa);
    m_groupBox->setLayout(layout_IA);

    // Groupe Box qui indique quel joueur commence
    m_commence = new QGroupBox("Qui commence :");
    m_iaCommence = new QRadioButton("IA");
    m_playerCommence = new QRadioButton("Joueur");

    m_iaCommence->setChecked(true);
    QHBoxLayout *layoutCommence = new QHBoxLayout;
    layoutCommence->addWidget(m_iaCommence);
    layoutCommence->addWidget(m_playerCommence);
    m_commence->setLayout(layoutCommence);

    // Le choix du type de l'IA contre laquelle on va jouer
    m_choixIA = new QComboBox(this);
    m_choixIA->addItem("IA Random");
    m_choixIA->addItem("IA Min Max");
    m_choixIA->addItem("IA Reseau de Neurones");

    // Le choix du fichier pour un IA réseau de neurones
    m_filepath = new QLineEdit(this);
    m_choosefilepath = new QPushButton("Choisir fichier", this);
    QHBoxLayout *layoutChoixFile = new QHBoxLayout;
    layoutChoixFile->addWidget(m_filepath);
    layoutChoixFile->addWidget(m_choosefilepath);


    m_layoutPrincipal->addWidget(m_canvas);
    m_layoutPrincipal->addLayout(m_layoutDroite);

    m_layoutDroite->addWidget(m_recommencer);
    m_layoutDroite->addWidget(m_groupBox);
    m_layoutDroite->addWidget(m_choixIA);
    m_layoutDroite->addLayout(layoutChoixFile);
    m_layoutDroite->addWidget(m_commence);

    this->setLayout(m_layoutPrincipal);

    jeu = new Jeu(this);

    connect(m_canvas, SIGNAL(click(int)), jeu, SLOT(actualiserGrille(int))); // Actualise la grille dans la classe Jeu si on clic sur une case

    connect(jeu, SIGNAL(changementGrille(vector<char>&)), m_canvas, SLOT(updateGrille(vector<char>&))); // Actualise la grille dans la classe Canvas si la grille à changer

    // Affiche une message box avec le vainqueur
    connect(jeu, SIGNAL(signalVictoire(char)), this, SLOT(indiquerVainqueur(char)));

    // Recommence la partie quand on appuie sur le bouton
    connect(m_recommencer, SIGNAL(clicked(bool)), this, SLOT(recommencer()));

    // Choix du fichier quand on appuie sur le bouton
    connect(m_choosefilepath, SIGNAL(clicked(bool)), this, SLOT(choisirFichier()));

    QTime t;
    t.start();

    IA *m = new IAReseauNeurone("C:\\Users\\Paul\\Documents\\Qt\\Morpion\\neuralnetwork\\first.txt");

    pair<int, int> r = m->train(0);


    qDebug("Partie perdue début : %d, Partie perdu fin : %d", r.first, r.second);
    qDebug("Time elapsed: %d ms", t.elapsed());





    jeu->recommencer(m_avecIa->isChecked(), m_choixIA->currentIndex(), m_iaCommence->isChecked());
}

MainWindow::~MainWindow()
{
    /*
    delete m_iaCommence;
    delete m_playerCommence;
    delete m_commence;

    delete m_choixIA;
    delete m_groupBox;

    delete m_avecIa;
    delete m_sansIa;

    delete m_recommencer;
    delete m_layoutDroite;

    delete m_canvas;
    delete m_layoutPrincipal;
    */
    delete jeu;
}

void MainWindow::indiquerVainqueur(char vainqueur)
{
    if(vainqueur == JOUEUR1)
        QMessageBox::information(this, "Fin de la partie !", "Le joueur 1 a remporter la partie !");
    else if(vainqueur == JOUEUR2)
        QMessageBox::information(this, "Fin de la partie !", "Le joueur 2 a remporter la partie !");
    else if(vainqueur == VIDE)
        QMessageBox::information(this, "Fin de la partie !", "Match Nul !");
}

void MainWindow::recommencer()
{
    jeu->recommencer(m_avecIa->isChecked(), m_choixIA->currentIndex(), m_iaCommence->isChecked());
}

void MainWindow::choisirFichier()
{
    m_filepath->setText(QFileDialog::getSaveFileName(this, "Choix du fichier", QString(), "Fichiers textes (*.txt *.xml)"));
}
