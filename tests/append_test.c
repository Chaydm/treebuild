#include <stdio.h>
#include "src/forward_link.h"
#include "src/binary_tree.h" 

#define PROJECT_NAME "treebuild"

void visit(binary_tree* node){
    if(node)
        printf("node data is %d\n",node->data);
}


void test_linked_list() {
    forward_link *head = NULL;
    
    printf("\nTesting linked list:\n");
    
    // 测试插入
    insert_at_head(&head, 10);
    insert_at_head(&head, 20);
    append(&head, 30);
    
    printf("List after inserts: ");
    print_list(head);
    
    // 测试长度
    printf("List length: %d\n", get_length(head));
    
    // 测试删除
    delete_node(&head, 20);
    printf("List after deleting 20: ");
    print_list(head);
    
    // 释放链表
    free_list(head);
}


void test_binary_tree(){
    // 创建节点
    binary_tree * root= create_treenode(10);
    
    // 插入节点
    insert_node(&root,2);
    int s = get_size(root);
    int h = get_height(root);
    printf("current size is %d,height is %d\n",s,h);
    insert_node(&root,18);
    printf("current size is %d,height is %d\n",get_size(root),get_height(root));
    insert_node(&root,4);
    printf("current size is %d,height is %d\n",get_size(root),get_height(root));
    insert_node(&root,23);
    printf("current size is %d,height is %d\n",get_size(root),get_height(root));
    insert_node(&root,13);
    printf("current size is %d,height is %d\n",get_size(root),get_height(root));
    insert_node(&root,13);
    printf("current size is %d,height is %d\n",get_size(root),get_height(root));

    // 层次遍历
    level_order(root,visit);
    //先序遍历
    pre_order(root,visit);
    //中序遍历
    in_order(root,visit);
    //后序遍历
    post_order(root,visit);

    // 删除节点
    remove_node(&root,13);
    printf("current size is %d,height is %d\n",get_size(root),get_height(root));
    remove_node(&root,13);
    printf("current size is %d,height is %d\n",get_size(root),get_height(root));
    remove_node(&root,130);
    remove_node(&root,4);

    // 层次遍历
    level_order(root,visit);
    remove_node(&root,2);
    printf("current size is %d,height is %d\n",get_size(root),get_height(root));
    remove_node(&root,18);
    remove_node(&root,23);
    
    // 释放列表
    free_tree(root);
}

int main(int argc, char **argv) {
    if(argc != 1) {
        printf("%s takes no arguments.\n", argv[0]);
        return 1;
    }
    printf("This is project %s.\n", PROJECT_NAME);
    // test_linked_list();
    test_binary_tree();
    printf("All tests passed!\n");
    return 0;
}
