char* getbufferdata (char* buffername,char* offset)
{  
static char buffernamee[1000];
strncpy(buffernamee, buffername, 1000);
static char offsett[1000];
strncpy(offsett, offset, 1000);
static char convbuf[1000];
if (strcmp(buffernamee,"bandsmovingbuffer")==0) { sprintf(convbuf,"%f",bandsmovingbuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"bandsupperbuffer")==0) { sprintf(convbuf,"%f",bandsupperbuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"bandslowerbuffer")==0) { sprintf(convbuf,"%f",bandslowerbuffer[atoi(offsett)]);return convbuf; } 
if (strcmp(buffernamee,"mabuffer")==0) { sprintf(convbuf,"%f",mabuffer[atoi(offsett)]);return convbuf; }                                                
if (strcmp(buffernamee,"upperbandbuffer")==0) { sprintf(convbuf,"%f",upperbandbuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"lowerbandbuffer")==0) { sprintf(convbuf,"%f",lowerbandbuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"zigzagbuffer")==0) { sprintf(convbuf,"%f",zigzagbuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"fx")==0) { sprintf(convbuf,"%f",fx[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"sqh")==0) { sprintf(convbuf,"%f",sqh[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"sql")==0) { sprintf(convbuf,"%f",sql[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"stdh")==0) { sprintf(convbuf,"%f",stdh[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"stdl")==0) { sprintf(convbuf,"%f",stdl[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"ADR112cppbuffer1")==0) { sprintf(convbuf,"%f",ADR112cppbuffer1[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"ADR112cppbuffer2")==0) { sprintf(convbuf,"%f",ADR112cppbuffer2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"ADR112cppbuffer3")==0) { sprintf(convbuf,"%f",ADR112cppbuffer3[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"ADR112cppbuffer4")==0) { sprintf(convbuf,"%f",ADR112cppbuffer4[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"ADR112cppbuffer5")==0) { sprintf(convbuf,"%f",ADR112cppbuffer5[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"TimeFrame1Level")==0) { sprintf(convbuf,"%f",TimeFrame1Level[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"TimeFrame2Level")==0) { sprintf(convbuf,"%f",TimeFrame2Level[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"SellPrice")==0) { sprintf(convbuf,"%f",SellPrice[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"BuyPrice")==0) { sprintf(convbuf,"%f",BuyPrice[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"TimeFrame2AverageMA1")==0) { sprintf(convbuf,"%f",TimeFrame2AverageMA1[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"TimeFrame2AverageMA2")==0) { sprintf(convbuf,"%f",TimeFrame2AverageMA2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"TimeFrame2AverageMA3")==0) { sprintf(convbuf,"%f",TimeFrame2AverageMA3[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"TimeFrame2AverageMA4")==0) { sprintf(convbuf,"%f",TimeFrame2AverageMA4[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"dinfibohighbuffer1")==0) { sprintf(convbuf,"%f",dinfibohighbuffer1[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"dinfibohighbuffer2")==0) { sprintf(convbuf,"%f",dinfibohighbuffer2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"tvBuffer")==0) { sprintf(convbuf,"%f",tvBuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"PBuffer")==0) { sprintf(convbuf,"%f",PBuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"S1Buffer")==0) { sprintf(convbuf,"%f",S1Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"R1Buffer")==0) { sprintf(convbuf,"%f",R1Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"S2Buffer")==0) { sprintf(convbuf,"%f",S2Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"R2Buffer")==0) { sprintf(convbuf,"%f",R2Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"S3Buffer")==0) { sprintf(convbuf,"%f",S3Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"R3Buffer")==0) { sprintf(convbuf,"%f",R3Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"RSTLbuffer")==0) { sprintf(convbuf,"%f",RSTLbuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"fx2")==0) { sprintf(convbuf,"%f",fx2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"sqh2")==0) { sprintf(convbuf,"%f",sqh2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"sql2")==0) { sprintf(convbuf,"%f",sql2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"stdh2")==0) { sprintf(convbuf,"%f",stdh2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"stdl2")==0) { sprintf(convbuf,"%f",stdl2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"sopr1")==0) { sprintf(convbuf,"%f",sopr1[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"sopr2")==0) { sprintf(convbuf,"%f",sopr2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"sopr3")==0) { sprintf(convbuf,"%f",sopr3[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"sopr4")==0) { sprintf(convbuf,"%f",sopr4[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"sopr5")==0) { sprintf(convbuf,"%f",sopr5[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"pod1")==0) { sprintf(convbuf,"%f",pod1[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"pod2")==0) { sprintf(convbuf,"%f",pod2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"pod3")==0) { sprintf(convbuf,"%f",pod3[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"pod4")==0) { sprintf(convbuf,"%f",pod4[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"pod5")==0) { sprintf(convbuf,"%f",pod5[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"pivot")==0) { sprintf(convbuf,"%f",pivot[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"r1")==0) { sprintf(convbuf,"%f",r1[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"r2")==0) { sprintf(convbuf,"%f",r2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"r3")==0) { sprintf(convbuf,"%f",r3[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"s1")==0) { sprintf(convbuf,"%f",s1[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"s2")==0) { sprintf(convbuf,"%f",s2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"s3")==0) { sprintf(convbuf,"%f",s3[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"ExtBuffer0")==0) { sprintf(convbuf,"%f",ExtBuffer0[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"ExtBuffer1")==0) { sprintf(convbuf,"%f",ExtBuffer1[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"ExtBuffer2")==0) { sprintf(convbuf,"%f",ExtBuffer2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"volatilitystopBuffer1")==0) { sprintf(convbuf,"%f",volatilitystopBuffer1[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"volatilitystopBuffer2")==0) { sprintf(convbuf,"%f",volatilitystopBuffer2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Ehlersfishertransformbuffer1")==0) { sprintf(convbuf,"%f",Ehlersfishertransformbuffer1[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"eftbandsmovingbuffer")==0) { sprintf(convbuf,"%f",eftbandsmovingbuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"eftbandsupperbuffer")==0) { sprintf(convbuf,"%f",eftbandsupperbuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"eftbandslowerbuffer")==0) { sprintf(convbuf,"%f",eftbandslowerbuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"MA_Chanels_FiboEnv_Midbuffer1")==0) { sprintf(convbuf,"%f",MA_Chanels_FiboEnv_Midbuffer1[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"MA_Chanels_FiboEnv_Midbuffer2")==0) { sprintf(convbuf,"%f",MA_Chanels_FiboEnv_Midbuffer2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"MA_Chanels_FiboEnv_Midbuffer3")==0) { sprintf(convbuf,"%f",MA_Chanels_FiboEnv_Midbuffer3[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"MA_Chanels_FiboEnv_Midbuffer4")==0) { sprintf(convbuf,"%f",MA_Chanels_FiboEnv_Midbuffer4[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"MA_Chanels_FiboEnv_Midbuffer5")==0) { sprintf(convbuf,"%f",MA_Chanels_FiboEnv_Midbuffer5[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"MA_Chanels_FiboEnv_Midbuffer6")==0) { sprintf(convbuf,"%f",MA_Chanels_FiboEnv_Midbuffer6[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"MA_Chanels_FiboEnv_Midbuffer7")==0) { sprintf(convbuf,"%f",MA_Chanels_FiboEnv_Midbuffer7[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"sig1n")==0) { sprintf(convbuf,"%f",sig1n[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"sig2n")==0) { sprintf(convbuf,"%f",sig2n[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Line1Buffer")==0) { sprintf(convbuf,"%f",Line1Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Line2Buffer")==0) { sprintf(convbuf,"%f",Line2Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Line3Buffer")==0) { sprintf(convbuf,"%f",Line3Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"steplevelup")==0) { sprintf(convbuf,"%f",steplevelup[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"stepleveldn")==0) { sprintf(convbuf,"%f",stepleveldn[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"spectrometerbuffer1")==0) { sprintf(convbuf,"%f",spectrometerbuffer1[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"spectrometerbuffer2")==0) { sprintf(convbuf,"%f",spectrometerbuffer2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"spectrometerbuffer3")==0) { sprintf(convbuf,"%f",spectrometerbuffer3[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"spectrometerbuffer4")==0) { sprintf(convbuf,"%f",spectrometerbuffer4[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"spectrometerbuffer5")==0) { sprintf(convbuf,"%f",spectrometerbuffer5[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"spectrometerbuffer6")==0) { sprintf(convbuf,"%f",spectrometerbuffer6[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"spectrometerbuffer7")==0) { sprintf(convbuf,"%f",spectrometerbuffer7[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"spectrometerbuffer8")==0) { sprintf(convbuf,"%f",spectrometerbuffer8[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"dbp")==0) { sprintf(convbuf,"%f",dbp[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"dbph")==0) { sprintf(convbuf,"%f",dbph[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"dbpl")==0) { sprintf(convbuf,"%f",dbpl[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Murrey_Mathbuffer1")==0) { sprintf(convbuf,"%f",Murrey_Mathbuffer1[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Murrey_Mathbuffer2")==0) { sprintf(convbuf,"%f",Murrey_Mathbuffer2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Murrey_Mathbuffer3")==0) { sprintf(convbuf,"%f",Murrey_Mathbuffer3[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Murrey_Mathbuffer4")==0) { sprintf(convbuf,"%f",Murrey_Mathbuffer4[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Murrey_Mathbuffer5")==0) { sprintf(convbuf,"%f",Murrey_Mathbuffer5[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Murrey_Mathbuffer6")==0) { sprintf(convbuf,"%f",Murrey_Mathbuffer6[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Murrey_Mathbuffer7")==0) { sprintf(convbuf,"%f",Murrey_Mathbuffer7[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Murrey_Mathbuffer8")==0) { sprintf(convbuf,"%f",Murrey_Mathbuffer8[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Murrey_Mathbuffer9")==0) { sprintf(convbuf,"%f",Murrey_Mathbuffer9[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Murrey_Mathbuffer10")==0) { sprintf(convbuf,"%f",Murrey_Mathbuffer10[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Murrey_Mathbuffer11")==0) { sprintf(convbuf,"%f",Murrey_Mathbuffer11[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Murrey_Mathbuffer12")==0) { sprintf(convbuf,"%f",Murrey_Mathbuffer12[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Murrey_Mathbuffer13")==0) { sprintf(convbuf,"%f",Murrey_Mathbuffer13[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"CoronaSwingPositionbuffer")==0) { sprintf(convbuf,"%f",CoronaSwingPositionbuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Tenkan_Buffer")==0) { sprintf(convbuf,"%f",Tenkan_Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Kijun_Buffer")==0) { sprintf(convbuf,"%f",Kijun_Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"SpanA_Buffer")==0) { sprintf(convbuf,"%f",SpanA_Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"SpanB_Buffer")==0) { sprintf(convbuf,"%f",SpanB_Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"Chinkou_Buffer")==0) { sprintf(convbuf,"%f",Chinkou_Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"SpanA2_Buffer")==0) { sprintf(convbuf,"%f",SpanA2_Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"SpanB2_Buffer")==0) { sprintf(convbuf,"%f",SpanB2_Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"FP_BuferUp")==0) { sprintf(convbuf,"%f",FP_BuferUp[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"FP_BuferDn")==0) { sprintf(convbuf,"%f",FP_BuferDn[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"NP_BuferUp")==0) { sprintf(convbuf,"%f",NP_BuferUp[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"NP_BuferDn")==0) { sprintf(convbuf,"%f",NP_BuferDn[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"HP_BuferUp")==0) { sprintf(convbuf,"%f",HP_BuferUp[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"HP_BuferDn")==0) { sprintf(convbuf,"%f",HP_BuferDn[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"RBCIbuffer")==0) { sprintf(convbuf,"%f",RBCIbuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"TSCDbuffer")==0) { sprintf(convbuf,"%f",TSCDbuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"tmBuffer")==0) { sprintf(convbuf,"%f",tmBuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"upBuffer")==0) { sprintf(convbuf,"%f",upBuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"dnBuffer")==0) { sprintf(convbuf,"%f",dnBuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"MACDLineBuffer")==0) { sprintf(convbuf,"%f",MACDLineBuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"SignalLineBuffer")==0) { sprintf(convbuf,"%f",SignalLineBuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"HistogramBuffer")==0) { sprintf(convbuf,"%f",HistogramBuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"WCCIExtMapBuffer1")==0) { sprintf(convbuf,"%f",WCCIExtMapBuffer1[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"WCCIExtMapBuffer2")==0) { sprintf(convbuf,"%f",WCCIExtMapBuffer2[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"WCCIExtMapBuffer3")==0) { sprintf(convbuf,"%f",WCCIExtMapBuffer3[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"WCCIExtMapBuffer4")==0) { sprintf(convbuf,"%f",WCCIExtMapBuffer4[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"WCCIExtMapBuffer5")==0) { sprintf(convbuf,"%f",WCCIExtMapBuffer5[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"WCCIExtMapBuffer6")==0) { sprintf(convbuf,"%f",WCCIExtMapBuffer6[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"WCCIExtMapBuffer7")==0) { sprintf(convbuf,"%f",WCCIExtMapBuffer7[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"WCCIExtMapBuffer8")==0) { sprintf(convbuf,"%f",WCCIExtMapBuffer8[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"prd_high2Buffer")==0) { sprintf(convbuf,"%f",prd_high2Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"prd_low2Buffer")==0) { sprintf(convbuf,"%f",prd_low2Buffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"MainBuffer")==0) { sprintf(convbuf,"%f",MainBuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"SignalBuffer")==0) { sprintf(convbuf,"%f",SignalBuffer[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"stochup")==0) { sprintf(convbuf,"%f",stochup[atoi(offsett)]);return convbuf; }
if (strcmp(buffernamee,"stochdn")==0) { sprintf(convbuf,"%f",stochdn[atoi(offsett)]);return convbuf; }
return 0;
}
