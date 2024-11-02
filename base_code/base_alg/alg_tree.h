#ifndef _MY_TREE_H__
#define _MY_TREE_H__

#include <iostream>
#include <mutex>
#include <thread>
#include <utility>

/**
 * 1、平衡二叉树
 */
namespace my_tree {
// 平衡二叉树节点类模板
template <typename T> 
class AVLNode {
public:
    T data;            // 节点值
    int height;        // 节点高度
    AVLNode<T> *left;  // 左子节点
    AVLNode<T> *right; // 右子节点

    // 构造函数
    AVLNode(T value) {
        data = value;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

// 平衡二叉树操作类模板
template <typename T> 
class AVLTree {
public:
    AVLNode<T> *root;

    // 构造函数
    AVLTree() { 
        root = nullptr; 
    }

    // 计算节点高度
    int get_height(AVLNode<T> *node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // 计算节点平衡因子
    int get_balance_factor(AVLNode<T> *node) {
        if (node == nullptr)
            return 0;
        return get_height(node->left) - get_height(node->right);
    }

    // 更新节点高度
    void update_height(AVLNode<T> *node) {
        if (node == nullptr)
            return;
        int leftHeight = get_height(node->left);
        int rightHeight = get_height(node->right);
        node->height = std::max(leftHeight, rightHeight) + 1;
    }

    // 右旋操作
    AVLNode<T> *right_rotate(AVLNode<T> *node) {
        AVLNode<T> *leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        update_height(node);
        update_height(leftChild);
        return leftChild;
    }

    // 左旋操作
    AVLNode<T> *left_rotate(AVLNode<T> *node) {
        AVLNode<T> *rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        update_height(node);
        update_height(rightChild);
        return rightChild;
    }

    // 插入节点
    AVLNode<T> *insert_node(AVLNode<T> *node, T value) {
        if (node == nullptr)
            return new AVLNode<T>(value);

        if (value < node->data) {
            node->left = insert_node(node->left, value);
            update_height(node);

            node = left_balance(node);
        } else if (value > node->data) {
            node->right = insert_node(node->right, value);
            update_height(node);

            node = right_balance(node);
        }

        return node;
    }

    // 中序遍历平衡二叉树
    void inorder_traversal(AVLNode<T> *node) {
        if (node == nullptr)
            return;

        inorder_traversal(node->left);
        std::cout << node->data << " ";
        inorder_traversal(node->right);
    }

    // 寻找最小节点
    AVLNode<T> *find_min_node(AVLNode<T> *node) {
        if (node == nullptr)
            return nullptr;
        if (node->left == nullptr)
            return node;
        return find_min_node(node->left);
    }

    // 删除节点
    AVLNode<T> *delete_node(AVLNode<T> *node, T value) {
        if (node == nullptr)
            return nullptr;

        if (value < node->data) {
            node->left = delete_node(node->left, value);
            update_height(node);

            node = right_balance(node);
        } else if (value > node->data) {
            node->right = delete_node(node->right, value);
            update_height(node);

            node = left_balance(node);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                // 叶节点，直接删除
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {
                // 只有右子节点，用右子节点替换被删除节点
                AVLNode<T> *rightChild = node->right;
                delete node;
                return rightChild;
            } else if (node->right == nullptr) {
                // 只有左子节点，用左子节点替换被删除节点
                AVLNode<T> *leftChild = node->left;
                delete node;
                return leftChild;
            } else {
                // 有两个子节点，找到右子树中最小节点，用最小节点的值替换被删除节点的值，并删除最小节点
                AVLNode<T> *minNode = find_min_node(node->right);
                node->data = minNode->data;
                node->right = delete_node(node->right, minNode->data);
                update_height(node);

                node = left_balance(node);
                return node;
            }
        }

        return node;
    }

private:
    // 右平衡
    AVLNode<T> *right_balance(AVLNode<T> *node) {
        int balanceFactor = get_balance_factor(node);
        if (balanceFactor == -2) {
            if (get_balance_factor(node->right) == -1) {
                // RR情况，进行左旋操作
                node = left_rotate(node);
            } else if (get_balance_factor(node->right) == 1) {
                // RL情况，先进行右旋操作，再进行左旋操作
                node->right = right_rotate(node->right);
                node = left_rotate(node);
            }
        }
        return node;
    }

    // 左平衡
    AVLNode<T> *left_balance(AVLNode<T> *node) {
        int balanceFactor = get_balance_factor(node);
        if (balanceFactor == 2) {
            if (get_balance_factor(node->left) == 1) {
                // LL情况，进行右旋操作
                node = right_rotate(node);
            } else if (get_balance_factor(node->left) == -1) {
                // LR情况，先进行左旋操作，再进行右旋操作
                node->left = left_rotate(node->left);
                node = right_rotate(node);
            }
        }
        return node;
    }
};

} // namespace my_tree

#endif