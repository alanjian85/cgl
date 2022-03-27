#ifndef CGL_CELL_H_
#define CGL_CELL_H_

namespace cgl {
    class World;

    class Cell {
    public:
        explicit Cell(bool alive = false) {
            alive_ = alive;
        }

        bool isAlive() const {
            return alive_;
        }

        void update(World& world, int x, int y);
    private:
        bool alive_;
    };
}

#endif // CGL_CELL_H_