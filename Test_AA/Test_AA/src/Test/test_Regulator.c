/*
 * test_Regulator.c
 *
 * Created: 2017-05-11 00:58:16
 *  Author: zoz
 */ 
#include <asf.h>
#include "../unity/unity.h"
#include "Regulator.h"
#include "test_Regulator.h"
extern int b, u;
void test_P_Regulator(void){
	TEST_ASSERT_FALSE(P_regulator(2,2));
	
}