#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
class Huffman
{
public:
	struct HuffmanNode
	{
		unsigned char value; //�ڵ�ֵ
		int frequency = 0; //�ڵ�Ƶ��
		struct HuffmanNode *Lchild = NULL;
		struct HuffmanNode *Rchild = NULL;

	};
private:
	struct CountVector
	{
		unsigned char value; //�ַ�
		int frequency = 0;  //�ַ�Ƶ��
		struct HuffmanNode *nodeAddress = NULL;
	};


	struct HuffmanCode
	{
		unsigned char value;
		int frequency = 0;
		string code;
		int codelen;
	};

	//���ڵ�

	static bool mysortfunction(CountVector A, CountVector B)
	{  //����sort�����㷨
		return A.frequency < B.frequency;
	}

public:
	HuffmanNode *root;
	string fileAddress;
	long int NumOfChar = 0;
	vector<CountVector> charCountFrequency;  //���ڴ洢�ַ�Ƶ��
	vector<HuffmanCode> HuffmanCodeVec;
	Huffman(string sourcefile);  //���캯��
	void count();   //ͳ�Ƹ����ַ���Ƶ������
	void CreateHuffmanTree(vector<CountVector> charFrequency);  //����huffman��
	void GetHuffmanCode(HuffmanNode *root, int len);
	void WriteCode(vector<HuffmanCode> hfCode);
	void Decode(string sourcefile, string dstfile);
};

Huffman::Huffman(string sourcefile)
{
	fileAddress = sourcefile;  //��ʼ���ļ������ַ
}

void Huffman::count()
{
	ifstream readfile;
	readfile.open(fileAddress, ios::in | ios::binary);
	unsigned char *now = new unsigned char;  //�洢��ǰ��ȡ�����ַ�
	while (!readfile.eof())
	{
		CountVector *presentChar = new CountVector;  //��ȡ�����ַ���Ϣ
		readfile.read((char*)now, sizeof(unsigned char));
		int flag = 0;   //��־�Ƿ����³��ֵ��ַ�
		for (int i = 0; i < charCountFrequency.size(); i++)
		{
			if (*now == charCountFrequency[i].value)
			{
				charCountFrequency[i].frequency++;
				NumOfChar++;
				flag = 1;
			}

		}
		if (flag == 0)
		{
			presentChar->value = *now;
			presentChar->frequency++;
			NumOfChar++;
			charCountFrequency.push_back(*presentChar);
		}
	}
	readfile.close();
}

void Huffman::CreateHuffmanTree(vector<CountVector> charFrequency)
{
	vector<CountVector>  buildtree;
	//HuffmanNode newNode;
	HuffmanNode *rootnode = new HuffmanNode;
	buildtree = charFrequency;
	sort(buildtree.begin(), buildtree.end(), mysortfunction);
	int treedepth = 0;
	while (buildtree.size() > 1)
	{
		HuffmanNode *nodeLeft = new HuffmanNode,
			*nodeRight = new HuffmanNode,
			*newNode = new HuffmanNode;
		CountVector insertnew;
		if (buildtree[0].nodeAddress != NULL)
		{  //�����Ҷ�ӽڵ�Ļ�  ���������ĵ�ַ��ΪNULL
			nodeLeft->Lchild = buildtree[0].nodeAddress->Lchild;
			nodeLeft->Rchild = buildtree[0].nodeAddress->Rchild;
		}
		else
		{
			nodeLeft->Lchild = NULL;
			nodeLeft->Rchild = NULL;
		}
		if (buildtree[1].nodeAddress != NULL)
		{
			nodeRight->Lchild = buildtree[1].nodeAddress->Lchild;
			nodeRight->Rchild = buildtree[1].nodeAddress->Rchild;
		}
		else
		{
			nodeRight->Lchild = NULL;
			nodeRight->Rchild = NULL;
		}
		nodeLeft->frequency = buildtree[0].frequency;
		nodeLeft->value = buildtree[0].value;
		nodeRight->frequency = buildtree[1].frequency;
		nodeRight->value = buildtree[1].value;
		newNode->frequency = nodeRight->frequency + nodeLeft->frequency;
		newNode->Lchild = nodeLeft;
		newNode->Rchild = nodeRight;
		insertnew.frequency = newNode->frequency;
		insertnew.value = 0;
		insertnew.nodeAddress = newNode;
		//vector<CountVector>::iterator it = buildtree.begin();
		buildtree.erase(buildtree.begin());
		//vector<CountVector>::iterator it = buildtree.begin();
		buildtree.erase(buildtree.begin());
		//vector<CountVector>::iterator it = buildtree.begin();
		buildtree.insert(buildtree.begin(), insertnew);
		sort(buildtree.begin(), buildtree.end(), mysortfunction);   //ÿ�θ�����Ҫ����
		rootnode = newNode;
		treedepth++;

	}
	//cout << treedepth;
	root = rootnode;
}

