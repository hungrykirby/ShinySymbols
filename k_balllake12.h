#ifndef KBALLLAKE12_H
#define KBALLLAKE12_H

class KBalllake12 {
public:
    KBalllake12(int pokemon);
    void loop();

private:
    void moveToInitialPlayerPosition();
    void symbolEncount();
    int convertToMSecFromPokemon();
    int symbol;
};

#endif
