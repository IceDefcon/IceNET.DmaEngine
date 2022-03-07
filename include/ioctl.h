#ifndef IOCTL_H
#define IOCTL_H

#define ICE_IOCTL_0     0
#define ICE_IOCTL_1     1

typedef struct
{
    unsigned int x;
    unsigned int y;
}ComplexData;

typedef struct 
{
    long (*ioctl) (ComplexData *pData, unsigned int cmd, unsigned long arg);
}   API;

static long Ice_Ioctl(ComplexData *pData, unsigned int cmd, unsigned long arg);

#endif /* IOCTL_H */