#ifndef DMA_H
#define DMA_H



#define ADDRESS_SPACE 8

struct dma_engine
{
    int (*Address)[ADDRESS_SPACE] = {nullptr};
};

struct data_engine
{
    int data[ADDRESS_SPACE] = {0x10,0x14,0x18,0x1B,0x20,0x24,0x28,0x2B};
};




void InitDma(void);
void TerminateDma(void);


#endif /* DMA_H */