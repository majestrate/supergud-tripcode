#include "supergud.h"
#include <stdio.h>

int main(int argc, char * argv[])
{
    if (argc == 2) {
	printf("%s -> %s\n", argv[1], supergud_hash(argv[1], "I_BET_THE_JEWS_DID_THIS"));
    }
}
