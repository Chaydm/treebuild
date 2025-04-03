#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "src/binary_tree.h"

// 测试节点创建
void test_create_node() {
    binary_tree *node = create_treenode(42);
    assert(node != NULL);
    assert(node->data == 42);
    assert(node->lchild == NULL);
    assert(node->rchild == NULL);
    free(node);
    printf("test_create_node passed\n");
}

// 测试节点插入
void test_insert_node() {
    binary_tree *root = NULL;
    insert_node(&root, 50);
    insert_node(&root, 30);
    insert_node(&root, 70);
    
    assert(root != NULL);
    assert(root->data == 50);
    assert(root->lchild != NULL && root->lchild->data == 30);
    assert(root->rchild != NULL && root->rchild->data == 70);
    
    free_tree(root);
    printf("test_insert_node passed\n");
}

// 测试节点删除
void test_remove_node() {
    binary_tree *root = NULL;
    insert_node(&root, 50);
    insert_node(&root, 30);
    insert_node(&root, 70);
    
    // 删除叶子节点
    remove_node(&root, 30);
    assert(root->lchild == NULL);
    
    // 删除单子树节点
    insert_node(&root, 60);
    remove_node(&root, 70);
    assert(root->rchild != NULL && root->rchild->data == 60);
    
    // 删除双子树节点
    insert_node(&root, 40);
    insert_node(&root, 20);
    remove_node(&root, 50);
    assert(root->data == 60); // 应该被替换为右子树最小值
    
    free_tree(root);
    printf("test_remove_node passed\n");
}

// 测试查找功能
void test_find_node() {
    binary_tree *root = NULL;
    insert_node(&root, 50);
    insert_node(&root, 30);
    insert_node(&root, 70);
    
    assert(find_node(root, 50) == root);
    assert(find_node(root, 30) == root->lchild);
    assert(find_node(root, 70) == root->rchild);
    assert(find_node(root, 100) == NULL);
    
    free_tree(root);
    printf("test_find_node passed\n");
}

// 测试树的高度和大小
void test_tree_properties() {
    binary_tree *root = NULL;
    insert_node(&root, 50);
    insert_node(&root, 30);
    insert_node(&root, 70);
    insert_node(&root, 20);
    insert_node(&root, 40);
    
    assert(get_height(root) == 3);
    assert(get_size(root) == 5);
    
    free_tree(root);
    printf("test_tree_properties passed\n");
}

// 测试遍历函数
static int visit_count = 0;
static void count_visit() {
    visit_count++;
}

void test_traversals() {
    binary_tree *root = NULL;
    insert_node(&root, 50);
    insert_node(&root, 30);
    insert_node(&root, 70);
    
    // 前序遍历
    visit_count = 0;
    pre_order(root, count_visit);
    assert(visit_count == 3);
    
    // 中序遍历
    visit_count = 0;
    in_order(root, count_visit);
    assert(visit_count == 3);
    
    // 后序遍历
    visit_count = 0;
    post_order(root, count_visit);
    assert(visit_count == 3);
    
    // 层次遍历
    visit_count = 0;
    level_order(root, count_visit);
    assert(visit_count == 3);
    
    free_tree(root);
    printf("test_traversals passed\n");
}

int main() {
    test_create_node();
    test_insert_node();
    test_remove_node();
    test_find_node();
    test_tree_properties();
    test_traversals();
    
    printf("All tests passed!\n");
    return 0;
}
