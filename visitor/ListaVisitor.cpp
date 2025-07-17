#include "ListaVisitor.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"

#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QHBoxLayout>

void ListaVisitor::Visit(File_Generico& file) {
    if (auto video = dynamic_cast<File_Video*>(&file)) {
        Visit(*video);
    } else if (auto libro = dynamic_cast<File_Libro*>(&file)) {
        Visit(*libro);
    } else if (auto serie = dynamic_cast<File_Serie*>(&file)) {
        Visit(*serie);
    }
}

void ListaVisitor::Visit(File_Video& video) {
    if (auto film = dynamic_cast<File_Film*>(&video)) {
        Visit(*film);
    } else if (auto episodio = dynamic_cast<File_Episodio*>(&video)) {
        Visit(*episodio);
    }
}

void ListaVisitor::Visit(File_Film& film) {
    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    icona = new QIcon(":/IMMAGINI/film_nero.png");
    label = new QLabel();
    label->setPixmap(icona->pixmap(35, 35));
    label->setAlignment(Qt::AlignLeft);
    layout->addWidget(label);

    QLabel* nome = new QLabel(QString::fromStdString(film.GetNome()));
    nome->setAlignment(Qt::AlignCenter);
    nome->setStyleSheet("color: white;");
    
    layout->addWidget(nome);
    layout->addStretch();

}

void ListaVisitor::Visit(File_Episodio& episodio) {
    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    icona = new QIcon(":/IMMAGINI/episodio_nero.png");
    label = new QLabel();
    label->setPixmap(icona->pixmap(35, 35));
    label->setAlignment(Qt::AlignLeft);
    layout->addWidget(label);

    QLabel* nome = new QLabel(QString::fromStdString(episodio.GetNome()));
    nome->setAlignment(Qt::AlignCenter);
    nome->setStyleSheet("color: white;");

    layout->addWidget(nome);
    layout->addStretch();
}

void ListaVisitor::Visit(File_Serie& serie) {
    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    icona = new QIcon(":/IMMAGINI/serie_nero.png");
    label = new QLabel();
    label->setPixmap(icona->pixmap(35, 35));
    label->setAlignment(Qt::AlignLeft);
    layout->addWidget(label);

    QLabel* nome = new QLabel(QString::fromStdString(serie.GetNome()));
    nome->setAlignment(Qt::AlignCenter);
    nome->setStyleSheet("color: white;");

    layout->addWidget(nome);
    layout->addStretch();
}

void ListaVisitor::Visit(File_Libro& libro) {
    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    icona = new QIcon(":/IMMAGINI/libro_nero.png");
    label = new QLabel();
    label->setPixmap(icona->pixmap(35, 35));
    label->setAlignment(Qt::AlignLeft);
    layout->addWidget(label);

    QLabel* nome = new QLabel(QString::fromStdString(libro.GetNome()));
    nome->setAlignment(Qt::AlignCenter);
    nome->setStyleSheet("color: white;");

    layout->addWidget(nome);
    layout->addStretch();
}

QHBoxLayout* ListaVisitor::GetLayout() const {
    return layout;
}