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

const bool board_state::operator==(const board_state& other) {
    if (n != other.n) return false;

    for (int i = 0; i < size; ++i) {
        if (board[i] != other.board[i]) return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, board_state& state) {
    os << "-----------------------" << std::endl;
    for (int i = 0; i < state.size; ++i) {
        if (i % state.n == 0) os << std::endl;
        os << std::setw(4) << state.board[i] << " ";
    }
    os << std::endl;
    return os;
}

const std::vector<board_state*> board_state::get_neighbours_state() {
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

const std::vector<board_state*> board_state::get_previous() { 
    return previous_states; 
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

std::vector<board_state*> board_state::a_star(board_state* cur) {
    std::vector<board_state*> result;
    //посещённые
    std::unordered_set<board_state*, size_t (*)(board_state*),
                       bool (*)(board_state*, board_state*)>
        visited(10, board_state::hash, board_state::compare_ptrs);

    //очередь с приоритетом с переопределением сравнения, чтобы сравнивались по
    //наименьшему манхеттену
    std::priority_queue<board_state*, std::vector<board_state*>,
                        bool (*)(board_state*, board_state*)>
        pqueue(board_state::compare_manh_dist);
    pqueue.push(cur);
    visited.insert(cur);
    while (!pqueue.empty()) {
        board_state* p = pqueue.top();
        pqueue.pop();

        if (p->manh_distance() == 0) {
            result = p->get_previous();
            result.push_back(p);
            break;
        }

        auto neighbours = p->get_neighbours_state();
        for (int i = 0; i < neighbours.size(); ++i) {
            auto res = visited.insert(neighbours[i]);
            if (res.second) {
                pqueue.push(neighbours[i]);
            } else {
                delete neighbours[i];
            }
        }
    }
    return result;
}