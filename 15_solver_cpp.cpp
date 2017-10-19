#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <set>

using namespace std;

int mod(int a, unsigned n){ //in c++  -1 % 4 = -1 or 3 but i want = 3 always
    int mod = a % n;
    return mod < 0 ? mod + n : mod;
}
unsigned manh_distance_in_matrix(int a, int b, int n){ //a b - coords, n - one side size
    return abs(a % n - b % n) + abs((int)(a / n) - (int)(b / n));
}

class board_state {
    int n; //width of board
    int size; //size = n^2
    int* board;
    vector<board_state*> previous_states;
public:
    board_state(int n, int* board) : n(n), size(n * n) {
        this->board = new int[size];
        for(int i = 0; i < size; ++i){
            this->board[i] = board[i];
        }
    }
    board_state(board_state* parent, int swap1, int swap2) {
        n = parent->n;
        size = parent->size;
        board = new int[size];
        for(int i = 0; i < size; ++i){
            board[i] = parent->board[i];
        }
        swap(board[swap1], board[swap2]);
        previous_states = parent->previous_states;
        previous_states.push_back(parent);
    }
    ~board_state(){
        delete[] board;
    }
    board_state(const board_state& obj) = delete;
    vector<board_state*> get_neighbours_state(){
        vector<board_state*> neighbours;
        int zero_coord = -1;
        for(int i = 0; i < size; ++i){
            if (board[i] == 0){
                zero_coord = i;
                break;
            }
        }
        if (zero_coord + 1 < 16 && manh_distance_in_matrix(zero_coord, zero_coord + 1, n) == 1){
            board_state* p = new board_state(this, zero_coord, zero_coord + 1);
            neighbours.push_back(p);
        }
        if (zero_coord - 1 >= 0 && manh_distance_in_matrix(zero_coord, zero_coord - 1, n) == 1){
            board_state* p = new board_state(this, zero_coord, zero_coord - 1);
            neighbours.push_back(p);
        }
        if (zero_coord - n >= 0 && manh_distance_in_matrix(zero_coord, zero_coord - n, n) == 1){
            board_state* p = new board_state(this, zero_coord, zero_coord - n);
            neighbours.push_back(p);
        }
        if (zero_coord + n >= 0 && manh_distance_in_matrix(zero_coord, zero_coord + n, n) == 1){
            board_state* p = new board_state(this, zero_coord, zero_coord + n);
            neighbours.push_back(p);
        }
        return neighbours;
    }

    int manh_distance(){
        int distance = 0;
        for(int i = 0; i < size; ++i){
            //сложные подсчёты которые невозможно описать
            // distance += abs(mod(board[i] - 1, size) % n - i % n) + abs((int)(mod(board[i] - 1, size) / n) - (int)(i / n));
            distance += manh_distance_in_matrix(mod(board[i] - 1, size), i, n);
        }
        return distance;
    }
    int linear_conflict(){
        return 0;
    }
    int corner_tiles(){
        return 0;
    }
    int last_move(){
        return 0;
    }

    const bool operator == (const board_state& other){
        if (n != other.n) return false;

        for (int i = 0; i < size; ++i){
            if (board[i] != other.board[i]) return false;    
        }

        return true;
    }
};

void a_star(board_state* cur){
    set<board_state*> visited; //посещённые AAAAAAAAAA переделать тут кароче должны храниться хэши массивов
    auto comp = [](board_state* a, board_state* b) { return a->manh_distance() > b->manh_distance(); };    
    //очередь с приоритетом с переопределением сравнения, чтобы сравнивались по наименьшему манхеттену
    priority_queue<board_state*, vector<board_state*>, decltype(comp)> pqueue(comp);
    pqueue.push(cur);
    while(!pqueue.empty()){
        board_state* p = pqueue.top();
        pqueue.pop();

    }

}

int main(){
    auto comp = [](board_state* a, board_state* b) {
        // это кароче так надо чтобы сравнивалось классно всё
        return !(*a == *b);
    };
    set<board_state*> visited;
    int pole[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,0,15};
    board_state* a = new board_state(4, pole);
    visited.insert(a);
    board_state* b = new board_state(4, pole);
    
    if (*a == *b) {
        cout << "hello a = b" << endl;
    }

    if (visited.count(b) > 0){
        cout << "hey" << endl;
    }
    cout << a->manh_distance() << endl;

    delete a;
    delete b;
    return 0;
}