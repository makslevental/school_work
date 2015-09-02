                            *
* CLASS:
*        ESI 6420: Fundamentals of Mathematical Programming
*
* PROBLEM:
*        Newsvendor Problem (Chapter 1)
*
* GAMS MODEL:
*        Jean-Philippe P. Richard
*        Professor
*        Department of Industrial and Systems Engineering
*        University of Florida
*        E-mail: richard@ise.ufl.edu


* Declare the parameters of the model
* -----------------------------------

scalar v /0.25/,
       c /1/,
       p /1.1/,
       mu /100/,
       sigma /20/;


* Declare the set of scenario & their parameters
* ----------------------------------------------

set E /1 * 11/;

parameters x(E) /1 4,
                      2 8,
                    3 12,
                    4 16,
                    5 20,
                    6 24,
                    7 28,
                    8 32,
                    9 36,
                   10 40,
                   11 44/

parameters y(E) /1 5,
                      2 4,
                    3 6,
                    4 5,
                    5 7,
                    6 4,
                    7 6,
                    8 9,
                    9 6,
                   10 5,
                   11 3/


parameters x0 /0/,
           y0 /4/,
           xn1 /48/,
           yn1 /8/
           c /1/;

* Define variables of the problem:
* --------------------------------
* - Q         : order quantity
* - expprofit : expected profit


free variable g(E);
positive variable f;

* Define equations
* ----------------
* - objdef:     Define objective

equations ydef,objdef;
ydef.. sqrt(power((g(E)-y(E),2)) =l= c;
y0def.. sqrt( power((x0 - x(1)),2) + power((y0 - g(1)),2) )
yn1def.. sqrt( power((x(11) - xn1),2) + power((g(11)-yn1),2) )
objdef.. f =e= sum(E,;

* Create Model
* ------------

model newsvendor /all/

* Solve model for all scenarios
* -----------------------------

file resfile /newsvendor.res/;
put resfile;

option nlp=minos;

loop(E,
p=pval(E);
solve newsvendor using nlp maximizing expprofit;

put /'p = 'p', Q = 'Q.l /;
)
