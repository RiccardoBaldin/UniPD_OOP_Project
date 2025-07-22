#ifndef DISPOSIZIONE_GRIGLIA_HPP
#define DISPOSIZIONE_GRIGLIA_HPP

#include <QWidget>
#include <QGridLayout>

class Biblioteca;
class QScrollArea;
class File_Generico;

class DisposizioneGriglia : public QWidget {
    Q_OBJECT

public:
    explicit DisposizioneGriglia(Biblioteca* biblioteca = nullptr, QWidget *parent = nullptr);
    void updateLayout();

protected:
    void resizeEvent(QResizeEvent*) override;

private:
    Biblioteca* biblioteca;
    std::vector<File_Generico*> lista;
    QGridLayout* layout;
    QScrollArea* scrollArea;


signals:
    void File_Clicked(File_Generico* file);
};


#endif // DISPOSIZIONE_GRIGLIA_HPP