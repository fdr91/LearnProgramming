#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define FIELD_SIZE 8
vector<int> x(FIELD_SIZE, 0);//позиция ферзя на i-й вертикали
vector<int> a(FIELD_SIZE, 1);//на i-й горизонтали нет ферзя
map<int,bool> b;//на i-й диагонали h8-a1 нет ферзя
map<int,bool> c;//на i-й диагонали a8-h1 нет ферзя

bool tryPut(int i){
	int j = 0;
	for (int j = 0; j < FIELD_SIZE; j++){
		if (a[j] && b[i+j] && c[i-j]){
			x[i] = j+1;
			a[j] = b[i + j] = c[i - j] = false;
			if (i == FIELD_SIZE-1) return true;//Позиция найдена
			if (tryPut(i + 1)) return true;
			a[j] = b.at(i + j) = c.at( i - j) = true;
		}
	}
	return false;
}

void printResult(){
	for (int i = 0; i < FIELD_SIZE; i++){
		for (int j = 0; j < FIELD_SIZE; j++)
			if (x[i]==j+1) cout << "+ ";
				else cout << "- ";
		cout << endl;
	}
}

int main(int argc, char** argv){
	if (argc != 1){
		cout << "Usage: EightQueen.exe" << endl;
		exit(-1);
	}
	for (int i = 0; i < FIELD_SIZE; i++){
		for (int j = 0; j < FIELD_SIZE; j++){
			b[i + j] = c[i - j] = true;
		}
	}
	tryPut(0);
	printResult();
	system("PAUSE");
	return 0;
}