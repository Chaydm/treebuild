project('treebuild', 'c', version: '0.1', default_options: ['warning_level=3'])
add_project_arguments('--save-temps', language: 'c')

if get_option('buildtype') == 'debug'
  add_project_arguments('-g', '-O0', language: 'c')
endif

sources = [
  'src/forward_link.c',
  'src/binary_tree.c',
  'src/circular_queue.c',
  'src/hash.c',
  'src/hash_link.c',
  'src/arr_binary_tree.c',
  'src/max_heap.c',
  'src/avl_binary_tree.c',
  'src/arr_graph.c',
  'src/common.c',
  'src/queue.c',
  'src/stack.c'
]

math_lib = meson.get_compiler('c').find_library('m', required: true)

dtlib = static_library('datastruct', sources: sources, install: false)

dtlib_dep = declare_dependency(link_with: dtlib)

exe = executable(
  'apdtest',
  'tests/append_test.c',
  dependencies: [dtlib_dep, math_lib],
  install: false,
)
test_binary_tree = executable(
  'binary_tree_test',
  'tests/binary_tree_test.c',
  dependencies: [dtlib_dep, math_lib],
)

test_circular_queue = executable('test_circular_queue', 'tests/circular_test.c', dependencies: [dtlib_dep])

test_hash_linked = executable('test_hash_linked', 'tests/hash_link_test.c', dependencies: [dtlib_dep])

test_abt_tree = executable('test_abt_tree', 'tests/abt_tree_test.c', dependencies: [dtlib_dep])

max_heap_test = executable('max_heap_test', 'tests/max_heap_test.c', dependencies: [dtlib_dep])

arr_graph_test = executable('arr_graph_test', 'tests/arr_graph_test.c', dependencies: [dtlib_dep])


test('apdtest', exe)
test('binary_tree_test', test_binary_tree)
test('test_circular_queue', test_circular_queue)
test('test_hash_linked', test_hash_linked)
test('test_abt_tree', test_abt_tree)
test('max_heap_test', max_heap_test)
test('arr_graph_test', arr_graph_test)
