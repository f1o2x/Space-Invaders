// Дубровкин Сергей
// ICQ: 597-023-587
// Skype: s3dworld
// E-mail: s3dworld@yandex.ru
// Сентябрь 2010 года

#pragma once

#define DBINARY_OK					+0			// Ошибок нет
#define DBINARY_ERROR_MEMORY		-1			// Не хватает памяти
#define DBINARY_ERROR_LENGTH		-2			// Предельно допустимая длина
#define DBINARY_ERROR_PARAMS		-3			// Не правильно указаны параметры
#define DBINARY_ERROR_ZERO			-4			// Длина данных равна нулю
#define DBINARY_ERROR_END_FIND		-5			// Индекс поиска на конце файла
#define DBINARY_ERROR_TYPE			-6			// Не тот тип

struct DBBYTE
{
	bool bits[8];
};

struct DBWORD
{
	bool bits[16];
};

struct DBDWORD
{
	bool bits[32];
};

struct DBLWORD
{
	bool bits[64];
};

struct DBLDWORD
{
	bool bits[128];
};

class DBinary
{
	private:
		int resultCode;

		unsigned long int length;
		char* data;

		bool isAccessIndexFind;

		bool isEndFind;
		unsigned long int findIndex;

		bool NewData(char** _bytes,const unsigned long int _length);
		void DelData(char** _bytes);

		bool IsCopyData(
			const char* _source1,
			const char* _source2,
			const unsigned long int _length) const;

		void CopyData(char* _receiver,const char* _source,const unsigned long int _length);

		void CopyDataIndexReceiver(
			char* _receiver,
			const char* _source,
			const unsigned long int _receiverIndex,
			const unsigned long int _length);

		void CopyDataIndexSource(
			char* _receiver,
			const char* _source,
			const unsigned long int _sourceIndex,
			const unsigned long int _length);

		void CopyDataIndexReceiverSource(
			char* _receiver,
			const char* _source,
			const unsigned long int _receiverIndex,
			const unsigned long int _sourceIndex,
			const unsigned long int _length);

	public:
		DBinary(void);

		DBinary(const char _byte);
		explicit DBinary(const char* _bytes,const unsigned long int _length);
		DBinary(const DBinary &_binary);
		DBinary(const bool _value);
		DBinary(const short int _value);
		DBinary(const int _value);
		DBinary(const long int _value);
		DBinary(const long long int _value);
		DBinary(const unsigned short int _value);
		DBinary(const unsigned int _value);
		DBinary(const unsigned long int _value);
		DBinary(const unsigned long long int _value);
		DBinary(const float _value);
		DBinary(const double _value);
		DBinary(const long double _value);

		~DBinary(void);

		int GetResult(void) const;

		unsigned long int GetLength(void) const;
		char* GetData(void);

		void Clear(void);

		bool Fix(const char _byte);
		bool Fix(const char* _values,const unsigned long int _length);
		bool Fix(const DBinary _binary);
		bool Fix(const bool _value);
		bool Fix(const short int _value);
		bool Fix(const int _value);
		bool Fix(const long int _value);
		bool Fix(const long long int _value);
		bool Fix(const unsigned short int _value);
		bool Fix(const unsigned int _value);
		bool Fix(const unsigned long int _value);
		bool Fix(const unsigned long long int _value);
		bool Fix(const float _value);
		bool Fix(const double _value);
		bool Fix(const long double _value);

		bool AddToBegin(const char _byte);
		bool AddToBegin(const char* _bytes,const unsigned long int _length);
		bool AddToBegin(const DBinary _binary);
		bool AddToBegin(const bool _value);
		bool AddToBegin(const short int _value);
		bool AddToBegin(const int _value);
		bool AddToBegin(const long int _value);
		bool AddToBegin(const long long int _value);
		bool AddToBegin(const unsigned short int _value);
		bool AddToBegin(const unsigned int _value);
		bool AddToBegin(const unsigned long int _value);
		bool AddToBegin(const unsigned long long int _value);
		bool AddToBegin(const float _value);
		bool AddToBegin(const double _value);
		bool AddToBegin(const long double _value);

