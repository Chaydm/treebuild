#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "stack.h"
#include "queue.h"

#include "arr_graph.h"
#include "common.h"

ArrGraph *init_arr_graph()
{
    ArrGraph *g = (ArrGraph *)malloc(sizeof(ArrGraph));
    if (!g)
        return NULL;
    g->size = 0;
    return g;
}

void free_arr_graph(ArrGraph *graph)
{
    free(graph);
}

/**
 * 添加顶点
 */
void add_vertex(ArrGraph *graph, int val)
{
    if (!graph || graph->size == MAX_GRAPH_SIZE)
        return;

    // 添加顶点
    graph->vertices[graph->size++] = val;

    // 邻接矩阵添加行和列
    for (int i = 0; i < graph->size; i++)
    {
        graph->adjMat[i][graph->size - 1] = 0;
        graph->adjMat[graph->size - 1][i] = 0;
    }
}

/**
 * 移除顶点
 */
void remove_vertex(ArrGraph *graph, int val)
{
    if (!graph || !graph->size)
        return;

    int index = contains_vertex(graph, val);
    if (index == -1)
        return;

    // 移除顶点
    for (int i = index; i < graph->size - 1; i++)
        graph->vertices[i] = graph->vertices[i + 1];

    // 移除顶点的边
    for (int i = 0; i < graph->size; i++)
    {
        for (int j = index + 1; j < graph->size; j++)
        {
            graph->adjMat[i][j - 1] = graph->adjMat[i][j];
        }
    }
    for (int i = 0; i < graph->size; i++)
    {
        for (int j = index + 1; j < graph->size; j++)
        {
            graph->adjMat[j - 1][i] = graph->adjMat[j][i];
        }
    }
    graph->size--;
}

void add_edges(ArrGraph *graph, int i, int j)
{
    if (!graph || i < 0 || j < 0 || i > graph->size || j > graph->size || i == j)
        return;
    graph->adjMat[i][j] = 1;
    graph->adjMat[j][i] = 1;
}

void remove_edges(ArrGraph *graph, int i, int j)
{
    if (!graph || i < 0 || j < 0 || i > graph->size || j > graph->size || i == j)
        return;
    graph->adjMat[i][j] = 0;
    graph->adjMat[j][i] = 0;
}

int has_edge(ArrGraph *graph, int i, int j)
{
    if (!graph || i < 0 || j < 0 || i > graph->size || j > graph->size || i == j)
        return -1;
    if (!graph->adjMat[i][j])
        return 0;
    return 1;
}

int get_vertex_degree(ArrGraph *graph, int val)
{
    if (!graph)
        return -1;

    int index = contains_vertex(graph, val);
    if (index == -1)
        return -1;

    return arr_sum(graph->adjMat[index], graph->size);
}

int contains_vertex(ArrGraph *graph, int val)
{
    if (!graph)
        return -1;
    for (int i = 0; i < graph->size; i++)
    {
        if (graph->vertices[i] == val)
            return i;
    }
    return -1;
}

/**
 * 深度优先遍历 (使用栈实现)
 */
void dfs(ArrGraph *graph, int start)
{
    if (!graph || start < 0 || start >= graph->size)
        return;

    int *visited = (int *)calloc(graph->size, sizeof(int));
    Stack *stack = init_stack();
    
    push(stack, start);
    visited[start] = 1;

    while (!is_empty_stack(stack)) {
        int current = pop(stack);
        printf("%d ->", graph->vertices[current]);

        // 将邻接点按逆序压入栈中
        for (int i = graph->size - 1; i >= 0; i--) {
            if (graph->adjMat[current][i] && !visited[i]) {
                push(stack, i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");

    free(visited);
    free_stack(stack);
}

/**
 * 广度优先遍历 (使用队列实现)
 */
void bfs(ArrGraph *graph, int start)
{
    if (!graph || start < 0 || start >= graph->size)
        return;

    int *visited = (int *)calloc(graph->size, sizeof(int));
    Queue *queue = init_queue();
    
    enqueue(queue, start);
    visited[start] = 1;

    while (!is_empty_queue(queue)) {
        int current = dequeue(queue);
        printf("%d ->", graph->vertices[current]);

        for (int i = 0; i < graph->size; i++) {
            if (graph->adjMat[current][i] && !visited[i]) {
                enqueue(queue, i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");

    free(visited);
    free_queue(queue);
}

/**
 * Dijkstra最短路径算法
 * @param graph 图指针
 * @param start 起始顶点索引
 */
void dijkstra(ArrGraph *graph, int start) 
{
    if (!graph || start < 0 || start >= graph->size) 
        return;

    int dist[MAX_GRAPH_SIZE];
    int visited[MAX_GRAPH_SIZE] = {0};

    // 初始化距离数组
    for (int i = 0; i < graph->size; i++) {
        dist[i] = graph->adjMat[start][i] ? graph->adjMat[start][i] : INT_MAX;
    }
    dist[start] = 0;
    visited[start] = 1;

    for (int count = 0; count < graph->size - 1; count++) {
        // 找到未访问的最小距离顶点
        int min_dist = INT_MAX;
        int u = -1;
        for (int v = 0; v < graph->size; v++) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }
        if (u == -1) break;

        visited[u] = 1;

        // 更新相邻顶点距离
        for (int v = 0; v < graph->size; v++) {
            if (!visited[v] && graph->adjMat[u][v] && 
                dist[u] != INT_MAX && 
                dist[u] + graph->adjMat[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->adjMat[u][v];
            }
        }
    }

    // 打印最短路径
    printf("顶点\t最短距离\n");
    for (int i = 0; i < graph->size; i++) {
        printf("%d\t%d\n", graph->vertices[i], dist[i]);
    }
}

/**
 * Floyd最短路径算法
 * @param graph 图指针
 */
void floyd(ArrGraph *graph) 
{
    if (!graph) return;

    int dist[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];

    // 初始化距离矩阵
    for (int i = 0; i < graph->size; i++) {
        for (int j = 0; j < graph->size; j++) {
            dist[i][j] = graph->adjMat[i][j] ? graph->adjMat[i][j] : INT_MAX;
            if (i == j) dist[i][j] = 0;
        }
    }

    // Floyd算法核心
    for (int k = 0; k < graph->size; k++) {
        for (int i = 0; i < graph->size; i++) {
            for (int j = 0; j < graph->size; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // 打印结果
    printf("Floyd最短路径矩阵:\n");
    for (int i = 0; i < graph->size; i++) {
        for (int j = 0; j < graph->size; j++) {
            if (dist[i][j] == INT_MAX)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }
}

int is_empty_graph(ArrGraph *graph)
{
    if (!graph || !graph->size)
        return 0;
    return 1;
}
