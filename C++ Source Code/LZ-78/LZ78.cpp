#include "LZ78.h"
#include <string>
#include <time.h>
int main()
{
	LZ78 haha;
	clock_t start, end;
	start = clock();
	haha.open("./KongFu.jpg");  //���ļ�
	haha.Press();   //ѹ���ļ�
	end = clock();
	cout << "ѹ���ļ���ʱ��" << endl << endl;
	cout << double((end - start) / CLOCKS_PER_SEC) << "/s" << endl << endl;
	start = clock();
	LZ78 nothaha;
	nothaha.Decode("./KongFu.jpg.lz", "KongFuout.jpg");
	cout << "��ѹ��ʱ��" << endl << endl;
	cout << double((start - end) / CLOCKS_PER_SEC) << "/s" << endl << endl;
	getchar();
}