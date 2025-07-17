#include "GrigliaVisitor.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"

#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QVBoxLayout>

void GrigliaVisitor::Visit(File_Generico& file) {
    if(dynamic_cast<File_Video*>(&file)){
        Visit(static_cast<File_Video&>(file));
    } else if(dynamic_cast<File_Libro*>(&file)){
        Visit(static_cast<File_Libro&>(file));
    }else if(dynamic_cast<File_Serie*>(&file)){
        Visit(static_cast<File_Serie&>(file));
    }
}

void GrigliaVisitor::Visit(File_Video& video) {
    if(dynamic_cast<File_Film*>(&video)){
        Visit(static_cast<File_Film&>(video));
    } else if(dynamic_cast<File_Episodio*>(&video)){
        Visit(static_cast<File_Episodio&>(video));
    }
}

void GrigliaVisitor::Visit(File_Film& film) {
    layout = new QVBoxLayout();
    icona = new QIcon(":/IMMAGINI/film_nero.png");
    label = new QLabel();
    label->setPixmap(icona->pixmap(65, 65));
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    QLabel* nome = new QLabel(QString::fromStdString(film.GetNome()));
    nome->setAlignment(Qt::AlignLeft);
    nome->setStyleSheet("color: black;");
    layout->addWidget(nome);
}

void GrigliaVisitor::Visit(File_Episodio& episodio) {
    layout = new QVBoxLayout();
    icona = new QIcon(":/IMMAGINI/episodio_nero.png");
    label = new QLabel();
    label->setPixmap(icona->pixmap(69, 69));
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    QLabel* nome = new QLabel(QString::fromStdString(episodio.GetNome()));
    nome->setAlignment(Qt::AlignLeft);
    nome->setStyleSheet("color: black;");
    layout->addWidget(nome);
}

void GrigliaVisitor::Visit(File_Serie& serie) {
    layout = new QVBoxLayout();
    icona = new QIcon(":/IMMAGINI/serie_nero.png");
    label = new QLabel();
    label->setPixmap(icona->pixmap(69,69));
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    QLabel* nome = new QLabel(QString::fromStdString(serie.GetNome()));
    nome->setAlignment(Qt::AlignLeft);
    nome->setStyleSheet("color: black;");
    layout->addWidget(nome);
}

void GrigliaVisitor::Visit(File_Libro& libro) {
    layout = new QVBoxLayout();
    icona = new QIcon(":/IMMAGINI/libro_nero.png");
    label = new QLabel();
    label->setPixmap(icona->pixmap(69, 69));
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    QLabel* nome = new QLabel(QString::fromStdString(libro.GetNome()));
    nome->setAlignment(Qt::AlignLeft);
    nome->setStyleSheet("color: black;");
    layout->addWidget(nome);
}

QVBoxLayout* GrigliaVisitor::GetLayout() const {
    return layout;
}