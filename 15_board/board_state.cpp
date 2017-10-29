#include "board_state.h"

board_state::board_state(int n, int* board) : n(n), size(n * n) {
    this->board = new int[size];
    for (int i = 0; i < size; ++i) {
        this->board[i] = board[i];
    }
}

board_state::board_state(board_state* parent, int swap1, int swap2) {
    n = parent->n;
    size = parent->size;
    board = new int[size];
    for (int i = 0; i < size; ++i) {
        board[i] = parent->board[i];
    }
    std::swap(board[swap1], board[swap2]);

    previous_states = parent->previous_states;
    previous_states.push_back(parent);
}

board_state::~board_state() { delete[] board; }

std::vector<board_state*> board_state::get_neighbours_state() {
    std::vector<board_state*> neighbours;
    int zero_coord = -1;
    for (int i = 0; i < size; ++i) {
        if (board[i] == 0) {
            zero_coord = i;
            break;
        }
    }
    // посмотрим на соседей
    if (zero_coord + 1 < size &&
        manh_distance_in_matrix(zero_coord, zero_coord + 1, n) == 1) {
        board_state* p = new board_state(this, zero_coord, zero_coord + 1);
        neighbours.push_back(p);
    }
    if (zero_coord - 1 >= 0 &&
        manh_distance_in_matrix(zero_coord, zero_coord - 1, n) == 1) {
        board_state* p = new board_state(this, zero_coord, zero_coord - 1);
        neighbours.push_back(p);
    }
    if (zero_coord + n < size &&
        manh_distance_in_matrix(zero_coord, zero_coord + n, n) == 1) {
        board_state* p = new board_state(this, zero_coord, zero_coord + n);
        neighbours.push_back(p);
    }
    if (zero_coord - n >= 0 &&
        manh_distance_in_matrix(zero_coord, zero_coord - n, n) == 1) {
        board_state* p = new board_state(this, zero_coord, zero_coord - n);
        neighbours.push_back(p);
    }
    return neighbours;
}

int board_state::manh_distance() {
    int distance = 0;
    for (int i = 0; i < size; ++i) {
        //сложные подсчёты
        distance += manh_distance_in_matrix(mod(board[i] - 1, size), i, n);
    }
    return distance;
}

int board_state::linear_conflict() { return 0; }
int board_state::corner_tiles() { return 0; }
int board_state::last_move() { return 0; }

const bool board_state::operator==(const board_state& other) {
    if (n != other.n) return false;

    for (int i = 0; i < size; ++i) {
        if (board[i] != other.board[i]) return false;
    }

    return true;
}

size_t board_state::hash(board_state* const state) {
    std::string str_hash = "";
    for (int i = 0; i < state->size; ++i) {
        str_hash += std::to_string(state->board[i]);
    }
    size_t hash = std::hash<std::string>()(str_hash);
    return hash;
}

bool board_state::compare_ptrs(board_state* const a, board_state* const b) {
    return *a == *b;
}

bool board_state::compare_manh_dist(board_state* const a,
                                    board_state* const b) {
    return a->manh_distance() >= b->manh_distance();
}

std::ostream& operator<<(std::ostream& os, board_state& c) {
    for (int i = 0; i < c.size; ++i) {
        os << c.board[i] << " ";
    }
    return os;
}