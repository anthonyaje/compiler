make clean
make
./parser sample/control.c
dot -T png AST_Graph.gv -o AST_Graph.png
xdg-open AST_Graph.png
