#ifndef KSUBERIDASHI8_H
#define KSUBERIDASHI8_H

class KSuberidashi8 {
public:
    KSuberidashi8(int pokemon);
    void loop();

private:
    void moveToInitialPlayerPosition();
    void symbolEncount();
    int convertToMSecFromPokemon();
    int symbol;
};

#endif
