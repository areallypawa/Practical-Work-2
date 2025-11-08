#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define RED     "\033[31m"
#define BLUE    "\033[94m"
#define GREEN   "\033[32m"
#define GREY    "\033[90m"
#define RESET   "\033[0m"

const int LEN_ARRAY = 5;
const string Sort = "quick";
const int BREAK_CODE = 993;

void clear() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void pause() {
	cout << '\n';
	system("Pause");
}

void print_main_menu(int *array, bool &is_array) {
	clear();

	cout << "  ============================================" << endl;
	cout << " | ";

	if (is_array) {
		cout << "Status:" << BLUE << setw(35) << "Array ready " << RESET << "|" << endl;
	}
	else {
		cout << "Status:" << RED << setw(35) << "None array " << RESET << "|" << endl;
	}
	

	cout << " |===========================================|" << endl;
	cout << " | 1 - Создать массив                        |" << endl;

	if (is_array) {
		
		cout << " | 2 - Вывести массив                        |" << endl;
		cout << " | 3 - Сортировка массива                    |" << endl;
		cout << " | 4 - Мин/Макс элементы                     |" << endl;
		cout << " | 5 - Среднее мин/макс + индексы            |" << endl;
		cout << " | 6 - Кол-во < a (в отсорт.)                |" << endl;
		cout << " | 7 - Кол-во > b (в отсорт.)                |" << endl;
		cout << " | 8 - Поиск числа (бинарный + линейный)     |" << endl;
		cout << " | 9 - Обмен элементов (с таймером)          |" << endl;
		cout << " | 10 - Interpolation search VS Binary Search|" << endl;
	}
	else {
		cout << GREY;
		cout << " | 2 - Вывести массив                 [lock] |" << endl;
		cout << " | 3 - Сортировка массива             [lock] |" << endl;
		cout << " | 4 - Мин/Макс элементы              [lock] |" << endl;
		cout << " | 5 - Среднее мин/макс + индексы     [lock] |" << endl;
		cout << " | 6 - Кол-во < a (в отсорт.)         [lock] |" << endl;
		cout << " | 7 - Кол-во > b (в отсорт.)         [lock] |" << endl;
		cout << " | 8 - Поиск числа                    [lock] |" << endl;
		cout << " | 9 - Обмен элементов                [lock] |" << endl;
		cout << " | 10 - Interpolation search VS\n | Binary Search                      [lock] |" << endl;
		cout << RESET;
	}

	cout << " | 0 - Перезапуск                            |" << endl;
	cout << "  ============================================" << endl;
}

void create_auto_array(int *array);
void create_hand_array(int *array);
void copy_array(int* array, int* array_copy);

void print_array_menu(int *array, int *array_copy, bool &flag) {
	clear();
	int user_choice;
	flag = false;
	cout << "  ================================" << endl;
	cout << " | Status:" << GREEN << setw(23) << "  CREATE ARRAY " << RESET << "|" << endl;
	cout << " | Size Array:" << GREEN << setw(18) << LEN_ARRAY << RESET << " |" << endl;
	cout << " |===============================|" << endl;
	cout << " | 1 - Сгенерировать массив      |" << endl;
	cout << " | 2 - Ввести массив вручную     |" << endl;
	cout << " | 0 - Выход                     |" << endl;
	cout << " ================================" << endl;
	cout << "Выбери действие (0-2): ";
	cin >> user_choice;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	switch (user_choice) {
	case 1: 
		create_auto_array(array);
		copy_array(array, array_copy);
		break;
	case 2: 
		create_hand_array(array);
		copy_array(array, array_copy);
		break;
	}
}

void copy_array(int* array, int* array_copy) {
	for (int i = 0; i < LEN_ARRAY; ++i) {
		array_copy[i] = array[i];
	}
}

void create_auto_array(int *array) {
	srand(time(NULL));
	for (int i = 0; i < LEN_ARRAY; ++i) {
		array[i] = rand() % 199 - 99;
	}
}

void create_hand_array(int *array) {
	for (int i = 0; i < LEN_ARRAY; i++)
		cin >> array[i];
}

