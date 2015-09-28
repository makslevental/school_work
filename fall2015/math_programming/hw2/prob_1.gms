* problem 1

set E /1 * 11/;
set F(E) /1 * 10/;
parameter x(E) /1 4,
                      2 8,
                    3 12,
                    4 16,
                    5 20,
                    6 24,
                    7 28,
                    8 32,
                    9 36,
                   10 40,
                   11 44/;

parameter y(E) /1 5,
                      2 4,
                    3 6,
                    4 5,
                    5 7,
                    6 4,
                    7 6,
                    8 9,
                    9 6,
                   10 5,
                   11 3/ ;


parameter x0 /0/,
           y0 /4/,
           xn1 /48/,
           yn1 /8/
           c /1/;


free variable g(E);
free variable obj;


equations ydef,objdef;
ydef(E).. sqr(g(E)-y(E)) =l= sqr(c);
objdef.. obj =e= sqr(x0 - x('1')) + sqr(y0 - g('1')) + sqr(x('11') - xn1) + sqr(g('11')-yn1) +  sum(F,sqr(x(F)-x(F+1)) + sqr(g(F)-g(F+1)) );

model skiing /all/


solve skiing using nlp minimizing obj;