		bool AddToIndexOnLeft(const unsigned long int _index,const char _byte);
		bool AddToIndexOnLeft(const unsigned long int _index,const char* _bytes,const unsigned long int _length);
		bool AddToIndexOnLeft(const unsigned long int _index,const DBinary _binary);
		bool AddToIndexOnLeft(const unsigned long int _index,const bool _value);
		bool AddToIndexOnLeft(const unsigned long int _index,const short int _value);
		bool AddToIndexOnLeft(const unsigned long int _index,const int _value);
		bool AddToIndexOnLeft(const unsigned long int _index,const long int _value);
		bool AddToIndexOnLeft(const unsigned long int _index,const long long int _value);
		bool AddToIndexOnLeft(const unsigned long int _index,const unsigned short int _value);
		bool AddToIndexOnLeft(const unsigned long int _index,const unsigned int _value);
		bool AddToIndexOnLeft(const unsigned long int _index,const unsigned long int _value);
		bool AddToIndexOnLeft(const unsigned long int _index,const unsigned long long int _value);
		bool AddToIndexOnLeft(const unsigned long int _index,const float _value);
		bool AddToIndexOnLeft(const unsigned long int _index,const double _value);
		bool AddToIndexOnLeft(const unsigned long int _index,const long double _value);

		bool AddToIndexOnRight(const unsigned long int _index,const char _byte);
		bool AddToIndexOnRight(const unsigned long int _index,const char* _bytes,const unsigned long int _length);
		bool AddToIndexOnRight(const unsigned long int _index,const DBinary _binary);
		bool AddToIndexOnRight(const unsigned long int _index,const bool _value);
		bool AddToIndexOnRight(const unsigned long int _index,const short int _value);
		bool AddToIndexOnRight(const unsigned long int _index,const int _value);
		bool AddToIndexOnRight(const unsigned long int _index,const long int _value);
		bool AddToIndexOnRight(const unsigned long int _index,const long long int _value);
		bool AddToIndexOnRight(const unsigned long int _index,const unsigned short int _value);
		bool AddToIndexOnRight(const unsigned long int _index,const unsigned int _value);
		bool AddToIndexOnRight(const unsigned long int _index,const unsigned long int _value);
		bool AddToIndexOnRight(const unsigned long int _index,const unsigned long long int _value);
		bool AddToIndexOnRight(const unsigned long int _index,const float _value);
		bool AddToIndexOnRight(const unsigned long int _index,const double _value);
		bool AddToIndexOnRight(const unsigned long int _index,const long double _value);

		bool AddToEnd(const char _byte);
		bool AddToEnd(const char* _bytes,const unsigned long int _length);
		bool AddToEnd(const DBinary _binary);
		bool AddToEnd(const bool _value);
		bool AddToEnd(const short int _value);
		bool AddToEnd(const int _value);
		bool AddToEnd(const long int _value);
		bool AddToEnd(const long long int _value);
		bool AddToEnd(const unsigned short int _value);
		bool AddToEnd(const unsigned int _value);
		bool AddToEnd(const unsigned long int _value);
		bool AddToEnd(const unsigned long long int _value);
		bool AddToEnd(const float _value);
		bool AddToEnd(const double _value);
		bool AddToEnd(const long double _value);

		bool DelAll(const char _byte);
		bool DelAll(const char* _bytes,const unsigned long int _length);
		bool DelAll(const DBinary _binary);

		bool DelOnIndex(const unsigned long int _index);
		bool DelOnRange(const unsigned long int _startIndex,const unsigned long int _endIndex);
		bool DelOnLength(const unsigned long int _index,const unsigned long int _length);

		bool SetByte(const unsigned long int _index,const char _byte);
		bool GetByte(char* _byte,const unsigned long int _index);

		void ResetFind(void);
		bool SetFind(const unsigned long int _index);
		unsigned long int GetFind(void) const;

		bool FindAll(unsigned long int* _count,const char _byte);
		bool FindAll(unsigned long int* _count,const char* _bytes,const unsigned long int _length);
		bool FindAll(unsigned long int* _count,const DBinary _binary);

		bool ReplaceAll(unsigned long int* _count,const char _oldByte,const char _newByte);
		bool ReplaceAll(unsigned long int* _count,const char* _oldBytes,const unsigned long int __oldBytesLength,const char* _newBytes,const unsigned long int _newBytesLength);
		bool ReplaceAll(unsigned long int* _count,const DBinary _oldBinary,const DBinary _newBinary);

		bool Find(bool* _isFind,const char _byte,unsigned long int* _index);
		bool Find(bool* _isFind,const char* _bytes,const unsigned long int _length,unsigned long int* _startIndex,unsigned long int* _endIndex);
		bool Find(bool* _isFind,const DBinary _binary,unsigned long int* _startIndex,unsigned long int* _endIndex);

		bool Replace(bool* _isReplace,const char _oldByte,const char _newByte,unsigned long int* _index);
		bool Replace(bool* _isReplace,const char* _oldBytes,const unsigned long int _oldBytesLength,const char* _newBytes,const unsigned long int _newBytesLength,unsigned long int* _startIndex,unsigned long int* _endIndex);
		bool Replace(bool* _isReplace,const DBinary _oldBinary,const DBinary _newBinary,unsigned long int* _startIndex,unsigned long int* _endIndex);

