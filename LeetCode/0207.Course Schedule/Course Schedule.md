```

class Solution(object):
    def canFinish(self, numCourses, prerequisites):
        graph = defaultdict(list)
        inorder = [0] * numCourses
        for edge in prerequisites:
            graph[edge[0]].append(edge[1])
            inorder[edge[1]] += 1

        q = deque()
        for node in range(numCourses):
            if inorder[node] == 0:
                q.append(node)

        while q:
            node = q.popleft()
            for nxt in graph[node]:
                inorder[nxt] -= 1
                if inorder[nxt] == 0:
                    q.append(nxt)

        return False if sum(inorder) > 0 else True
```

I used Topological order.

To solve this problem.
I defined graph that is made with (a, b) directed edges and nodes and indegree that contains indegree values for each node.
And I initialize indegree as 0. Also, I append nodes that has 0 indegree value to queue object.
The reason why I append it is that they do not require previously visited nodes.

The core logic is as follows:
Until queue is not empty, I repeat following steps.
I get node that comes from queue and decrease nodes' indegree value.
In this case, nodes mean that these nodes are connected from current node.
Also, I append some of these nodes those indegree are zero.

Finally, I return True if indegree value is not remained, if not I return False
It means that there is no unreached nodes 

This logics time complexity is O(n)(n is numOfCourses) and space complexity is O(n + v)(n is numOfCourses and v is numOfEdges(len(prerequisites)))
