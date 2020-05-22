/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   tests.c
 * Author: Salta
 *
 * Created on May 21, 2020, 4:24 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "puertos.h"

/*
 * Simple C Test Suite
 */

int testfail;
int testpass;
int testfailglo = 0;
int testpassglo = 0;

void BitSet(char puerto, int bit)
{
    testfail = 0;
    testpass = 0;
    
    switch (puerto)
    {
        case 'D':
        case 'd':
            if (bit == 1 && registro.bits.b1 == 1)
            {
                testpass++;
                testpassglo++;
            }
            if(bit == 10 && registro.bits.b10 == 1)
            {
                testpass++;
                testpassglo++;
            }
            else
            {
                testfail++;
                testfailglo++;
            }
            break;
            
        case 'a':    
        case 'A':
             if (bit == 9 && registro.bits.b9 == 1)
            {
                testpass++;
                testpassglo++;
            }
            else
            {
                testfail++;
                testfailglo++;
            }
             break;
        
        case 'b':
        case 'B':
         if (bit == 4 && registro.bits.b4 == 1)
            {
                testpass++;
                testpassglo++;
            }
            else
            {
                testfail++;
                testfailglo++;
            }
         break;
    }
    if(testfail != 0)
    {
        printf("%%TEST_FAILED%% time=0 testname=testBitClr (tests) message=error message sample\n");
    }
    printf("TEST PASS BITCLR = %d TEST FAIL BITCLR = %d", testpass,testfail);
}

void testBitClr(char puerto, int bit) 
{
    BitClr(puerto, bit);
    
    switch (puerto)
    {
        case 'D':
        case 'd':
            if (bit == 0 && registro.bits.b0 == 0)
            {
                testpass++;
                testpassglo++;
            }
            if(bit == 15 && registro.bits.b15 == 0)
            {
                testpass++;
            }
            else
            {
                testfail++;
                testfailglo++;
            }
            break;
            
        case 'a':    
        case 'A':
             if (bit == 10 && registro.bits.b10 == 0)
            {
                testpass++;
            }
            else
            {
                testfail++;
                testfailglo++;
            }
             break;
        
        case 'b':
        case 'B':
         if (bit == 1 && registro.bits.b1 == 0)
            {
                testpass++;
            }
            else
            {
                testfail++;
                testfailglo++;
            }
         break;
    }
    if(testfail != 0)
    {
        printf("%%TEST_FAILED%% time=0 testname=testBitClr (tests) message=error message sample\n");
    }
    printf("TEST PASS BITCLR = %d TEST FAIL BITCLR = %d", testpass,testfail);
}

void testBitGet(char puerto, int bit) 
{
    testfail = 0;
    testpass = 0;
    BitClr(puerto, bit);
    BitSet(puerto, bit);
    int result = BitGet(puerto, bit);
    if(result == 1)
    {
        testpass++;
        testpassglo++;
    }
    else
    {
        testfail++;
        testfailglobal++;
        printf("%%TEST_FAILED%% time=0 testname=testBitGet (tests) message=error message sample\n");
    }
    printf("TEST PASS BITGET = %d TEST FAIL BITGET= %d", testpass, testfail);
}

void testBitToggle() {
    char puerto;
    int bit;
    BitToggle(puerto, bit);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testBitToggle (tests) message=error message sample\n");
    }
}

void testMaskOn() {
    testfail = 0;
    testpass = 0;
    char puertoD, puertoA,puertoB;
    registro.portD.Word==0xAAAA;				//1010 1010 1010 1010
    int mascara=0x5555;						//0101 0101 0101 0101
    testfail = 0;
    testpass = 0;
    MaskOn(puertoD, mascara); 
    if((registro.portD.word)==(0xFFFF))
    {
	testpass++;
	testpassglo++;
    }
    else 
    {
	testfail++;
	testfailglo++;
    }
    registro.portD.Word==0xAAAA;
    mascara=0x55;							//0101 0101 0000 0000
    MaskOn(puertoA,mascara);
    if((registro.portA.high==0xFF) && (registro.portD.word==0xFFAA))
    {
	testpass++;
	testpassglo++;
    } 
    else
    {
	testfail++;
	testfailglo++;	
    }
    registro.portD.Word==0xAAAA;
    MaskOn(puertoB,mascara);
    if((registro.portB.low=0xFF) && (registro.portD.word==0xAAFF))
    {
	testpass++;
	testpastglo++;
    }
    else
    {
	testfail++;
	testfailglo++;
    }
    if(testfail != 0)
    {
        printf("%%TEST_FAILED%% time=0 testname=testBitClr (tests) message=error message sample\n");
    }
    printf("TEST PASS BITCLR = %d TEST FAIL BITCLR = %d", testpass,testfail);
}

