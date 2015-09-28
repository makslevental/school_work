import sys
import fileinput
import subprocess
import os
# replace all occurrences of 'sit' with 'SIT' and insert a line after the 5th
bashCommand = "/home/maksim/apps/gams24.4_linux_x64_64_sfx/gams prob_2.gms &> circ_out.1"
os.system(bashCommand)    


for j in range(2,10):
    for i,line in enumerate(fileinput.input('prob_2.gms', inplace=1)):
        sys.stdout.write(line.replace("\*"+str(j-1), "\*"+str(j)))  # replace 'sit' and write
    bashCommand = "/home/maksim/apps/gams24.4_linux_x64_64_sfx/gams prob_2.gms &> circ_out."+str(j)
    os.system(bashCommand)    

    

        
