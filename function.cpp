#include "function.h"
//зміна кольору шрифта і фона
void SetColor(int text, ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
void show_1menu() {
	cout << "Оберіть режим:\n"
		<< "a. 2 гравці    b. проти комп'ютера\n";
}
void show_2menu() {
	cout << "Оберіть рівень інтелекту комп'тера:\n"
		<< "a. легкий    b. середній	c. важкий\n: ";
}
void load_title() {
	ifstream fin;
	string buff;
	fin.open("title.txt");
	if (!fin.is_open()) {
		cout << "file can't be open\n";
		exit(EXIT_FAILURE);
	}
	for (int i = 0; fin.good(); i++) {
		getline(fin, buff);
		for (int i = 0; buff[i]; i++) {
			if (buff[i] == '*') {
				SetColor(LightGreen, Black);
				cout << buff[i];
			}
			else {
				SetColor(Blue, Black); 
				cout << buff[i];
			}
		}
		cout << endl;
		SetColor(LightGreen, Black);
	}
	fin.close();
}
void play_table(char table[ROW][COL]) {
	for (int i = 0; i < ROW; i++){
		for (int j = 0; j < COL; j++){
			table[i][j] = '-';
		}
	}
}

//відображення гральної дошки та статистики
void show_arr(char table[ROW][COL]) {
	system("cls");
	load_title();
	cout << "\t\t\t\t   0 1 2 3 4\n";
	for (int i = 0; i < ROW; i++) {
		SetColor(LightGreen, Black);
		cout << "\t\t\t\t" << i << ": ";
		for (int j = 0; j < COL; j++) {
			if (table[i][j] != '-') SetColor(Black, LightBlue);
			else if (table[i][j] == '-') SetColor(LightBlue, LightBlue);
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
	SetColor(Blue, Black);
	cout << "Слова 1-го гравця: ";
	for (int i = 0; i < f_player.size; i++) {
		cout << f_player.pl_words[i] << ", ";
	}
	cout <<"\b\b." << endl;
	cout << "Очки: " << f_player.player_points << endl;
	cout << "Слова 2-го гравця: ";
	for (int i = 0; i < s_player.size; i++) {
		cout << s_player.pl_words[i] << ", ";
	}
	cout <<"\b\b." << endl;
	cout << "Очки: " << s_player.player_points << endl;
	cout << endl;
}
//завантаження нового слова у текстовий файл словник
void add_to_lib(string word) {
	ofstream fout;
	string buff;
	fout.open("custom_words.txt", ios_base::app);
	if (!fout.is_open()) {
		cout << "file can't be open\n";
		exit(EXIT_FAILURE);
	}
	fout << word << endl;
	fout.close();
}
//завантаження словника з тхт в масив
void load_words(string*& lib, int &size) {
	ifstream fin;
	string buff;
	fin.open("words.txt");
	if (!fin.is_open()) {
		cout << "file can't be open\n";
		exit(EXIT_FAILURE);
	}
	for (int i = 0; fin.good(); i++) {
		fin >> buff;
		increase_lib(lib, size, buff);
	}
	fin.close();
	fin.open("custom_words.txt");
	if (!fin.is_open()) {
		cout << "file can't be open\n";
		exit(EXIT_FAILURE);
	}
	for (int i = 0; fin.good(); i++) {
		fin >> buff;
		increase_lib(lib, size, buff);
	}
	fin.close();
}
void increase_lib(string*& lib, int &size, string word) {
	string* temp_arr = new string[size + 1];
	for (int i = 0; i < size; i++) {
		temp_arr[i] = lib[i];
	}
	temp_arr[size] = word;
	size++;
	delete[] lib;
	lib = temp_arr;
	temp_arr = nullptr;
}

void QuickSort(string *a, int start, int end) {
	int i = start, j = end;

	string middle = a[(start + end) / 2];

	do
	{
		while (middle > a[i]) i++;
		while (middle < a[j]) j--;

		if (i <= j) {
			swap(a[i], a[j]);
			i++;
			j--;
		}
	} while (i < j);

	if (i < end) QuickSort(a, i, end);
	if (j > start) QuickSort(a, start, j);

}
int BinSearch(string *a, int start, int end, string key) {
	
	if (start > end) return 0;
	
	int middle = (start + end) / 2;
	
	if (a[middle] == key) return middle;
	else if (key > a[middle]) return BinSearch(a, middle + 1, end, key);
	else if (key < a[middle]) return BinSearch(a, start, middle - 1, key);
	
}
int linesearch(string* a, int start, int end, string key) {
	for (int i = start; i < end; i++) {
		if (a[i] == key) return 1;
	}
	return 0;
}

void game(string f_word, string*& lib, int &lib_size, char table[ROW][COL], int difficulty) {
	string word;
	int step_count = 0;
	
	if (f_word == "r") {
		while (f_word.size() != 5) {
			f_word = lib[rand() % (lib_size - 1)];
		}
	}

	for (int i = 0; i < 5; i++) {
		table[2][i] = f_word[i];
	}
	do {
		word.clear();
		show_arr(table);
		/*for (int i = 0; i < lib_size; i++) {
			cout << lib[i] << " ";
		}*/
		cout << endl;
		step_count++;
		SetColor(Red, Black);
		(step_count % 2) ? (cout << "Ходить 1-й гравець:\n") : (cout << "Ходить 2-й гравець:\n");
		SetColor(Blue, Black);
		if (!difficulty) word = moving(table, lib, lib_size);
		else if (!(step_count % 2) && difficulty) 
			word = cpumov(table, lib, lib_size, difficulty);
		else if (step_count % 2 && difficulty)  
			word = moving(table, lib, lib_size);
		if (step_count % 2) {
			increase_lib(f_player.pl_words, f_player.size, word);
			f_player.player_points += word.size();
		}
		else {
			increase_lib(s_player.pl_words, s_player.size, word);
			s_player.player_points += word.size();
		}
	} while (checking(table));
	if (f_player.player_points > s_player.player_points) cout << "Перший гравець переміг!\n";
	else if (f_player.player_points < s_player.player_points) cout << "Другий гравець переміг!\n";
	else cout << "Нічия!\n";	
}
//перевірка на вільні клітитки на столі
bool checking(char table[ROW][COL]) {
	int count = 0;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (table[i][j] == '-')
				count++;
		}
	}
	if (!count) return 0;
	//else if (letter == '1') return 0;
	else return 1;
}
//перевірка коректності вводу координат
bool check_pos(char table[ROW][COL], int x, int y, vector<int>& moves) {
	if (x < 5 && x >= 0 && y < 5 && y >= 0) {
		if ((table[x + 1][y] != '-' && x + 1 < 5 && !ch_past_pos(moves, x + 1, y)) || (table[x - 1][y] != '-' && x - 1 >= 0 && !ch_past_pos(moves, x - 1, y))
			|| (table[x][y + 1] != '-' && y + 1 < 5 && !ch_past_pos(moves, y + 1, y)) || (table[x][y - 1] != '-' && x - 1 >= 0 && !ch_past_pos(moves, y - 1, y))) return false;
	}
	else return true;
}

string moving(char table[ROW][COL], string*& lib, int &lib_size) {
	string word;
	char move, letter;
	int x, y;
	int count = 0, count_new_let = 0;
	int temp_x, temp_y; // тимчасові змінні для запам'ятовування клітинки з всталеною буквою
	vector<int> stack_moves;
	
	do
	{
		if (count == 0) {
			cout << "Введіть координати початковаї клітинки, використовуючи пробіл: ";
			do
			{
				cin >> x >> y;
				if (check_pos(table, x, y, stack_moves))
					cout << "Невірні координати, введіть координати клітинки яка знаходиться по сусідству з іншою літерою для утворення слова: ";
			} while (check_pos(table, x, y, stack_moves));
		}
		
		if (table[x][y] == '-' && count == 0 ) {
			cout << "Введіть першу літеру: ";
			cin >> letter;
			word += letter;
			table[x][y] = letter;
			temp_x = x;
			temp_y = y;
			count++;
			count_new_let++;
			stack_moves.insert(stack_moves.end(), x);
			stack_moves.insert(stack_moves.end(), y);
		}
		else if (table[x][y] != '-' && count == 0) {
			word += table[x][y];
			count++;
			stack_moves.insert(stack_moves.end(), x);
			stack_moves.insert(stack_moves.end(), y);
		}
		cout << "Наступний хід: ";
		cin >> move;
		switch (move)
		{
		case 'w':
			if (table[x - 1][y] != '-' && x - 1 >= 0 && !ch_past_pos(stack_moves, x - 1, y)) {
				word += table[--x][y];
				cout << word << endl;
				count++;
				stack_moves.insert(stack_moves.end(), x);
				stack_moves.insert(stack_moves.end(), y);
			}
			else if (table[x - 1][y] == '-' && x - 1 >= 0 && count_new_let == 0) {
				cout << "Введіть літеру: ";
				cin >> letter;
				word += letter;
				table[x - 1][y] = letter;
				cout << word << endl;
				x--;
				temp_x = x;
				temp_y = y;
				count++;
				count_new_let++;
				stack_moves.insert(stack_moves.end(), x);
				stack_moves.insert(stack_moves.end(), y);
			}
			break;
		case 'd':
			if (table[x][y + 1] != '-' && y + 1 < 5 && !ch_past_pos(stack_moves, x, y + 1)) {
				word += table[x][++y];
				cout << word << endl;
				count++;
				stack_moves.insert(stack_moves.end(), x);
				stack_moves.insert(stack_moves.end(), y);
			}
			else if (table[x][y + 1] == '-' && y + 1 < 5 && count_new_let == 0) {
				cout << "Введіть літеру: ";
				cin >> letter;
				word += letter;
				table[x][y + 1] = letter;
				cout << word << endl;
				y++;
				temp_x = x;
				temp_y = y;
				count++;
				count_new_let++;
				stack_moves.insert(stack_moves.end(), x);
				stack_moves.insert(stack_moves.end(), y);
			}
			break;
		case 's':
			if (table[x + 1][y] != '-' && x + 1 < 5 && !ch_past_pos(stack_moves, x + 1, y)) {
				word += table[++x][y];
				cout << word << endl;
				count++;
				stack_moves.insert(stack_moves.end(), x);
				stack_moves.insert(stack_moves.end(), y);
			}
			else if (table[x + 1][y] == '-' && x + 1 < 5 && count_new_let == 0) {
				cout << "Введіть літеру: ";
				cin >> letter;
				word += letter;
				table[x + 1][y] = letter;
				cout << word << endl;
				x++;
				temp_x = x;
				temp_y = y;
				count++;
				count_new_let++;
				stack_moves.insert(stack_moves.end(), x);
				stack_moves.insert(stack_moves.end(), y);
			}
			break;
		case 'a':
			if (table[x][y - 1] != '-' && y - 1 >= 0 && !ch_past_pos(stack_moves, x, y - 1)) {
				word += table[x][--y];
				cout << word << endl;
				count++;
				stack_moves.insert(stack_moves.end(), x);
				stack_moves.insert(stack_moves.end(), y);
			}
			else if (table[x][y - 1] == '-' && y - 1 >= 0 && count_new_let == 0) {
				cout << "Введіть літеру: ";
				cin >> letter;
				word += letter;
				table[x][y - 1] = letter;
				cout << word << endl;
				y--;
				temp_x = x;
				temp_y = y;
				count++;
				count_new_let++;
				stack_moves.insert(stack_moves.end(), x);
				stack_moves.insert(stack_moves.end(), y);
			}
			break;
		case 'Q':
			if (!BinSearch(lib, 0, lib_size - 1, word)) {
				cout << "Cлова \"" << word << "\" немає в словнику, хочете додати його в словник?(y/n): ";
				cin >> move;
				if (move == 'y') {
					add_to_lib(word);
					increase_lib(lib, lib_size, word);
					QuickSort(lib, 0, lib_size - 1);
					return word;
				}
				else if (move == 'n') {
					cout << "Подумайте ще, aбо натисніть \"E\" для пропуска ходу\n: ";
					cin >> move;
					count = 0;
					if (count_new_let) table[temp_x][temp_y] = '-';
					count_new_let = 0;
					word.clear();
					stack_moves.clear();
					system("cls");
					if (move == 'E') return word;
					show_arr(table);
					break;
				}
			}
			else if (linesearch(f_player.pl_words, 0, f_player.size, word) || linesearch(s_player.pl_words, 0, s_player.size, word)) {
				cout << "Це слово вже використовувалось, думайте далі! Aбо пропускайте хід(\"E\")\n:";
				cin >> move;
				if (count_new_let) table[temp_x][temp_y] = '-';
				count = 0;
				count_new_let = 0;
				word.clear();
				if (move == 'E') return word;
				system("pause");
				system("cls");
				show_arr(table);
				break;
			}
			else  return word;
			break;
		default:
			break;
		}
	} while (true);
}
//cpumov: недолік - шукає слово по одному і тому ж шляху
string cpumov(char table[ROW][COL], string*& lib, int& lib_size, int difficulty) {

	int count = 0; // рахує кількість всталених букв
	int temp_x, temp_y; // тимчасові змінні для запам'ятовування клітинки з всталеною буквою
	string word;
	vector<int> stack_moves;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (check_pos_cpu(table, i, j, count, stack_moves) == 1) {
				for (int a = 97; a < 123; a++) {
					word += (char)a;
					count++;
					
					stack_moves.insert(stack_moves.end(), i);
					stack_moves.insert(stack_moves.end(), j);
					table[i][j] = (char)a;
					temp_x = i;
					temp_y = j;
					for (int b = 0, t_i = i, t_j = j; b < difficulty - 1; b++) {
						if (next_pos_cpu(table, t_i, t_j, stack_moves) == 12) {
							t_i++;
							word += table[t_i][t_j];
							stack_moves.insert(stack_moves.end(), t_i);
							stack_moves.insert(stack_moves.end(), t_j);
						}
						else if (next_pos_cpu(table, t_i, t_j, stack_moves) == 3) {
							t_i--;
							word += table[t_i][t_j];
							stack_moves.insert(stack_moves.end(), t_i);
							stack_moves.insert(stack_moves.end(), t_j);
						}
						else if (next_pos_cpu(table, t_i, t_j, stack_moves) == 6) {
							t_j++;
							word += table[t_i][t_j];
							stack_moves.insert(stack_moves.end(), t_i);
							stack_moves.insert(stack_moves.end(), t_j);
						}
						else if (next_pos_cpu(table, t_i, t_j, stack_moves) == 9) {
							t_j--;
							word += table[t_i][t_j];
							stack_moves.insert(stack_moves.end(), t_i);
							stack_moves.insert(stack_moves.end(), t_j);
						}
					}
					if (!BinSearch(lib, 0, lib_size - 1, word)) {
						if (count)
							table[temp_x][temp_y] = '-';
						count = 0;
						word.clear();
						stack_moves.clear();
						
					}
					else if (!linesearch(f_player.pl_words, 0, f_player.size, word) && !linesearch(s_player.pl_words, 0, s_player.size, word)) {
						
						return word;
					}
					else 
						if (count)
							table[temp_x][temp_y] = '-';
						count = 0;
						word.clear();
						stack_moves.clear();
				}
			}
			else if (check_pos_cpu(table, i, j, count, stack_moves) == 2) {
				for (int b = 0, t_i = i, t_j = j; b < difficulty; b++) {
					if (next_pos_cpu(table, t_i, t_j, stack_moves) == 12) {
						t_i++;
						b++;
						word += table[t_i][t_j];
						stack_moves.insert(stack_moves.end(), t_i);
						stack_moves.insert(stack_moves.end(), t_j);
					}
					else if (check_pos_cpu(table, i, j, count, stack_moves) == 1) {
						word = check_if_empty(table, lib, lib_size, difficulty, stack_moves, t_i, t_j, word, b);
						return word;
					}
					if (next_pos_cpu(table, t_i, t_j, stack_moves) == 3) {
						t_i--;
						b++;
						word += table[t_i][t_j];
						stack_moves.insert(stack_moves.end(), t_i);
						stack_moves.insert(stack_moves.end(), t_j);
					}
					else if (check_pos_cpu(table, i, j, count, stack_moves) == 2) {
						word = check_if_empty(table, lib, lib_size, difficulty, stack_moves, t_i, t_j, word, b);
						return word;
					}
					if (next_pos_cpu(table, t_i, t_j, stack_moves) == 6) {
						t_j++;
						b++;
						word += table[t_i][t_j];
						stack_moves.insert(stack_moves.end(), t_i);
						stack_moves.insert(stack_moves.end(), t_j);
					}
					else if (check_pos_cpu(table, i, j, count, stack_moves) == 3) {
						word = check_if_empty(table, lib, lib_size, difficulty, stack_moves, t_i, t_j, word, b);
						return word;
					}
					if (next_pos_cpu(table, t_i, t_j, stack_moves) == 9) {
						t_j--;
						b++;
						word += table[t_i][t_j];
						stack_moves.insert(stack_moves.end(), t_i);
						stack_moves.insert(stack_moves.end(), t_j);
					}
					else if (check_pos_cpu(table, i, j, count, stack_moves) == 4) {
						word = check_if_empty(table, lib, lib_size, difficulty, stack_moves, t_i, t_j, word, b);
						return word;
					}
				}
				if (!BinSearch(lib, 0, lib_size - 1, word)) {
					word.clear();
					stack_moves.clear();
				}
				else if (!linesearch(f_player.pl_words, 0, f_player.size, word) && !linesearch(s_player.pl_words, 0, s_player.size, word)) {

					return word;
				}
				else
					if (count)
						table[temp_x][temp_y] = '-';
				count = 0;
				word.clear();
				stack_moves.clear();
			}
		}
	}
	if (!BinSearch(lib, 0, lib_size - 1, word)) {
		cout << "В мене доволі примітивний алгоритм + я не можу додати нове слово до словника тому я не знайшов жодного слова, давай ти краще\n";
		word.clear();
	}
	//delete[] stack_moves;
	return word;
}
int check_pos_cpu(char table[ROW][COL], int x, int y, int count, vector<int>& moves) {
	if (table[x][y] == '-' && !count && ((table[x + 1][y] != '-' && x + 1 < 5 && !ch_past_pos(moves, x + 1, y)) || (table[x - 1][y] != '-' && x - 1 >= 0 && !ch_past_pos(moves, x - 1, y))
		|| (table[x][y + 1] != '-' && y + 1 < 5 && !ch_past_pos(moves, x, y + 1)) || (table[x][y - 1] != '-' && y - 1 >= 0 && !ch_past_pos(moves, x, y - 1)))) return 1;
	else if (table[x][y] != '-' && ((table[x + 1][y] != '-' && x + 1 < 5 && !ch_past_pos(moves, x + 1, y)) || (table[x - 1][y] != '-' && x - 1 >= 0 && !ch_past_pos(moves, x - 1, y))
		|| (table[x][y + 1] != '-' && y + 1 < 5 && !ch_past_pos(moves, x, y + 1)) || (table[x][y - 1] != '-' && y - 1 >= 0 && !ch_past_pos(moves, x, y - 1)))) return 2;
	else return 0;
}
int next_pos_cpu(char table[ROW][COL], int x, int y, vector<int>& moves) {
	if (table[x + 1][y] != '-' && x + 1 < 5 && !ch_past_pos(moves, x + 1, y)) return 12;
	if (table[x - 1][y] != '-' && x - 1 >= 0 && !ch_past_pos(moves, x - 1, y)) return 3;
	if (table[x][y + 1] != '-' && y + 1 < 5 && !ch_past_pos(moves, x, y + 1)) return 6;
	if (table[x][y - 1] != '-' && y - 1 >= 0 && !ch_past_pos(moves, x, y - 1)) return 9;
}

