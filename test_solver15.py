import unittest
from solver15 import chain15, manh_dst_matrix


class test_chain15(unittest.TestCase):
    def test_manh_dst_matrix(self):
        """
        0 1
        2 3
        """
        self.assertEqual(manh_dst_matrix(0, 3, 2), 2)

        """
        0  1  2  3
        4  5  6  7
        8  9 10 11
        12 13 14 15
        """
        self.assertEqual(manh_dst_matrix(1, 10, 4), 3)
        self.assertEqual(manh_dst_matrix(0, 15, 4), 6)
        self.assertEqual(manh_dst_matrix(15, 11, 4),
                         manh_dst_matrix(11, 15, 4))

    def test_chain15_manh(self):
        comb1 = chain15((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15))
        self.assertEqual(comb1.manh_dst(), 2)
        comb2 = chain15((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0))
        self.assertEqual(comb2.manh_dst(), 0)

    def test_chain15_get_neighbours(self):
        comb1 = chain15((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0))
        # comb1.get_neighbours()
        self.assertEqual(comb1.get_neighbours()[0].board_state, chain15(
            (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15)).board_state)
        self.assertEqual(comb1.get_neighbours()[1].board_state, chain15(
            (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 13, 14, 15, 12)).board_state)


if __name__ == "__main__":
    unittest.main()
