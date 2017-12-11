import a_star
import time  # For Debug
from math import sqrt


def manh_dst_matrix(a, b, n):
    """Find manhattan distance between `a` and `b` in matrix of size `n`
    """
    return abs(a % n - b % n) + abs(a // n - b // n)


class chain15:
    def __str__(self):
        i = 0
        sstr = ""
        while i < self.size ** 2:
            sstr += str(self.board_state[i]) + " "
            if i % self.size == 3:
                sstr += "\n"
            i += 1
        return sstr

    def __init__(self, board_state, history=[]):
        self.board_state = list(board_state)
        self.size = int(sqrt(len(board_state)))
        self.history = history
        self.quad_size = int(self.size * self.size)

    def manh_dst(self):
        dst = 0
        for i in range(0, self.quad_size):
            dst += manh_dst_matrix((self.board_state[i] - 1) % self.quad_size, i, self.size)
        return int(dst)

    def last_node(self):
        """Must be hashable value (list not hashable :( )
        """
        return str(self.board_state)

    def linear_conflict(self):
        conflict_count = 0
        # ToDo some heuristic :)
        return 2 * conflict_count

    def last_move(self):
        if self.board_state[-1] == self.quad_size - 1 or self.board_state[-1] == self.quad_size - self.size:
            return 0
        return 2

    def corner_tiles(self):
        conflict_count = 0
        # upper left corner
        if self.board_state[0] != 1:
            if self.board_state[1] == 2 or self.board_state[self.size] == self.size + 1:
                conflict_count += 1
        # upper right corner
        if self.board_state[self.size - 1] != self.size:
            if self.board_state[self.size - 2] == self.size - 1 or self.board_state[self.size * 2 - 1] == self.size * 2:
                conflict_count += 1
        # lower left corner
        if self.board_state[self.quad_size - self.size] != self.quad_size - self.size + 1:
            if self.board_state[self.quad_size - self.size * 2] == self.quad_size - self.size * 2 + 1 or self.board_state[self.quad_size - self.size + 1] == self.quad_size - self.size + 2:
                conflict_count += 1

        return 2 * conflict_count

    def simple_heur(self):
        dst = 0
        for i in range(0, int(self.quad_size)):
            if (self.board_state[i] - 1) != i:
                dst += 1
        return dst

    def h(self):
        return self.manh_dst() + self.last_move()

    def g(self):
        return len(self.history)

    def f(self):
        return self.h()

    def __lt__(self, other):
        return self.f() < other.f()

    def get_neighbours(self):
        neighs = []
        zero_coord = self.board_state.index(0)

        # look at neighbours
        if zero_coord + 1 < self.size ** 2 and manh_dst_matrix(zero_coord, zero_coord + 1, self.size) == 1:
            new_state = self.board_state.copy()
            new_state[zero_coord], new_state[zero_coord + 1] = new_state[zero_coord + 1], new_state[zero_coord]
            neighs.append(chain15(new_state, self.history + [self.board_state]))

        if zero_coord - 1 >= 0 and manh_dst_matrix(zero_coord, zero_coord - 1, self.size) == 1:
            new_state = self.board_state.copy()
            new_state[zero_coord], new_state[zero_coord - 1] = new_state[zero_coord - 1], new_state[zero_coord]
            neighs.append(chain15(new_state, self.history + [self.board_state]))

        if zero_coord + self.size < self.size ** 2 and manh_dst_matrix(zero_coord, zero_coord + self.size,
                                                                       self.size) == 1:
            new_state = self.board_state.copy()
            new_state[zero_coord], new_state[zero_coord + self.size] = new_state[zero_coord + self.size], new_state[
                zero_coord]
            neighs.append(chain15(new_state, self.history + [self.board_state]))

        if zero_coord - self.size >= 0 and manh_dst_matrix(zero_coord, zero_coord - self.size, self.size) == 1:
            new_state = self.board_state.copy()
            new_state[zero_coord], new_state[zero_coord - self.size] = new_state[zero_coord - self.size], new_state[
                zero_coord]
            neighs.append(chain15(new_state, self.history + [self.board_state]))

        # # Debug
        # for i in neighs:
        #     print(i.last_node() + "   " + str(i.f()))
        # print("-------------------")
        # time.sleep(1)
        return neighs


if __name__ == '__main__':
    # start = chain15((1,2,6,3,4,9,5,7,8,13,11,15,12,14,0,10))
    # start = chain15((1,2,6,3,4,9,5,7,8,13,11,15,12,0,14,10))
    # start = chain15(( 1, 3, 4, 8, 5, 2, 11, 7, 10, 6,0,12,9,13,14,15))
    # end = chain15((1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,0))
    start = chain15((5, 1, 9, 3, 11, 13, 6, 8, 14, 10, 4, 15, 0, 12, 7, 2))
    end = chain15((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0))
    print(str(start))  # Debug

    result = a_star.a_star(start, end.last_node())
    print(result)
    print(len(result.history))
    # # Debug
    # for node in result.history:
    #     print (node)
    # print(result.board_state)