bool ch_past_pos(vector<int>& moves, int x, int y) {
	for (int i = 0; i < moves.size(); i += 2) {
		if (moves[i] == x && moves[i + 1] == y) return true;
	}
	return false;
}

string check_if_empty(char table[ROW][COL], string*& lib, int& lib_size, int difficulty, vector<int>& stack_moves, int x, int y, string word, int &b) {
	int temp_x, temp_y; // тимчасові змінні для запам'ятовування клітинки з всталеною буквою
	string temp_word;
	temp_word = word;
	int count = 0;
	for (int a = 97; a < 123; a++) {
		b++;
		temp_word += (char)a;
		table[x][y] = (char)a;
		temp_x = x;
		temp_y = y;
		count++;
		stack_moves.insert(stack_moves.end(), x);
		stack_moves.insert(stack_moves.end(), y);
		for ( int t_i = x, t_j = y; b < difficulty; b++) {
			if (next_pos_cpu(table, t_i, t_j, stack_moves) == 12) {
				t_i++;
				temp_word += table[t_i][t_j];
				stack_moves.insert(stack_moves.end(), t_i);
				stack_moves.insert(stack_moves.end(), t_j);
			}
			else if (next_pos_cpu(table, t_i, t_j, stack_moves) == 3) {
				t_i--;
				temp_word += table[t_i][t_j];
				stack_moves.insert(stack_moves.end(), t_i);
				stack_moves.insert(stack_moves.end(), t_j);
			}
			else if (next_pos_cpu(table, t_i, t_j, stack_moves) == 6) {
				t_j++;
				temp_word += table[t_i][t_j];
				stack_moves.insert(stack_moves.end(), t_i);
				stack_moves.insert(stack_moves.end(), t_j);
			}
			else if (next_pos_cpu(table, t_i, t_j, stack_moves) == 9) {
				t_j--;
				temp_word += table[t_i][t_j];
				stack_moves.insert(stack_moves.end(), t_i);
				stack_moves.insert(stack_moves.end(), t_j);
			}
		}
		if (!BinSearch(lib, 0, lib_size - 1, word)) {
			if (count) table[temp_x][temp_y] = '-';
			count = 0;
			word.clear();
			stack_moves.clear();
		}
		else if (BinSearch(lib, 0, lib_size - 1, temp_word) && !linesearch(f_player.pl_words, 0, f_player.size, temp_word) && !linesearch(s_player.pl_words, 0, s_player.size, temp_word))
			return temp_word;
	}
	if (count) table[temp_x][temp_y] = '-';
	temp_word.clear();
	stack_moves.clear();
	return temp_word;
}