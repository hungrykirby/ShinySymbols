#ifndef KNEDOKO26_H
#define KNEDOKO26_H

class KNedoko26 {
public:
    KNedoko26(int pokemon);
    void loop();

private:
    void moveToInitialPlayerPosition();
    void symbolEncount();
    int convertToMSecFromPokemon();
    int symbol;
};

#endif
