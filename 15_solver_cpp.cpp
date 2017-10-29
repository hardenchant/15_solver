#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include "15_board/board_state.h"

// ToDo
// - Сделать проверку комбинаторным способом на наличие решения
// - Допилить интерфейс
// - Мб нормальный вывод или нет
// - Последний шаг не выводится пока что
// - Память пока что не очищается в конце программы

using namespace std;

void a_star(board_state* cur) {
    //посещённые
    unordered_set<board_state*, size_t (*)(board_state*),
                  bool (*)(board_state*, board_state*)>
        visited(10, board_state::hash, board_state::compare_ptrs);

    //очередь с приоритетом с переопределением сравнения, чтобы сравнивались по
    //наименьшему манхеттену
    priority_queue<board_state*, vector<board_state*>,
                   bool (*)(board_state*, board_state*)>
        pqueue(board_state::compare_manh_dist);
    pqueue.push(cur);
    visited.insert(cur);
    while (!pqueue.empty()) {
        board_state* p = pqueue.top();
        pqueue.pop();

        if (p->manh_distance() == 0) {
            cout << "SOLVED" << endl;
            auto previous = p->get_previous();
            for (int i = 0; i < previous.size(); ++i) {
                cout << *previous[i] << endl;
            }
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
    cout << "UNDEFINED BEHAVIOR" << endl;
}

int main() {
    int pole[16] = {12, 5, 7, 1, 13, 8, 6, 2, 14, 4, 3, 11, 15, 10, 9, 0};

    board_state* a = new board_state(4, pole);

    cout << a->manh_distance() << endl;

    a_star(a);

    delete a;
    return 0;
}