(* Content-type: application/vnd.wolfram.cdf.text *)

(*** Wolfram CDF File ***)
(* http://www.wolfram.com/cdf *)

(* CreatedBy='Mathematica 9.0' *)

(*************************************************************************)
(*                                                                       *)
(*  The Mathematica License under which this file was created prohibits  *)
(*  restricting third parties in receipt of this file from republishing  *)
(*  or redistributing it by any means, including but not limited to      *)
(*  rights management or terms of use, without the express consent of    *)
(*  Wolfram Research, Inc. For additional information concerning CDF     *)
(*  licensing and redistribution see:                                    *)
(*                                                                       *)
(*        www.wolfram.com/cdf/adopting-cdf/licensing-options.html        *)
(*                                                                       *)
(*************************************************************************)

(*CacheID: 234*)
(* Internal cache information:
NotebookFileLineBreakTest
NotebookFileLineBreakTest
NotebookDataPosition[      1063,         20]
NotebookDataLength[     28272,        572]
NotebookOptionsPosition[     28498,        556]
NotebookOutlinePosition[     28938,        576]
CellTagsIndexPosition[     28895,        573]
WindowFrame->Normal*)

(* Beginning of Notebook Content *)
Notebook[{
Cell[BoxData[
 RowBox[{
  RowBox[{
   RowBox[{"f", "[", 
    RowBox[{"x_", ",", "y_"}], "]"}], ":=", 
   RowBox[{
    RowBox[{"2", 
     SuperscriptBox["x", "2"]}], "+", 
    RowBox[{"2", 
     SuperscriptBox["y", "2"]}]}]}], ";"}]], "Input"],

Cell[BoxData[
 RowBox[{
  RowBox[{
   RowBox[{"g", "[", 
    RowBox[{"x_", ",", "y_"}], "]"}], ":=", 
   RowBox[{
    SuperscriptBox[
     RowBox[{"(", 
      RowBox[{"x", "-", "2"}], ")"}], "2"], "+", 
    SuperscriptBox["y", "2"]}]}], ";"}]], "Input"],

Cell[BoxData[
 RowBox[{
  RowBox[{"p1", "=", 
   RowBox[{"Plot3D", "[", 
    RowBox[{
     RowBox[{"g", "[", 
      RowBox[{"x", ",", "y"}], "]"}], ",", 
     RowBox[{"{", 
      RowBox[{"x", ",", 
       RowBox[{"-", "5"}], ",", "5"}], "}"}], ",", 
     RowBox[{"{", 
      RowBox[{"y", ",", 
       RowBox[{"-", "5"}], ",", "5"}], "}"}], ",", 
     RowBox[{"Axes", "\[Rule]", "True"}], ",", 
     RowBox[{"PlotRange", "\[Rule]", 
      RowBox[{"{", 
       RowBox[{
        RowBox[{"-", "1"}], ",", "5"}], "}"}]}], ",", 
     RowBox[{"ClippingStyle", "\[Rule]", "None"}], ",", 
     RowBox[{"PlotStyle", "\[Rule]", 
      RowBox[{"{", "Orange", "}"}]}], ",", 
     RowBox[{"AxesOrigin", "\[Rule]", 
      RowBox[{"{", 
       RowBox[{"0", ",", "0", ",", "0"}], "}"}]}], ",", 
     RowBox[{"Mesh", "\[Rule]", "None"}], ",", 
     RowBox[{"Boxed", "\[Rule]", "False"}]}], "]"}]}], ";"}]], "Input"],

Cell[BoxData[
 RowBox[{
  RowBox[{"p2", "=", 
   RowBox[{"Plot3D", "[", 
    RowBox[{
     RowBox[{"f", "[", 
      RowBox[{"x", ",", "y"}], "]"}], ",", 
     RowBox[{"{", 
      RowBox[{"x", ",", 
       RowBox[{"-", "5"}], ",", "5"}], "}"}], ",", 
     RowBox[{"{", 
      RowBox[{"y", ",", 
       RowBox[{"-", "5"}], ",", "5"}], "}"}], ",", 
     RowBox[{"Axes", "\[Rule]", "True"}], ",", 
     RowBox[{"PlotRange", "\[Rule]", 
      RowBox[{"{", 
       RowBox[{
        RowBox[{"-", "1"}], ",", "5"}], "}"}]}], ",", 
     RowBox[{"ClippingStyle", "\[Rule]", "None"}], ",", 
     RowBox[{"PlotStyle", "\[Rule]", 
      RowBox[{"{", "Blue", "}"}]}], ",", 
     RowBox[{"AxesOrigin", "\[Rule]", 
      RowBox[{"{", 
       RowBox[{"0", ",", "0", ",", "0"}], "}"}]}], ",", 
     RowBox[{"Mesh", "\[Rule]", "None"}], ",", 
     RowBox[{"Boxed", "\[Rule]", "False"}]}], "]"}]}], ";"}]], "Input"],

Cell[CellGroupData[{

Cell[BoxData[
 RowBox[{"Show", "[", 
  RowBox[{"p1", ",", "p2"}], "]"}]], "Input"],

Cell[BoxData[
 Graphics3DBox[{GraphicsComplex3DBox[CompressedData["
1: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
    "], {{
      {RGBColor[1, 0.5, 0], EdgeForm[None], 
       GraphicsGroup3DBox[{Polygon3DBox[CompressedData["
1:eJwBcASP+yFib1JiAgAAAHUBAAADAAAASyEBTCICwQjUTiUDeGcyUCYEVCoG
UigFLAcNsicJQzoVe2s0OBMZ9jDntDEPs7Ipfn02Lg0TrnA/g2o76hTIh249
eXcyc0Q8n0ZAZUgcQRkeyRrLZEcbZkkd3gHz3R7K7x/P8SDQ3wL00wO9SyIE
TSQGwAe/TiYJTCMFjVAoVCwMLw0HJw4Ij1IqfHo0dUU+WDEOUSkJMRQOubi0
RUAcRkEdMBMNiIY9hII7RD4br4o/QzwaQh4Z4yTiAyEER2QfqHZFBSMG0QG6
ZEgfZUkgBCIFAiIBORkTBiQHq382BCYDjFEmTycIk5JVWCcPkI5TBSgEaVkp
BioFkWhTlm1aVzANmW9bTyUJ1AjClGxVViwNBywG2BTGXC4TgFYu1g7EXjEV
qWkyoGgyomw0t7VZgV8zqm00l3FamnJbnIVgbzYSgDYMnXRgnolhYjgZXTkT
XjoUrIE7i1w4pXE7XzwVGjwbrYU9pnI9Gz4ciT8Yiz8SHUEetnZhHEAdYkEY
Y0IZp3REOkMaPEMVPEQbPkUcQEYdSGQbH0ggG0caHEgbHUkcHkod8wHRQUYY
7krc8iDN9ALSIUsEIksBJ1gOJU4JI0wCI00GwgjkJk4DKFAEJU8IJ08JsIxQ
JlEJZ1EKsY5SjVMKa1MLklQMKlIFLFQGfVUMLFYMLlYNj1ULL1cNaakQIkwF
MVgPo25as1kPoWpZlXdamHpbMF0TpHBbm39cOFwTxhTqMV4UOl4Vc18WgmAW
dWAXuF8VhmEXimIYQWIZOWMZn2EYxA7oc6dESGUgdahFUWcpoGcKSmYdzx/w
U2gKeGkpoWkQP3ASeWgr0CDypWoQt2ozkWsrVWwLfGwto20Rl241pm4RomsL
fm8tpG8SNn0Me20rmnA3aHkyYHQWX3M8mHIRiHI3RHQ+nXU+YXYXlXEQqHUX
p3MWRXZAqXcQZ3gpaXgyd3krqnoRa3srmXotlncrbXs0enwthHE1bHw0lH0t
cZVaVoAMb342Nn8SXH8uq4AunII1g4EzX4EWrIIWaoMzgYM7goQ1h4U1YIUX
rYYXcYQ7noY3hYc9hog3cog9boc1rok3fX4tYYkYYoo4UYwKm4sSr4s4sI0K
kI0osY8LP4oYUo4oU44LUIwmbZYrk48qjZBTa5FTVJIqVZIMaJErkpMqbJQt
fZRVd5UQj5NVjpAodKcWd5ZaX7gzepgRcphbhZw1gpxgbpdaeplbb5kti5tc
cpo3f5sSdJ0+aqEQhp5hRp8YcZc1aaFZiZ43tp9AdZ1gZ6AyaKAKcJpba6I0
bKILaqU7dqgXd6kySWUccKQScaUQb6RbcqYRbqY9baoRhq09cK43gKs2bqMR
baNaf6sueqo0gawWia4/ha0Xgqw7i68/jLAKiq84zh7djrELj7FSJ7IP2Tnp
KbIJ2kLssrMPjbBQubUzvAPTWbMpWbUPMbQVdrZA1zD2tbczardZtLgVzB/v
n7ZhuLkztbm01S/mtbQPuwLfrZKWXg==
          "]], 
         Polygon3DBox[{{237, 71, 31, 204}, {225, 35, 2, 187}, {202, 30, 66, 
          218}, {210, 2, 1, 222}, {199, 99, 57, 217}, {224, 33, 3, 188}, {186,
           1, 33, 224}, {189, 3, 37, 229}, {236, 66, 99, 199}, {235, 58, 26, 
          201}, {232, 14, 20, 216}, {240, 31, 32, 241}, {231, 48, 87, 195}, {
          191, 7, 36, 227}, {226, 36, 77, 190}, {233, 57, 93, 197}, {229, 37, 
          8, 193}, {195, 87, 47, 213}, {200, 20, 58, 235}, {203, 26, 71, 
          237}, {228, 8, 14, 214}, {205, 32, 73, 219}, {219, 73, 102, 245}, {
          220, 74, 30, 206}, {190, 77, 35, 225}, {197, 93, 48, 215}, {230, 47,
           7, 192}, {245, 102, 74, 238}}]}]}, {}, {}, {}, {}}, 
     {GrayLevel[0], 
      Line3DBox[{209, 186, 224, 188, 211, 189, 229, 193, 212, 194, 228, 214, 
       196, 232, 216, 198, 234, 200, 235, 201, 203, 237, 204, 239, 207, 240, 
       241, 208, 242, 205, 219, 245, 238, 220, 206, 221, 202, 218, 236, 199, 
       217, 233, 197, 215, 246, 231, 195, 213, 230, 192, 191, 227, 226, 190, 
       225, 187, 223, 244, 210, 222, 243, 209}]}},
    VertexNormals->CompressedData["
1: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
     "]], 
   GraphicsComplex3DBox[CompressedData["
1:eJx1l29o1VUYx+ddwZy2f12aTioX28hqIaQvcoPfzwxZEgVF4V60boXDinJJ
e9GLIAax0ZtoReawmv1R2ixXbRI69pPISSZjrG0Y9WLd3JWG0HRuOtPd4nee
z3M5DyXI4XzP93yf7/Oc55zdX+Wzux7bkcjLyzvz7//8PP6NDx5ecfMbL/26
EG0517hhz+MlYX88z0SM22I8L4Tv47NBt5sH4PXCR5d9Vh8cHeb++Mv96IPX
Cv9zp6/4RqPPvnrjH7zW+PfxHJ846P/QULS2s+pCxFhbNV1R2FQWDsW8ScVX
PdOy7PWdNyifdfD33TxgvVRweIzb47hTwVHHU/4dEhcd+PWGD54QfeoDvjbG
L6kuevihDr6fUdWFT1zqyHq+6MNjvN34BP875fsELzM+2Ucd8Onr53zCpw74
hD+f8n3Cxw9zxnKJi0/wwfKygYn2QvXj8xMaF/wr4aNDfmOCM2d9zOj7fZjQ
/oHP+RJX+1d0yBc+dcYf+KDxo/fRxAWnT9AH51zQB6c+6KtfiYs+uO0rcM4R
fXDq/NFI+VRD5/loLMaHo4kYvxqAtzk8GBEc3qlY7/doXRz3bAAPvEJw+Iyt
cb7HFWdfveBH3H5dX0o5HXD4f6X8uIz5Rv8tl0fwjfiHB95r8sX/0JsfHxzd
vkzrQ703zKWL2vZc1zyJQx3AGTfF53hR48KvNz7R3xjrjCsffLXg1AH9KtEH
h38szmtG8yQOdQBH55DJF71vBYcHTlxw/Npzh79kzgucc4RP/15L+XUAn0r5
dWAsFj/kBb5f/IOj12v6mbwnTJ+A0//kq30h+tSd9YzUHx/wqSf5gNdIX4Fr
H4kOc94H11dpPW/yoH/AyWO16St03H3p07joUH9w9lF/6olO3WunN+9rW9S4
5H3M+GffIVM38FJTB62fqSf8/UaH31nfxXip1hl8QHDy2dRTMprNzkWNsf/l
IfmDPyW41l3wyp51Hdlsgd4X1pukDsz9dyCt9WW9VepPXuDFwuf3Fvn1iP/1
zofqPSg+4ZP3QcMn71D44MQtkLyY++9qn/KoP+eu76b4pP/h++9/n54ffM6d
euK/xry3ej+Mvv8OpLWees/MewieL/r4oH49pn/AqSf5UD/qT73AQ9M/5Ndk
7gs4f1/oV9bpZ/qP+PQnfPwOGD6+6HN41IM6oMvvjufn2scPTCXUP3nRJ+jy
++JR4bOf9R2C630QX+vjuDfp/QVfea7/5d2FK0LOkbgrhY9/8PMZx2c/+6qF
D86+G0WffDnfnx+5+53p90rC5vStHU8+MR34321J/V165afZbZPtOZzfVUsG
X3TzwP/OS+p5Nbk4il8f6mjorFrU9wEcf+8aflb0/e/CZNgl/v3vwqSe4zUX
R/Gjn7VNFrQejx5I/dFVNHNF9U/ds2brb0fmgxd+TFx6u+pPxeGxD/xsb7Jo
pnshuO3hW/Y1N+f8sB891dlaW134SiZYuLN7rO5AzucupxtYP03Ln+748MyF
iFHPRfQPO/1cnWXeb/ynnc+owvlUvFh8Z2QdvMXtD04a/UbnI3jO+JmSOtxl
9EOXT5A1dSNP8gbfLPx+g+MDX+D4wBc4PvCldZDzqDY6zNPmvOhj+hqc/ssa
HN/kYfvQ7/dkyL2y98Xv19y94L7Z/v/kcumrs7svmu+qpH63sg7Oe9XlcI3L
3P/OS4Z7Zb/F0f/U6DC3fti/1/jhXbDvD+/k8IkXKwvacveCd+2kwU+4eeB/
j+beE94J7Svh+9+peu+CJtNXvEf2nSEe8f/Hp+LkY32Sf/N/+4ysz8C9J9G8
e09y973ryy01D30f2Xfv3kxLXdng6Wjk6y8+GL6a87Mo+++T9wmcvxerist3
Xl6T0/kHTXyIHw==
    "], {{
      {RGBColor[0, 0, 1], EdgeForm[None], 
       GraphicsGroup3DBox[{Polygon3DBox[CompressedData["
1:eJwNxVdTGgYAAGD23ntPUUFkCLKngCJbtrhRFAVFRdwbXLhX+tD0mjaXa9q7
5jpy7V1zuex0pum49ve038snzJaiWRAAAJABAQDw/58UpR1OWqeB8Yr8qNvL
OjwgbFmF63puj5lfWeDYJYLPgE/yjaIGHuol7osWMiTdhE9JiQYZeMVFW/Ox
NoLcaIR/e3O0HRd2eRj3oXff8B6/wD1sxoEuLyZ1CkJhiriflPVl5IMm5TPx
d71u2Wvyl/1G+YhF5W+lummgsbBGR4Od1xUlIyPQRl81MYZCSgsL8Zb3IGtT
TcS0fhYkoeYEuKjNMP8b5NMQF3ZWkyzZ+E+AnySEiGOHNibEXF/tPhe/axdj
ympqdUeQa0CdViW4JpC4EeNsBk0XpGkZaDynWXZI9pLS9jhnNIHwyiF3oV8f
KqDkVsiMXnEP+8OwRzXgUs6alXNW1WJFHdSgniK/GvWp7Rp0vB0T0aLzWkxK
Du7QEbh6WMkA7jWQzvV0uRE8o4PNmuBdRsqSGT5kZnZbKEIrImtlz1kQwzb4
sh3Na0NFbexxu0DrQJ85RDQnSNdBG/FQnB0Emgu24iYNukgyN2jVAzd0klg+
hKeLYuximDoZLC/E201R+6j9Xoqlm5VpgbT6IeEePjeIGgsy2wKogRCsJ8zc
CDGbnYT1AF0TRm9G0JEo29zDtEX52hhGGMes+akTEfZWjN1pIm0nOLVTSV+K
2JQG7aXA+2m8oVfm7iWFhpihDa4sCZZnIKk+uWsA1pIhmgZJoQFlpo/oGlR6
++XmIaV9XOMZUdmybMsIxZpVeYbh4TGmbxRhG1YFxzQNOUFsgp0bF2hyqMiE
9qfJHxvzmOO8yNhPKU4CpwrAyyLeWAJPF4HFaal+BlaYBupmFAsVpKHE+GX+
I8ucyjqHMM0qzbPw+TJ1sYwszyPVFU55Ue1ZZdiW4PZliXmJ71hGP8S9fCd+
Ji0QK4vIR+TXrhWSb41qWoX711iBdW5wg5kYVbtXaPp1+mPe25Mk/lPyq9iW
ML7NsW6xE9vCv4/+klQFtV3sH7sf36lir2ui1J40uY8/rWGTe+CDQ6jikJDe
l4U30fUj6G2dnj/WFk/wjmNR8kSqqENrZ6LqKdZxJqmf0/XniotLfPFysukC
/w/23tW1KLLJb7wS1a53b27pbTf0D6Z+/vDgz89xL+q3R+93/v195/2vC799
L35evbPzLe/Nf5eSBvA=
          "]], 
         Polygon3DBox[{{170, 14, 40, 188}, {173, 19, 43, 153}, {182, 35, 53, 
          158}, {215, 148, 50, 190}, {181, 32, 129, 206}, {216, 150, 13, 
          213}, {171, 16, 135, 155}, {165, 30, 36, 184}, {204, 116, 9, 178}, {
          185, 38, 35, 183}, {172, 17, 106, 151}, {164, 28, 116, 203}, {175, 
          21, 45, 154}, {184, 36, 32, 181}, {188, 40, 16, 171}, {153, 43, 17, 
          172}, {158, 53, 28, 164}, {161, 1, 105, 200}, {199, 105, 144, 
          212}, {157, 114, 21, 175}, {201, 106, 1, 167}, {190, 50, 30, 179}, {
          209, 135, 5, 163}, {154, 45, 19, 162}, {176, 9, 114, 202}, {186, 13,
           130, 208}, {159, 130, 146, 166}, {152, 39, 14, 169}, {177, 5, 137, 
          211}, {166, 146, 38, 185}, {210, 137, 148, 215}, {212, 144, 39, 
          152}, {214, 129, 150, 216}}]}]}, {}, {}, {}, {}}, 
     {GrayLevel[0], 
      Line3DBox[{200, 199, 212, 152, 169, 193, 168, 194, 170, 188, 171, 155, 
       209, 163, 156, 177, 211, 210, 215, 190, 179, 197, 180, 198, 165, 184, 
       181, 206, 207, 214, 216, 213, 160, 186, 208, 159, 166, 185, 183, 192, 
       205, 191, 182, 158, 164, 203, 204, 178, 189, 176, 202, 157, 175, 154, 
       162, 195, 174, 196, 173, 153, 172, 151, 201, 167, 187, 161, 200}]}},
    VertexNormals->CompressedData["
1:eJxVVws81mcbdj6l85qi+CoU1WILb1s8vBFR0dsiZSPpa8ocO4qNT9q3Fn1t
rZLOtoo1ORP1PthbIRrDYlQOkRD1VcrU7H/jer+P36/f83uu//1c931f9/U8
76+ZvkGSzUoKCgp1wj9lBflf1Om0+yc+je1lza0TbQ5NuMm2Dl736+9rk68V
ojNi08I7zDNYb8VOQwfp2ic6n727qGdkX8vWl/VRHB9Zmb1unDXFgxd5wD/6
vIMUPK8HB68MDnpL/28V/nrZ2KXMX4jn6b/GOFD88FrLMoOmJQr8HPyhM6pF
xI86UBfqwfnRfLXM+fuFmykOKx8IF1E8eJEH/A6SFhfPNe3y9bKBftya32Vs
Q6DJ9DPF1Uz7hFZaT9ITppO50nZSym35Ht+Bez26PFfY8/t2E1Lpe9T0HTaE
S3d7ae52fChft50+UjTOr5EdGXjgJuTjtueMHSmvkWXmvymv3tiGiUIcl6om
K1P8tU0JVyl+aurWdIGXH0458y7l1a05KCL+r+50rYx162JxMwyXx7o1sMUR
tx79ol/NUAfqQj233K/UVnhKpL+kJsiMrDpH9i0M+ZAfeb009rkJ/Dz05Xwx
8Ucte9RC/Hon5mhTHNZJJqfTKb5zbfAVqvPQ7NmzKW+sdZYl5d39YbAz1em3
8tY6gYd7bfRoIx70Dz2gg/7qCRVU53sJ58uEOvnwvoWhf+gBHVy3a5AO3NGo
cjXx/zBvVxPxow7UhXq2rlJeQfmwGozkzXW1fvVrQDM7VNM7YDW7kxemFG6e
vbmEuTSs9G+cYi2tN69Vyzbp5cP7CtZ/4MKfQjyXzDjfT/FXncX/pPitX2oO
EM8R16mEM9/8idsIxx7fgW/73i2U+PPOryL+kX2FfK6YM+ZbmvLeW8r717Tr
r4gvMqXCn3igL/SGzugH/aGv0fmspcg72h8SKXwyeh4SKeYyWhdrKfRBfagX
dcJP8Bd8hflhnpgj9IXe0PnLGWMkTNzDQr0dtwwuKmHHmZpZ+7NKlsK+ciO8
qOnFVwLOtcYsWEi4bL62XXz0b2x53P7AtcVd7HHSgP2RjnpWZla2TsB5d9ay
bYR72D63I9xt/n+Czr/TJF/TkxZMcY5pZzrlTf60N3rXL0pYeet00VjCJasK
QoTzfHzEwQ8pz6I9LR8RT9+OvZSPa0c5SyjPj1P+EBHelZ0VTuex6h8VqxLP
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
     "]]},
  Axes->True,
  AxesOrigin->{0, 0, 0},
  BoxRatios->{1, 1, 0.4},
  Boxed->False,
  ImageSize->{748., 608.},
  Method->{"RotationControl" -> "Globe"},
  PlotRange->{{-5, 5}, {-5, 5}, {-1, 5}},
  PlotRangePadding->{
    Scaled[0.02], 
    Scaled[0.02], Automatic},
  ViewPoint->{0.6854752455173867, -2.776736785103823, 1.8082744576070782`},
  ViewVertical->{0., 0., 1.}]], "Output"]
}, Open  ]],

Cell[CellGroupData[{

Cell[BoxData[
 RowBox[{"Manipulate", "[", 
  RowBox[{
   RowBox[{"ContourPlot3D", "[", 
    RowBox[{
     RowBox[{
      RowBox[{"f", "[", 
       RowBox[{"x", ",", "y"}], "]"}], "+", 
      RowBox[{"l", " ", 
       RowBox[{"g", "[", 
        RowBox[{"x", ",", "y"}], "]"}]}]}], ",", 
     RowBox[{"{", 
      RowBox[{"x", ",", 
       RowBox[{"-", "5"}], ",", "5"}], "}"}], ",", 
     RowBox[{"{", 
      RowBox[{"y", ",", 
       RowBox[{"-", "5"}], ",", "5"}], "}"}], ",", 
     RowBox[{"{", 
      RowBox[{"l", ",", 
       RowBox[{"-", "5"}], ",", "5"}], "}"}], ",", 
     RowBox[{"AxesOrigin", "\[Rule]", 
      RowBox[{"{", 
       RowBox[{"0", ",", "0", ",", "0"}], "}"}]}], ",", 
     RowBox[{"Mesh", "\[Rule]", "None"}], ",", 
     RowBox[{"Boxed", "\[Rule]", "False"}], ",", 
     RowBox[{"Contours", "\[Rule]", 
      RowBox[{"{", "a", "}"}]}]}], "]"}], ",", 
   RowBox[{"{", 
    RowBox[{"a", ",", 
     RowBox[{"-", "20"}], ",", "20"}], "}"}]}], "]"}]], "Input"],

Cell[BoxData[
 TagBox[
  StyleBox[
   DynamicModuleBox[{$CellContext`a$$ = 6.5, Typeset`show$$ = True, 
    Typeset`bookmarkList$$ = {}, Typeset`bookmarkMode$$ = "Menu", 
    Typeset`animator$$, Typeset`animvar$$ = 1, Typeset`name$$ = 
    "\"untitled\"", Typeset`specs$$ = {{
      Hold[$CellContext`a$$], -20, 20}}, Typeset`size$$ = {
    360., {193., 198.}}, Typeset`update$$ = 0, Typeset`initDone$$, 
    Typeset`skipInitDone$$ = True, $CellContext`a$888$$ = 0}, 
    DynamicBox[Manipulate`ManipulateBoxes[
     1, StandardForm, "Variables" :> {$CellContext`a$$ = -20}, 
      "ControllerVariables" :> {
        Hold[$CellContext`a$$, $CellContext`a$888$$, 0]}, 
      "OtherVariables" :> {
       Typeset`show$$, Typeset`bookmarkList$$, Typeset`bookmarkMode$$, 
        Typeset`animator$$, Typeset`animvar$$, Typeset`name$$, 
        Typeset`specs$$, Typeset`size$$, Typeset`update$$, Typeset`initDone$$,
         Typeset`skipInitDone$$}, "Body" :> 
      ContourPlot3D[$CellContext`f[$CellContext`x, $CellContext`y] + \
$CellContext`l $CellContext`g[$CellContext`x, $CellContext`y], \
{$CellContext`x, -5, 5}, {$CellContext`y, -5, 5}, {$CellContext`l, -5, 5}, 
        AxesOrigin -> {0, 0, 0}, Mesh -> None, Boxed -> False, 
        Contours -> {$CellContext`a$$}], 
      "Specifications" :> {{$CellContext`a$$, -20, 20}}, "Options" :> {}, 
      "DefaultOptions" :> {}],
     ImageSizeCache->{407., {237., 244.}},
     SingleEvaluation->True],
    Deinitialization:>None,
    DynamicModuleValues:>{},
    SynchronousInitialization->True,
    UnsavedVariables:>{Typeset`initDone$$},
    UntrackedVariables:>{Typeset`size$$}], "Manipulate",
   Deployed->True,
   StripOnInput->False],
  Manipulate`InterpretManipulate[1]]], "Output"]
}, Open  ]]
},
WindowSize->{740, 867},
Visible->True,
ScrollingOptions->{"VerticalScrollRange"->Fit},
ShowCellBracket->False,
Deployed->True,
CellContext->Notebook,
TrackCellChangeTimes->False,
FrontEndVersion->"9.0 for Linux x86 (64-bit) (February 7, 2013)",
StyleDefinitions->"Default.nb"
]
(* End of Notebook Content *)

(* Internal cache information *)
(*CellTagsOutline
CellTagsIndex->{}
*)
(*CellTagsIndex
CellTagsIndex->{}
*)
(*NotebookFileOutline
Notebook[{
Cell[1463, 33, 242, 9, 34, "Input"],
Cell[1708, 44, 253, 9, 34, "Input"],
Cell[1964, 55, 897, 25, 77, "Input"],
Cell[2864, 82, 895, 25, 77, "Input"],
Cell[CellGroupData[{
Cell[3784, 111, 82, 2, 32, "Input"],
Cell[3869, 115, 21857, 367, 623, "Output"]
}, Open  ]],
Cell[CellGroupData[{
Cell[25763, 487, 977, 29, 77, "Input"],
Cell[26743, 518, 1739, 35, 498, "Output"]
}, Open  ]]
}
]
*)

(* End of internal cache information *)

(* NotebookSignature mx0dGecTTe4FrBgfTkHP8iRH *)
