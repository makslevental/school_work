*
* CLASS:
*        ESI 6420: Fundamentals of Mathematical Programming
*
* PROBLEM:
*        Springs Problem (Chapter 1)
*
* GAMS MODEL:
*        Jean-Philippe P. Richard
*        Professor
*        Department of Industrial and Systems Engineering
*        University of Florida
*        E-mail: richard@ise.ufl.edu


* Declare sets
* -------------
* - I: set of springs

set I     /1*5/;


* Define parameters of the model:
* --------------------------------
* - xbar1  : x position of the first node
* - ybar1  : y position of the first node
* - xbarn  : x position of the last node
* - ybarn  : y position of the last node
* - w(I)   : weight associated with node i
* - l(I)   : natural length of spring i (no meaning is associated to l(N))
* - k(I)   : stiffness of spring i (no meaning is associated to k(N))

parameter xbar1  /0/,
          ybar1  /0/,
          xbarn /10/,
          ybarn  /0/;

parameter w(I);
w(I)=1;

parameter l(I);
l(I)=1.5;

parameter k(I);
k(I)=2;


* Define variables of the model:
* -------------------------------
* - tension(I)  : tension in the ith spring (no meaning associated to N)
* - x(I)        : x-position of node i
* - y(I)        : y-position of node i
* - totalenergy : total energy of the system

positive variable tension(I);
free variable x(I), y(I), totalenergy;

* Define IVRs of the model:
* -------------------------------

x.fx('1')=xbar1;
y.fx('1')=ybar1;
x.fx(I)$(ord(I) eq card(I))=xbarn;
y.fx(I)$(ord(I) eq card(I))=ybarn;
tension.fx(I)$(ord(I) eq card(I))=0;


* Define equations
* ----------------
* - tensiondef(I) : Compute tension in all of the springs
* - objdef        : Compute total energy in the system

equations
tensiondef(I), objdef;

tensiondef(I)$(ord(I) le card(I)-1)..
tension(I) =g= k(I)*(sqrt(sqr(x(I+1)-x(I))+sqr(y(I+1)-y(I)))-l(I));

objdef..
totalenergy =e= sum(I,w(I)*y(I)) + sum(I$(ord(I) le card(I) -1),1/(2*k(I))*sqr(tension(I)));

* Create Model
* ------------

model springs /all/;
solve springs using nlp minimizing totalenergy;

* Perform sensitivity on weight 4 and produce report
* --------------------------------------------------

file resfile /springs.res/;
put resfile;

set E /1*3/;

loop(E,
w('4')=ord(E);
solve springs using nlp minimizing totalenergy;
put /'Configuration: 'ord(E):1:0 /;
loop(I, put 'x(' I.tl:1:0 ')=' x.l(I):7:4 ',   ' ;) put /;
loop(I, put 'y(' I.tl:1:0 ')=' y.l(I):7:4 ',   ' ;) put /;
)
