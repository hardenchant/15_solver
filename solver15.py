import a_star
# import time # For Debug
from math import sqrt


def manh_dst_matrix(a, b, n):
    """Find manhattan distance between `a` and `b` in matrix of size `n`
    """
    return abs(a % n - b % n) + abs(a // n - b // n)


class chain15:
    def __init__(self, board_state, history=[]):
        self.board_state = list(board_state)
        self.size = int(sqrt(len(board_state)))
        self.history = history

    def manh_dst(self):
        dst = 0
        for i in range(0, int(self.size ** 2)):
            dst += manh_dst_matrix((self.board_state[i] - 1) %
                                   (self.size ** 2), i, self.size)
        return int(dst)

    def last_node(self):
        """Must be hashable value (list not hashable :( )
        """
        return str(self.board_state)

    def linear_conflict():
        pass

    def last_move():
        pass

    def corner_tiles():
        pass

    def h(self):
        return self.manh_dst()  # + linear_conflict() + last_move() + corner_tiles()

    def g(self):
        return len(self.history)

    def f(self):
        return self.h() + self.g()

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

        if zero_coord + self.size < self.size ** 2 and manh_dst_matrix(zero_coord, zero_coord + self.size, self.size) == 1:
            new_state = self.board_state.copy()
            new_state[zero_coord], new_state[zero_coord + self.size] = new_state[zero_coord + self.size], new_state[zero_coord]
            neighs.append(chain15(new_state, self.history + [self.board_state]))

        if zero_coord - self.size >= 0 and manh_dst_matrix(zero_coord, zero_coord - self.size, self.size) == 1:
            new_state = self.board_state.copy()
            new_state[zero_coord], new_state[zero_coord - self.size] = new_state[zero_coord - self.size], new_state[zero_coord]
            neighs.append(chain15(new_state, self.history + [self.board_state]))

        # # Debug
        # for i in neighs:
        #     print(i.last_node() + "   " + str(i.f()))
        # print("-------------------")
        # time.sleep(1)
        return neighs


if __name__ == '__main__':
    start = chain15((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15))
    end = chain15((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0))
    # print(end.last_node() + "    START") # Debug

    result = a_star.a_star(start, end.last_node())

    # # Debug
    # for node in result.history:
    #     print (node)
    # print(result.board_state)
