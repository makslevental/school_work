function prob3()

flights = [0       165     80      125     120     155     195     100     185;
        180     0       110     160     135     185     90      180     90;
        95      155     0       195     175     60      95      90      140;
        55      110     50      0       140     130     55      95      175;
        60      185     90      180     0       85      160     60      145;
        55      110     195     50      155     0       145     125     195;
        155     140     85      130     70      140     0       80      125;
        145     100     70      110     190     60      125     0       180;
        65      180     55      130     125     150     50      140     0];
xlocs = [14,15,20,20,39,43,51,52,93];
ylocs = [73,40,65,61,18,9,94,30,35];
locs = [xlocs;ylocs];
combos = nchoosek(1:9,3);


grandtotal = {};
for i=1:size(combos,1)
    total = 0;
    hublocs = locs(:,combos(i,:));
    nearesthubind = dsearchn(hublocs',locs');
    for j=1:9
        for k=1:9
            total = total + flights(j,k)*metric(j,k);
        end
    end
    grandtotal{i,1} = combos(i,:);
    grandtotal{i,2} = total;
            
end

[c,i]=min(cell2mat(grandtotal(:,2)));
display(grandtotal{i,1})
display(grandtotal{i,2})

    function d = metric(sourceInd,destInd)
        d = norm(locs(sourceInd)-locs(nearesthubind(sourceInd)))+ ...
            .5*norm(locs(nearesthubind(sourceInd))-locs(nearesthubind(destInd)))+ ...
            norm(locs(nearesthubind(destInd))-locs(destInd));
        
    end
end