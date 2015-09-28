* problem 3


function grandtotal = prob3()

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
    hubs = combos(i,:);
    nonhubs = setdiff(1:9,hubs);
    [a,b,c,d,e,f]=ndgrid(hubs',hubs',hubs',...
                         hubs',hubs',hubs');
    X = [a(:),b(:),c(:),d(:),e(:),f(:)];
    for m=1:729
        total = 0;
        hubchoices = X(m,:);
        for j=1:6
            nonhubsrcind = nonhubs(j);
            locsrc = locs(:,nonhubsrcind);
            locsrcshub = locs(:,hubchoices(j));
            for k=1:6
                nonhubinddst = nonhubs(k);
                locdst = locs(:,nonhubinddst);
                locdsthub = locs(:,hubchoices(k));
                
                d = norm(locsrc-locsrcshub)+.5*norm(locsrcshub-locdsthub)+norm(locdsthub-locdst); 
                
                total = total + flights(nonhubsrcind,nonhubinddst)*d;
            end
            
            for k=1:3
                hubindsrc = hubs(k);
                d = norm(locsrc-locsrcshub)+.5*norm(locsrcshub-locs(hubindsrc));  
                total = total + flights(nonhubsrcind,hubindsrc)*d;
            end
        end
        for j=1:3
            hubindsrc = hubs(j);
            lochubsrc = locs(:,hubindsrc);
            for k=1:6
                nonhubinddst = nonhubs(k);
                locdst = locs(:,nonhubs(k));
                locsdsthub = locs(:,hubchoices(k));
                
                d = .5*norm(lochubsrc-locsdsthub)+norm(locsdsthub-locdst); 
                total = total + flights(hubindsrc,nonhubinddst)*d;
            end
            for k=1:3
                hubinddst = hubs(k);
                lochubdst =  locs(:,hubinddst);
                d = .5*norm(lochubsrc-lochubdst);  
                total = total + flights(hubindsrc,hubinddst)*d;
            end
        end
        grandtotal{end+1,1} = combos(i,:);
        grandtotal{end,2} = hubchoices;
        grandtotal{end,3} = nonhubs;
        grandtotal{end,4} = total;
    end

    
            
end

[c,i]=min(cell2mat(grandtotal(:,4)));
display(grandtotal{i,1})
display(grandtotal{i,2})
display(grandtotal{i,3})
display(grandtotal{i,4})
display(locs(:,grandtotal{i,1}));
display(locs(:,grandtotal{i,3}));
end