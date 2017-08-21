#include <string>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;
#define N 100 //������ַ�Ӧ�ò�����50��
struct L //�ṹ��������ַ��������
{
	char ch; //�洢���ֵ��ַ������ظ���
	int num; //�洢�ַ����ֵĴ���
	double f;//�洢�ַ��ĸ���
};
//��ʾ��Ϣ
void disp();
//����ʺ��������룺�ַ�����������ַ����顢�ַ��ĸ�������;���أ����鳤�ȣ� int proba(string str,char c[],long double p[],int count);
//����ʵĸ�������
int search(vector<L> arch, char, int n);
long double bma(char c[], long double p[], string str, int number, int size);
int proba(string str, char c[], long double p[], int count);
//���뺯�������룺�ַ������ַ����飬�������飬�Լ����鳤�ȣ������������ long double bma(char c[],long double p[],string str,int number,int size);
//���뺯�������룺���������ַ������ַ����飬�������飬�Լ����ǵĳ��ȣ�������ַ���
//�ú����������ڼ������Ƿ���ȷ
void yma(string str, char c[], long double p[], int number, int size, long double input);


int main()
{
	string str; //����Ҫ�����String�����ַ���
	int number = 0, size = 0; //number--�ַ����в��ظ����ַ�������size--�ַ������� 
	char c[N]; //���ڴ洢���ظ����ַ�
	long double p[N], output; //p[N]--���ظ��ַ��ĸ��ʣ�output--������ 
	disp();
	cout << "����Ҫ������ַ���:";
	getline(cin, str); //����Ҫ������ַ���
	size = str.length(); //�ַ�������
	number = proba(str, c, p, size);//��������ʺ��������ز��ظ��ַ��ĸ���
	cout.setf(ios::fixed); //��ħ���䷽���涨��С�����ֵĸ���
	cout.setf(ios::showpoint); //�ڴ˹涨��������С��������ʮ��
	cout.precision(10);//���ñ��뺯�������ر�����
	output = bma(c, p, str, number, size);//�������뺯�������Ҫ������ַ�����
	yma(str, c, p, number, size, output); //����֤�����Ƿ���ȷ	
	getchar();
	return 0;
}

//��ʾ��Ϣ

void disp()

{
	cout << endl;
	cout << "!-------------------��������--------------------!\n";
	cout << "!-------------------���ߣ�С��¸�----------------!\n";
	cout << "!---------------               --------------!\n";
	cout << endl;
	cout << "�˳���ֻ��Ҫ����Ҫ������ַ���������Ҫ�����ַ�����\n";
	cout << endl;

}

//����ʺ���

int proba(string str, char c[], long double p[], int count)

