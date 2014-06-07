int global;

int main(){
  int a,b;
  int c[6][7][10];

  a = 5;
  b = 11;
  global = b;
  c[3][2][3] = global;
  a = c[3][2][3];
  /*write("finish\n");
  */
  return a;
}
