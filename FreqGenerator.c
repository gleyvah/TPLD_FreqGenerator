//TPLD frequency generator
//version 0.1
/************************************************************************************
This algorithm calculates the settings of a counter to generate the target frequency
1201 - 801
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    // ----- Frequency defined by user --------------------------------
    unsigned int OSC_FREQ = 25000; 
    float TARGET_FREQ = 6.25;
    // ----------------------------------------------------------------
    

    bool exactFreqFound = false;
    unsigned int CntPreDiv, OscPreDiv;
    int CntPrediv_Array[] = {1,4,12,24, 64,4096};
    int CntArray_length = sizeof(CntPrediv_Array) / sizeof(CntPrediv_Array[0]);
    
    int OscPrediv_Array[] = {1,2,4,8};
    int OscArray_length = sizeof(OscPrediv_Array) / sizeof(OscPrediv_Array[0]);
    

    unsigned int delta_freq, previous_delta_freq;
    unsigned int pre_CntPreDiv,  pre_OscPreDiv, pre_j, pre_k;
    float FREQ;
    float nearest_freq, bestFreq;

    nearest_freq= OSC_FREQ;
    previous_delta_freq = OSC_FREQ;
    
    int j, k;
    printf("Calculating frequency dividers\n");

    for(int a = 0; a < CntArray_length; a++) {
       CntPreDiv=  CntPrediv_Array[a];
    //for (int i=1; i<255; i++){
        for(int j = 0; j < OscArray_length; j++) {
           OscPreDiv=  OscPrediv_Array[j];
        //for (j=1; j<255; j++){
            for (k=1; k<255; k++){
                FREQ = TARGET_FREQ * CntPreDiv * OscPreDiv * k;
                if (FREQ == OSC_FREQ){
                    exactFreqFound = true;
                    printf("SETTINGS --> OSC PRE_DIV= %d, CNT PRE_DIV= %d, CNT VALUE= %d\n", OscPreDiv ,CntPreDiv , k);
                }
                else{
                    if (!exactFreqFound){
                        delta_freq = abs(FREQ - OSC_FREQ);
                        if (delta_freq < previous_delta_freq){
                            nearest_freq = FREQ;
                            previous_delta_freq = delta_freq;
                            pre_CntPreDiv = CntPreDiv;
                            pre_OscPreDiv = OscPreDiv;
                            //pre_j= j;
                            pre_k= k;
                            //printf("Nearest = %f --> Delta %d --> multiples = %d %d %d \n" ,nearest_freq, delta_freq ,CntPreDiv , OscPreDiv, k);   
                        }
                    }

                }
            }
        }
    }
    //printf("Nearest = %f \n" ,nearest_freq);
    if (!exactFreqFound){
        bestFreq= (float)OSC_FREQ / (pre_CntPreDiv *pre_OscPreDiv* pre_k) ;
        printf("OSC FREQ = %d --> Best Freq Gotten %.3f --> SETTINGS --> OSC PRE_DIV= %d, CNT PRE_DIV= %d, CNT VALUE= %d \n" ,OSC_FREQ, bestFreq ,pre_OscPreDiv, pre_CntPreDiv , pre_k);   
    }
    printf("Done\n");
        

    return 0;
}
