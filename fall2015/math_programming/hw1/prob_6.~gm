set k /0 * 14/;

parameters eta /.05/,h /1/,bmax /.5/,fmax /4/,LL /300/,SS /.8/, vto /40/;

positive variables p(k),v(k),b(k),f(k);
v.l('0')=0;
p.l('0')=0;
f.l('0')=0;
b.l('0')=0;

free variable obj;

* Define equations
* ----------------
* - objdef:     Define objective

equations pupdate,vupdate,bbound,fbound,fdelbound,runwayend,objdef,vbound,objdef;

vupdate(k).. v(k) =e= (1-eta)*v(k-1)+h*(f(k-1)+b(k-1));
pupdate(k).. p(k) =e= p(k-1)+h*v(k-1);
bbound(k).. b(k) =l= min(bmax,f(k));
fbound(k).. f(k) =l= fmax;
fdelbound(k).. abs(f(k)-f(k-1)) =l= SS;
runwayend.. p('13') =l= LL;
vbound.. v('13') =g= vto;
objdef.. obj =e= v('13');
model takeoff /all/;

solve takeoff using dnlp minimizing obj;
