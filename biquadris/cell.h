#ifndef _CELL_
#define _CELL_


class Cell : public Subject <Coordinates> {
    Observer<
    char value;
    bool blinded;
    Coordinates coordinates;

    public:
    Cell (Coordinates);

    void blindCell();
    void unblindCell();
    void setValue();
    void getValue();

    Coordinates getinfo() const override;
};
#endif
