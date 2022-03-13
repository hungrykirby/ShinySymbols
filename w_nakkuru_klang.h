#ifndef WNAKURUKLANG
#define WNAKURUKLANG

class WNakkuruKlang {
public:
    WNakkuruKlang(int pokemon);
    void loop();

private:
    void moveToInitialPlayerPosition();
    void symbolEncount();
    int convertToMSecFromPokemon();
    int symbol;
};

#endif;
