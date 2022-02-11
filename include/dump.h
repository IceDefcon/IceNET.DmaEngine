#ifndef DUMP_H
#define DUMP_H

#include <inttypes.h>

extern "C" unsigned long _RAX(void);
extern "C" unsigned long _RBX(void);
extern "C" unsigned long _RCX(void);
extern "C" unsigned long _RDX(void);
extern "C" unsigned long _RSP(void);
extern "C" unsigned long _RBP(void);
extern "C" unsigned long _RSI(void);
extern "C" unsigned long _RDI(void);

extern "C" int _RSS(void);
extern "C" int _RCS(void);
extern "C" int _RDS(void);
extern "C" int _RES(void);
extern "C" int _RFS(void);
extern "C" int _RGS(void);

extern "C" int _EFLAGS(void);

extern "C" unsigned long _CPU_RAX(void);
extern "C" unsigned long _CPU_RBX(void);
extern "C" unsigned long _CPU_RCX(void);
extern "C" unsigned long _CPU_RDX(void);

void RegDump(void) { 

    printf("\nGeneral-Purpose Registers:\n"); 
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"); 
    printf("RAX_Accumulator         : %#018" PRIx64 " \n",_RAX());
    printf("RBX_Base                : %#018" PRIx64 " \n",_RBX());
    printf("RCX_Counter             : %#018" PRIx64 " \n",_RCX());
    printf("RDX_Data                : %#018" PRIx64 " \n",_RDX());
    printf("RSP_Stack_Pointer       : %#018" PRIx64 " \n",_RSP());
    printf("RBP_Base_Pointer        : %#018" PRIx64 " \n",_RBP());
    printf("RSI_Source_Index        : %#018" PRIx64 " \n",_RSI());
    printf("RDI_Destination_Index   : %#018" PRIx64 " \n",_RDI());

    printf("\nSegment Register:\n"); 
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"); 
    printf("SS_Stack_Segment        : 0x%02hhx \n",_RSS());
    printf("CS_Code_Segment         : 0x%02hhx \n",_RCS());
    printf("DS_Data_Segment         : 0x%02hhx \n",_RDS());
    printf("ES_Extra_Segment        : 0x%02hhx \n",_RES());
    printf("FS_Extra_Segment        : 0x%02hhx \n",_RFS());
    printf("GS_Extra_Segment        : 0x%02hhx \n",_RGS());

    printf("\nEFLAGS Register:\n"); 
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"); 
    printf("32-Bit Flag Register    : 0x%08x\n",_EFLAGS());

    printf("\nCPU Register:\n"); 
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"); 
    printf("CPU ID RAX              : %#018" PRIx64 " \n",_CPU_RAX());
    printf("CPU ID RBX              : %#018" PRIx64 " \n",_CPU_RBX());
    printf("CPU ID RCX              : %#018" PRIx64 " \n",_CPU_RCX());
    printf("CPU ID RDX              : %#018" PRIx64 " \n",_CPU_RDX());
}

#endif /* DUMP_H */