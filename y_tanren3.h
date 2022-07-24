#ifndef YTANREN3_H
#define YTANREN3_H

class YTanren3 {
public:
    YTanren3(int pokemon);
    void loop();

private:
    void moveToInitialPlayerPosition();
    void symbolEncount();
    int convertToMSecFromPokemon();
    int symbol;
};

#endif
