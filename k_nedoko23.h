#ifndef KNEDOKO23_H
#define KNEDOKO23_H

class KNedoko23 {
public:
    KNedoko23(int pokemon);
    void loop();

private:
    void moveToInitialPlayerPosition();
    void symbolEncount();
    int convertToMSecFromPokemon();
    int symbol;
};

#endif