void delete_array(int* array) {
	fill(array, array + LEN_ARRAY, -1000);
}

void read_array(int* array) {
	for (int i = 0; i < LEN_ARRAY; i++)
		cout << array[i] << ' ';
}

int binary_search(int *arr, int &target) {
	int left = 0, right = LEN_ARRAY - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] == target) return mid;
		if (arr[mid] < target) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
}

int interpolation_search(int* arr, int &target) {
	int left = 0;
	int right = LEN_ARRAY - 1;

	while (left <= right && target >= arr[left] && target <= arr[right]) {
		if (left == right) {
			if (arr[left] == target) return left;
			return -1;
		}

		int pos = left + ((double)(target - arr[left]) * (right - left)) / (arr[right] - arr[left]);

		if (arr[pos] == target)
			return pos;
		else if (arr[pos] < target)
			left = pos + 1;
		else
			right = pos - 1;
	}

	return -1; 
}

void quick_sort(int *arr, int  st, int en, bool& flag) {

	flag = true;
	int pilot = arr[en];
	int i = st - 1;
	while (st < en) {
		if (pilot >= arr[st]) {
			i++;
			swap(arr[i], arr[st]);
		}
		st++;
	}
	swap(arr[i + 1], arr[en]);

	if (i > 0) {
		quick_sort(arr, 0, i, flag);
	}
	if ((i + 2) < en) {
		quick_sort(arr, i + 2, en, flag);
	}
}

void bubble_sort(int* arr, bool& flag) {
	flag = true;
	for (int i = 0; i < LEN_ARRAY; i++) {
		for (int j = 0; j < LEN_ARRAY - i - 1; j++) {
			if (arr[j+1] < arr[j]) {
				swap(arr[j+1], arr[j]);
			}
		}
	}
}

void shaker_sort(int* arr, bool& flag) {
	flag = true;
	int left = 0, right = LEN_ARRAY - 1;
	while (left <= right) {
		// Проход слева направо
		for (int i = left; i < right; ++i) {
			if (arr[i] > arr[i + 1]) swap(arr[i], arr[i + 1]);
		}
		--right;

		// Проход справа налево
		for (int i = right; i > left; --i) {
			if (arr[i] < arr[i - 1]) swap(arr[i], arr[i - 1]);
		}
		--left;
	}
}