void  Huffman::GetHuffmanCode(HuffmanNode* root, int depth)
{
	static char code[512];
	//�ж������
	if (root->Lchild != NULL)
	{
		code[depth] = '0';
		code[depth + 1] = '\0';
		GetHuffmanCode(root->Lchild, depth + 1);
	}
	if (root->Rchild != NULL)
	{
		code[depth] = '1';
		code[depth + 1] = '\0';
		GetHuffmanCode(root->Rchild, depth + 1);
	}
	else
	{
		HuffmanCode insertCode;
		int codelength = 0;
		for (int i = 0; i < charCountFrequency.size(); i++)
		{
			if (root->value == charCountFrequency[i].value)
			{
				insertCode.code = code;
				insertCode.value = charCountFrequency[i].value;
				insertCode.frequency = charCountFrequency[i].frequency;
			}
		}
		for (int j = 0; code[j] != '\0'; j++)
		{
			codelength++;
		}
		insertCode.codelen = codelength;
		HuffmanCodeVec.push_back(insertCode);

	}

}

void Huffman::WriteCode(vector<HuffmanCode> HFCode)
{
	//���ļ��ܶ�ȡ�ַ������б���
	int codeNum = HFCode.size();
	string address = fileAddress;
	ofstream writecode;
	ifstream read;
	read.open(address, ios::in | ios::binary);   //�����ļ�
	writecode.open(address + ".dada", ios::out | ios::binary);   //��*.dada����
	unsigned char *now = new unsigned char; //��ȡ�� ��ǰ�ַ�
	unsigned char save = 0;  //ÿһ�α���һ���ֽڵĳ���
	int len = 0;
	long int totalLen = 0; //�ļ������ܳ�
	int last; //���д��ʱ��λ��

	for (int i = 0; i < HFCode.size(); i++)
	{
		totalLen = totalLen + HFCode[i].codelen;
	}
	last = totalLen % 8;
	// ��Huffman����д��ͷ��������ͷ�ļ��������������
	char head = '>';
	writecode.write((char*)&head, sizeof(char));
	writecode.write((char *)&codeNum, sizeof(int));
	writecode.write((char *)& last, sizeof(int));  //д�����һ��д���λ��
	for (int i = 0; i < codeNum; i++)
	{    //д���ַ�ֵ��Ƶ��
		writecode.write((char*)&charCountFrequency[i].value, sizeof(unsigned char));
		writecode.write((char*)&charCountFrequency[i].frequency, sizeof(int));
	}
	//read.read((char*)now, 1);
	read.read((char*)now, sizeof(unsigned char));
	while (!read.eof())
	{
		int flag = 0;
		for (int i = 0; i < HFCode.size(); i++)
		{
			if (*now == HFCode[i].value)
			{
				flag = 1;
				for (int j = 0; j < HFCode[i].codelen; j++)
				{
					if (len != 0)
						save = save << 1;
					save = save | (HFCode[i].code[j] - '0');
					len++;
					if (len == 8)
					{
						writecode.write((char *)&save, sizeof(unsigned char));
						save = 0;
						len = 0;
					}
				}

			}
		}
		if (flag == 0)
		{
			cout << *now << "û�ڱ����ҵ�" << endl;
		}
		read.read((char*)now, sizeof(unsigned char));
		//*now = read.get();
	}
	if (len != 0)
	{
		writecode.write((char*)&save, sizeof(unsigned char));
	}

	read.close();
	writecode.close();

}

void Huffman::Decode(string sourcefile, string dstfile)
{
	ifstream read;
	ofstream write;
	vector<CountVector> arr;
	unsigned char now;  //��ȡ�ĵ�ǰ�ַ�
	int last = 0;   //���һ�ζ�ȡ��λ��
	int n; //�ַ�����
	read.open(sourcefile, ios::in | ios::binary);  //��ȡ�����ļ�
	write.open(dstfile, ios::out | ios::binary); //�򿪽������ļ�
	read.read((char*)&now, sizeof(now));
	if (!(now == '>'))
	{
		cout << "���ļ���Huffman�����ʽ����ȷ" << endl << endl;
		read.close();
		return;
	}
	read.read((char*)&n, sizeof(int));
	read.read((char*)&last, sizeof(last));

	for (int i = 0; i < n; i++)
	{
		CountVector *insert = new CountVector;

		read.read((char*)&(insert->value), sizeof(unsigned char));
		read.read((char*)&(insert->frequency), sizeof(int));
		arr.push_back(*insert);
	}
	this->root = new HuffmanNode;
	CreateHuffmanTree(arr);
	GetHuffmanCode(root, 0);
	HuffmanNode *pNow = root;

	unsigned char *temp = new unsigned char; //ÿ�ζ�һ���ֽ�
	read.read((char*)temp, sizeof(unsigned char));
	while (!read.eof())
	{
		unsigned char *ifLast = new unsigned char; //�����ж��Ƿ�����ļ�ĩβ
		read.read((char*)ifLast, sizeof(unsigned char));
		int i;
		if (read.eof())
		{
			i = last - 1;
		}
		else
		{
			i = 7;
		}
		for (; i >= 0; i--)
		{
			if ((*temp >> i & 1) == 0)   //�����ƶ�7λ�ж϶�������0 ����1 
				pNow = pNow->Lchild;
			else
				pNow = pNow->Rchild;
			if (pNow->Lchild == NULL && pNow->Rchild == NULL)
			{
				write.write((char*)&(pNow->value), sizeof(unsigned char));
				pNow = root;
			}
		}
		temp = ifLast;
	}

	read.close();
	write.close();

}





