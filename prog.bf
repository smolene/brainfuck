r>+>+<<[>[->>+>+<<<]>>[-<+>]<[-<+>]>>[-<<+>>]<<<<-]>p
0112210011122332110001122

0: loop
1: a     0
2: b     a+b
3: a1    0
4: a2    a2

a = 1;
b = 1;

while (r > 0) {
    --r;

    tmp = a;
    a += b;
    b = tmp;
}

r>r<[->+<]p>p
3
4