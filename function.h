#pragma once
#include <iostream>
#include "windows.h" //для коректної укр мови та зміни кольрів у консолі
#include <ctime> //для рандомного пошуку
#include <fstream> // для файлового ввода/вивода
#include <string> // Шаблонний клас стрінг
#include <vector>
#include <iterator> // заголовочный файл итераторов
using namespace std;

const int ROW = 5;//змінні відповідальні за розмір поля
const int COL = 5;
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};
enum difficulty{Easy = 3, Medium = 4, Hard = 5 };
struct points {//
	int player_points = 0;
	int size = 0;
	string* pl_words = new string[size];
}static f_player, s_player;
void show_1menu();
void show_2menu();

void SetColor(int text, ConsoleColor background);
void play_table(char table[ROW][COL]);
void load_title();
void load_words(string*&, int &size);
void increase_lib(string*& lib, int &size, string word);
void QuickSort(string *a, int start, int end);
int BinSearch(string* a, int start, int end, string key);
int linesearch(string* a, int start, int end, string key);
void show_arr(char table[ROW][COL]);
void add_to_lib(string);

void game(string f_word, string*& lib, int &lib_size, char table[ROW][COL], int difficulty);
bool checking(char table[ROW][COL]);
bool check_pos(char table[ROW][COL], int x, int y, vector<int>& moves);
string moving(char table[ROW][COL], string*& lib, int& lib_size);
string cpumov(char table[ROW][COL], string*& lib, int& lib_size, int difficulty);
int check_pos_cpu(char table[ROW][COL], int x, int y, int count, vector<int> &moves);
bool ch_past_pos(vector<int>& moves, int x, int y);
int next_pos_cpu(char table[ROW][COL], int x, int y, vector<int>& moves);

string check_if_empty(char table[ROW][COL], string*& lib, int& lib_size, int difficulty, vector<int>& stack_moves, int x, int y, string word, int& b);

