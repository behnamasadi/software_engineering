#include <iostream>
#include <memory>

// Represents a node in the tree
class TreeNode {
public:
    std::unique_ptr<TreeNode> left, right;
    int value;

    explicit TreeNode(int val) : value(val) {}

    virtual bool isNull() const { return false; }
};

// Null object to replace nullptr
class NullTreeNode : public TreeNode {
public:
    NullTreeNode() : TreeNode(0) {}  // Default value for null nodes

    bool isNull() const override { return true; }
};

// Utility function to create a null node
std::unique_ptr<TreeNode> createNullNode() {
    return std::make_unique<NullTreeNode>();
}

// Computes tree size
int treeSizeAfter(const TreeNode* node) {
    if (!node || node->isNull()) {
        std::cout << "Encountered a null node\n";
        return 0;
    }
    return 1 + treeSizeAfter(node->left.get()) + treeSizeAfter(node->right.get());
}

int main() {
    // Creating tree nodes
    auto root = std::make_unique<TreeNode>(9);
    root->left = std::make_unique<TreeNode>(8);
    root->right = std::make_unique<TreeNode>(6);

    root->left->left = std::make_unique<TreeNode>(7);
    root->left->right = std::make_unique<TreeNode>(4);

    root->right->right = std::make_unique<TreeNode>(2);

    std::cout << "Tree size: " << treeSizeAfter(root.get()) << std::endl;

    return 0;
}
