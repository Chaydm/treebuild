# TreeBuild 数据结构练习

C语言实现的数据结构的练习，包含多种常用数据结构实现。

## 包含数据结构
- 二叉搜索树
- AVL树
- 最大堆
- 哈希表
- 循环队列
- 链表

## 构建说明

```bash
meson setup builddir
meson compile -C builddir
```

## 运行测试

```bash
meson test -C builddir
```

## 使用示例

```c
#include "src/binary_tree.h"

int main() {
    TreeNode *root = NULL;
    root = insertNode(root, 10);
    insertNode(root, 20);
    // 更多操作...
    return 0;
}
```

## 许可证
MIT License
