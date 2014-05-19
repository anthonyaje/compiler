make clean
make
./parser sample/func.c
dot -T png AST_Graph.gv -o AST_Graph.png
