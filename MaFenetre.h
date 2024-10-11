
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDoubleValidator>

#define DECIMAL_BINAIRE 0
#define BINAIRE_DECIMAL 1


    class MaFenetre : public QDialog
    {
        Q_OBJECT
    public:
        MaFenetre(QWidget *parent = 0);

    private:
        // Les widgets
        QLineEdit *valeur;
        QLabel *resultat;
        QLabel *unite;
        QComboBox *choixConversion;
        QPushButton *bConvertir;
        QPushButton *bQuitter;

        // Méthodes
        void afficherUnite();

    private slots: // Déclaration des slots
        void convertir();
        void permuter();

    signals: // Ajoute cette section
        void actualiser(); // Déclare le signal ici
    };
