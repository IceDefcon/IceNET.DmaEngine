#ifndef DATABASE_H
#define DATABASE_H


int InitMySQL(void);
int ReadDmaTable(void);
int ReadLastId(void);
int InsertIntoDmaTable(void);
int DeleteFormDmaTable(void);
int DeleteDatabase(void);


#endif /* DATABASE_H */
