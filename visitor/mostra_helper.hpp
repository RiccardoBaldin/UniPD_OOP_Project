#ifndef MOSTRA_HELPER_HPP
#define MOSTRA_HELPER_HPP

#include "../visitor/MostraVisitor.hpp"

#include <QObject>
#include <QLayout>


class File_Generico;
class File_Episodio;
class File_Serie;
class MostraVisitor;
class QVBoxLayout;
class QTreeWidgetItem;

class MostraVisitorHelper : public QWidget {
    Q_OBJECT

public:
    explicit MostraVisitorHelper(File_Generico* file = nullptr, QWidget* parent = nullptr);

signals:
    void AggiuntaEpisodio();
    void EpisodioSelezionato(File_Episodio* episodio);

private:
    QVBoxLayout* layout;
    File_Serie* serie = nullptr;

private slots:
    void Episodio_Clicked(QTreeWidgetItem*);
};

#endif //MOSTRA_HELPER_HPP