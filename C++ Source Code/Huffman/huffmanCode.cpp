#include <string>
#include "huffmanClass.h"
#include <time.h>
int main()
{
	clock_t start, end, start1, end1;
	cout << "��-------------Huffmanѹ������---------��" << endl << endl;
	cout << "!--------------���ߣ�С��¸�------------��" << endl << endl;
	cout << "!--------------ѹ������----------------! " << endl << endl;
	cout << "!--------------csdn-------! " << endl << endl;
	string filePath;
	cout << "������������ļ���ַ" << endl << endl;
	getline(cin, filePath);
	Huffman huf(filePath);
	start = clock();
	huf.count();  //��ȡ�ַ�Ƶ������charCountFrequency������
	cout << huf.charCountFrequency.size() << endl;
	//getchar();
	huf.CreateHuffmanTree(huf.charCountFrequency);
	huf.GetHuffmanCode(huf.root, 0);
	huf.WriteCode(huf.HuffmanCodeVec);
	end = clock();
	cout << "ѹ��ʹ��ʱ��Ϊ :   " << double((end - start) / CLOCKS_PER_SEC) * 1000 << " /ms" << endl << endl;
	
	cout << "!--------------�������------------!" << endl << endl;
	//cout << "!--------------�������������ļ�--------------!" << endl << endl;
	//string outfilePath;
	//getline(cin, outfilePath);
	//Huffman hufdecode(outfilePath);
	//huf.root = new Huffman::HuffmanNode;
	start1 = clock();
	Huffman hufde(filePath);
	hufde.Decode(filePath + ".dada", "./Out/" + filePath);
	end1 = clock();
	cout << "����ʹ��ʱ��Ϊ :   " << double((end1 - start1) / CLOCKS_PER_SEC) * 1000 << " /ms" << endl << endl;

	getchar();
}