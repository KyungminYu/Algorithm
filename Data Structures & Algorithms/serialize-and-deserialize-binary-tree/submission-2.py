# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Codec:
    def serialize(self, root: Optional[TreeNode]) -> str:
        values = []

        def dfs(node):
            if node is None:
                values.append("#")
                return

            values.append(str(node.val))
            dfs(node.left)
            dfs(node.right)

        dfs(root)
        return ",".join(values)

    def deserialize(self, data: str) -> Optional[TreeNode]:
        values = iter(data.split(","))

        def dfs():
            value = next(values)

            if value == "#":
                return None

            node = TreeNode(int(value))
            node.left = dfs()
            node.right = dfs()
            return node

        return dfs()