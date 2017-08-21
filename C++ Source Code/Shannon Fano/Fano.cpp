#include "fano.h"
#include <string>
#include <time.h>
int main()
{
	string filepath;
	cout << "�������ѹ���ļ��ĵ�ַ" << endl << endl;
	getline(cin, filepath);
	clock_t start, end;
	start = clock();
	/*
	Fano myFano;
	myFano.open(filepath);
	myFano.count();
	myFano.root = new Fano::FanoNode;
	myFano.CreateTree(myFano.charFrequency, myFano.root);
	myFano.GetFanoCode(myFano.root, 0);
	myFano.WriteCode(myFano.FanoCodeVec);
	end = clock();
	cout << "ѹ���ļ���ʱ��" << double((end - start) / CLOCKS_PER_SEC) << "/s" << endl;
	*/
	Fano myfanoDecode;
	myfanoDecode.open(filepath);
	myfanoDecode.Decode(filepath + ".dada", "./Result/ " + filepath);
	end = clock();
	cout << "��ѹ�ļ���ʱ:" << double((start - end) / CLOCKS_PER_SEC) << "/s" << endl;
	getchar();

}