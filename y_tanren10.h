#ifndef YTANREN10_H
#define YTANREN10_H

class YTanren10 {
public:
    YTanren10(int pokemon);
    void loop();

private:
    void moveToInitialPlayerPosition();
    void symbolEncount();
    int symbol;
};

#endif