void insertion_sort(int* arr, bool& flag) {
	flag = true;
	for (int i = 1; i < LEN_ARRAY; i++) {
		int key = arr[i];
		int j = i - 1;
		// pos ffor key
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

void selection_sort(int* arr, bool& flag) {
	for (int i = 0; i < LEN_ARRAY - 1; ++i) {
		int minIdx = i;
		// mini
		for (int j = i + 1; j < LEN_ARRAY; ++j) {
			if (arr[j] < arr[minIdx]) {
				minIdx = j;
			}
		}
		swap(arr[i], arr[minIdx]);
	}
}

void chek_array_sort(int* array, bool& array_already_sort) {
	if (!array_already_sort) {
		if (Sort == "quick") {
			quick_sort(array, 0, LEN_ARRAY - 1, array_already_sort);
		}
		else if (Sort == "bubble") {
			bubble_sort(array, array_already_sort);
		}
		else if (Sort == "shaker") {
			shaker_sort(array, array_already_sort);
		}
		else if (Sort == "insert") {
			insertion_sort(array, array_already_sort);
		}
		else if (Sort == "select") {
			selection_sort(array, array_already_sort);
		}
	}
}

void search_medium_index(int *array, int &medium) {
	int count = 0;
	cout << "Index`s: ";
	for (int i = 0; i < LEN_ARRAY; i++) {
		if (array[i] == medium) {
			cout << i << ' ';
			count++;
		}
	}
	cout << " Количество: " << count;
}

int main() {
	setlocale(LC_ALL, "RU");
	int array[LEN_ARRAY];
	int array_copy[LEN_ARRAY]; // NSA (Not Sorted Array)
	bool array_already_sort = 0;

	while (true) {
		int user_choice;
		bool is_array = !(array[0] < -100);
		print_main_menu(array, is_array);
		cout << "Input: ";
		cin >> user_choice;

		if (cin.fail()) {
			cin.clear(); 
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
			continue;
		}
		
		if (user_choice == 1) {
			print_array_menu(array, array_copy, array_already_sort);
		}
		else if (user_choice == BREAK_CODE) {
			break;
		}
		else {
			if (is_array) {
				cout << "Output:\n";
				switch (user_choice) {
				case 0:
					delete_array(array);
					break;
				case 1:
					// Create array
					print_array_menu(array, array_copy, array_already_sort);
					break;
				case 2:
					// Read array
					read_array(array);
					pause();
					break;
				case 3:
					// Sort Array + print time
				{
					auto start = high_resolution_clock::now();

					chek_array_sort(array, array_already_sort);
					//quick_sort(array, 0, LEN_ARRAY - 1, array_already_sort);
					//bubble_sort(array, array_already_sort);

					auto end = high_resolution_clock::now();
					auto duration = duration_cast<nanoseconds>(end - start).count();
					cout << "Сортировка завершена за " << duration << " наносекунд.\n";
					pause();
					break;
				}
				case 4:
				{
					chek_array_sort(array, array_already_sort);
					// Min - max elements 
					auto start1 = high_resolution_clock::now();
					cout << "Min:" << array[0] << "  Max: " << array[LEN_ARRAY - 1];
					auto end1 = high_resolution_clock::now();
					auto duration1 = duration_cast<nanoseconds>(end1 - start1).count();
					cout << "\nПоиск в отсортированном массиве завершен за   " << duration1 << " наносекунд.\n";

					auto start2 = high_resolution_clock::now();
					int mini = array_copy[0], maxi = array_copy[0];
					for (int i = 1; i < LEN_ARRAY; i++) {
						if (array_copy[i] < mini) {
							mini = array_copy[i];
						}
						else if (array_copy[i] > maxi) {
							maxi = array_copy[i];
						}
					}
					cout << "Min:" << mini << "  Max: " << maxi;
					auto end2 = high_resolution_clock::now();
					auto duration2 = duration_cast<nanoseconds>(end2 - start2).count();
					cout << "\nПоиск в НЕотсортированном массиве завершен за " << duration2 << " наносекунд.\n";

					pause();
					break;
				}
				case 5:
				{
					chek_array_sort(array, array_already_sort);
					int medium;
					// SORTED 
					auto start1 = high_resolution_clock::now();
					medium = (array[0] + array[LEN_ARRAY - 1]) / 2;
					cout << "Medium (sort) " << medium << '\n';
					search_medium_index(array, medium);
					auto end1 = high_resolution_clock::now();
					auto duration1 = duration_cast<nanoseconds>(end1 - start1).count();

					// NOT SORTED 
					auto start2 = high_resolution_clock::now();
					int mini = array_copy[0], maxi = array_copy[0];
					for (int i = 1; i < LEN_ARRAY; i++) {
						if (array_copy[i] < mini) {
							mini = array_copy[i];
						}
						else if (array_copy[i] > maxi) {
							maxi = array_copy[i];
						}
					}
					medium = (mini + maxi) / 2;
					cout << "\nMedium (Not sort) " << medium << '\n';
					search_medium_index(array_copy, medium);
					auto end2 = high_resolution_clock::now();
					auto duration2 = duration_cast<nanoseconds>(end2 - start2).count();
					cout << "\n\nПоиск в   отсортированном массиве завершен за " << duration1 << " наносекунд.\n";
					cout << "Поиск в НЕотсортированном массиве завершен за " << duration2 << " наносекунд.\n";
					pause();
					break;
				}
				case 6:
				{
					chek_array_sort(array, array_already_sort);

					int task_int_a;
					cout << "Введи число a: ";
					cin >> task_int_a;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						continue;
					}

					cout << "Числа < a: ";
					for (int i = 0; i < LEN_ARRAY; i++) {
						if (array[i] < task_int_a) {
							cout << array[i] << ' ';
						}
					}
					pause();
					break;
				}
				case 7:
				{
					chek_array_sort(array, array_already_sort);

					int task_int_b;
					cout << "Введи число b: ";
					cin >> task_int_b;
					
					if (cin.fail()) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						continue;
					}

					cout << "Числа > b: ";
					for (int i = 0; i < LEN_ARRAY; i++) {
						if (array[i] > task_int_b) {
							cout << array[i] << ' ';
						}
					}
					pause();
					break;
				}
				case 8:
				{
					chek_array_sort(array, array_already_sort);

					int task_int_c;
					int idx_c;
					bool found_c = false;
					cout << "Введи число C: ";
					cin >> task_int_c;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						continue;
					}

					auto start1 = high_resolution_clock::now();
					idx_c = binary_search(array, task_int_c);
					if (idx_c != -1) {
						cout << "S: Число " << task_int_c << " есть в массиве под индексом " << idx_c << '\n';
					}
					else {
						cout << "S: Числа " << task_int_c << " нет в массиве" << '\n';
					}
					auto end1 = high_resolution_clock::now();
					auto duration1 = duration_cast<nanoseconds>(end1 - start1).count();

					auto start2 = high_resolution_clock::now();
					for (int i = 0; i < LEN_ARRAY; i++) {
						if (array[i] == task_int_c) {
							cout << "N.S: Число " << task_int_c << " есть в массиве под индексом " << i << '\n';
							found_c = true;
						}
					}
					if (!found_c) {
						cout << "N.S: Числа " << task_int_c << " нет в массиве" << '\n';
					}
					auto end2 = high_resolution_clock::now();
					auto duration2 = duration_cast<nanoseconds>(end2 - start2).count();
					cout << "\n\nПоиск в   отсортированном массиве завершен за " << duration1 << " наносекунд.\n";
					cout << "Поиск в НЕотсортированном массиве завершен за " << duration2 << " наносекунд.\n";
					pause();
					break;
				}
				case 9:
				{
					int i, j;
					cout << "Введи индексы элементов: ";
					cin >> i >> j;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						continue;
					}

					if (i < 0 || i >= LEN_ARRAY || j < 0 || j >= LEN_ARRAY) {
						cout << "Ошибка: недопустимые индексы." << endl;
						pause();
						break;
					}

					cout << "Массив до: ";
					read_array(array);

					auto start = high_resolution_clock::now();

					swap(array[i], array[j]);

					auto end = high_resolution_clock::now();
					auto duration = duration_cast<nanoseconds>(end - start).count();

					cout << " | Массив после: ";
					read_array(array);

					cout << "\n\nМена завершена за " << duration << " наносекунд.\n";
					pause();
					break;
				}

				case 10:
					// IDZ
					chek_array_sort(array, array_already_sort);
					int target;
					cout << "Target: ";
					cin >> target;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						continue;
					}

					auto start1 = high_resolution_clock::now();
					int binResult = binary_search(array, target);
					auto end1 = high_resolution_clock::now();
					auto duration1 = duration_cast<nanoseconds>(end1 - start1).count();

					auto start2 = high_resolution_clock::now();
					int interpResult = interpolation_search(array, target);
					auto end2 = high_resolution_clock::now();
					auto duration2 = duration_cast<nanoseconds>(end2 - start2).count();

					if (binResult != -1)
						cout << "Бинарный поиск: элемент найден на позиции " << binResult << endl;
					else
						cout << "Бинарный поиск: элемент не найден." << endl;

					if (interpResult != -1)
						cout << "Интерполяционный поиск: элемент найден на позиции " << interpResult << endl;
					else
						cout << "Интерполяционный поиск: элемент не найден." << endl;

					cout << "\n\nBinary Search завершен за " << duration1 << " наносекунд.\n";
					cout << "\Interpolation Search завершен за " << duration2 << " наносекунд.\n";

					pause();
					break;
				}

			}
			else {
				continue;
			}
		}
	}
	return 0;
}
	
