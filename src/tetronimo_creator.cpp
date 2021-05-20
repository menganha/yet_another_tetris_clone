#include "tetromino_creator.h"

Tetromino*
TetrominoCreator::create_block(tetrominoType type)
{

    switch (type) {
        case tetrominoType::T_block:
            return new Tetromino({ { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } });
        case tetrominoType::L_block:
            return new Tetromino({ { { 2, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } });
        case tetrominoType::J_block:
            return new Tetromino({ { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } });
        case tetrominoType::Z_block:
            return new Tetromino({ { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } } });
        case tetrominoType::S_block:
            return new Tetromino({ { { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 } } });
        case tetrominoType::O_block:
            return new Tetromino({ { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } } });
        case tetrominoType::I_block:
            return new Tetromino({ { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } } });
        default:
            return nullptr;
    }
}
