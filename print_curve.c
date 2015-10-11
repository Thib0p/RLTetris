#include "learning_curve.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
static FILE*  file;

int main(int argc, char *argv[])
{
	file = fopen("lc_agent_clever_learning_curve.txt","w");
	learning_curve_plot();
	return 0;
}