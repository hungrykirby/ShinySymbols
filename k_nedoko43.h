#ifndef KNEDOKO43_H
#define kNEDOKO43_H

class KNedoko43 {
public:
    KNedoko43(int pokemon);
    void loop();

private:
    void moveToInitialPlayerPosition();
    void symbolEncount();
    int convertToMSecFromPokemon();
    int symbol;
};

#endif