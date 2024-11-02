#include "alg_tree.h"

// 树测试
void test_tree_insrt() {
    my_tree::AVLTree<int> avlTree;

    // 插入节点
    avlTree.root = avlTree.insert_node(avlTree.root, 5);
    avlTree.root = avlTree.insert_node(avlTree.root, 3);
    avlTree.root = avlTree.insert_node(avlTree.root, 7);
    avlTree.root = avlTree.insert_node(avlTree.root, 2);
    avlTree.root = avlTree.insert_node(avlTree.root, 4);
    avlTree.root = avlTree.insert_node(avlTree.root, 6);
    avlTree.root = avlTree.insert_node(avlTree.root, 8);

    // 中序遍历
    avlTree.inorder_traversal(avlTree.root);
    std::cout << std::endl;
}

void test_tree_delete() {
    my_tree::AVLTree<std::string> avlTree;

    // 插入节点
    avlTree.root = avlTree.insert_node(avlTree.root, "banana");
    avlTree.root = avlTree.insert_node(avlTree.root, "apple");
    avlTree.root = avlTree.insert_node(avlTree.root, "cherry");
    avlTree.root = avlTree.insert_node(avlTree.root, "grape");
    avlTree.root = avlTree.insert_node(avlTree.root, "fig");

    // 中序遍历
    avlTree.inorder_traversal(avlTree.root);
    std::cout << std::endl;

    // 删除节点
    avlTree.root = avlTree.delete_node(avlTree.root, "apple");
    // 中序遍历
    avlTree.inorder_traversal(avlTree.root);
    std::cout << std::endl;

    // 删除节点
    // avlTree.root = avlTree.delete_node(avlTree.root, "apple");
    avlTree.root = avlTree.delete_node(avlTree.root, "fig");

    // 中序遍历
    avlTree.inorder_traversal(avlTree.root);
    std::cout << std::endl;
}

// 测试函数入口
int main(int argc, char *argv[]) {
    test_tree_insrt();
    test_tree_delete();
    return 0;
}