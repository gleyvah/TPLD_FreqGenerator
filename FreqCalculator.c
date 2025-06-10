//TPLD frequency generator
//version 0.2
/************************************************************************************
This algorithm calculates the settings of a counter to generate the target frequency
1201 - 801 - 1202 - 2001
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

    // ----- Parameters defined by user --------------------------------
    // DEV values can be 1201, 1202, 2001
#define DEV 1201
    
    // OSC number can be 0, 1, 2 depending of the device
#define OSC_NUM 0

    // User Target frequency (it could be float number)
#define TARGET_FREQ 5000
    // ----------------------------------------------------------------

 

// function to fullfill zeros in to array
int FillZeros(int* arr, int size)
{

    int sum = 0;
    // calculating cumulative sum of all the array elements
    for (int i = 0; i < size; i++) {
        arr[i] = 0;
    }

    // returning zero
    return 0;
}

int CopyArrays(int* SourceArray, int* DestArray, int size)
{


    // fullfill zeros in to array
    for (int i = 0; i < size; i++) {
        DestArray[i] = SourceArray[i];
    }

    // returning zero
    return 0;
}

int PrintArray(int* arr, int size)
{

    // printing array elements
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // returning zero
    return 0;
}





int main()
{

    // Freq must be aligned with the OSC Number choosen
    unsigned int OSC_FREQ = 0; 

    bool exactFreqFound = false;
    bool validParameters = true;
    unsigned int CntPreDiv, OscPreDiv;
    unsigned int OscArray_length, CntArray_length;


    int CntOSC0_div2001_Array[] = {1,8, 64, 512, 4096, 32768, 262144};
    int CntOSC0_div2001_Array_length = sizeof(CntOSC0_div2001_Array) / sizeof(CntOSC0_div2001_Array[0]);

    int CntOSC1_div2001_Array[] = {1,8, 64, 512};
    int CntOSC1_div2001_Array_length = sizeof(CntOSC1_div2001_Array) / sizeof(CntOSC1_div2001_Array[0]);

    int CntOSC2_div2001_Array[] = {1,4};
    int CntOSC2_div2001_Array_length = sizeof(CntOSC2_div2001_Array) / sizeof(CntOSC2_div2001_Array[0]);

    int CntOSC0_div1201_Array[] = {1,4,12,24, 64,4096};
    int CntOSC0_div1201_Array_length = sizeof(CntOSC0_div1201_Array) / sizeof(CntOSC0_div1201_Array[0]);

    int CntOSC0_div1202_Array[] = {1,8,12,24, 64, 512, 4096};
    int CntOSC0_div1202_Array_length = sizeof(CntOSC0_div1202_Array) / sizeof(CntOSC0_div1202_Array[0]);

    int CntOSC1_div1202_Array[] = {1,4,8, 64, 512};
    int CntOSC1_div1202_Array_length = sizeof(CntOSC1_div1202_Array) / sizeof(CntOSC1_div1202_Array[0]);
    
    int OscPrediv_type1_Array[] = {1,2,4,8};
    int OscArray1_length = sizeof(OscPrediv_type1_Array) / sizeof(OscPrediv_type1_Array[0]);
    
    int OscPrediv_type2_Array[] = {1,2,4,8, 12, 24, 48};
    int OscArray2_length = sizeof(OscPrediv_type2_Array) / sizeof(OscPrediv_type2_Array[0]);
    
    int OscPrediv_Array[] = {0,0,0,0,0,0,0,0};
    int OscPrediv_Array_length = sizeof(OscPrediv_Array) / sizeof(OscPrediv_Array[0]);

    int CntPrediv_Array[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int CntPrediv_Array_length = sizeof(CntPrediv_Array) / sizeof(CntPrediv_Array[0]);

    unsigned int delta_freq, previous_delta_freq;
    unsigned int pre_CntPreDiv,  pre_OscPreDiv, pre_j, pre_k;
    float FREQ;
    float nearest_freq, bestFreq;

    //preparing the general arrays before copy
    FillZeros(OscPrediv_Array, OscPrediv_Array_length);
    FillZeros(CntPrediv_Array, CntPrediv_Array_length);
    
    //choosing the arrays and their lenghts
    if (DEV == 2001 && OSC_NUM == 0){
        OSC_FREQ = 2000;
        // choosing OSC Divider array type 1
        OscArray_length= OscArray1_length;
        CopyArrays(OscPrediv_type1_Array, OscPrediv_Array, OscArray_length );
        
        //chossing CNT array
        CntArray_length= CntOSC0_div2001_Array_length;
        CopyArrays(CntOSC0_div2001_Array, CntPrediv_Array, CntArray_length );
    }
    
    else if (DEV == 2001 && OSC_NUM == 1){
        OSC_FREQ = 2000000;
        // choosing OSC Divider array type 2
        OscArray_length= OscArray1_length;
        CopyArrays(OscPrediv_type1_Array, OscPrediv_Array, OscArray_length );
        
        //chossing CNT array
        CntArray_length= CntOSC1_div2001_Array_length;
        CopyArrays(CntOSC1_div2001_Array, CntPrediv_Array, CntArray_length );
    }

    else if (DEV == 2001 && OSC_NUM == 2){
        OSC_FREQ = 25000000;
        // choosing OSC Divider array type 2
        OscArray_length= OscArray1_length;
        CopyArrays(OscPrediv_type1_Array, OscPrediv_Array, OscArray_length );
        
        //chossing CNT array
        CntArray_length= CntOSC2_div2001_Array_length;
        CopyArrays(CntOSC2_div2001_Array, CntPrediv_Array, CntArray_length );
    }

    else if (DEV == 1201 && OSC_NUM == 0){
        OSC_FREQ = 25000;
        // choosing OSC Divider array type 1
        OscArray_length= OscArray1_length;
        CopyArrays(OscPrediv_type1_Array, OscPrediv_Array, OscArray_length );
        
        //chossing CNT array
        CntArray_length= CntOSC0_div1201_Array_length;
        CopyArrays(CntOSC0_div1201_Array, CntPrediv_Array, CntArray_length );
    }
    
    else if (DEV == 1201 && OSC_NUM == 1){
        OSC_FREQ = 2000000;
        // choosing OSC Divider array type 2
        OscArray_length= OscArray1_length;
        CopyArrays(OscPrediv_type1_Array, OscPrediv_Array, OscArray_length );
        
        //chossing CNT array
        CntArray_length= CntOSC0_div1201_Array_length;
        CopyArrays(CntOSC0_div1201_Array, CntPrediv_Array, CntArray_length );
    }

    else if (DEV == 1202 && OSC_NUM == 0){
        OSC_FREQ = 10000;
        // choosing OSC Divider array type 1
        OscArray_length= OscArray1_length;
        CopyArrays(OscPrediv_type1_Array, OscPrediv_Array, OscArray_length );
        
        //chossing CNT array
        CntArray_length= CntOSC0_div1202_Array_length;
        CopyArrays(CntOSC0_div1202_Array, CntPrediv_Array, CntArray_length );
    }
    
    else if (DEV == 1202 && OSC_NUM == 1){
        OSC_FREQ = 25000000;
        // choosing OSC Divider array type 2
        OscArray_length= OscArray2_length;
        CopyArrays(OscPrediv_type2_Array, OscPrediv_Array, OscArray_length );
        
        //chossing CNT array
        CntArray_length= CntOSC1_div1202_Array_length;
        CopyArrays(CntOSC1_div1202_Array, CntPrediv_Array, CntArray_length );
    }
    else {
            printf("Device %d or OSC# %d not found\n" , DEV, OSC_NUM);
        // choosing OSC array type 1
        OscArray_length= OscArray1_length;
        //preparing the general arrays before copy
        FillZeros(OscPrediv_Array, OscArray_length);
        //update valud parameter variable
        validParameters = false;

    }

    nearest_freq= OSC_FREQ;
    previous_delta_freq = OSC_FREQ;
    
    
    if (validParameters) {
        printf("Device = TPLD%d \n" , DEV);
        printf("OSC Freq = %d \n" , OSC_FREQ);
        printf("OSC Pre-Div: ");
        PrintArray(OscPrediv_Array, OscPrediv_Array_length);
        printf("CNT Pre-Div: ");
        PrintArray(CntPrediv_Array, CntArray_length);
        
        int j, k;
        printf("Calculating frequency dividers\n");
    
        for(int a = 0; a < CntArray_length; a++) {
            //CntPreDiv=  CntOSC0_div1201_Array[a]; 
           CntPreDiv=  CntPrediv_Array[a];
        //for (int i=1; i<255; i++){
            for(int j = 0; j < OscArray_length; j++) {
               //OscPreDiv=  OscPrediv_type1_Array[j];
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
    
            
    } // close of validParameters check

    printf("Done!\n");
        

    return 0;
}
