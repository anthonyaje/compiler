make clean
make
<<<<<<< HEAD
./parser sample/func.c
dot -T png AST_Graph.gv -o AST_Graph.png
=======
./parser sample/decl.c
dot -T png AST_Graph.gv -o AST_Graph.png
xdg-open AST_Graph.png
>>>>>>> 3e0beea08065dc9a6b8ed4dc01745130c470fb8c
