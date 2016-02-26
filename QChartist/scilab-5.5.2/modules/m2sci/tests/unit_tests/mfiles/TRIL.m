% Test file for function tril()
% Matlab version: 7.9.0.529 (R2009b)

% TEST 1
res1 = tril([]);
% TEST 2
res2 = tril(m2sciUnknownType([]));
% TEST 3
res3 = tril(m2sciUnknownDims([]));
% TEST 4
res4 = tril([1]);
% TEST 5
res5 = tril([1,2,3]);
% TEST 6
res6 = tril([1;2;3]);
% TEST 7
res7 = tril([1,2,3;4,5,6]);
% TEST 8
res8 = tril(m2sciUnknownType([1]));
% TEST 9
res9 = tril(m2sciUnknownType([1,2,3]));
% TEST 10
res10 = tril(m2sciUnknownType([1;2;3]));
% TEST 11
res11 = tril(m2sciUnknownType([1,2,3;4,5,6]));
% TEST 12
res12 = tril(m2sciUnknownDims([1]));
% TEST 13
res13 = tril(m2sciUnknownDims([1,2,3]));
% TEST 14
res14 = tril(m2sciUnknownDims([1;2;3]));
% TEST 15
res15 = tril(m2sciUnknownDims([1,2,3;4,5,6]));
% TEST 16
res16 = tril([i]);
% TEST 17
res17 = tril([i,2i,3i]);
% TEST 18
res18 = tril([i;2i;3i]);
% TEST 19
res19 = tril([i,2i,3i;4i,5i,6i]);
% TEST 20
res20 = tril(m2sciUnknownType([i]));
% TEST 21
res21 = tril(m2sciUnknownType([i,2i,3i]));
% TEST 22
res22 = tril(m2sciUnknownType([i;2i;3i]));
% TEST 23
res23 = tril(m2sciUnknownType([i,2i,3i;4i,5i,6i]));
% TEST 24
res24 = tril(m2sciUnknownDims([i]));
% TEST 25
res25 = tril(m2sciUnknownDims([i,2i,3i]));
% TEST 26
res26 = tril(m2sciUnknownDims([i;2i;3i]));
% TEST 27
res27 = tril(m2sciUnknownDims([i,2i,3i;4i,5i,6i]));
% TEST 28
res28 = tril(['s']);
% TEST 29
res29 = tril(['str1']);
% TEST 30
res30 = tril(['str1','str2','str3']);
% TEST 31
res31 = tril(['str1';'str2';'str3']);
% TEST 32
res32 = tril(['str1','str2','str3';'str4','str5','str6']);
% TEST 33
res33 = tril(m2sciUnknownType(['s']));
% TEST 34
res34 = tril(m2sciUnknownType(['str1']));
% TEST 35
res35 = tril(m2sciUnknownType(['str1','str2','str3']));
% TEST 36
res36 = tril(m2sciUnknownType(['str1';'str2';'str3']));
% TEST 37
res37 = tril(m2sciUnknownType(['str1','str2','str3';'str4','str5','str6']));
% TEST 38
res38 = tril(m2sciUnknownDims(['s']));
% TEST 39
res39 = tril(m2sciUnknownDims(['str1']));
% TEST 40
res40 = tril(m2sciUnknownDims(['str1','str2','str3']));
% TEST 41
res41 = tril(m2sciUnknownDims(['str1';'str2';'str3']));
% TEST 42
res42 = tril(m2sciUnknownDims(['str1','str2','str3';'str4','str5','str6']));
% TEST 43
res43 = tril([[1]==[1]]);
% TEST 44
res44 = tril([[1,2,3]==[1,0,3]]);
% TEST 45
res45 = tril([[1;2;3]==[1;0;3]]);
% TEST 46
res46 = tril([[1,2,3;4,5,6]==[1,0,3;4,5,0]]);
% TEST 47
res47 = tril(m2sciUnknownType([[1]==[1]]));
% TEST 48
res48 = tril(m2sciUnknownType([[1,2,3]==[1,0,3]]));
% TEST 49
res49 = tril(m2sciUnknownType([[1;2;3]==[1;0;3]]));
% TEST 50
res50 = tril(m2sciUnknownType([[1,2,3;4,5,6]==[1,0,3;4,5,0]]));
% TEST 51
res51 = tril(m2sciUnknownDims([[1]==[1]]));
% TEST 52
res52 = tril(m2sciUnknownDims([[1,2,3]==[1,0,3]]));
% TEST 53
res53 = tril(m2sciUnknownDims([[1;2;3]==[1;0;3]]));
% TEST 54
res54 = tril(m2sciUnknownDims([[1,2,3;4,5,6]==[1,0,3;4,5,0]]));
% TEST 55
res55 = tril([],1);
% TEST 56
res56 = tril(m2sciUnknownType([]),1);
% TEST 57
res57 = tril(m2sciUnknownDims([]),1);
% TEST 58
res58 = tril([1],1);
% TEST 59
res59 = tril([1,2,3],1);
% TEST 60
res60 = tril([1;2;3],1);
% TEST 61
res61 = tril([1,2,3;4,5,6],1);
% TEST 62
res62 = tril(m2sciUnknownType([1]),1);
% TEST 63
res63 = tril(m2sciUnknownType([1,2,3]),1);
% TEST 64
res64 = tril(m2sciUnknownType([1;2;3]),1);
% TEST 65
res65 = tril(m2sciUnknownType([1,2,3;4,5,6]),1);
% TEST 66
res66 = tril(m2sciUnknownDims([1]),1);
% TEST 67
res67 = tril(m2sciUnknownDims([1,2,3]),1);
% TEST 68
res68 = tril(m2sciUnknownDims([1;2;3]),1);
% TEST 69
res69 = tril(m2sciUnknownDims([1,2,3;4,5,6]),1);
% TEST 70
res70 = tril([i],1);
% TEST 71
res71 = tril([i,2i,3i],1);
% TEST 72
res72 = tril([i;2i;3i],1);
% TEST 73
res73 = tril([i,2i,3i;4i,5i,6i],1);
% TEST 74
res74 = tril(m2sciUnknownType([i]),1);
% TEST 75
res75 = tril(m2sciUnknownType([i,2i,3i]),1);
% TEST 76
res76 = tril(m2sciUnknownType([i;2i;3i]),1);
% TEST 77
res77 = tril(m2sciUnknownType([i,2i,3i;4i,5i,6i]),1);
% TEST 78
res78 = tril(m2sciUnknownDims([i]),1);
% TEST 79
res79 = tril(m2sciUnknownDims([i,2i,3i]),1);
% TEST 80
res80 = tril(m2sciUnknownDims([i;2i;3i]),1);
% TEST 81
res81 = tril(m2sciUnknownDims([i,2i,3i;4i,5i,6i]),1);
% TEST 82
res82 = tril(['s'],1);
% TEST 83
res83 = tril(['str1'],1);
% TEST 84
res84 = tril(['str1','str2','str3'],1);
% TEST 85
res85 = tril(['str1';'str2';'str3'],1);
% TEST 86
res86 = tril(['str1','str2','str3';'str4','str5','str6'],1);
% TEST 87
res87 = tril(m2sciUnknownType(['s']),1);
% TEST 88
res88 = tril(m2sciUnknownType(['str1']),1);
% TEST 89
res89 = tril(m2sciUnknownType(['str1','str2','str3']),1);
% TEST 90
res90 = tril(m2sciUnknownType(['str1';'str2';'str3']),1);
% TEST 91
res91 = tril(m2sciUnknownType(['str1','str2','str3';'str4','str5','str6']),1);
% TEST 92
res92 = tril(m2sciUnknownDims(['s']),1);
% TEST 93
res93 = tril(m2sciUnknownDims(['str1']),1);
% TEST 94
res94 = tril(m2sciUnknownDims(['str1','str2','str3']),1);
% TEST 95
res95 = tril(m2sciUnknownDims(['str1';'str2';'str3']),1);
% TEST 96
res96 = tril(m2sciUnknownDims(['str1','str2','str3';'str4','str5','str6']),1);
% TEST 97
res97 = tril([[1]==[1]],1);
% TEST 98
res98 = tril([[1,2,3]==[1,0,3]],1);
% TEST 99
res99 = tril([[1;2;3]==[1;0;3]],1);
% TEST 100
res100 = tril([[1,2,3;4,5,6]==[1,0,3;4,5,0]],1);
% TEST 101
res101 = tril(m2sciUnknownType([[1]==[1]]),1);
% TEST 102
res102 = tril(m2sciUnknownType([[1,2,3]==[1,0,3]]),1);
% TEST 103
res103 = tril(m2sciUnknownType([[1;2;3]==[1;0;3]]),1);
% TEST 104
res104 = tril(m2sciUnknownType([[1,2,3;4,5,6]==[1,0,3;4,5,0]]),1);
% TEST 105
res105 = tril(m2sciUnknownDims([[1]==[1]]),1);
% TEST 106
res106 = tril(m2sciUnknownDims([[1,2,3]==[1,0,3]]),1);
% TEST 107
res107 = tril(m2sciUnknownDims([[1;2;3]==[1;0;3]]),1);
% TEST 108
res108 = tril(m2sciUnknownDims([[1,2,3;4,5,6]==[1,0,3;4,5,0]]),1);
% TEST 109
res109 = tril([],2);
% TEST 110
res110 = tril(m2sciUnknownType([]),2);
% TEST 111
res111 = tril(m2sciUnknownDims([]),2);
% TEST 112
res112 = tril([1],2);
% TEST 113
res113 = tril([1,2,3],2);
% TEST 114
res114 = tril([1;2;3],2);
% TEST 115
res115 = tril([1,2,3;4,5,6],2);
% TEST 116
res116 = tril(m2sciUnknownType([1]),2);
% TEST 117
res117 = tril(m2sciUnknownType([1,2,3]),2);
% TEST 118
res118 = tril(m2sciUnknownType([1;2;3]),2);
% TEST 119
res119 = tril(m2sciUnknownType([1,2,3;4,5,6]),2);
% TEST 120
res120 = tril(m2sciUnknownDims([1]),2);
% TEST 121
res121 = tril(m2sciUnknownDims([1,2,3]),2);
% TEST 122
res122 = tril(m2sciUnknownDims([1;2;3]),2);
% TEST 123
res123 = tril(m2sciUnknownDims([1,2,3;4,5,6]),2);
% TEST 124
res124 = tril([i],2);
% TEST 125
res125 = tril([i,2i,3i],2);
% TEST 126
res126 = tril([i;2i;3i],2);
% TEST 127
res127 = tril([i,2i,3i;4i,5i,6i],2);
% TEST 128
res128 = tril(m2sciUnknownType([i]),2);
% TEST 129
res129 = tril(m2sciUnknownType([i,2i,3i]),2);
% TEST 130
res130 = tril(m2sciUnknownType([i;2i;3i]),2);
% TEST 131
res131 = tril(m2sciUnknownType([i,2i,3i;4i,5i,6i]),2);
% TEST 132
res132 = tril(m2sciUnknownDims([i]),2);
% TEST 133
res133 = tril(m2sciUnknownDims([i,2i,3i]),2);
% TEST 134
res134 = tril(m2sciUnknownDims([i;2i;3i]),2);
% TEST 135
res135 = tril(m2sciUnknownDims([i,2i,3i;4i,5i,6i]),2);
% TEST 136
res136 = tril(['s'],2);
% TEST 137
res137 = tril(['str1'],2);
% TEST 138
res138 = tril(['str1','str2','str3'],2);
% TEST 139
res139 = tril(['str1';'str2';'str3'],2);
% TEST 140
res140 = tril(['str1','str2','str3';'str4','str5','str6'],2);
% TEST 141
res141 = tril(m2sciUnknownType(['s']),2);
% TEST 142
res142 = tril(m2sciUnknownType(['str1']),2);
% TEST 143
res143 = tril(m2sciUnknownType(['str1','str2','str3']),2);
% TEST 144
res144 = tril(m2sciUnknownType(['str1';'str2';'str3']),2);
% TEST 145
res145 = tril(m2sciUnknownType(['str1','str2','str3';'str4','str5','str6']),2);
% TEST 146
res146 = tril(m2sciUnknownDims(['s']),2);
% TEST 147
res147 = tril(m2sciUnknownDims(['str1']),2);
% TEST 148
res148 = tril(m2sciUnknownDims(['str1','str2','str3']),2);
% TEST 149
res149 = tril(m2sciUnknownDims(['str1';'str2';'str3']),2);
% TEST 150
res150 = tril(m2sciUnknownDims(['str1','str2','str3';'str4','str5','str6']),2);
% TEST 151
res151 = tril([[1]==[1]],2);
% TEST 152
res152 = tril([[1,2,3]==[1,0,3]],2);
% TEST 153
res153 = tril([[1;2;3]==[1;0;3]],2);
% TEST 154
res154 = tril([[1,2,3;4,5,6]==[1,0,3;4,5,0]],2);
% TEST 155
res155 = tril(m2sciUnknownType([[1]==[1]]),2);
% TEST 156
res156 = tril(m2sciUnknownType([[1,2,3]==[1,0,3]]),2);
% TEST 157
res157 = tril(m2sciUnknownType([[1;2;3]==[1;0;3]]),2);
% TEST 158
res158 = tril(m2sciUnknownType([[1,2,3;4,5,6]==[1,0,3;4,5,0]]),2);
% TEST 159
res159 = tril(m2sciUnknownDims([[1]==[1]]),2);
% TEST 160
res160 = tril(m2sciUnknownDims([[1,2,3]==[1,0,3]]),2);
% TEST 161
res161 = tril(m2sciUnknownDims([[1;2;3]==[1;0;3]]),2);
% TEST 162
res162 = tril(m2sciUnknownDims([[1,2,3;4,5,6]==[1,0,3;4,5,0]]),2);
% TEST 163
res163 = tril([],10);
% TEST 164
res164 = tril(m2sciUnknownType([]),10);
% TEST 165
res165 = tril(m2sciUnknownDims([]),10);
% TEST 166
res166 = tril([1],10);
% TEST 167
res167 = tril([1,2,3],10);
% TEST 168
res168 = tril([1;2;3],10);
% TEST 169
res169 = tril([1,2,3;4,5,6],10);
% TEST 170
res170 = tril(m2sciUnknownType([1]),10);
% TEST 171
res171 = tril(m2sciUnknownType([1,2,3]),10);
% TEST 172
res172 = tril(m2sciUnknownType([1;2;3]),10);
% TEST 173
res173 = tril(m2sciUnknownType([1,2,3;4,5,6]),10);
% TEST 174
res174 = tril(m2sciUnknownDims([1]),10);
% TEST 175
res175 = tril(m2sciUnknownDims([1,2,3]),10);
% TEST 176
res176 = tril(m2sciUnknownDims([1;2;3]),10);
% TEST 177
res177 = tril(m2sciUnknownDims([1,2,3;4,5,6]),10);
% TEST 178
res178 = tril([i],10);
% TEST 179
res179 = tril([i,2i,3i],10);
% TEST 180
res180 = tril([i;2i;3i],10);
% TEST 181
res181 = tril([i,2i,3i;4i,5i,6i],10);
% TEST 182
res182 = tril(m2sciUnknownType([i]),10);
% TEST 183
res183 = tril(m2sciUnknownType([i,2i,3i]),10);
% TEST 184
res184 = tril(m2sciUnknownType([i;2i;3i]),10);
% TEST 185
res185 = tril(m2sciUnknownType([i,2i,3i;4i,5i,6i]),10);
% TEST 186
res186 = tril(m2sciUnknownDims([i]),10);
% TEST 187
res187 = tril(m2sciUnknownDims([i,2i,3i]),10);
% TEST 188
res188 = tril(m2sciUnknownDims([i;2i;3i]),10);
% TEST 189
res189 = tril(m2sciUnknownDims([i,2i,3i;4i,5i,6i]),10);
% TEST 190
res190 = tril(['s'],10);
% TEST 191
res191 = tril(['str1'],10);
% TEST 192
res192 = tril(['str1','str2','str3'],10);
% TEST 193
res193 = tril(['str1';'str2';'str3'],10);
% TEST 194
res194 = tril(['str1','str2','str3';'str4','str5','str6'],10);
% TEST 195
res195 = tril(m2sciUnknownType(['s']),10);
% TEST 196
res196 = tril(m2sciUnknownType(['str1']),10);
% TEST 197
res197 = tril(m2sciUnknownType(['str1','str2','str3']),10);
% TEST 198
res198 = tril(m2sciUnknownType(['str1';'str2';'str3']),10);
% TEST 199
res199 = tril(m2sciUnknownType(['str1','str2','str3';'str4','str5','str6']),10);
% TEST 200
res200 = tril(m2sciUnknownDims(['s']),10);
% TEST 201
res201 = tril(m2sciUnknownDims(['str1']),10);
% TEST 202
res202 = tril(m2sciUnknownDims(['str1','str2','str3']),10);
% TEST 203
res203 = tril(m2sciUnknownDims(['str1';'str2';'str3']),10);
% TEST 204
res204 = tril(m2sciUnknownDims(['str1','str2','str3';'str4','str5','str6']),10);
% TEST 205
res205 = tril([[1]==[1]],10);
% TEST 206
res206 = tril([[1,2,3]==[1,0,3]],10);
% TEST 207
res207 = tril([[1;2;3]==[1;0;3]],10);
% TEST 208
res208 = tril([[1,2,3;4,5,6]==[1,0,3;4,5,0]],10);
% TEST 209
res209 = tril(m2sciUnknownType([[1]==[1]]),10);
% TEST 210
res210 = tril(m2sciUnknownType([[1,2,3]==[1,0,3]]),10);
% TEST 211
res211 = tril(m2sciUnknownType([[1;2;3]==[1;0;3]]),10);
% TEST 212
res212 = tril(m2sciUnknownType([[1,2,3;4,5,6]==[1,0,3;4,5,0]]),10);
% TEST 213
res213 = tril(m2sciUnknownDims([[1]==[1]]),10);
% TEST 214
res214 = tril(m2sciUnknownDims([[1,2,3]==[1,0,3]]),10);
% TEST 215
res215 = tril(m2sciUnknownDims([[1;2;3]==[1;0;3]]),10);
% TEST 216
res216 = tril(m2sciUnknownDims([[1,2,3;4,5,6]==[1,0,3;4,5,0]]),10);
% TEST 217
res217 = tril([],'a');
% TEST 218
res218 = tril(m2sciUnknownType([]),'a');
% TEST 219
res219 = tril(m2sciUnknownDims([]),'a');
% TEST 220
res220 = tril([1],'a');
% TEST 221
res221 = tril([1,2,3],'a');
% TEST 222
res222 = tril([1;2;3],'a');
% TEST 223
res223 = tril([1,2,3;4,5,6],'a');
% TEST 224
res224 = tril(m2sciUnknownType([1]),'a');
% TEST 225
res225 = tril(m2sciUnknownType([1,2,3]),'a');
% TEST 226
res226 = tril(m2sciUnknownType([1;2;3]),'a');
% TEST 227
res227 = tril(m2sciUnknownType([1,2,3;4,5,6]),'a');
% TEST 228
res228 = tril(m2sciUnknownDims([1]),'a');
% TEST 229
res229 = tril(m2sciUnknownDims([1,2,3]),'a');
% TEST 230
res230 = tril(m2sciUnknownDims([1;2;3]),'a');
% TEST 231
res231 = tril(m2sciUnknownDims([1,2,3;4,5,6]),'a');
% TEST 232
res232 = tril([i],'a');
% TEST 233
res233 = tril([i,2i,3i],'a');
% TEST 234
res234 = tril([i;2i;3i],'a');
% TEST 235
res235 = tril([i,2i,3i;4i,5i,6i],'a');
% TEST 236
res236 = tril(m2sciUnknownType([i]),'a');
% TEST 237
res237 = tril(m2sciUnknownType([i,2i,3i]),'a');
% TEST 238
res238 = tril(m2sciUnknownType([i;2i;3i]),'a');
% TEST 239
res239 = tril(m2sciUnknownType([i,2i,3i;4i,5i,6i]),'a');
% TEST 240
res240 = tril(m2sciUnknownDims([i]),'a');
% TEST 241
res241 = tril(m2sciUnknownDims([i,2i,3i]),'a');
% TEST 242
res242 = tril(m2sciUnknownDims([i;2i;3i]),'a');
% TEST 243
res243 = tril(m2sciUnknownDims([i,2i,3i;4i,5i,6i]),'a');
% TEST 244
res244 = tril(['s'],'a');
% TEST 245
res245 = tril(['str1'],'a');
% TEST 246
res246 = tril(['str1','str2','str3'],'a');
% TEST 247
res247 = tril(['str1';'str2';'str3'],'a');
% TEST 248
res248 = tril(['str1','str2','str3';'str4','str5','str6'],'a');
% TEST 249
res249 = tril(m2sciUnknownType(['s']),'a');
% TEST 250
res250 = tril(m2sciUnknownType(['str1']),'a');
% TEST 251
res251 = tril(m2sciUnknownType(['str1','str2','str3']),'a');
% TEST 252
res252 = tril(m2sciUnknownType(['str1';'str2';'str3']),'a');
% TEST 253
res253 = tril(m2sciUnknownType(['str1','str2','str3';'str4','str5','str6']),'a');
% TEST 254
res254 = tril(m2sciUnknownDims(['s']),'a');
% TEST 255
res255 = tril(m2sciUnknownDims(['str1']),'a');
% TEST 256
res256 = tril(m2sciUnknownDims(['str1','str2','str3']),'a');
% TEST 257
res257 = tril(m2sciUnknownDims(['str1';'str2';'str3']),'a');
% TEST 258
res258 = tril(m2sciUnknownDims(['str1','str2','str3';'str4','str5','str6']),'a');
% TEST 259
res259 = tril([[1]==[1]],'a');
% TEST 260
res260 = tril([[1,2,3]==[1,0,3]],'a');
% TEST 261
res261 = tril([[1;2;3]==[1;0;3]],'a');
% TEST 262
res262 = tril([[1,2,3;4,5,6]==[1,0,3;4,5,0]],'a');
% TEST 263
res263 = tril(m2sciUnknownType([[1]==[1]]),'a');
% TEST 264
res264 = tril(m2sciUnknownType([[1,2,3]==[1,0,3]]),'a');
% TEST 265
res265 = tril(m2sciUnknownType([[1;2;3]==[1;0;3]]),'a');
% TEST 266
res266 = tril(m2sciUnknownType([[1,2,3;4,5,6]==[1,0,3;4,5,0]]),'a');
% TEST 267
res267 = tril(m2sciUnknownDims([[1]==[1]]),'a');
% TEST 268
res268 = tril(m2sciUnknownDims([[1,2,3]==[1,0,3]]),'a');
% TEST 269
res269 = tril(m2sciUnknownDims([[1;2;3]==[1;0;3]]),'a');
% TEST 270
res270 = tril(m2sciUnknownDims([[1,2,3;4,5,6]==[1,0,3;4,5,0]]),'a');
