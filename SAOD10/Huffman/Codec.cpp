#include "stdafx.h"
#include "Codec.h"


void Codec::outputCode(ofstream &os, const HC::Code &c)
{
	static unsigned char cBuffer;		// ��� �������� �������� ����������� ����
	static int iNumberOfBitsInBuffer;	// ��� �������� ����� ������� � �����

	// ���������� �����������
	if (c.len > 0) {
		int iCode = c.bits;
		unsigned int selector = 1 << (c.len - 1);
		while(selector != 0)
		{
			// �������� � ����� ���� �������� ����
			cBuffer <<= 1;
			cBuffer += (selector&iCode) != 0? 1:0;
			selector >>= 1;
			iNumberOfBitsInBuffer++;
			// ���� �������� ����, �� ����� ��� � �������� �����, ���������� ����� � �������� ����������� ��������� ����
			if (iNumberOfBitsInBuffer == 8) {
				os.put(cBuffer);
				cBuffer = (unsigned char)0;
				iNumberOfBitsInBuffer = 0;
			}
		}
	}
	// ����� � ����� ��������� ��� (������� �����) � ��������� ���� - ���������� ����� � ��������� �����
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
	// ������ ��������� ����
	if (mask == 0 && !is.eof())
	{
		buff = last;
		is.get(last);
		mask = 0x80;	// ������� ��� �����
	}
	
	// ��������� ���� ��� �������. � ��� ���������� �������� ����� � ���������� �����
	if (is.peek() == EOF)
		if (last > 0) // �������� �������� ����
		{
			bit = (mask&buff) != 0 ? 1 : 0;
			mask >>= 1;				// �������� � ���������� ����
			last--;
			return true;
		}
		else
			return false;

	bit = (mask&buff) != 0 ? 1 : 0;
	mask >>= 1;				// �������� � ���������� ����
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

	/// ��������� ����� ��������
	HC hc;
	hc.GenerateCodes(chTbl);

	/// ���������� ������ � ����� ������� �����
	int n = 0;
	for (int i = 0; i < hc.TblSize(); i++)
		if (hc.GetCode(i).len)
			n++;

	// ����� ������� ����� � ����
	// int n - ���������� ������� � �������
	// {ch, len, code} �� ����� �������
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

	/// ��������� ������ �������� ������ � ��� �����������
	is.clear();
	is.seekg(0, ios::beg);

#ifdef WITH_BLOCKS
	auto r = Analyze(is);

	is.clear();
	is.seekg(0, ios::beg);

	int blockLen = 0;
	int nBlk = 0;

	auto rit = r.begin();		// �������� ��� ������ ��������
	int pos = 0, bbPos = 0;		// ������� � ����� � ������� ������ �����
	is.get((char&)chCurrent);
	while (!is.eof())
	{
		if (rit != r.end() && rit->second > 0)
		{
			if (pos < rit->first && bbPos < MAX_BLOCK_LEN)	//�������� �� ��������
			{
				if (bbPos++ == 0)	// ������� ��������� ����� ����� �� �������� � ������� ����� �����
					outputCode(os, MakeCode(rit->first - pos));

				outputCode(os, hc.GetCode(chCurrent));
			}
			else if (pos == rit->first) // ������� ��������� ��� RLE
			{
				outputCode(os, MakeCode(rit->second, chCurrent));
			}
			if (pos + 1 == rit->first + rit->second) {		// �������� ���� ����� ��������
				rit++;										// ������ �������� ���������� �������.
				bbPos = 0;									// ���������� ������ ����� �� ��������.
			}
		}
		else {					// ������ ������ RLE ���
			if (bbPos++ == 0 && rit != r.end()) {			// ������� ��������� ����� ����� �� ��������
				outputCode(os, MakeCode(rit->first - pos));	// ����� ����� ������� ����� �� �����!
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

/// �� �����������
int Codec::DeCompressFile(ifstream &is, ofstream &os) {
	// ������ ������� �����
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

	// �������������� ������ ����� ��������
	shared_ptr<HC::SimpleNode> root = hc.ReconstructTree();

	// ������������� � ������ � �������� �����
	shared_ptr<HC::SimpleNode> node = root;
	int bit;
	while (getBit(is, bit)) {
		node = bit ? node->right : node->left;

		if (node->IsLeave()) {
			os.put(node->ch);
			node = root;
		}

		if (is.eof()) // �������� �� ����� �����
			break;
	}
	return 1;
}
