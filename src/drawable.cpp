#include "drawable.h"
#include "board_piece.h"

namespace kmint {
    drawable::drawable(const board_piece &act) : _board_piece{&act} {
    }
}
