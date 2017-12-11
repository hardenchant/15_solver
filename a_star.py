from heapq import heappop, heappush

# `a_star`
#
# `start_chain` - its a class with heuristic function in overload of `__lt__`
# and function `start.last_node()` which return a `node`
# `start_chain` has subclass 'node' with usefull info about graph edge (board state for 15 puzzle)
# and overload of `__eq__` which return result of last move in decision tree.
# `goal` - value which compare with `last_move`; its a target of this algh
#
# `heapqpop` working as LIFO if keys are equal
# it means that algh will be worked as deep search in this case


def a_star(start_chain, goal_node):
    node_hash = {}
    chains_queue = []
    heappush(chains_queue, start_chain)
    while chains_queue:
        cur_chain = heappop(chains_queue)
        cur_node = cur_chain.last_node()
        if cur_node == goal_node:
            return cur_chain
        node_hash[cur_node] = cur_chain.g()
        for chain in cur_chain.get_neighbours():
            if chain.last_node() in node_hash:
                if chain.g() >= node_hash[chain.last_node()]:
                    continue
                node_hash[chain.last_node()] = chain.g()
            heappush(chains_queue, chain)

    raise Exception("No solution?!")
