#ifndef EPISODIO_ITEM_HPP
#define EPISODIO_ITEM_HPP

#include <QTreeWidgetItem>
#include "../CLASSI_FILE/File_Episodio.hpp"

class EpisodioItem : public QTreeWidgetItem {

private:
    File_Episodio *episodio;

public:
    EpisodioItem(QTreeWidgetItem* parent, File_Episodio* episodio);

    File_Episodio* getEpisodio() const;
};



#endif //EPISODIO_ITEM_HPP