
class Solution(object):
    def findRedundantConnection(self, edges):
        # I will use Union Find
        # First, I will define parent list that contains each node's parent index and initialize it as a itself
        n = len(edges)
        parent = [i for i in range(n + 1)]
        # Second, I define find method that find node v's root value.
        def find(v):
            if parent[v] != v:
                parent[v] = find(parent[v])
            return parent[v]

        # Third, I define union method that update node v's parent as a node u's parent
        def union(v, u):
            vRoot = find(v)
            uRoot = find(u)
            if vRoot == uRoot:
                return False

            parent[vRoot] = uRoot
            return True

        # Finally, I return edge that is already merged
        for edge in edges:
            if not union(edge[0], edge[1]):
                return edge

        return []