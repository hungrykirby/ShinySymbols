#ifndef YTANREN4_H
#define YTANREN4_H

class YTanren4 {
public:
    YTanren4(int pokemon);
    void loop();

private:
    void moveToInitialPlayerPosition();
    void symbolEncount();
    int convertToMSecFromPokemon();
    int symbol;
};

#endif