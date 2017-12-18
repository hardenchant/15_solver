import unittest
from a_star import a_star

class test_a_star(unittest.TestCase):
    '''
    This class shows the usage of a_star for other programs
    '''
    class chain():
        """
        Shows which function are be overload for working in a_star algorithm
        """
        def last_node(self):
            """
            Its func must return hashable value (e.g. str)
            """
            return "last_node"
        def f(self):
            """
            Return sum of heuristics
            """
            return 1
        def g(self):
            """
            Return distance from start to self edge
            """
            return 2
        def get_neighbours(self):
            """
            Return neighbours of this edge
            """
            return []
        def __lt__(self, other):
            """
            This is used in priority queue for choosing next proceed object
            """
            return self.f() < other.f()

    def test_usage(self):
        start = self.chain()
        end = start.last_node()
        self.assertEqual(a_star(start, end), start)


if __name__ == "__main__":
    unittest.main()