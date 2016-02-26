% Test file for function fftshift()
% Matlab version: 7.9.0.529 (R2009b)

% TEST 1
res1 = fftshift([]);
% TEST 2
res2 = fftshift(m2sciUnknownType([]));
% TEST 3
res3 = fftshift(m2sciUnknownDims([]));
% TEST 4
res4 = fftshift([1]);
% TEST 5
res5 = fftshift([1,2,3]);
% TEST 6
res6 = fftshift([1;2;3]);
% TEST 7
res7 = fftshift([1,2,3;4,5,6]);
% TEST 8
res8 = fftshift(m2sciUnknownType([1]));
% TEST 9
res9 = fftshift(m2sciUnknownType([1,2,3]));
% TEST 10
res10 = fftshift(m2sciUnknownType([1;2;3]));
% TEST 11
res11 = fftshift(m2sciUnknownType([1,2,3;4,5,6]));
% TEST 12
res12 = fftshift(m2sciUnknownDims([1]));
% TEST 13
res13 = fftshift(m2sciUnknownDims([1,2,3]));
% TEST 14
res14 = fftshift(m2sciUnknownDims([1;2;3]));
% TEST 15
res15 = fftshift(m2sciUnknownDims([1,2,3;4,5,6]));
% TEST 16
res16 = fftshift([i]);
% TEST 17
res17 = fftshift([i,2i,3i]);
% TEST 18
res18 = fftshift([i;2i;3i]);
% TEST 19
res19 = fftshift([i,2i,3i;4i,5i,6i]);
% TEST 20
res20 = fftshift(m2sciUnknownType([i]));
% TEST 21
res21 = fftshift(m2sciUnknownType([i,2i,3i]));
% TEST 22
res22 = fftshift(m2sciUnknownType([i;2i;3i]));
% TEST 23
res23 = fftshift(m2sciUnknownType([i,2i,3i;4i,5i,6i]));
% TEST 24
res24 = fftshift(m2sciUnknownDims([i]));
% TEST 25
res25 = fftshift(m2sciUnknownDims([i,2i,3i]));
% TEST 26
res26 = fftshift(m2sciUnknownDims([i;2i;3i]));
% TEST 27
res27 = fftshift(m2sciUnknownDims([i,2i,3i;4i,5i,6i]));
% TEST 28
res28 = fftshift(['s']);
% TEST 29
res29 = fftshift(['str1']);
% TEST 30
res30 = fftshift(['str1','str2','str3']);
% TEST 31
res31 = fftshift(['str1';'str2';'str3']);
% TEST 32
res32 = fftshift(['str1','str2','str3';'str4','str5','str6']);
% TEST 33
res33 = fftshift(m2sciUnknownType(['s']));
% TEST 34
res34 = fftshift(m2sciUnknownType(['str1']));
% TEST 35
res35 = fftshift(m2sciUnknownType(['str1','str2','str3']));
% TEST 36
res36 = fftshift(m2sciUnknownType(['str1';'str2';'str3']));
% TEST 37
res37 = fftshift(m2sciUnknownType(['str1','str2','str3';'str4','str5','str6']));
% TEST 38
res38 = fftshift(m2sciUnknownDims(['s']));
% TEST 39
res39 = fftshift(m2sciUnknownDims(['str1']));
% TEST 40
res40 = fftshift(m2sciUnknownDims(['str1','str2','str3']));
% TEST 41
res41 = fftshift(m2sciUnknownDims(['str1';'str2';'str3']));
% TEST 42
res42 = fftshift(m2sciUnknownDims(['str1','str2','str3';'str4','str5','str6']));
% TEST 43
res43 = fftshift([[1]==[1]]);
% TEST 44
res44 = fftshift([[1,2,3]==[1,0,3]]);
% TEST 45
res45 = fftshift([[1;2;3]==[1;0;3]]);
% TEST 46
res46 = fftshift([[1,2,3;4,5,6]==[1,0,3;4,5,0]]);
% TEST 47
res47 = fftshift(m2sciUnknownType([[1]==[1]]));
% TEST 48
res48 = fftshift(m2sciUnknownType([[1,2,3]==[1,0,3]]));
% TEST 49
res49 = fftshift(m2sciUnknownType([[1;2;3]==[1;0;3]]));
% TEST 50
res50 = fftshift(m2sciUnknownType([[1,2,3;4,5,6]==[1,0,3;4,5,0]]));
% TEST 51
res51 = fftshift(m2sciUnknownDims([[1]==[1]]));
% TEST 52
res52 = fftshift(m2sciUnknownDims([[1,2,3]==[1,0,3]]));
% TEST 53
res53 = fftshift(m2sciUnknownDims([[1;2;3]==[1;0;3]]));
% TEST 54
res54 = fftshift(m2sciUnknownDims([[1,2,3;4,5,6]==[1,0,3;4,5,0]]));
% TEST 55
res55 = fftshift([],1);
% TEST 56
res56 = fftshift(m2sciUnknownType([]),1);
% TEST 57
res57 = fftshift(m2sciUnknownDims([]),1);
% TEST 58
res58 = fftshift([1],1);
% TEST 59
res59 = fftshift([1,2,3],1);
% TEST 60
res60 = fftshift([1;2;3],1);
% TEST 61
res61 = fftshift([1,2,3;4,5,6],1);
% TEST 62
res62 = fftshift(m2sciUnknownType([1]),1);
% TEST 63
res63 = fftshift(m2sciUnknownType([1,2,3]),1);
% TEST 64
res64 = fftshift(m2sciUnknownType([1;2;3]),1);
% TEST 65
res65 = fftshift(m2sciUnknownType([1,2,3;4,5,6]),1);
% TEST 66
res66 = fftshift(m2sciUnknownDims([1]),1);
% TEST 67
res67 = fftshift(m2sciUnknownDims([1,2,3]),1);
% TEST 68
res68 = fftshift(m2sciUnknownDims([1;2;3]),1);
% TEST 69
res69 = fftshift(m2sciUnknownDims([1,2,3;4,5,6]),1);
% TEST 70
res70 = fftshift([i],1);
% TEST 71
res71 = fftshift([i,2i,3i],1);
% TEST 72
res72 = fftshift([i;2i;3i],1);
% TEST 73
res73 = fftshift([i,2i,3i;4i,5i,6i],1);
% TEST 74
res74 = fftshift(m2sciUnknownType([i]),1);
% TEST 75
res75 = fftshift(m2sciUnknownType([i,2i,3i]),1);
% TEST 76
res76 = fftshift(m2sciUnknownType([i;2i;3i]),1);
% TEST 77
res77 = fftshift(m2sciUnknownType([i,2i,3i;4i,5i,6i]),1);
% TEST 78
res78 = fftshift(m2sciUnknownDims([i]),1);
% TEST 79
res79 = fftshift(m2sciUnknownDims([i,2i,3i]),1);
% TEST 80
res80 = fftshift(m2sciUnknownDims([i;2i;3i]),1);
% TEST 81
res81 = fftshift(m2sciUnknownDims([i,2i,3i;4i,5i,6i]),1);
% TEST 82
res82 = fftshift(['s'],1);
% TEST 83
res83 = fftshift(['str1'],1);
% TEST 84
res84 = fftshift(['str1','str2','str3'],1);
% TEST 85
res85 = fftshift(['str1';'str2';'str3'],1);
% TEST 86
res86 = fftshift(['str1','str2','str3';'str4','str5','str6'],1);
% TEST 87
res87 = fftshift(m2sciUnknownType(['s']),1);
% TEST 88
res88 = fftshift(m2sciUnknownType(['str1']),1);
% TEST 89
res89 = fftshift(m2sciUnknownType(['str1','str2','str3']),1);
% TEST 90
res90 = fftshift(m2sciUnknownType(['str1';'str2';'str3']),1);
% TEST 91
res91 = fftshift(m2sciUnknownType(['str1','str2','str3';'str4','str5','str6']),1);
% TEST 92
res92 = fftshift(m2sciUnknownDims(['s']),1);
% TEST 93
res93 = fftshift(m2sciUnknownDims(['str1']),1);
% TEST 94
res94 = fftshift(m2sciUnknownDims(['str1','str2','str3']),1);
% TEST 95
res95 = fftshift(m2sciUnknownDims(['str1';'str2';'str3']),1);
% TEST 96
res96 = fftshift(m2sciUnknownDims(['str1','str2','str3';'str4','str5','str6']),1);
% TEST 97
res97 = fftshift([[1]==[1]],1);
% TEST 98
res98 = fftshift([[1,2,3]==[1,0,3]],1);
% TEST 99
res99 = fftshift([[1;2;3]==[1;0;3]],1);
% TEST 100
res100 = fftshift([[1,2,3;4,5,6]==[1,0,3;4,5,0]],1);
% TEST 101
res101 = fftshift(m2sciUnknownType([[1]==[1]]),1);
% TEST 102
res102 = fftshift(m2sciUnknownType([[1,2,3]==[1,0,3]]),1);
% TEST 103
res103 = fftshift(m2sciUnknownType([[1;2;3]==[1;0;3]]),1);
% TEST 104
res104 = fftshift(m2sciUnknownType([[1,2,3;4,5,6]==[1,0,3;4,5,0]]),1);
% TEST 105
res105 = fftshift(m2sciUnknownDims([[1]==[1]]),1);
% TEST 106
res106 = fftshift(m2sciUnknownDims([[1,2,3]==[1,0,3]]),1);
% TEST 107
res107 = fftshift(m2sciUnknownDims([[1;2;3]==[1;0;3]]),1);
% TEST 108
res108 = fftshift(m2sciUnknownDims([[1,2,3;4,5,6]==[1,0,3;4,5,0]]),1);
% TEST 109
res109 = fftshift([],5);
% TEST 110
res110 = fftshift(m2sciUnknownType([]),5);
% TEST 111
res111 = fftshift(m2sciUnknownDims([]),5);
% TEST 112
res112 = fftshift([1],5);
% TEST 113
res113 = fftshift([1,2,3],5);
% TEST 114
res114 = fftshift([1;2;3],5);
% TEST 115
res115 = fftshift([1,2,3;4,5,6],5);
% TEST 116
res116 = fftshift(m2sciUnknownType([1]),5);
% TEST 117
res117 = fftshift(m2sciUnknownType([1,2,3]),5);
% TEST 118
res118 = fftshift(m2sciUnknownType([1;2;3]),5);
% TEST 119
res119 = fftshift(m2sciUnknownType([1,2,3;4,5,6]),5);
% TEST 120
res120 = fftshift(m2sciUnknownDims([1]),5);
% TEST 121
res121 = fftshift(m2sciUnknownDims([1,2,3]),5);
% TEST 122
res122 = fftshift(m2sciUnknownDims([1;2;3]),5);
% TEST 123
res123 = fftshift(m2sciUnknownDims([1,2,3;4,5,6]),5);
% TEST 124
res124 = fftshift([i],5);
% TEST 125
res125 = fftshift([i,2i,3i],5);
% TEST 126
res126 = fftshift([i;2i;3i],5);
% TEST 127
res127 = fftshift([i,2i,3i;4i,5i,6i],5);
% TEST 128
res128 = fftshift(m2sciUnknownType([i]),5);
% TEST 129
res129 = fftshift(m2sciUnknownType([i,2i,3i]),5);
% TEST 130
res130 = fftshift(m2sciUnknownType([i;2i;3i]),5);
% TEST 131
res131 = fftshift(m2sciUnknownType([i,2i,3i;4i,5i,6i]),5);
% TEST 132
res132 = fftshift(m2sciUnknownDims([i]),5);
% TEST 133
res133 = fftshift(m2sciUnknownDims([i,2i,3i]),5);
% TEST 134
res134 = fftshift(m2sciUnknownDims([i;2i;3i]),5);
% TEST 135
res135 = fftshift(m2sciUnknownDims([i,2i,3i;4i,5i,6i]),5);
% TEST 136
res136 = fftshift(['s'],5);
% TEST 137
res137 = fftshift(['str1'],5);
% TEST 138
res138 = fftshift(['str1','str2','str3'],5);
% TEST 139
res139 = fftshift(['str1';'str2';'str3'],5);
% TEST 140
res140 = fftshift(['str1','str2','str3';'str4','str5','str6'],5);
% TEST 141
res141 = fftshift(m2sciUnknownType(['s']),5);
% TEST 142
res142 = fftshift(m2sciUnknownType(['str1']),5);
% TEST 143
res143 = fftshift(m2sciUnknownType(['str1','str2','str3']),5);
% TEST 144
res144 = fftshift(m2sciUnknownType(['str1';'str2';'str3']),5);
% TEST 145
res145 = fftshift(m2sciUnknownType(['str1','str2','str3';'str4','str5','str6']),5);
% TEST 146
res146 = fftshift(m2sciUnknownDims(['s']),5);
% TEST 147
res147 = fftshift(m2sciUnknownDims(['str1']),5);
% TEST 148
res148 = fftshift(m2sciUnknownDims(['str1','str2','str3']),5);
% TEST 149
res149 = fftshift(m2sciUnknownDims(['str1';'str2';'str3']),5);
% TEST 150
res150 = fftshift(m2sciUnknownDims(['str1','str2','str3';'str4','str5','str6']),5);
% TEST 151
res151 = fftshift([[1]==[1]],5);
% TEST 152
res152 = fftshift([[1,2,3]==[1,0,3]],5);
% TEST 153
res153 = fftshift([[1;2;3]==[1;0;3]],5);
% TEST 154
res154 = fftshift([[1,2,3;4,5,6]==[1,0,3;4,5,0]],5);
% TEST 155
res155 = fftshift(m2sciUnknownType([[1]==[1]]),5);
% TEST 156
res156 = fftshift(m2sciUnknownType([[1,2,3]==[1,0,3]]),5);
% TEST 157
res157 = fftshift(m2sciUnknownType([[1;2;3]==[1;0;3]]),5);
% TEST 158
res158 = fftshift(m2sciUnknownType([[1,2,3;4,5,6]==[1,0,3;4,5,0]]),5);
% TEST 159
res159 = fftshift(m2sciUnknownDims([[1]==[1]]),5);
% TEST 160
res160 = fftshift(m2sciUnknownDims([[1,2,3]==[1,0,3]]),5);
% TEST 161
res161 = fftshift(m2sciUnknownDims([[1;2;3]==[1;0;3]]),5);
% TEST 162
res162 = fftshift(m2sciUnknownDims([[1,2,3;4,5,6]==[1,0,3;4,5,0]]),5);
