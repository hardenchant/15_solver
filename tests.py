import solver15
import filecmp
import a_star

"""
This test checks whether the output is correct and the algorithm works in your cfg.
It also shows what should be the input and output of the program.
"""

if __name__ == '__main__':
    board_str = ""

    with open("in.dat") as input_file:
        board_str = input_file.read()

    start_state = list(map(int, board_str.split()))
    start = solver15.chain15(start_state)
    end = solver15.chain15((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0))

    result = a_star.a_star(start, end.last_node())
    with open("test_out.ans", 'w') as output_file:
        print(str(len(result.history)), file=output_file)
        for node in result.history:
            print(str(node), file=output_file)
            print("-------------------------", file=output_file)
        print(str(result), file=output_file)

    if filecmp.cmp("test_out.ans", "out.ans"):
        print("Test complete!")
    else:
        print("Test error!")