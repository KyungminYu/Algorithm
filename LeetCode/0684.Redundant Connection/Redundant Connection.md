```

class Solution(object):
    def findRedundantConnection(self, edges):
        n = len(edges)
        parent = [i for i in range(n + 1)]
        def find(v):
            if parent[v] != v:
                parent[v] = find(parent[v])
            return parent[v]

        def union(v, u):
            vRoot = find(v)
            uRoot = find(u)
            if vRoot == uRoot:
                return False

            parent[vRoot] = uRoot
            return True
        
        for edge in edges:
            if not union(edge[0], edge[1]):
                return edge

        return []
```

I will use the Union-Find algorithm to detect the edge that creates a cycle.
First, I initialize a parent array so that each node is its own parent.
Second, I define a find function that finds the root of a node. It also applies path compression to make future searches faster.
Third, I define a union function that connects the roots of two nodes. If both nodes already have the same root, they are already connected, so adding the edge would create a cycle.
Finally, I iterate through the edges and return the first edge whose endpoints are already connected.
The time complexity is O(E), which is nearly linear, and the space complexity is O(V).