#include "episodio_item.hpp"

#include "../mouse/mouse_handler.hpp"

EpisodioItem::EpisodioItem(QTreeWidgetItem* parent, File_Episodio* episodio) : QTreeWidgetItem(parent), episodio(episodio){
    mouseMenu *click = new mouseMenu(episodio);

}

File_Episodio* EpisodioItem::getEpisodio() const { return episodio; }