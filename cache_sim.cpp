#include <iostream>
#include <fstream>
#include <string> 

using namespace std;

/* Prosty symulator
	48 bitow - pamiec wirtualna
		32 - znacznik
		10 - wiersz
		3 - offset
		3 - bajt

	Mamy do dyspozycji pamiec o 8*1024 8 bajtowych komorek.
	1024 wiersze po 8 blokow
*/

int main()
{
	int block, blockMask = 0;
	cin>>block;
	for(int i = 0; i < block; i++)
		blockMask = (blockMask<<1)+1;
	blockMask<<=3; // przesuwam za 3 pierwsze bity ( adresujace bajty)

	
	int cache[(8*1024)>>block];
	bool akt[(8*1024)>>block];
	
	long long int memCell, ins, memRefCount = 0, misses = 0;
	int bits, tag, row, rowMask = 0xFFF8 xor blockMask; // 48 bitów adresu - [32 -znacznik, 10 -wiersz, 3 - Off, 3-bajt] offset, offMask = 0x38
	//cout<< hex << rowMask <<endl;
	string isWrite = ": W ";
	char buff[5];
	
	do{
		cin >> hex >> ins;
		cin.get(buff, 5);
		cin >> hex >> memCell;
		cin >> bits;
		tag = memCell >>(3+3+10);
		row = (memCell & rowMask)>>6;
		//cout << "ROW: " << hex <<row << "\tTAG: " << tag << endl;
		if(akt[row])
		{
			if(cache[row] != tag)
			{
				//cout <<"miss in " << hex << ins<< endl;
				misses++;
			}
		}
		else
		{
			akt[row] = true;
		}	
		cache[row] = tag;
		memRefCount++;
	}while( cin.good());
	cout<<"Rozmiar tablicy " << sizeof(cache)/sizeof(cache[0]) << "\t Rozmiar bloku: " << block << endl;
	cout<<"MISSES: " << dec<< misses<<endl;
	cout<<"MISSES RATE: " << dec<< (double)misses/memRefCount<<endl;
	return 0;
}

/*

		string temp = (str == ptr) ? "W" :"R";
		cout << y << " "<<  temp << " " << z << endl;
	*/
