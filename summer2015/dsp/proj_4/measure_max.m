function measure_max(w1,w2)
f=fdesign.lowpass('N,Fp,Fst',30,.15*2,.2*2);
Hd2 = design(f,'equiripple','Wpass',w1,'Wstop',w2,'SystemObject',true);

hfvt = fvtool(Hd2,'Analysis','impulse','Color','white');


hfvt = fvtool(Hd2,'MagnitudeDisplay','Magnitude','Color','white');


hfvt = fvtool(Hd2,'MagnitudeDisplay','Magnitude (dB)','Color','white');


hfvt = fvtool(Hd2,'Analysis','grpdelay','Color','white');


hfvt = fvtool(Hd2,'Analysis','phase','Color','white');


hfvt = fvtool(Hd2,'Analysis','polezero','Color','white');



measure(Hd2)