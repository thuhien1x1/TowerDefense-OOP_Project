#include "cpoint.h"

cpoint::cpoint() { row = col = c = 0; }
cpoint::cpoint(int trow, int tcol, int tc) { row = trow; col = tcol; c = tc; }

int cpoint::getRow() const { return row; }
int cpoint::getCol() const { return col; }
int cpoint::getC() const { return c; }
void cpoint::setC(int tc) { c = tc; }

<<<<<<< HEAD
int cpoint::getPixelX() const { return col * TILE_SIZE + TILE_SIZE / 2; } // |  |  |  | => there are 4 cols (start from 0) ( | ), the object is in the space between 2 cols, so pixel = cols * size + halfOfSize (?)
int cpoint::getPixelY() const { return row * TILE_SIZE + TILE_SIZE / 2; }

void cpoint::setPixelX(int pixelX)
{
    this->col = pixelX / TILE_SIZE;
}

void cpoint::setPixelY(int pixelY)
{
    this->row = pixelY / TILE_SIZE;
}

=======
// Convert from column to horizontal pixels and re-center the tile
int cpoint::getPixelX() const { return col * TILE_SIZE + TILE_SIZE / 2; }
// Convert from row to vertical pixels and re-center the tile
int cpoint::getPixelY() const { return row * TILE_SIZE + TILE_SIZE / 2; }

// Pixel → Tiles: Determine tile from mouse, bullet, enemy position
>>>>>>> github-desktop-chinnnn3107/Update3
cpoint cpoint::fromXYToRowCol(int x, int y, int c) {
    return cpoint(y / TILE_SIZE, x / TILE_SIZE, c);
}
// Tiles → Pixel: Display object at tile
cpoint cpoint::fromRowColToXY(int row, int col, int c) {
    return cpoint(row * TILE_SIZE, col * TILE_SIZE, c);
}
