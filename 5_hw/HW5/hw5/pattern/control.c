int a = 3;
int main() {
    int b;
    float c, d;
    b = 0;
    if (a > b) {
        write("correct\n");
    } else {
        write("wrong\n");
    }
    if (a < b) {
        write("wrong\n");
    } else {
        write("correct\n");
    }
    if (a == b) {
        write("wrong\n");
    } else {
        write("correct\n");
    }
    if (a != b) {
        write("correct\n");
    } else {
        write("wrong\n");
    }

    c = 1.0;
    d = 0.0;
    if (c > d) {
        write("correct\n");
    } else {
        write("wrong\n");
    }
    if (c < d) {
        write("wrong\n");
    } else {
        write("correct\n");
    }
    if (c != d) {
        write("correct\n");
    } else {
        write("wrong\n");
    }

    if (a && b) {
        write("wrong\n");
    }

    if (a || b) {
        write("correct\n");
    }

    while (a<10) {
        write("correct: ");
        write(a);
        write("\n");
        a = a+1;
    }
    if (a == 10) {
        write("correct\n");
    }

    return 0;
}
