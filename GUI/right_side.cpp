#include "right_side.hpp"
#include "upper_bar.hpp"
#include "disposizione_griglia.hpp"
#include "disposizione_linee.hpp"
#include "linea_orizzontale.hpp"
#include "add_file_widget.hpp"

#include <QVBoxLayout>
#include <QStackedWidget>


RightSide::RightSide(Biblioteca *biblioteca, QWidget *parent) : QWidget(parent){
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    upperBar = new UpperBar(biblioteca, this);
    linea = new LineaOrizzontale(this);
    
    stackedWidget = new QStackedWidget(this);
    Griglia = new DisposizioneGriglia(biblioteca, this);
    Linee = new DisposizioneLinee(biblioteca, this);

    stackedWidget->addWidget(Griglia);
    stackedWidget->addWidget(Linee);

    layout->addWidget(upperBar);
    layout->addWidget(linea);
    layout->addWidget(stackedWidget);

    setMinimumWidth(600);
    setLayout(layout);

    connect(upperBar, &UpperBar::layoutChanged, this, &RightSide::changeLayout);
    connect(upperBar, &UpperBar::layoutChanged, this, &RightSide::updateLayout);
}

void RightSide::changeLayout(int index) {
    stackedWidget->setCurrentIndex(index);
}

void RightSide::updateLayout() {

    qDebug() << "RightSide::updateLayout() chiamato";

    Griglia->updateLayout();
    Linee->updateLayout();
}