{

	cout.setf(ios::fixed); //��ħ���䷽���涨��С������λ��Ϊ��λ
	cout.setf(ios::showpoint);
	cout.precision(3);
	vector<L>pt; //�����˽ṹ���͵�����������ͬʱ�洢���ظ����ַ��������
	L temp; //�ṹ���͵ı���
	temp.ch = str[0]; //�ݴ��ַ����ĵ�һ���ַ������ĸ�������Ϊ1
	temp.num = 1;
	temp.f = 0.0;
	pt.push_back(temp); //�����ַ��������ѹ������
	for (int i = 1; i<count; i++)//�������ַ�������ɨ��

	{
		temp.ch = str[i]; //�ݴ�ڶ����ַ�
		temp.num = 1;
		temp.f = 0.0;
		for (int j = 0; j<pt.size(); j++) //�ڽṹ������Ѱ���Ƿ����ظ��ַ�����
		{ //���ظ������ַ�������1��������ѭ�� 
			int k; //�����ظ�����ѹ����ַ���������ѭ�� 
			k = search(pt, str[i], pt.size());
			if (k >= 0)

			{
				pt[k].num++;
				break;
			}
			else
			{
				pt.push_back(temp);
				break;
			}

		}

	}

	for (int i = 0; i<pt.size(); i++) //���㲻�ظ��ַ����ֵĸ���

	{
		pt[i].f = double(pt[i].num) / count;
	}
	int number = pt.size(); //���㲻�ظ��ַ����ֵĴ���
	cout << "���ַ��������£�\n";
	for (int i = 0; i<number; i++) //��ʾ���õĸ��ʣ���֤�Ƿ���ȷ
	{
		if (count == 0)
		{
			cout << "NO sample!\n";
		}
		else
		{
			c[i] = pt[i].ch;
			p[i] = pt[i].f;
			cout << c[i] << "�ĸ���Ϊ��" << p[i] << endl;
		}
	}
	return number; //���ز��ظ��ַ��ĸ���

}
//����ʵĸ�������
//�������������ظ��ַ���������
//���򣬷���-1
int search(vector<L> arch, char ch1, int n)
{
	for (int i = 0; i<n; i++)
	{
		if (ch1 == arch[i].ch) return i;
	}
return -1;
}
//���뺯��
long double bma(char c[], long double p[], string str, int number, int size)
{
	long double High = 0.0, Low = 0.0, high, low, range;
	//High--��һ��������������ޣ�Low--��һ��������������ޣ�
	//high--�м����������������һ��������������ޣ�
	//low--�м����������������һ��������������ޣ�
	//range--��һ�����������䳤��
	int i, j = 0;
	for (i = 0; i<number; i++)
	{
		if (str[0] == c[i]) break; //�����һ���ַ�
	}
	while (j<i)
	{
		Low += p[j++]; //Ѱ�Ҹ��ַ��ĸ�����������
	}
	range = p[j]; //�õ����ַ��ĸ��ʳ���
	High = Low + range; //�õ����ַ�������������
	for (i = 1; i<size; i++) //��ʼ����ڶ����ַ�
	{
		for (j = 0; j<number; j++) //Ѱ�Ҹ��ַ���c�����е�λ��
		{
			if (str[i] == c[j])
			{
				if (j == 0) //�����ַ���c�����еĵ�һ���ַ�
				{
					low = Low; //��ʱ���ַ��ĸ����������޸պ�Ϊ�� 
					high = Low + p[j] * range;
					High = high;
					range *= p[j]; //������ַ��ı������䳤��
				}
				else //���ñ����ַ�����c�����еĵ�һ�� 
				{
					float proba_next = 0.0;
					for (int k = 0; k <= j - 1; k++)
						proba_next += p[k]; //�ٴ�Ѱ���ַ��ĸ�����������
					low = Low + range*proba_next; //������������ 
					high = Low + range*(proba_next + p[j]);//������������
					Low = low; //������������ 
					High = high; //������������ 
					range *= p[j]; //�������䳤��
				}
			}
			else continue; //i++��������һ���ַ� 
		}
	}
	cout << endl;
	cout << "�����ַ����ı���Ϊ:" << Low << endl;
	return Low;
}
//���뺯��
void yma(string str, char c[], long double p[], int number, int size, long double input)
{
	vector<char> v; //����char��������v
	long double temp; //�м����
	long double sum[N]; //�洢���ظ��ַ��������������
	sum[0] = 0.0; //�����һ��Ԫ��Ϊ0
	for (int i = 1; i<number + 1; i++) //���������Ԫ�ص�ֵ
	{
		sum[i] = sum[i - 1] + p[i - 1];
	}
	for (int j = 0; j<size; j++)
	{
		for (int k = 0; k<number; k++)
		{
			//ȷ���������ַ����������ڡ�0��1��֮�����һ�� 
			if ((input>sum[k]) && (input<sum[k + 1])) //�������ľͽ����ڸöε��ַ�ѹ������v

			{
				v.push_back(str[j]);
				temp = (input - sum[k]) / (sum[k + 1] - sum[k]);//������һ���������ַ������� 
				input = temp;
				break;
			}
			else
				continue;
		}
	}
	cout << endl;
	cout << "�������Ϊ��"; //�����������
	for (int m = 0; m<v.size(); m++)
	{
		cout << v[m];
	}
	cout << endl;
}
