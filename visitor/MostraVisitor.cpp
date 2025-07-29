#include "MostraVisitor.hpp"

#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"
#include "episodio_item.hpp"

#include <QLabel>
#include <QPixmap>
#include <QTreeWidget>
#include <set>
#include <QString>

void MostraVisitor::Visit(File_Generico& file) {

    delete widget;
    widget = new QWidget();
    layout = new QVBoxLayout(widget);

    sopra = new QHBoxLayout();
    sotto = new QHBoxLayout();
    sottoSx = new QVBoxLayout();
    sottoDx = new QVBoxLayout();

    nome->setText(QString::fromStdString(file.GetNome()));
    autore->setText(QString::fromStdString(file.GetAutore()));
    genere->setText(QString::fromStdString(file.GetGenere()));
    anno->setText(QString::fromStdString(std::to_string(file.GetAnno())));
    
    sottoSx->addWidget(autore);
    sottoSx->addWidget(genere);
    sottoSx->addWidget(anno);

    sotto->addLayout(sottoSx);

    widgetIcona = new QLabel();
    widgetIcona->setAlignment(Qt::AlignCenter);

    sopra->addWidget(widgetIcona);

    sopra->addWidget(nome);

    layout->addLayout(sopra);
    layout->addLayout(sotto);

}

void MostraVisitor::Visit(File_Video& video) {
    Visit(static_cast<File_Generico&>(video));
    durata = new QLabel(QString::fromStdString(std::to_string(video.GetDurata())));
    regista = new QLabel(QString::fromStdString(video.GetRegista()));
    casa_di_produzione = new QLabel(QString::fromStdString(video.GetCasaDiProduzione()));
    
    sottoDx->addWidget(durata);
    sottoDx->addWidget(regista);
    sottoDx->addWidget(casa_di_produzione);

    sotto->addLayout(sottoDx);
}

void MostraVisitor::Visit(File_Film& film) {
    Visit(static_cast<File_Video&>(film));
    icona = new QIcon(":/IMMAGINI/film_nero.png");
    oscar = new QIcon(":/IMMAGINI/Oscar.png");
    widgetIcona->setPixmap(icona->pixmap(200,200));
    if(film.GetOscar()){
        QLabel *widgetOscar = new QLabel();
        widgetOscar->setPixmap(oscar->pixmap(200,200));
        widgetOscar->setAlignment(Qt::AlignCenter);
        sotto->addWidget(widgetOscar);
    };
}

void MostraVisitor::Visit(File_Episodio& episodio) {
    Visit(static_cast<File_Video&>(episodio));
    icona = new QIcon(":/IMMAGINI/episodio_nero.png");
    widgetIcona->setPixmap(icona->pixmap(200,200));
    serie = new QLabel(QString::fromStdString(episodio.GetSerieTV()));
    numero_episodio = new QLabel(QString::fromStdString(std::to_string(episodio.GetNumeroEpisodio())));
    numero_stagione = new QLabel(QString::fromStdString(std::to_string(episodio.GetNumeroStagione())));

    sottoDx->addWidget(serie);
    sottoDx->addWidget(numero_stagione);
    sottoDx->addWidget(numero_episodio);

    sotto->addLayout(sottoDx);
    
}

void MostraVisitor::Visit(File_Libro& libro) {
    Visit(static_cast<File_Generico&>(libro));
    icona = new QIcon(":/IMMAGINI/libro_nero.png");
    widgetIcona->setPixmap(icona->pixmap(200,200));
    pagine = new QLabel(QString::fromStdString(std::to_string(libro.GetPagine())));
    editore = new QLabel(QString::fromStdString(libro.GetEditore()));

    sottoDx->addWidget(pagine);
    sottoDx->addWidget(editore);

    sotto->addLayout(sottoDx);
}

void MostraVisitor::Visit(File_Serie& serie) {
    Visit(static_cast<File_Generico&>(serie));
    icona = new QIcon(":/IMMAGINI/serie_nero.png");
    widgetIcona->setPixmap(icona->pixmap(200,200));
    numero_episodi = new QLabel(QString::fromStdString(std::to_string(serie.GetNumeroEpisodi())));
    numero_stagioni = new QLabel(QString::fromStdString(std::to_string(serie.GetNumeroStagioni())));
    casa_di_produzione_serie = new QLabel(QString::fromStdString(serie.GetCasaDiProduzione()));
    
    sottoDx->addWidget(numero_stagioni);
    sottoDx->addWidget(numero_episodi);
    sottoDx->addWidget(casa_di_produzione_serie);
    
    sotto->addLayout(sottoDx);

    CreaAlberoEpisodi(serie);

    if (albero_episodi) {
        layout->addWidget(albero_episodi);
    }

}

void MostraVisitor::CreaAlberoEpisodi(const File_Serie& serie){

    auto episodi = serie.GetEpisodi();

    std::set<unsigned int> stagioni;
    for(const auto& cit : episodi){
        stagioni.insert(cit->GetNumeroStagione());
    }

    if(stagioni.size()==0) return;

    albero_episodi = new QTreeWidget();
    albero_episodi->setHeaderHidden(true);
    albero_episodi->setAlternatingRowColors(true);
    albero_episodi->setRootIsDecorated(false);

    for(unsigned int s : stagioni){
        QString N_Stagione = QString("Stagione %1").arg(s);
        QTreeWidgetItem* RamoStagione = new QTreeWidgetItem(albero_episodi);
        RamoStagione->setText(0, N_Stagione);
        for(const auto& ep : episodi){
            if(ep->GetNumeroStagione() < s) continue;
            if(ep->GetNumeroStagione() > s) break;
                EpisodioItem* e = new EpisodioItem(RamoStagione, ep);
                e->setText(0, QString::fromStdString(ep->GetNome()));
                e->setIcon(0, QIcon(":/IMMAGINI/episodio_nero.png"));
        }
    }
    albero_episodi->expandAll();
}

QWidget* MostraVisitor::GetWidget() const {
    return widget;
}

QTreeWidget* MostraVisitor::GetAlberoEpisodi() const {
    return albero_episodi;
}