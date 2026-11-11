
class Solution(object):
    def canFinish(self, numCourses, prerequisites):
        # To address this problem, I will use topological order.
        # First, I will make graph ant inorder object that contains inorder degrees for each node.
        graph = defaultdict(list)
        inorder = [0] * numCourses
        for edge in prerequisites:
            graph[edge[0]].append(edge[1])
            inorder[edge[1]] += 1

        # Second, put the nodes that has 0 indegree to the queue
        q = deque()
        for node in range(numCourses):
            if inorder[node] == 0:
                q.append(node)

        # Third, popleft node from queue and decrease nodes' indegree.
        # In this case, nodes are connected from current node.
        # And put some of these nodes those indegree are zero
        # Repeat these step until q is empty

        while q:
            node = q.popleft()
            for nxt in graph[node]:
                inorder[nxt] -= 1
                if inorder[nxt] == 0:
                    q.append(nxt)

        # Finally, return False, if indegree value is remained.
        # It means that there are not reached nodes.
        return False if sum(inorder) > 0 else True
