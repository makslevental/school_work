set i /1 * 10/;
set j(i) /1 * 10/;

parameter r(i);
r(i) = ord(i);

positive variables x(i), y(i);
positive variables cx,cy;
free variable obj;


equations southbound,westbound,intersectbound,eastbound,northbound,objdef;
southbound(i).. x(i) =g= r(i);
westbound(i).. y(i) =g= r(i);
intersectbound(i,j)$(ord(i) ne ord(j)).. sqr(x(i)-x(j)) + sqr(y(i)-y(j)) =g= r(i)+r(j);
eastbound(i).. x(i) + r(i) =l= cx;
northbound(i).. y(i) + r(i) =l= cy;
objdef.. obj =e= cx*cy;

model circles /all/


solve circles using nlp minimizing obj;