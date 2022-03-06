#ifndef KNEDOKO28_H
#define KNEDOKO28_H

class KNedoko28 {
public:
    KNedoko28(int pokemon);
    void loop();

private:
    void moveToInitialPlayerPosition();
    void symbolEncount();
    int convertToMSecFromPokemon();
    int symbol;
};

#endif
