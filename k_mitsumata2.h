#ifndef KMITSUMATA2_H
#define KMITSUMATA2_H

class KMitsumata2 {
public:
    KMitsumata2(int pokemon);
    void loop();

private:
    void moveToInitialPlayerPosition();
    void symbolEncount();
    int convertToMSecFromPokemon();
    int symbol;
};

#endif
