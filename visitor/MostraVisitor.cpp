#include "MostraVisitor.hpp"

#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"

#include <QLabel>
#include <QPixmap>
#include <QTreeWidget>
#include <set>
#include <QString>

void MostraVisitor::Visit(File_Generico& file) {

    nome->setText(QString::fromStdString(file.GetNome()));
    autore->setText(QString::fromStdString(file.GetAutore()));
    genere->setText(QString::fromStdString(file.GetGenere()));
    anno->setText(QString::fromStdString(std::to_string(file.GetAnno())));
    
    sottoSx->addWidget(autore);
    sottoSx->addWidget(genere);
    sottoSx->addWidget(anno);

    sotto->addLayout(sottoSx);

    if(dynamic_cast<File_Video*>(&file)){
        Visit(static_cast<File_Video&>(file));
    } else if(dynamic_cast<File_Libro*>(&file)){
        Visit(static_cast<File_Libro&>(file));
    }if(dynamic_cast<File_Serie*>(&file)){
        Visit(static_cast<File_Serie&>(file));
    }

    widgetIcona = new QLabel();
    widgetIcona->setPixmap(icona->pixmap(200,200));
    widgetIcona->setAlignment(Qt::AlignCenter);

    sopra->addWidget(widgetIcona);

    sopra->addWidget(nome);

    layout->addLayout(sopra);
    layout->addLayout(sotto);

    if(dynamic_cast<File_Serie*>(&file)) layout->addWidget(albero_episodi);
}

void MostraVisitor::Visit(File_Video& video) {
    durata = new QLabel(QString::fromStdString(std::to_string(video.GetDurata())));
    regista = new QLabel(QString::fromStdString(video.GetRegista()));
    casa_di_produzione = new QLabel(QString::fromStdString(video.GetCasaDiProduzione()));
    
    sottoDx->addWidget(durata);
    sottoDx->addWidget(regista);
    sottoDx->addWidget(casa_di_produzione);

    sotto->addLayout(sottoDx);
    
    if(dynamic_cast<File_Film*>(&video)){
        Visit(static_cast<File_Film&>(video));
    } else if(dynamic_cast<File_Episodio*>(&video)){
        Visit(static_cast<File_Episodio&>(video));
    }
}

void MostraVisitor::Visit(File_Film& film) {
    icona = new QIcon(":/IMMAGINI/film_nero.png");
    oscar = new QIcon(":/IMMAGINI/Oscar.png");
    if(film.GetOscar()){
        QLabel *widgetOscar = new QLabel();
        widgetOscar->setPixmap(oscar->pixmap(200,200));
        widgetOscar->setAlignment(Qt::AlignCenter);
        sotto->addWidget(widgetOscar);
    };
}

void MostraVisitor::Visit(File_Episodio& episodio) {
    icona = new QIcon(":/IMMAGINI/episodio_nero.png");
    serie = new QLabel(QString::fromStdString(episodio.GetSerieTV()));
    numero_episodio = new QLabel(QString::fromStdString(std::to_string(episodio.GetNumeroEpisodio())));
    numero_stagione = new QLabel(QString::fromStdString(std::to_string(episodio.GetNumeroStagione())));

    sottoDx->addWidget(serie);
    sottoDx->addWidget(numero_stagione);
    sottoDx->addWidget(numero_episodio);

    sotto->addLayout(sottoDx);
    
}

void MostraVisitor::Visit(File_Libro& libro) {
    icona = new QIcon(":/IMMAGINI/libro_nero.png");
    pagine = new QLabel(QString::fromStdString(std::to_string(libro.GetPagine())));
    editore = new QLabel(QString::fromStdString(libro.GetEditore()));

    sottoDx->addWidget(pagine);
    sottoDx->addWidget(editore);

    sotto->addLayout(sottoDx);
}

void MostraVisitor::Visit(File_Serie& serie) {
    icona = new QIcon(":/IMMAGINI/serie_nero.png");
    numero_episodi = new QLabel(QString::fromStdString(std::to_string(serie.GetNumeroEpisodi())));
    numero_stagioni = new QLabel(QString::fromStdString(std::to_string(serie.GetNumeroStagioni())));
    casa_di_produzione_serie = new QLabel(QString::fromStdString(serie.GetCasaDiProduzione()));
    
    sottoDx->addWidget(numero_stagioni);
    sottoDx->addWidget(numero_episodi);
    sottoDx->addWidget(casa_di_produzione_serie);
    
    sotto->addLayout(sottoDx);

    CreaAlberoEpisodi(serie);
}

void MostraVisitor::CreaAlberoEpisodi(const File_Serie& serie){
    albero_episodi = new QTreeWidget();
    albero_episodi->setHeaderHidden(true);
    albero_episodi->setAlternatingRowColors(true);
    albero_episodi->setRootIsDecorated(false);

    auto episodi = serie.GetEpisodi();

    std::set<unsigned int> stagioni;
    for(const auto& cit : episodi){
        stagioni.insert(cit->GetNumeroStagione());
    }

    if(stagioni.size()==0) return;

    for(unsigned int s : stagioni){
        QString N_Stagione = QString("Stagione %1").arg(s);
        QTreeWidgetItem* RamoStagione = new QTreeWidgetItem(QStringList(N_Stagione));
        for(const auto& ep : episodi){
            if(ep->GetNumeroStagione < s) continue;
            if(ep->GetNumeroStagione > s) break;
            QTreeWidgetItem* e = new QTreeWidgetItem();
            e->setText(0, QString::fromStdString(e->GetNome()));
            e->setIcon(0, QIcon(":/IMMAGINI/episodio_nero.png"));
            RamoStagione->addChild(e);
        }
    }
}

QVBoxLayout* MostraVisitor::GetLayout(){
    return layout;
}