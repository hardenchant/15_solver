#ifndef BOARD_STATE_H
#define BOARD_STATE_H

#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "utils.h"

class board_state {
    int n;     // width of board
    int size;  // size = n^2
    int* board;
    std::vector<board_state*> previous_states;

   public:
    board_state(int n, int* board);
    board_state(board_state* parent, int swap1, int swap2);
    board_state(const board_state& obj) = delete;
    ~board_state();

    std::vector<board_state*> get_neighbours_state();

    std::vector<board_state*> get_previous() { return previous_states; }

    int manh_distance(); // манхэттенское расстояние
    int linear_conflict();
    int corner_tiles();
    int last_move();

    const bool operator==(const board_state& other);

    friend std::ostream& operator<<(std::ostream& os, board_state& c);

    static size_t hash(
        board_state* const state);  // для unordered_set функция хэширования
    static bool compare_manh_dist(
        board_state* const a,   //предикат для выставления приоритета в очереди
        board_state* const b);  //возвращает 0 если a < b

    static bool compare_ptrs(board_state* const a,
                             board_state* const b);  //предикат для сравнения по
                                                     //указателям, то же самое
                                                     //что == только для
                                                     //указателей
};

#endif