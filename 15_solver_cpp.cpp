#include <fstream>
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


int main() {
    int pole[16] = {2, 10, 9, 1, 4, 15, 14, 11, 8, 6, 3, 5, 13, 12, 7, 0};
    
    // ifstream fin("task.in");
    ofstream fout("solution.out");
    


    board_state* a = new board_state(4, pole);

    auto vect = board_state::a_star(a);
    fout << "Solution size: " << vect.size() << endl;
    for (int i = 0; i < vect.size(); ++i){
        fout << *vect[i] << endl;
    }

    delete a;

    fout.close();
    return 0;
}