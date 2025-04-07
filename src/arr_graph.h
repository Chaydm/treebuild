/**
 * 邻接矩阵实现的图结构
 * 顶点数上限为MAX_SIZE
 */
#define MAX_GRAPH_SIZE 10

typedef struct _ArrGraph {
    int vertices[MAX_GRAPH_SIZE];    // 顶点数组
    int adjMat[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE]; // 邻接矩阵
    int size;                  // 当前顶点数
} ArrGraph;

/* 基本操作 */
ArrGraph *init_arr_graph();    // O(1)
void free_arr_graph(ArrGraph *graph); // O(1)

/* 顶点操作 */
void add_vertex(ArrGraph *graph, int val); // O(1)
void remove_vertex(ArrGraph *graph, int val); // O(n^2)

/* 边操作 */
void add_edges(ArrGraph *graph, int i, int j); // O(1)
void remove_edges(ArrGraph *graph, int i, int j); // O(1)
int has_edge(ArrGraph *graph, int i, int j); // O(1) 检查边是否存在

/* 顶点查询 */
int get_vertex_degree(ArrGraph *graph, int val); // O(n) 获取顶点度数

/**
 * @return 顶点存在，返回 index ,不存在返回 -1;
 */
int contains_vertex(ArrGraph *graph, int val); // O(n) 检查顶点是否存在

/* 图遍历算法 */
void dfs(ArrGraph *graph, int start); // O(n^2) 深度优先遍历
void bfs(ArrGraph *graph, int start); // O(n^2) 广度优先遍历

/* 最短路径算法 */
void dijkstra(ArrGraph *graph, int start); // O(n^2) Dijkstra算法
void floyd(ArrGraph *graph); // O(n^3) Floyd算法

/* 图属性 */
int is_empty_graph(ArrGraph *graph); // O(1) 图是否为空
