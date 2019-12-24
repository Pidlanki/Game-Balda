#include "function.h"

int main()
{
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	load_title();
	const int PVP = 0;
	int lib_size = 0;
	string* library = new string[lib_size];
	load_words(library, lib_size);
	char table[ROW][COL];
	play_table(table);
	QuickSort(library, 0, lib_size - 1);
	char ch;
	string f_word;
	
	do
	{
		show_1menu();
		cin >> ch;
		switch (ch)
		{
		case 'a':
			cout << "¬вед≥ть перше слово з п'€ти букв, або натисн≥ть клав≥шу \"r\" дл€ вибору випадкового слова ";
			do
			{
				cin >> f_word;
				if (f_word.size() != 5 && f_word != "r")
					cout << "¬вед≥ть слово €ке м≥стить 5 букв, або л≥теру \"r\"\n";
			} while (f_word.size() != 5 && f_word != "r");
			if (f_word != "r" && !BinSearch(library, 0, lib_size - 1, f_word)) {
				cout << "Cлова \"" << f_word << "\" немаЇ в словнику, хочете додати його в словник?(y/n): ";
				cin >> ch;
				if (ch == 'y') { add_to_lib(f_word); increase_lib(library, lib_size, f_word); QuickSort(library, 0, lib_size - 1); }
			}	
			game(f_word, library, lib_size, table, PVP);
			cout << "’очете з≥грати ще? (y/n) ";
			cin >> ch;
			break;
		case 'b':
			show_2menu();
			cin >> ch;
			switch (ch)
			{
			case 'a':
				cout << "¬вед≥ть перше слово з п'€ти букв, або натисн≥ть клав≥шу \"r\" дл€ вибору випадкового слова ";
				do
				{
					cin >> f_word;
					if (f_word.size() != 5 && f_word != "r")
						cout << "¬вед≥ть слово €ке м≥стить 5 букв, або л≥теру \"r\"\n";
				} while (f_word.size() != 5 && f_word != "r");
				if (f_word != "r" && !BinSearch(library, 0, lib_size - 1, f_word)) {
					cout << "Cлова \"" << f_word << "\" немаЇ в словнику, хочете додати його в словник?(y/n): ";
					cin >> ch;
					if (ch == 'y') { add_to_lib(f_word); increase_lib(library, lib_size, f_word); QuickSort(library, 0, lib_size - 1); }
				}
				game(f_word, library, lib_size, table, Easy);
				cout << "’очете з≥грати ще? (y/n) ";
				cin >> ch;
				break;
			case'b':
				break;
			case'c':
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		delete[]f_player.pl_words;
		delete[]s_player.pl_words;
	} while (ch != 'n');
	
	show_arr(table);
	delete[] library;
	return 0;
}