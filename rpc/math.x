struct vars {
    int a;
    int b;
};

program MATHPROG {
    version MATHVERS {
        int ADD(vars) = 1;
        int SUB(vars) = 2;
    } = 2;
} = 1;
