#ifndef CGL_CELL_H_
#define CGL_CELL_H_

namespace cgl {
    class World;

    class Cell {
    public:
        Cell() = default;

        explicit Cell(bool alive, int x, int y) {
            x_ = x;
            y_ = y;
            alive_ = alive;
        }

        bool isAlive() const {
            return alive_;
        }

        void setAlive(bool alive) {
            alive_ = alive;
        }

        void update(World& world);
    private:
        int x_;
        int y_;
        bool alive_;
    };
}

#endif // CGL_CELL_H_