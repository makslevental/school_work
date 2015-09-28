set i /1 * 10/;
set t /1 * 4/;
parameter a(i)  /1 40,
                 2 39,
                 3 36,
                 4 32,
                 5 25,
                 6 23,
                 7 21,
                 8 14,
                 9 13,
                 10 6/;

parameter b(i)  /1 6,
                 2 3,
                 3 3,
                 4 6,
                 5 3,
                 6 4,
                 7 9,
                 8 8,
                 9 2,
                 10 6/;

parameter f(i);

positive variables p(i),c,r(i);
free variable obj, d(i);

* Define equations
* ----------------
* - objdef:     Define objective

equations demand,capacity,gross,objdef;
demand(i).. d(i) =e= a(i)-b(i)*p(i);
capacity(i).. c =g= d(i);
**d(i);
gross(i).. r(i) =e= p(i)*d(i);
objdef.. obj =e= sum(i,r(i)-f(i)*c);

* Create Model
* ------------

model production /all/;


loop(t,

f(i)=5*ord(t)/card(i);

solve production using nlp maximizing obj;

);