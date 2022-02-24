#ifndef DATABASE_H
#define DATABASE_H


int InitMySQL(void);

int CreateServerTable(void);
int DeleteServerTable(void);

int CreateDmaTable(void);
int DeleteDmaTable(void);

int ReadDmaTable(void);
int ReadLastId(void);
int InsertIntoDmaTable(void);
int DeleteFormDmaTable(void);
int DeleteDatabase(void);


#endif /* DATABASE_H */
