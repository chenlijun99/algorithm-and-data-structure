# Source: https://www.geeksforgeeks.org/creating-tree-left-child-right-sibling-representation/

class Node:
    def __init__(self, key):
        self.child = None
        self.rightSibling = None
        self.key = key

    def addSibling(self, key):
        node = self
        while (node.rightSibling):
            node = node.rightSibling

        node.rightSibling = Node(key)
        return node.rightSibling

    def addChild(self, key):
        if (self.child):
            return self.child.addSibling(key)
        else:
            self.child = Node(key)
            return self.child

    def iterativeBFS(self):
        print("BFS:")
        queue = [self]

        while (len(queue) > 0):
            node = queue.pop(0)
            print(f"{node.key}")
            child = node.child
            while (child is not None):
                queue.append(child)
                child = child.rightSibling

Tree = Node;

if __name__ == '__main__':
    tree = Tree(10)
    tree.addChild(2)
    tree.addChild(3)

    child4 = tree.addChild(4)
    child4.addChild(6)

    child5 = tree.addChild(5)
    child5.addChild(7)
    child5.addChild(7)
    child5.addChild(9)

    tree.iterativeBFS()
