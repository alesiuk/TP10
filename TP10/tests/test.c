/*
 * File:   test.c
 * Author: alito
 *
 * Created on May 21, 2020, 4:12:06 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "puertos.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

int Toggle(int bit);

void testToggle() {
    int bit;
    int result = Toggle(bit);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testBitSet() {
    char puerto;
    int bit;
    BitSet(puerto, bit);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testBitClr() {
    char puerto;
    int bit;
    BitClr(puerto, bit);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testBitGet() {
    char puerto;
    int bit;
    int result = BitGet(puerto, bit);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testBitToggle() {
    char puerto;
    int bit;
    BitToggle(puerto, bit);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testMaskOn() {
    char puerto;
    int mascara;
    MaskOn(puerto, mascara);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testMaskOff() {
    char puerto;
    int mascara;
    MaskOff(puerto, mascara);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testMaskToggle() {
    char puerto;
    int mascara;
    MaskToggle(puerto, mascara);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testToggle", testToggle)) ||
            (NULL == CU_add_test(pSuite, "testBitSet", testBitSet)) ||
            (NULL == CU_add_test(pSuite, "testBitClr", testBitClr)) ||
            (NULL == CU_add_test(pSuite, "testBitGet", testBitGet)) ||
            (NULL == CU_add_test(pSuite, "testBitToggle", testBitToggle)) ||
            (NULL == CU_add_test(pSuite, "testMaskOn", testMaskOn)) ||
            (NULL == CU_add_test(pSuite, "testMaskOff", testMaskOff)) ||
            (NULL == CU_add_test(pSuite, "testMaskToggle", testMaskToggle))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