void testMaskOff() {
    testfail = 0;
    testpass = 0;
    char puertoA='A', puertoB ='B',puertoD='D';
    registro.portD.word=0xAAAA;								//1010 1010 1010 1010
    int mascara=0xAAAA;										//1010 1010 1010 1010
    MaskOff(puertoD,mascara);
    if(registro.portD.word==0x0000)
    {
	testpast++;
	testpastglo++;
    }
    else 
    {
	testfail++;
	testfailglo++;
    }
    registro.portD.word=0xAAAA;
    mascara=0xAA;									//1010 1010 0000 0000
    MaskOff(puertoA,mascara);
    if((registro.portA.high==0x00) && (registro.portD.word==0x00AA))
    {
	testpast++;
	testpastglo++;
    }
    else
    {
	testfail++;
	testfailglo++;
    }
    registro.portD.word=0xAAAA;
    MaskOff(puertoB,mascara);                                               	 //la  mascara que se le pasa es 0000 0000 1010 1010
    if((registro.portB.low==0x00) && (registro.portD.word==0xAA00))
    {
	testpast++;
	testpastglo++;
    }
    else
    {
	testfail++;
	testfailglo++;
    }
    if(testfail != 0)
    {
        printf("%%TEST_FAILED%% time=0 testname=testBitClr (tests) message=error message sample\n");
    }
    printf("TEST PASS BITCLR = %d TEST FAIL BITCLR = %d", testpass,testfail);
}

void testMaskToggle() {
    testfail = 0;
    testpass = 0;
    char puertoA='A',puertoB='B', puertoD='D';
    registro.portD.word=0xAAAA;
    int mascara=0x5555;
    MaskToggle(puertoD, mascara);
    if(registro.portD.word==0xFFFF)
    {
	testpast++;
	testpastglo++;
    }
    else
    {
	testfail++;
	testfailglo++;	
    }
    registro.portD.word=0xAAAA;
    MaskToggle(puertoA,mascara);
    if((registro.portA.high==0xFF) && (registro.portD.word==0xFFAA))
    {
	testpast++;
	testpastglo++;
    }
    else
    {
	testfail++;
	testfailglo++;
    } 
    registro.portD.word=0xAAAA;
    MaskToggle(puertoB,mascara);
    if((registro.portB.low==0xFF) && (registro.portD.word==0xAAFF))
    {
	testpast++;
	testpastglo++;
    }
    else
    {
	testfail++;
	testfailglo++;
    } 
    if(testfail != 0)
    {
        printf("%%TEST_FAILED%% time=0 testname=testBitClr (tests) message=error message sample\n");
    }
    printf("TEST PASS BITCLR = %d TEST FAIL BITCLR = %d", testpass,testfail);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% tests\n");
    printf("%%SUITE_STARTED%%\n");

    

    printf("%%TEST_STARTED%%  testBitSet (tests)\n");
    testBitSet();
    printf("%%TEST_FINISHED%% time=0 testBitSet (tests)\n");

    printf("%%TEST_STARTED%%  testBitClr (tests)\n");
    testBitClr();
    printf("%%TEST_FINISHED%% time=0 testBitClr (tests)\n");

    printf("%%TEST_STARTED%%  testBitGet (tests)\n");
    testBitGet();
    printf("%%TEST_FINISHED%% time=0 testBitGet (tests)\n");

    printf("%%TEST_STARTED%%  testBitToggle (tests)\n");
    testBitToggle();
    printf("%%TEST_FINISHED%% time=0 testBitToggle (tests)\n");

    printf("%%TEST_STARTED%%  testMaskOn (tests)\n");
    testMaskOn();
    printf("%%TEST_FINISHED%% time=0 testMaskOn (tests)\n");

    printf("%%TEST_STARTED%%  testMaskOff (tests)\n");
    testMaskOff();
    printf("%%TEST_FINISHED%% time=0 testMaskOff (tests)\n");

    printf("%%TEST_STARTED%%  testMaskToggle (tests)\n");
    testMaskToggle();
    printf("%%TEST_FINISHED%% time=0 testMaskToggle (tests)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
