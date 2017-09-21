#include <stdio.h>

static inline void native_cpuid(unsigned int *eax, unsigned int *ebx,
				unsigned int *ecx, unsigned int *edx)
{
	/* ecx is often an input as well as an output. */
	asm volatile("cpuid"
	    : "=a" (*eax),
	      "=b" (*ebx),
	      "=c" (*ecx),
	      "=d" (*edx)
	    : "0" (*eax), "2" (*ecx)
	    : "memory");
}

int main(int argc, char **argv) 
{
    unsigned eax, ebx, ecx, edx;

    eax = 0x1; /* processor info and feature bits */
    native_cpuid(&eax, &ebx, &ecx, &edx);

    printf("stepping %d\n", eax & 0xF);
    printf("model %d\n", (eax >> 4) & 0xF);
    printf("family %d\n", (eax >> 8) & 0xF);
    printf("processor type %d\n", (eax >> 12) & 0x3);
    printf("extended model %d\n", (eax >> 16) & 0xF);
    printf("extended family %d\n", (eax >> 20) & 0xFF);

    eax = 0x3; /* processor serial number */
    native_cpuid(&eax, &ebx, &ecx, &edx);

    printf("serial number 0x%08x%08x\n", edx, ecx);

    return 0;
}
