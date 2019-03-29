#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

void Dijkstra(int n, int **Graph, int Node1, int Node2)
{
	ofstream f;
	f.open("Outp.txt");
	set <int> S;//множество непросмотренных вершин
	int *D = new int[n];//метки вершин
	int i, j, m, p, k;
	vector<int> parent (n,-1);
	int Max_Sum = 0;
	bool beacon=0;
	vector <int> way;
	way.push_back(Node1-1);
	Node1--;//так как нумерация с 0
	Node2--;
	for (i = 0 ; i < n ; i++)
		for (j = 0 ; j < n ; j++)
			Max_Sum += Graph[i][j];//вычисление суммы элементов (максимально возможное значение)
	for (i = 0 ; i < n ; i++)
		for (j = 0 ; j < n ; j++)
			if (Graph[i][j] == 0) 
				Graph[i][j] = Max_Sum;//если путь к вершине отсутствует, то считаем его равным максимальному значению
	for (i=0;i<n;i++)
	{
		D[i]=Max_Sum;//ставим все метки равными максимальному значению
		S.insert(i);//заносим вершины в множество непросмотренных
	}
	p=Node1;//текущая просматриваемая вершина
	D[Node1]=0;//путь к первому элементу равен 0
	j=0;
	while (p!=Node2) //пока просматриваемая вершина не совпала с конечной
	{
		for  (i=0;i<n;i++) //перебираем все вершины
		{
			if (S.find(i)!=S.end())
			{
				if (Graph[p][i]<Max_Sum) //вершина смежна с текущей
				{
					if (D[i] > D[p]+Graph[p][i]) //метка вершины больше суммы метки просматриваемой вершины и длины пути из нее до данной вершины
					{
						D[i]= D[p]+Graph[p][i]; //замена метки на меньшее значение
						parent.at(i) = p;
					}
				}
			}
		}
		S.erase(p);//удаляем из множества вершину как просмотренную
		m=Node2;//m - переменная, где будет храниться номер ближайшей смежной вершины (в начале считаем таковой конечную вершину)
		for (i=0;i<n;i++)//перебираем все вершины
			if (S.find(i)!=S.end()) //если вершина не просмотрена
				if (D[m]>D[i])
					m=i; //ищем ближайшую смежную вершины
		p=m;
	}
	f << D[Node2] << endl;
	cout << "Длина: "<<D[Node2] << "\n" << "Путь: ";//вывод результата
	vector<int>temp;     // n - 1, так как не забываем про индексацию
	for(int i = p;i != -1;i = parent.at(i))
		temp.push_back(i+1);
	reverse(temp.begin(),temp.end());
	for(int i = 0;i<temp.size();++i)
	{
		cout << temp.at(i) << " ";
		f << temp.at(i) << " ";
	}
	cout << endl;
}

int main()
{
	int n,i,j,k1,k2,l;
	ifstream f;
	f.open("a.txt",ios::in);
	cout << "Введите количество вершин:";
	cin>>n;
	int **a;
        a=new int *[n];//задаем массив из n элементов, каждый из которых является адресом строки
	for(i=0;i<n;i++)
		a[i]=new int[n];
	for (i=0;i<n;i++)
		a[i]=new int[n]; //выделяем память  под каждую строку массива
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			f>>a[i][j];
	for(i =0;i<n;i++)
	{
		for(j=0;j<n;j++)
			cout << setw(4) << a[i][j] << "   ";
		cout << "\n";
	}
	f>>k1;//начальная вершина
	cout << "Начальная точка: " << k1 << endl;
	f>>k2;//конечная вершина
	cout << "Конечная точка: " << k2 << endl;
	Dijkstra(n, a, k1,k2 );
	return 0;
}