		bool TestBool(void) const;
		bool TestShortInt(void) const;
		bool TestInt(void) const;
		bool TestLongInt(void) const;
		bool TestLongLongInt(void) const;
		bool TestFloat(void) const;
		bool TestDouble(void) const;
		bool TestLongDouble(void) const;

		bool TestBoolOnRange(const unsigned long int _startIndex,const unsigned long int _endIndex) const;
		bool TestShortIntOnRange(const unsigned long int _startIndex,const unsigned long int _endIndex) const;
		bool TestIntOnRange(const unsigned long int _startIndex,const unsigned long int _endIndex) const;
		bool TestLongIntOnRange(const unsigned long int _startIndex,const unsigned long int _endIndex) const;
		bool TestLongLongIntOnRange(const unsigned long int _startIndex,const unsigned long int _endIndex) const;
		bool TestFloatOnRange(const unsigned long int _startIndex,const unsigned long int _endIndex) const;
		bool TestDoubleOnRange(const unsigned long int _startIndex,const unsigned long int _endIndex) const;
		bool TestLongDoubleOnRange(const unsigned long int _startIndex,const unsigned long int _endIndex) const;

		bool TestBoolOnLength(const unsigned long int _index,const unsigned long int _length) const;
		bool TestShortIntOnLength(const unsigned long int _index,const unsigned long int _length) const;
		bool TestIntOnLength(const unsigned long int _index,const unsigned long int _length) const;
		bool TestLongIntOnLength(const unsigned long int _index,const unsigned long int _length) const;
		bool TestLongLongIntOnLength(const unsigned int long _index,const unsigned long int _length) const;
		bool TestFloatOnLength(const unsigned long int _index,const unsigned long int _length) const;
		bool TestDoubleOnLength(const unsigned long int _index,const unsigned long int _length) const;
		bool TestLongDoubleOnLength(const unsigned long int _index,const unsigned long int _length) const;

		bool ToChar(char* _source,const unsigned long int _sourceIndex);
		bool ToBinary(DBinary* _binary,const unsigned long int _index);
		bool ToBool(bool* _value);
		bool ToSignedShortInt(short int* _value);
		bool ToSignedInt(int* _value);
		bool ToSignedLongInt(long int* _value);
		bool ToSignedLongLongInt(long long int* _value);
		bool ToUnsignedShortInt(unsigned short int* _value);
		bool ToUnsignedInt(unsigned int* _value);
		bool ToUnsignedLongInt(unsigned long int* _value);
		bool ToUnsignedLongLongInt(unsigned long long int* _value);
		bool ToFloat(float* _value);
		bool ToDouble(double* _value);
		bool ToLongDouble(long double* _value);

		bool ToCharOnRange(char* _source,const unsigned long int _sourceIndex,const unsigned long int _startIndex,const unsigned long int _endIndex);
		bool ToBinaryOnRange(DBinary* _binary,const unsigned long int _startIndex,const unsigned long int _endIndex);
		bool ToBoolOnRange(bool* _value,const unsigned long int _startIndex,const unsigned long int _endIndex);
		bool ToSignedShortIntOnRange(short int* _value,const unsigned long int _startIndex,const unsigned long int _endIndex);
		bool ToSignedIntOnRange(int* _value,const unsigned long int _startIndex,const unsigned long int _endIndex);
		bool ToSignedLongIntOnRange(long int* _value,const unsigned long int _startIndex,const unsigned long int _endIndex);
		bool ToSignedLongLongIntOnRange(long long int* _value,const unsigned long int _startIndex,const unsigned long int _endIndex);
		bool ToUnsignedShortIntOnRange(unsigned short int* _value,const unsigned long int _startIndex,const unsigned long int _endIndex);
		bool ToUnsignedIntOnRange(unsigned int* _value,const unsigned long int _startIndex,const unsigned long int _endIndex);
		bool ToUnsignedLongIntOnRange(unsigned long int* _value,const unsigned long int _startIndex,const unsigned long int _endIndex);
		bool ToUnsignedLongLongIntOnRange(unsigned long long int* _value,const unsigned long int _startIndex,const unsigned long int _endIndex);
		bool ToFloatOnRange(float* _value,const unsigned long int _startIndex,const unsigned long int _endIndex);
		bool ToDoubleOnRange(double* _value,const unsigned long int _startIndex,const unsigned long int _endIndex);
		bool ToLongDoubleOnRange(long double* _value,const unsigned long int _startIndex,const unsigned long int _endIndex);

