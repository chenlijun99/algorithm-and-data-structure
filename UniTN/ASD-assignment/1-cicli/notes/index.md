# Axioms

* The breadth first tree contains the shortest path for all the vertices pair in
  a undirected unweighted connected acyclic graph (a.k.a. tree).

# Conjectures

* The breadth first tree contains the shortest path for all the vertices pair in
  a undirected unweighted graph.
    * Counterexample: V = {1,2,3}, E={(1,2), (2, 3), (3,1)}
        * BFS from 1: path (2,3) = 2
        * BFS from 2: path (1,3) = 2
        * BFS from 3: path (1,2) = 2

# It won't work

* Adjacency matrix: not enough space.

# Solution

* Search from the bottom of the BFS tree.
    1. One branch goes up the tree until the two branch have the same depth
    2. Go up together, until them converge into the same internal node.
* Assign an id to each cycle. Intersection of ids.
