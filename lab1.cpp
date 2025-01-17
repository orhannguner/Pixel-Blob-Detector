﻿

#include<iostream>
#include<fstream>

using namespace std;

int recursive(char* Box, int column, int row, int i, int n) {
	while (i < (column * row)) {
		if (Box[i + 1] == 'x') {
			n++;
			n += 1000000;
			Box[i + 1] = 'k';
			n = recursive(Box, column, row, i + 1, n);
		}
		else if (Box[i + column] == 'x') {
			n++;
			n += 1000;
			Box[i + column] = 'k';
			n = recursive(Box, column, row, i + column, n);
		}
		else if (Box[i - column] == 'x') {
			n++;
			Box[i - column] = 'k';
			n = recursive(Box, column, row, i - column, n);
		}
		else if (i % column != 0) {
			if (Box[i - 1] == 'x') {
				n++;
				Box[i - 1] = 'k';
				n = recursive(Box, column, row, i - 1, n);
			}
			else {
				return n;
			}
		}
		else return n;

	}

}
int Pixel(int num, int num2, char Pixel_box[], int column)
{
	for (int i = num; i < (num2); i++) {
		cout << Pixel_box[i];
		if (i % column == column - 1) cout;
	}
	return 0;
}
int recursive_ucgen(char* Box, int column, int row, int i, int n) {
	while (i < (column * row)) {
		if (Box[i + column - 1] == 'k') {
			n++;
			Box[i + column - 1] = 'h';
			return recursive_ucgen(Box, column, row, i + 1 + column, n);
		}
		else return n;
	}
}
int main() {
	int row, column;
	ifstream read;
	string fileName;
	cout << "Enter the file name: " << endl;
	cin >> fileName;
	read.open(fileName);
	read >> row >> column;

	char* Pixel_box = new char[row * column];
	char pix;

	for (int k = 0; k < (row * column); k++) {
		read >> noskipws >> pix;
		if (pix == '\n') {
			k--;
			continue;
		}
		Pixel_box[k] = pix;
	}
	cout << "  ";
	for (int i = 0; i < column; i++)
	{
		cout << i % 10;
	}
	cout << "  ";
	cout << endl;
	cout << " +";
	for (int i = 0; i < column; i++)
	{
		cout << "-";
	}
	cout << "+ " << endl;
	int num;
	int num2;
	for (int i = 0; i < row; i++)
	{
		cout << i % 10 << "|";
		num = (i * column);
		num2 = (i + 1) * 20;
		Pixel(num, num2, Pixel_box, column);
		cout << "|" << i % 10 << endl;

	}
	cout << " +";
	for (int i = 0; i < column; i++)
	{
		cout << "-";
	}
	cout << "+ " << endl;
	cout << "  ";
	for (int i = 0; i < column; i++)
	{
		cout << i % 10;
	}
	cout << endl;
	read.close();
	int sayac = 0;
	cout << endl << endl << endl << "+------+------------+---------+------------+" << endl;
	cout << "| BLOB | NoOfPixels | CoM Row | CoM Column |" << endl;
	cout << "+------+------------+---------+------------+" << endl;
	for (int i = 0; i < (column * row); i++) {
		if (Pixel_box[i] == 'x') {
			if (Pixel_box[i + column - 1] != 'x') {
				sayac++;
				int sum = recursive(Pixel_box, column, row, i, 0);
				int n = sum % 100;
				int lenght = sum / 1000000 + 1;
				int high = n / lenght;
				double y_konum = (i / column) + ((float)(high - 1) / 2);
				double x_konum = (i % column) + ((float)(lenght - 1) / 2);
				cout << "|     " << sayac << "|          " << n << "|        " << y_konum << "|          " << x_konum << "|" << endl;
			}
			else if (i % column == 0) {
				sayac++;
				int sum = recursive(Pixel_box, column, row, i, 0);
				int n = sum % 100;
				int lenght = sum / 1000000 + 1;
				int high = n / lenght;
				double y_konum = (i / column) + ((float)(high - 1) / 2);
				double x_konum = (i % column) + ((float)(lenght - 1) / 2);
				cout << "|     " << sayac << "|          " << n << "|        " << y_konum << "|         " << x_konum << "|" << endl;
			}
			else {
				int sum = recursive(Pixel_box, column, row, i, 0);
				if (Pixel_box[i - 1] == 'h') {
					while (Pixel_box[i] == 'h') i++;
				}
				sayac++;
				int n = sum % 100;
				int high = recursive_ucgen(Pixel_box, column, row, i, 0);
				high++;
				int lenght = 1;
				for (int i = 1; i < high; i++) {
					lenght += 2;
				}
				double x_konum = (i % column);
				double y_konum = (i / column) + ((float)(high - 1) * 2 / 3);
				cout << "|     " << sayac << "|          " << n << "|  " << y_konum << "|           " << x_konum << "|" << endl;
			}

		}
	}

	delete Pixel_box;
	return 0;
}