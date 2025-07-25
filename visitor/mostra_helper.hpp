#ifndef MOSTRA_HELPER_HPP
#define MOSTRA_HELPER_HPP

#include "../visitor/MostraVisitor.hpp"

#include <QObject>
#include <QLayout>


class File_Generico;
class File_Serie;
class MostraVisitor;
class QVBoxLayout;

class MostraVisitorHelper : public QWidget {
    Q_OBJECT

public:
    explicit MostraVisitorHelper(File_Generico* file = nullptr, QWidget* parent = nullptr);
    QVBoxLayout* GetLayout();

signals:
    void AggiuntaEpisodio();

private:
    QVBoxLayout* layout = new QVBoxLayout();
    File_Serie* serie = nullptr;
    MostraVisitor visitor;

private slots:
    void Aggiungi_Clicked();
};

#endif //MOSTRA_HELPER_HPP