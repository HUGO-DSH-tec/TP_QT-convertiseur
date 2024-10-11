#include "MaFenetre.h"
#include <QApplication>

MaFenetre::MaFenetre( QWidget *parent ) : QDialog( parent )
{
    // 1. Instancier les widgets
    valeur = new QLineEdit(this);
    resultat = new QLabel(this);
    unite = new QLabel(this);
    choixConversion = new QComboBox(this);
    bQuitter = new QPushButton(QString::fromUtf8("Quitter"), this);

    // 2. Personnaliser les widgets
    valeur->setStyleSheet("color: #0a214c; background-color: #C19A6B;");
    valeur->clear();
    QFont font("Liberation Sans", 12, QFont::Bold);
    choixConversion->setFont(font);
    choixConversion->addItem(QString::fromUtf8("DECIMAL -> BINAIRE"));
    choixConversion->addItem(QString::fromUtf8("BINAIRE -> DECIMAL"));
    resultat->setStyleSheet("color: #0a214c;");
    unite->setStyleSheet("color: #0a214c;");

    // 3. Instancier les layouts
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // 4. Positionner les widgets dans les layouts
    hLayout1->addWidget(valeur);
    hLayout1->addWidget(choixConversion);
    hLayout1->addWidget(resultat);
    hLayout1->addWidget(unite);
    hLayout2->addWidget(bQuitter);
    mainLayout->addLayout(hLayout1);
    mainLayout->addLayout(hLayout2);
    setLayout(mainLayout);

    // 5. Connecter les signaux et slots
    connect(this, SIGNAL(actualiser()), this, SLOT(convertir()));
    connect(choixConversion, SIGNAL(currentIndexChanged(int)), this,SLOT(permuter()));
    connect(bQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    // bonus : conversion automatique
    connect(valeur, SIGNAL(textChanged(const QString &)), this, SLOT(convertir()));

    // 6. Personnaliser la fenêtre
    setWindowTitle(QString::fromUtf8("Convertisseur Decimal en Binaire "));
    adjustSize();
    // on lance une conversion
    //convertir();
    // ou :emit actualiser();
}

//7. Définir les slots
void MaFenetre::convertir()
{
    QString valeurEntree = valeur->text();
    if (valeurEntree.isEmpty())
    {
        resultat->setText(QString::fromUtf8("--.--"));
        afficherUnite();
        return;
    }



    switch (choixConversion->currentIndex())
    {
    case DECIMAL_BINAIRE:
    {
        bool ok;// Déclaration
        int decimal = valeurEntree.toInt(&ok);
        if (ok)
        {
            QString binaire = QString::number(decimal, 2);
            resultat->setText(binaire);
        }
        else
        {
            resultat->setText(QString::fromUtf8("Erreur de conversion"));
        }
        break;
    }

    case BINAIRE_DECIMAL:
    {
        bool ok;// Déclaration
        int decimal = valeurEntree.toInt(&ok, 2); // Utilisation de la base 2
        if (ok)
        {
            resultat->setText(QString::number(decimal));
        }
        else
        {
            resultat->setText(QString::fromUtf8("Erreur de conversion"));
        }
        break;
    }
    }
}


void MaFenetre::permuter()
{
    if(resultat->text() != "--.--")
    {
        valeur->setText(resultat->text());
        emit actualiser();
    }
    afficherUnite();
}

// 8. Définir les méthodes
void MaFenetre::afficherUnite()
{
    switch (choixConversion->currentIndex())
    {
    case  DECIMAL_BINAIRE:
        unite->setText(QString::fromUtf8(" B2"));
        break;
    case BINAIRE_DECIMAL:
        unite->setText(QString::fromUtf8(" D10"));
        break;
    }
}
