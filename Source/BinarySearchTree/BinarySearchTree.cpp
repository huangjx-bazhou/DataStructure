﻿#include <iostream>

template<typename T>
class BinarySearchTree
{
public:
    BinarySearchTree() : root(nullptr) {}
    BinarySearchTree(const BinarySearchTree& other) : root(this->clone(other.root)) {}
    ~BinarySearchTree()
    {
        this->makeEmpty();
    }

    // 置空
    void makeEmpty()
    {
        this->makeEmpty(root);
    }

    // 是否为空
    bool isEmpty() const
    {
        return nullptr == root;
    }

    // 插入
    void insert(const T& x)
    {
        this->insert(x, root);
    }

    // 删除
    void remove(const T& x)
    {
        this->remove(x, root);
    }

    // 查找最小值
    bool findMin(T& min) const
    {
        BinaryNode* node = this->findMin(root);
        if (node)
        {
            min = node->element;
            return true;
        }
        else
        {
            return false;
        }
    }

    // 查找最大值
    bool findMax(T& max) const
    {
        BinaryNode* node = this->findMax(root);
        if (node)
        {
            max = node->element;
            return true;
        }
        else
        {
            return false;
        }
    }

    // 是否存在
    bool contains(const T& x) const
    {
        return this->contains(x, root);
    }

    // 打印
    void printTree() const
    {   
        std::cout << "中序遍历" << std::endl;
        this->printTree(root);
        std::cout << std::endl;
    }

private:
    struct BinaryNode
    {
        T element;
        BinaryNode* left;  /// 左子树
        BinaryNode* right; /// 右子树

        BinaryNode(const T& e, BinaryNode* l, BinaryNode* r) :
            element(e), left(l), right(r) {}
    };

    BinaryNode* root;

    // 置空
    void makeEmpty(BinaryNode*& t)
    {
        if (nullptr != t)
        {
            // 置空左子树
            this->makeEmpty(t->left);

            // 置空右子树
            this->makeEmpty(t->right);

            std::cout << "删除节点:" << t->element << std::endl;

            delete t;

            t = nullptr;
        }
    }

    // 插入
    void insert(const T& x, BinaryNode*& t)
    {
        if (nullptr == t)
        {
            t = new BinaryNode(x, nullptr, nullptr);

            std::cout << "插入:" << x << std::endl;
        }
        else if (x < t->element)
        {
            this->insert(x, t->left);
        }
        else if (x > t->element)
        {
            this->insert(x, t->right);
        }
        else
        {

        }
    }

    // 删除
    void remove(const T& x, BinaryNode*& t)
    {
        if (nullptr == t)
        {
            return;
        }

        if (x < t->element)
        {
            this->remove(x, t->left);
        }
        else if (x > t->element)
        {
            this->remove(x, t->right);
        }
        else
        {
            if (t->left && t->right)
            {
                // 有两个儿子
                t->element = this->findMin(t->right)->element;
                this->remove(t->element, t->right);
            }
            else
            {
                BinaryNode* old = t;
                t = (t->left != nullptr) ? t->left : t->right;
                delete old;
            }
        }
    }

    // 查找最小值
    BinaryNode* findMin(BinaryNode* t) const
    {
        if (nullptr == t)
        {
            return nullptr;
        }
        
        if (nullptr == t->left)
        {
            return t;
        }

        return this->findMin(t->left);
    }

    // 查找最大值
    BinaryNode* findMax(BinaryNode* t) const
    {
        if (nullptr == t)
        {
            return nullptr;
        }

        if (nullptr == t->right)
        {
            return t;
        }

        return this->findMax(t->right);
    }

    // 是否存在
    bool contains(const T& x, BinaryNode* t) const
    {
        if (nullptr == t)
        {
            return false;
        }

        if (x < t->element)
        {
            return this->contains(x, t->left);
        }
        else if (x > t->element)
        {
            return this->contains(x, t->right);
        }
        else
        {
            return true;
        }
    }

    // 打印
    void printTree(BinaryNode* t) const
    {
        if (nullptr == t)
        {
            return;
        }

        this->printTree(t->left);

        std::cout << t->element << " ";

        this->printTree(t->right);
    }

    BinaryNode* clone(BinaryNode* t) const
    {
        if (nullptr == t)
        {
            return nullptr;
        }
        else
        {
            return new BinaryNode(t->element, this->clone(t->left), this->clone(t->right));
        }
    }
};

// 打印最值
template<typename T>
void printMaxMin(const BinarySearchTree<T>& bst)
{
    int min = 0;
    int max = 0;

    if (bst.findMin(min))
    {
        std::cout << "最小值:" << min << std::endl;
    }
    else
    {
        std::cout << "没有最小值" << std::endl;
    }

    if (bst.findMax(max))
    {
        std::cout << "最大值:" << max << std::endl;
    }
    else
    {
        std::cout << "没有最大值" << std::endl;
    }
}

int main()
{
    BinarySearchTree<int> bst;

    std::cout << "=====初始化完成=====" << std::endl;

    int x = 17;
    std::cout << "是否为空:" << bst.isEmpty() << std::endl;
    std::cout << "是否存在" << x << ": " << bst.contains(x) << std::endl;

    printMaxMin(bst);

    std::cout << "=====插入数据=====" << std::endl;

    bst.insert(6);
    bst.insert(7);
    bst.insert(1);
    bst.insert(17);
    bst.insert(13);
    bst.insert(12);
    bst.insert(3);
    bst.insert(5);

    BinarySearchTree<int> bst2(bst);
    
    bst.printTree();
    std::cout << "是否为空:" << bst.isEmpty() << std::endl;
    std::cout << "是否存在" << x << ": " << bst.contains(x) << std::endl;

    printMaxMin(bst);

    std::cout << "=====删除=====" << std::endl;

    bst.remove(x);
    std::cout << "是否为空:" << bst.isEmpty() << std::endl;
    std::cout << "是否存在" << x << ": " << bst.contains(x) << std::endl;
    printMaxMin(bst);

    std::cout << "=====置空=====" << std::endl;

    bst.makeEmpty();

    std::cout << "是否为空:" << bst.isEmpty() << std::endl;
    std::cout << "是否存在" << x << ": " << bst.contains(x) << std::endl;

    
    bst2.remove(13);
    bst2.remove(13);
    bst2.remove(1);
    bst2.remove(5);
    bst2.printTree();
}