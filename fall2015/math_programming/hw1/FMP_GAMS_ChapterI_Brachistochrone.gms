*
* CLASS:
*        ESI 6420: Fundamentals of Mathematical Programming
*
* PROBLEM:
*        Brachistochrone Problem (Chapter 1)
*
* GAMS MODEL:
*        Jean-Philippe P. Richard
*        Professor
*        Department of Industrial and Systems Engineering
*        University of Florida
*        E-mail: richard@ise.ufl.edu



* Declare sets
* -------------
* - N: set of discretization points

set N /0*30/;

* Declare constants
* -----------------
* - g: gravity
* - epsi: epsilon

parameter g /9.81/;
parameter epsi /0.0001/;

* Declare grid parameters
* -----------------------
* - x(N): x-locations of the grid

parameter x(N);
x(N)=(ord(N)-1)/(card(N)-1);
*x(N)=sqr(ord(N)-1)/sqr(card(N)-1);
*x(N)=sqr(sqr(ord(N)-1))/sqr(sqr(card(N)-1));


* Define the variables of the model
* ---------------------------------
* - y(N): y-locations of the ramp for each point of the grid
* - v(N): speed at the N-th point of the ramp
* - t(N): time used to travel the N-th interval of the ramp
* - totattime: total time to go traverse the ramp

positive variable y(N);
positive variable v(N);
free variable t(N);
free variable totaltime;

* Fix the heights of the ramp at origin and end
* ----------------------------------------------

y.fx('0')=0;
y.fx(N)$(ord(N) eq card(N))=1;

* Define constraints of the model:
* --------------------------------
* - slope(N) : computation of the speed at point N
* - delta(N) : computation of the time to travel interval N
* - objdef :   definition of totattime

equations slope(N),delta(N),objdef;

slope(N)$(ord(N) ge 2).. v(N) =e= (y(N)-y(N-1))/(x(N)-x(N-1));
delta(N)$(ord(N) ge 2).. t(N) =g= (x(N)-x(N-1))*sqrt((1+v(N)*v(N))/(2*g*y(N-1)+epsi));
objdef.. totaltime =e= sum(N$(ord(N) ge 2), t(N));


* Create model
* ------------
* - set solver to be conopt

model brachistochrone /all/;
brachistochrone.optcr=0.0;
option nlp=conopt;
solve brachistochrone using nlp minimizing totaltime;

* Produce report
* ---------------
* - report (x,y) coordinates of the ramp

file resfile /Brachsol.sol/;
put resfile;

put 'x=['
loop(N,
put ' ',x(N):7:5,
)
put ']' /;


put 'y=['
loop(N,
put ' ',y.l(N):7:5,
)
put ']' /;

