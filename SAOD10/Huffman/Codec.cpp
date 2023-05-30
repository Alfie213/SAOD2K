#include "stdafx.h"
#include "Codec.h"


void Codec::outputCode(ofstream &os, const HC::Code &c)
{
	static unsigned char cBuffer;		// для хранения остатков предыдущего кода
	static int iNumberOfBitsInBuffer;	// для хранения длины остатка в битах

	// Собственно кодирование
	if (c.len > 0) {
		int iCode = c.bits;
		unsigned int selector = 1 << (c.len - 1);
		while(selector != 0)
		{
			// Помещаем в буфер биты входного кода
			cBuffer <<= 1;
			cBuffer += (selector&iCode) != 0? 1:0;
			selector >>= 1;
			iNumberOfBitsInBuffer++;
			// Если заполнен байт, то пишем его в выходной поток, сбрасываем буфер и начинаем накапливать следующий байт
			if (iNumberOfBitsInBuffer == 8) {
				os.put(cBuffer);
				cBuffer = (unsigned char)0;
				iNumberOfBitsInBuffer = 0;
			}
		}
	}
	// Пишем в поток последний код (остатки битов) и последний байт - количество битов в последнем байте
	else 
	{
		if (iNumberOfBitsInBuffer != 0)
		{
			os.put(cBuffer << (8 - iNumberOfBitsInBuffer));
			os.put((char)(iNumberOfBitsInBuffer));
		}
		else
			os.put(8);
	}
}


bool Codec::getBit(ifstream &is, int &bit)
{
	static bool init = true;
	static char last;
	static char buff;
	static unsigned char mask;

 	if (init)
	{
		init = false;
		is.get(last);
	}
	// Читаем следующий байт
	if (mask == 0 && !is.eof())
	{
		buff = last;
		is.get(last);
		mask = 0x80;	// старший бит байта
	}
	
	// Последний байт уже прочтен. В нем количество значимых битов в предыдущем байте
	if (is.peek() == EOF)
		if (last > 0) // добираем неполный байт
		{
			bit = (mask&buff) != 0 ? 1 : 0;
			mask >>= 1;				// перейдем к следующему биту
			last--;
			return true;
		}
		else
			return false;

	bit = (mask&buff) != 0 ? 1 : 0;
	mask >>= 1;				// перейдем к следующему биту
	return true;
}

int Codec::CompressFile(ifstream& is, ofstream& os)
{
	map<char, int> chTbl;
	unsigned char chCurrent;
	is.get((char&)chCurrent);
	while (!is.eof())
	{
		chTbl[chCurrent]++;
		is.get((char&)chCurrent);
	}

	/// Генерация кодов Хаффмана
	HC hc;
	hc.GenerateCodes(chTbl);

	/// Подготовка вывода в поток таблицы кодов
	int n = 0;
	for (int i = 0; i < hc.TblSize(); i++)
		if (hc.GetCode(i).len)
			n++;

	// Вывод таблицы кодов в файл
	// int n - количество записей в таблице
	// {ch, len, code} по числу записей
	os.write(reinterpret_cast<const char*>(&n), sizeof(n));
	for (int i = 0; i < hc.TblSize(); i++) {
		HC::Code c = hc.GetCode(i);
		if (c.len != 0)
		{
			os.put(c.ch);
			os.put(static_cast<char>(c.len));
			os.write(reinterpret_cast<const char*>(&c.bits), sizeof(c.bits));
		}
	}

	/// Повторное чтение входного потока и его кодирование
	is.clear();
	is.seekg(0, ios::beg);

#ifdef WITH_BLOCKS
	auto r = Analyze(is);

	is.clear();
	is.seekg(0, ios::beg);

	int blockLen = 0;
	int nBlk = 0;

	auto rit = r.begin();		// Итератор для списка повторов
	int pos = 0, bbPos = 0;		// Позиция в файле и позиция начала блока
	is.get((char&)chCurrent);
	while (!is.eof())
	{
		if (rit != r.end() && rit->second > 0)
		{
			if (pos < rit->first && bbPos < MAX_BLOCK_LEN)	//кодируем по Хаффману
			{
				if (bbPos++ == 0)	// Выводим заголовок блока кодов по Хаффману и считаем длину блока
					outputCode(os, MakeCode(rit->first - pos));

				outputCode(os, hc.GetCode(chCurrent));
			}
			else if (pos == rit->first) // Выводим заголовок для RLE
			{
				outputCode(os, MakeCode(rit->second, chCurrent));
			}
			if (pos + 1 == rit->first + rit->second) {		// Начинаем блок кодов Хаффмана
				rit++;										// читаем описание следующего повтора.
				bbPos = 0;									// Сбрасываем начало блока по Хаффману.
			}
		}
		else {					// Больше блоков RLE нет
			if (bbPos++ == 0 && rit != r.end()) {			// Выводим заголовок блока кодов по Хаффману
				outputCode(os, MakeCode(rit->first - pos));	// Нужно знать сколько кодов до конца!
			}
			outputCode(os, hc.GetCode(chCurrent));
		}

		is.get((char&)chCurrent);
		pos++;
	}
	outputCode(os, HC::Code(0, 0));
#else
	is.get((char&)chCurrent);
	while (!is.eof())
	{
		outputCode(os, hc.GetCode((unsigned char)chCurrent));
		is.get((char&)chCurrent);
	}
	outputCode(os, HC::Code(0, 0));
#endif
	return 0;
}


void readCodesReverseOrder(std::istream& input, HC& hc)
{
	int tableSize = hc.TblSize();
	for (int i = tableSize - 1; i >= 0; i--)
	{
		char len;
		unsigned int bits;
		char ch;
		input.read(reinterpret_cast<char*>(&len), sizeof(len));
		input.read(reinterpret_cast<char*>(&bits), sizeof(bits));
		input.read(reinterpret_cast<char*>(&ch), sizeof(ch));
		hc.SetCode(HC::Code(len, bits, ch));
	}
}

/// Не реализована
int Codec::DeCompressFile(ifstream &is, ofstream &os) {
	// Чтение таблицы кодов
	int tblSize;
	is.read((char*)&tblSize, sizeof(tblSize));

	HC hc;
	for (int i = 0; i < tblSize; i++) {
		char ch;
		char len;
		unsigned int bits;
		is.get(ch);
		is.get(len);
		is.read((char*)&bits, sizeof(bits));

		HC::Code c(len, bits, ch);
		hc.SetCode(c);
	}

	// Восстановление дерева кодов Хаффмана
	shared_ptr<HC::SimpleNode> root = hc.ReconstructTree();

	// Декодирование и запись в выходной поток
	shared_ptr<HC::SimpleNode> node = root;
	int bit;
	while (getBit(is, bit)) {
		node = bit ? node->right : node->left;

		if (node->IsLeave()) {
			os.put(node->ch);
			node = root;
		}

		if (is.eof()) // Проверка на конец файла
			break;
	}
	return 1;
}
