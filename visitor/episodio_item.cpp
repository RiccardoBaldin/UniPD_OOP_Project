#include "episodio_item.hpp"

EpisodioItem::EpisodioItem(QTreeWidgetItem* parent, File_Episodio* episodio) 
                            : QTreeWidgetItem(parent), episodio(episodio){}

File_Episodio* EpisodioItem::getEpisodio() const { return episodio; }