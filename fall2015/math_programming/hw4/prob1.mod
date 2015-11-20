set coordinates := 1 .. 20;

set data_points := 1 .. 100;
param x{data_points,coordinates};
param y{data_points};
param omit_points;
param nz_a;

var alpha {coordinates};
var b {data_points} binary integer;
var p {coordinates} binary integer;
var beta;

minimize obj: sum{c in coordinates} alpha[c]*alpha[c];

s.t. margin{d in data_points}: b[d]*(y[d]*( ( sum{c in coordinates} p[c]*alpha[c]*x[d,c] ) - beta) -1 ) >= 0;
s.t. constraint_mask:  sum{d in data_points} b[d] >= 100 - omit_points;
s.t. non_zero_a: sum{c in coordinates} p[c] <= nz_a;
