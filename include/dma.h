


#define ADDRESS_SPACE 8

extern int shutdown;

struct dma_engine
{
    int (*address)[ADDRESS_SPACE] = {nullptr};
};

struct data_engine
{
    int data[ADDRESS_SPACE] = {0x10,0x14,0x18,0x1B,0x20,0x24,0x28,0x2B};
};

int  DmaInit(void);
void DmaDump(void);