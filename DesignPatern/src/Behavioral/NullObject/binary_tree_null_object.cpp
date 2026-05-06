// Null Object — binary tree variant.
// Instead of nullptr children, missing branches are represented by a shared
// "null leaf" that knows how to answer queries trivially. Tree algorithms
// then need no nullptr checks.

#include <iostream>
#include <memory>

class Node {
public:
    virtual ~Node() = default;
    virtual int size() const = 0;
    virtual int sum() const = 0;
};

class NullNode : public Node {
public:
    int size() const override { return 0; }
    int sum()  const override { return 0; }

    // One shared instance is enough — null nodes are stateless.
    static const std::shared_ptr<Node>& instance() {
        static const std::shared_ptr<Node> inst = std::make_shared<NullNode>();
        return inst;
    }
};

class TreeNode : public Node {
public:
    explicit TreeNode(int value) : value_(value),
                                   left_(NullNode::instance()),
                                   right_(NullNode::instance()) {}

    void setLeft(std::shared_ptr<Node> n)  { left_  = std::move(n); }
    void setRight(std::shared_ptr<Node> n) { right_ = std::move(n); }

    int size() const override { return 1 + left_->size() + right_->size(); }
    int sum()  const override { return value_ + left_->sum()  + right_->sum();  }

private:
    int value_;
    std::shared_ptr<Node> left_, right_;
};

int main() {
    auto root = std::make_shared<TreeNode>(9);
    auto l    = std::make_shared<TreeNode>(8);
    auto r    = std::make_shared<TreeNode>(6);
    root->setLeft(l);
    root->setRight(r);
    l->setLeft(std::make_shared<TreeNode>(7));
    l->setRight(std::make_shared<TreeNode>(4));
    r->setRight(std::make_shared<TreeNode>(2));

    std::cout << "size = " << root->size() << '\n';   // 6
    std::cout << "sum  = " << root->sum()  << '\n';   // 36
}
