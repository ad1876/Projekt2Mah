/*
 * test_Regulator.c
 *
 * Created: 2017-05-11 00:58:16
 *  Author: zoz
 */ 
#include <asf.h>
#include "../unity/unity.h"
#include "CalculateAngle.h"
#include "test_CalculateAngle.h"

void test_getX_diff(void){
	TEST_ASSERT_FALSE(getX_diff(2,5));
}