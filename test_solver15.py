import unittest
from a_star import a_star
from solver15 import chain15, manh_dst_matrix


class test_chain15(unittest.TestCase):
    """
    Unit tests for check correctness of chain15 class.
    """
    def test_manh_dst_matrix(self):
        """
        Unit test: check the correctness of the manhattan distance calculation in matrix function
        This is the most useful test for debugging this program.
        """

        # 0 1
        # 2 3

        self.assertEqual(manh_dst_matrix(0, 3, 2), 2)

        # 0  1  2  3
        # 4  5  6  7
        # 8  9 10 11
        # 12 13 14 15

        self.assertEqual(manh_dst_matrix(1, 10, 4), 3)
        self.assertEqual(manh_dst_matrix(0, 15, 4), 6)
        self.assertEqual(manh_dst_matrix(15, 11, 4),
                         manh_dst_matrix(11, 15, 4))

    def test_chain15_manh(self):
        """
        Unit test: check calculating manhattan distance in board of 15 puzzle
        """

        comb1 = chain15((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15))
        self.assertEqual(comb1.manh_dst(), 2)
        comb2 = chain15((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0))
        self.assertEqual(comb2.manh_dst(), 0)

    def test_chain15_get_neighbours(self):
        """
        Unit test: check true neighbours of knuckle at the board
        """
        comb1 = chain15((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0))
        # comb1.get_neighbours()
        self.assertEqual(comb1.get_neighbours()[0].board_state, chain15(
            (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15)).board_state)
        self.assertEqual(comb1.get_neighbours()[1].board_state, chain15(
            (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 13, 14, 15, 12)).board_state)


class test_solver15(unittest.TestCase):
    """
    Test class for check the result of working a_star over chain15
    """
    def test_solve(self):
        # start = chain15((1,2,6,3,4,9,5,7,8,13,11,15,12,14,0,10))
        # start = chain15((1,2,6,3,4,9,5,7,8,13,11,15,12,0,14,10))
        # start = chain15(( 1, 3, 4, 8, 5, 2, 11, 7, 10, 6,0,12,9,13,14,15))
        # end = chain15((1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,0))
        start = chain15((5, 1, 9, 3, 11, 13, 6, 8, 14, 10, 4, 15, 0, 12, 7, 2))
        end = chain15((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0))

        self.assertEqual(a_star(start, end.last_node()).last_node(), end.last_node())


if __name__ == "__main__":
    unittest.main()