		bool ToCharOnLength(char* _source,const unsigned long int _sourceIndex,const unsigned long int _index,const unsigned long int _length);
		bool ToBinaryOnLength(DBinary* _binary,const unsigned long int _index,const unsigned long int _length);
		bool ToBoolOnLength(bool* _value,const unsigned long int _index,const unsigned long int _length);
		bool ToSignedShortIntOnLength(short int* _value,const unsigned long int _index,const unsigned long int _length);
		bool ToSignedIntOnLength(int* _value,const unsigned long int _index,const unsigned long int _length);
		bool ToSignedLongIntOnLength(long int* _value,const unsigned long int _index,const unsigned long int _length);
		bool ToSignedLongLongIntOnLength(long long int* _value,const unsigned long int _index,const unsigned long int _length);
		bool ToUnsignedShortIntOnLength(unsigned short int* _value,const unsigned long int _index,const unsigned long int _length);
		bool ToUnsignedIntOnLength(unsigned int* _value,const unsigned long int _index,const unsigned long int _length);
		bool ToUnsignedLongIntOnLength(unsigned long int* _value,const unsigned long int _index,const unsigned long int _length);
		bool ToUnsignedLongLongIntOnLength(unsigned long long int* _value,const unsigned long int _index,const unsigned long int _length);
		bool ToFloatOnLength(float* _value,const unsigned long int _index,const unsigned long int _length);
		bool ToDoubleOnLength(double* _value,const unsigned long int _index,const unsigned long int _length);
		bool ToLongDoubleOnLength(long double* _value,const unsigned long int _index,const unsigned long int _length);

		bool SetByteOnBits(const unsigned long int _index,const DBBYTE _byte);
		bool SetWordOnBits(const unsigned long int _index,const DBWORD _word);
		bool SetDWordOnBits(const unsigned long int _index,const DBDWORD _dword);
		bool SetLWordOnBits(const unsigned long int _index,const DBLWORD _lword);
		bool SetLDWordOnBits(const unsigned long int _index,const DBLDWORD _ldword);

		bool GetByteOnBits(DBBYTE* _byte,const unsigned long int _index);
		bool GetWordOnBits(DBWORD* _word,const unsigned long int _index);
		bool GetDWordOnBits(DBDWORD* _dword,const unsigned long int _index);
		bool GetLWordOnBits(DBLWORD* _lword,const unsigned long int _index);
		bool GetLDWordOnBits(DBLDWORD* _ldword,const unsigned long int _index);

		bool TestMultiple(bool* _isMultiple,const unsigned long int _value);
		bool TestIndex(const unsigned long int _index) const;

		DBinary& operator=(const char _byte);
		DBinary& operator=(const DBinary _binary);
		DBinary& operator=(const bool _value);
		DBinary& operator=(const short int _value);
		DBinary& operator=(const int _value);
		DBinary& operator=(const long int _value);
		DBinary& operator=(const long long int _value);
		DBinary& operator=(const unsigned short int _value);
		DBinary& operator=(const unsigned int _value);
		DBinary& operator=(const unsigned long int _value);
		DBinary& operator=(const unsigned long long int _value);
		DBinary& operator=(const float _value);
		DBinary& operator=(const double _value);
		DBinary& operator=(const long double _value);

		DBinary& operator+=(const char _byte);
		DBinary& operator+=(const DBinary _binary);
		DBinary& operator+=(const bool _value);
		DBinary& operator+=(const short int _value);
		DBinary& operator+=(const int _value);
		DBinary& operator+=(const long int _value);
		DBinary& operator+=(const long long int _value);
		DBinary& operator+=(const unsigned short int _value);
		DBinary& operator+=(const unsigned int _value);
		DBinary& operator+=(const unsigned long int _value);
		DBinary& operator+=(const unsigned long long int _value);
		DBinary& operator+=(const float _value);
		DBinary& operator+=(const double _value);
		DBinary& operator+=(const long double _value);

		DBinary operator+(const char _byte);
		DBinary operator+(const DBinary _binary);
		DBinary operator+(const bool _value);
		DBinary operator+(const short int _value);
		DBinary operator+(const int _value);
		DBinary operator+(const long int _value);
		DBinary operator+(const long long int _value);
		DBinary operator+(const unsigned short int _value);
		DBinary operator+(const unsigned int _value);
		DBinary operator+(const unsigned long int _value);
		DBinary operator+(const unsigned long long int _value);
		DBinary operator+(const float _value);
		DBinary operator+(const double _value);
		DBinary operator+(const long double _value);

		bool operator==(const DBinary _binary) const;
		bool operator!=(const DBinary _binary) const;
		bool operator>(const DBinary _binary) const;
		bool operator>=(const DBinary _binary) const;
		bool operator<(const DBinary _binary) const;
		bool operator<=(const DBinary _binary) const;
		bool operator&&(const DBinary _binary) const;
		bool operator||(const DBinary _binary) const;
};

// Дубровкин Сергей © 2010