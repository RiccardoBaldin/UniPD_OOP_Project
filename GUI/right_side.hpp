#ifndef RIGHT_SIDE_HPP
#define RIGHT_SIDE_HPP

#include <QWidget>

class UpperBar;
class LineaOrizzontale;
class Biblioteca;
class QStackedWidget;
class DisposizioneGriglia;
class DisposizioneLinee;

class RightSide : public QWidget {
    Q_OBJECT

public:
    explicit RightSide(Biblioteca *biblioteca = nullptr, QWidget *parent = nullptr);
    void updateLayout();

private:
    UpperBar *upperBar;
    LineaOrizzontale *linea;
    Biblioteca *biblioteca;
    QStackedWidget *stackedWidget;
    DisposizioneGriglia *Griglia;
    DisposizioneLinee *Linee;

private slots:
    void changeLayout(int index);
        
};

#endif // RIGHT_SIDE_HPP