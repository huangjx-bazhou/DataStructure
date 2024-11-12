#include <iostream>

template<typename T>
class AVL
{
public:
    AVL() : root(nullptr) {}

    AVL(const AVL& other) : root(this->clone(other.root)) {}

    ~AVL()
    {
        this->makeEmpty();
    }

    // 清空
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
        AVLNode* node = this->findMin(root);
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
        AVLNode* node = this->findMax(root);
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

    // 是否包含
    bool contains(const T& x) const
    {
        return this->contains(x, root);
    }

    // 打印
    void printTree() const
    {
        std::cout << "中序遍历:" << std::endl;
        this->printTree(root);
        std::cout << std::endl;
    }

private:
    struct AVLNode
    {
        T element;
        int height;
        AVLNode* left;
        AVLNode* right;

        AVLNode(const T& e, AVLNode* l, AVLNode* r, int h = 0) :
            element(e), height(h), left(l), right(r) {}
    };

    AVLNode* root;

    // 高度
    int height(AVLNode* node) const
    {
        return node ? node->height : -1;
    }

    // 清空
    void makeEmpty(AVLNode*& t)
    {
        if (nullptr == t)
        {
            return;
        }

        this->makeEmpty(t->left);

        this->makeEmpty(t->right);

        delete t;

        t = nullptr;
    }

    // 插入
    void insert(const T& x, AVLNode*& t)
    {
        if (nullptr == t)
        {
            t = new AVLNode(x, nullptr, nullptr);
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

        this->balance(t);
    }

    // 删除
    void remove(const T& x, AVLNode*& t)
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
                t->element = this->findMin(t->right)->element;
                this->remove(t->element, t->right);
            }
            else
            {
                AVLNode* old = t;
                t = (t->left != nullptr) ? t->left : t->right;
                delete old;
            }
        }

        this->balance(t);
    }

    // 最小值
    AVLNode* findMin(AVLNode* t) const
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

    // 最大值
    AVLNode* findMax(AVLNode* t) const
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

    // 是否包含
    bool contains(const T& x, AVLNode* t) const
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
    void printTree(AVLNode* t) const
    {
        if (nullptr == t)
        {
            return;
        }

        this->printTree(t->left);

        std::cout << t->element << " ";

        this->printTree(t->right);
    }

    AVLNode* clone(AVLNode* t) const
    {
        if (nullptr == t)
        {
            return nullptr;
        }
        else
        {
            return new AVLNode(t->element, this->clone(t->left), this->clone(t->right), t->height);
        }
    }

    void rotateWithLeftChild(AVLNode*& k2)
    {
        AVLNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max(this->height(k2->left), this->height(k2->right)) + 1;
        k1->height = std::max(this->height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(AVLNode*& k2)
    {
        AVLNode* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = std::max(this->height(k2->right), this->height(k2->left)) + 1;
        k1->height = std::max(this->height(k1->right), k2->height) + 1;
        k2 = k1;
    }

    void doubleWithLeftChild(AVLNode*& k3)
    {
        this->rotateWithRightChild(k3->left);
        this->rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(AVLNode*& k3)
    {
        this->rotateWithLeftChild(k3->right);
        this->rotateWithRightChild(k3);
    }

    // 平衡
    void balance(AVLNode*& t)
    {
        if (nullptr == t)
        {
            return;
        }

        //
        if (this->height(t->left) - this->height(t->right) > 1)
        {
            if (this->height(t->left->left) >= this->height(t->left->right))
            {
                this->rotateWithLeftChild(t);
            }
            else
            {
                this->doubleWithLeftChild(t);
            }
        }
        else if (this->height(t->right) - this->height(t->left) > 1)
        {
            if (this->height(t->right->right) >= this->height(t->right->left))
            {
                this->rotateWithRightChild(t);
            }
            else
            {
                this->doubleWithRightChild(t);
            }
        }

        t->height = std::max(this->height(t->left), this->height(t->right)) + 1;
    }
};

int main()
{
    AVL<int> avl;

    std::cout << "=====初始化完成=====" << std::endl;

    int x = 17;
    std::cout << "是否为空:" << avl.isEmpty() << std::endl;
    std::cout << "是否存在" << x << ": " << avl.contains(x) << std::endl;


    std::cout << "=====插入数据=====" << std::endl;

    avl.insert(6);
    avl.insert(7);
    avl.insert(1);
    avl.insert(17);
    avl.insert(13);
    avl.insert(12);
    avl.insert(3);
    avl.insert(5);

    AVL<int> avl2(avl);

    avl.printTree();
    std::cout << "是否为空:" << avl.isEmpty() << std::endl;
    std::cout << "是否存在" << x << ": " << avl.contains(x) << std::endl;


    std::cout << "=====删除=====" << std::endl;

    avl.remove(x);
    std::cout << "是否为空:" << avl.isEmpty() << std::endl;
    std::cout << "是否存在" << x << ": " << avl.contains(x) << std::endl;

    std::cout << "=====置空=====" << std::endl;

    avl.makeEmpty();

    std::cout << "是否为空:" << avl.isEmpty() << std::endl;
    std::cout << "是否存在" << x << ": " << avl.contains(x) << std::endl;


    avl2.remove(13);
    avl2.remove(13);
    avl2.remove(1);
    avl2.remove(5);
    avl2.printTree();

    return 0;
}