#ifndef KSUBERIDASHI12_H
#define KSUBERIDASHI12_H

class KSuberidashi12 {
public:
    KSuberidashi12(int pokemon);
    void loop();

private:
    void moveToInitialPlayerPosition();
    void symbolEncount();
    int convertToMSecFromPokemon();
    int symbol;
};

#endif
