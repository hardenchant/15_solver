import queue

# a_star
#
# start_chain - its a class with heuristic function in overload of __lt__ and function start.last_node()
# chain has subclass 'node' with usefull info (board state for 15 puzzle)
# and overload of __eq__ which return result of last move in decision tree.
# goal - value which compare with last_move; its a target of this algh


def a_star(start_chain, goal_node):
    node_hashs = {}
    chains_queue = queue.PriorityQueue(0)
    chains_queue.put(start_chain)
    while not chains_queue.empty():
        cur_chain = chains_queue.get()
        cur_node = cur_chain.last_node()
        if cur_node in node_hashs:
            continue
        if cur_node == goal_node:
            return cur_chain
        node_hashs[cur_node] = None
        for chain in cur_chain.get_neighbours():
            chains_queue.put(chain)
