#ifndef DATABASE_H
#define DATABASE_H



class MySQL {

	public:
		virtual int InitMySQL(void);

		virtual int CreateServerTable(void);
		virtual int DeleteServerTable(void);

		virtual int CreateDmaTable(void);
		virtual int DeleteDmaTable(void);

		virtual int ReadDmaTable(void);
		virtual int ReadLastId(void);
		virtual int InsertIntoDmaTable(void);
		virtual int DeleteFormDmaTable(void);
		virtual int DeleteDatabase(void);

};

#endif /* DATABASE_H */
