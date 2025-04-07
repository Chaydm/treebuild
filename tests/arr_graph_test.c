#include <stdio.h>
#include <assert.h>

#include "src/arr_graph.h"

void test_arr_graph()
{
    ArrGraph *g = init_arr_graph();
    int arr[7] = {1, 2, 11, 3, 9, 12, 21};
    add_vertex(g, 1);
    add_vertex(g, 2);
    add_vertex(g, 11);
    add_vertex(g, 3);
    add_vertex(g, 9);
    add_vertex(g, 12);
    add_vertex(g, 21);
    assert(g->size == 7);
    for (int i = 0; i < 7; i++)
    {
        assert(g->vertices[i] == arr[i]);
    }

    add_edges(g, 0, 1);
    add_edges(g, 0, 2);
    add_edges(g, 0, 4);
    add_edges(g, 0, 5);
    add_edges(g, 1, 6);
    add_edges(g, 1, 2);
    add_edges(g, 2, 3);
    add_edges(g, 5, 6);

    dfs(g, 0);
    bfs(g, 0);

    remove_vertex(g, 1);
    assert(g->size == 6);
    for (int i = 0; i < g->size; i++)
    {
        assert(g->vertices[i] == arr[i + 1]);
    }

    free_arr_graph(g);
}

int main(void)
{
    test_arr_graph();
    printf("all test passed");
}
