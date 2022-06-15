#include "Color.h"
namespace Mage {
    Color::Color() {}
    Color::Color(std::array<int,4> colarray): r(colarray[0]), g(colarray[1]), b(colarray[2]), a(colarray[3])  {}
    Color::Color(int r, int g, int b, int a) : r(r), b(b), g(g), a(a) {}
    Color::~Color() {}
}