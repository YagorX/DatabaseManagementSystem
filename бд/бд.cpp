#include <stdio.h>
#include <string.h>
#include <locale>
#include <ctype.h>
#include <cstring>
#include "memory.h"

const int max_count_person = 200;
const int max_lenght_name = 25; // максимальная длинна имени
const int max_lenght_suma = 10;
const int max_lenght_payed = 30; // максимальная длинна причины долга
const int max_count_people = 300;
const int max_time_lenght = 12;

struct Time
{
	int year;
	int month;
	int day;
};

struct Information
{
	char name[max_lenght_name];
	int suma;
	char prichina[max_lenght_payed];
	Time datecin;
};


void CreatedStructMaxPerson(Information*& arr)
{
	Information* mass = new Information[max_count_person];
	delete[] arr;
	arr = mass;
}

void CreatedStruct(Information*& arr, int size) 
{
	Information* mass = new Information[size];
	for (int i{}; i < size; i++) {
		mass[i] = arr[i];
	}
	delete[] arr;
	arr = mass;
}

void eat_newline(char* str)
{
	char* find;
	if ((find = strchr(str, '\n')) != NULL) {
		*find = '\0';
	}
}

int CinStructInfDolg(Information*& arr, int& size, int count_repeat, char* name, char* suma, char* prichina, char* time){
	Information newPeople;
	Information* newArr = new Information[count_repeat];
	const int max_lenght_buffer = 256;
	char buff[max_lenght_buffer];
	size = count_repeat;
	int lena_name = 0, lena_suma = 0, lena_prich = 0, lena_time = 0;
	char day[2], month[2], year[4];
	int counter{ 0 };
	printf("Введите данные о должнике (в формате: Имя должника Сумма долга Причина долга День.Месяц.Год)\n");
	gets_s(buff, max_lenght_buffer);
	while (count_repeat > 0) {
		gets_s(buff, max_lenght_buffer);
		for (int i{}; i < max_lenght_name; i++) {
			if (!(buff[i] == ' ' && isdigit(buff[i + 1]))) {
				name[i] = buff[i];
			}
			else {
				lena_name = i + 1;
				for (int j{}; j < max_lenght_suma; j++) {
					if (!(buff[lena_name + j] == ' ' && isalpha(buff[lena_name + j + 1]))) {
						suma[j] = buff[lena_name + j];
					}
					else {
						lena_suma = j + 1;
						for (int k{}; k < max_lenght_payed; k++) {
							if (!(buff[lena_name + lena_suma + k] == ' ' && isdigit(buff[lena_name + lena_suma + k + 1]))) {
								prichina[k] = buff[lena_name + lena_suma + k];
							}
							else {
								lena_prich = k + 1;
								for (int s{}; s < max_time_lenght + 1; s++) {
									if (buff[lena_name + lena_prich + lena_suma + s] != '\n' && buff[lena_name + lena_prich + lena_suma + s] != '\0')
										time[s] = buff[lena_name + lena_prich + lena_suma + s];
									else {
										lena_time = s + 1;
										break;
									}
								}
								break;
							}
						}
						break;
					}
				}
				break;
			}
		}
		// замена strcpy name + проверка
		for (int count{}; count < lena_name - 1; count++) {
			if (isdigit(name[count])) {
				printf("Неверно введено имя пользователя!");
				system("pause");
				return 0;
			}
			else {
				newPeople.name[count] = name[count];
			}
		}
		newPeople.name[lena_name - 1] = '\0';

		// проверка
		for (int count{}; count < lena_suma-1; count++) {
			if (isalpha(suma[count])) {
				printf("Неверно введена сумма долга\n");
				system("pause");
				return 0;
			}
		}
		newPeople.suma = strtol(suma, NULL, 10);

		// замена strcpy prichina + проверка
		for (int count{}; count < lena_prich - 1; count++) {
			if (isdigit(prichina[count])) {
				printf("Неверно введена причина\n");
				system("pause");
				return 0;
			}
			else {
				newPeople.prichina[count] = prichina[count];
			}
		}
		newPeople.prichina[lena_prich - 1] = '\0';

		// замена strcpy time
		day[0] = time[0];
		day[1] = time[1];
		month[0] = time[3];
		month[1] = time[4];
		year[0] = time[6];
		year[1] = time[7];
		year[2] = time[8];
		year[3] = time[9];
		for (int count{}; count < lena_time; count++) {
			if (isalpha(time[count])) {
				printf("Неверно введена дата\n");
				system("pause");
				return 0;
			}
		}
		newPeople.datecin.day = strtol(day, NULL, 10);
		newPeople.datecin.month = strtol(month, NULL, 10);
		newPeople.datecin.year = strtol(year, NULL, 10);
		if (newPeople.datecin.month == 1 || newPeople.datecin.month == 3 || newPeople.datecin.month == 5 || newPeople.datecin.month == 7 || newPeople.datecin.month == 8 || newPeople.datecin.month == 10 || newPeople.datecin.month == 12) {
			if (newPeople.datecin.day > 31) {
				printf("Неверно введено количество дней\n");
				system("pause");
				return 0;
			}
		}
		else if (newPeople.datecin.month == 2) {
			if (newPeople.datecin.day > 29) {
				printf("Неверно введено количество дней\n");
				system("pause");
				return 0;
			}
		}
		else {
			if (newPeople.datecin.day > 30) {
				printf("Неверно введено количество дней\n");
				system("pause");
				return 0;
			}
			else if (newPeople.datecin.month > 12) {
				printf("Неверно введен месяц\n");
				system("pause");
				return 0;
			}
		};
		newArr[counter] = newPeople;
		counter++;
		count_repeat--;
	}
	delete[] arr;
	arr = newArr;
	return 1;
}

void CoutStructInfDolg(Information* mass, int size)
{
	
	for (int i{}; i < 82; i++) {
		printf("-");
	}
	printf("\n");
	printf("| id |        Инициалы         |  Сумма   |          Причина        |    Дата    |\n");
	for (int i{}; i < 82; i++) {
		printf("-");
	}
	printf("\n");
	for (int j{}; j < size; j++) {
		printf("| %-3d| %-23s | %-8d | %-23s | %-02d.%-02d.%-4d |\n", j+1, mass[j].name, mass[j].suma, mass[j].prichina, mass[j].datecin.day, mass[j].datecin.month, mass[j].datecin.year);
		for (int i{}; i < 82; i++) {
			printf("-");
		}
		printf("\n");
	}
}


int AddStructInfDolg(Information*& arr, int& size, char* name, char* suma, char* prichina, char* time)
{
	Information people;
	Information* newArr = new Information[size + 1];
	const int max_lenght_buffer = 256;
	char buff[max_lenght_buffer];
	int lena_name = 0, lena_suma = 0, lena_prich = 0, lena_time = 0;
	char day[2], month[2], year[4];
	int counter{ 0 };
	printf("Введите данные о должнике (в формате: Имя должника Сумма долга Причина долга День.Месяц.Год)\n");
	gets_s(buff, max_lenght_buffer);
	gets_s(buff, max_lenght_buffer);
	for (int i{}; i < max_lenght_name; i++) {
		if (!(buff[i] == ' ' && isdigit(buff[i + 1]))) {
			name[i] = buff[i];
		}
		else {
			lena_name = i + 1;
			for (int j{}; j < max_lenght_suma; j++) {
				if (!(buff[lena_name + j] == ' ' && isalpha(buff[lena_name + j + 1]))) {
					suma[j] = buff[lena_name + j];
				}
				else {
					lena_suma = j + 1;
					for (int k{}; k < max_lenght_payed; k++) {
						if (!(buff[lena_name + lena_suma + k] == ' ' && isdigit(buff[lena_name + lena_suma + k + 1]))) {
							prichina[k] = buff[lena_name + lena_suma + k];
						}
						else {
							lena_prich = k + 1;
							for (int s{}; s < max_time_lenght + 1; s++) {
								if (buff[lena_name + lena_prich + lena_suma + s] != '\n' && buff[lena_name + lena_prich + lena_suma + s] != '\0')
									time[s] = buff[lena_name + lena_prich + lena_suma + s];
								else {
									lena_time = s + 1;
									break;
								}
							}
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}

	// замена strcpy name + проверка
	for (int count{}; count < lena_name - 1; count++) {
		if (isdigit(name[count])) {
			printf("Неверно введено имя пользователя!");
			system("pause");
			return 0;
		}
		else {
			people.name[count] = name[count];
		}
	}
	people.name[lena_name - 1] = '\0';

	// проверка
	for (int count{}; count < lena_suma - 1; count++) {
		if (isalpha(suma[count])) {
			printf("Неверно введена сумма долга\n");
			system("pause");
			return 0;
		}
	}
	people.suma = strtol(suma, NULL, 10);

	// замена strcpy prichina + проверка
	for (int count{}; count < lena_prich - 1; count++) {
		if (isdigit(prichina[count])) {
			printf("Неверно введена причина\n");
			system("pause");
			return 0;
		}
		else {
			people .prichina[count] = prichina[count];
		}
	}
	people.prichina[lena_prich - 1] = '\0';

	// замена strcpy time
	day[0] = time[0];
	day[1] = time[1];
	month[0] = time[3];
	month[1] = time[4];
	year[0] = time[6];
	year[1] = time[7];
	year[2] = time[8];
	year[3] = time[9];
	for (int count{}; count < lena_time; count++) {
		if (isalpha(time[count])) {
			printf("Неверно введена дата\n");
			system("pause");
			return 0;
		}
	}
	people.datecin.day = strtol(day, NULL, 10);
	people.datecin.month = strtol(month, NULL, 10);
	people.datecin.year = strtol(year, NULL, 10);
	if (people.datecin.month == 1 || people.datecin.month == 3 || people.datecin.month == 5 || people.datecin.month == 7 || people.datecin.month == 8 || people.datecin.month == 10 || people.datecin.month == 12) {
		if (people.datecin.day > 31) {
			printf("Неверно введено количество дней\n");
			system("pause");
			return 0;
		}
	}
	else if (people.datecin.month == 2) {
		if (people.datecin.day > 29) {
			printf("Неверно введено количество дней\n");
			system("pause");
			return 0;
		}
	}
	else if (people.datecin.month == 4 || people.datecin.month == 6 || people.datecin.month == 9 || people.datecin.month == 11) {
		if (people.datecin.day > 30) {
			printf("Неверно введено количество дней\n");
			system("pause");
			return 0;
		}
		
	}
	else {
		printf("Неверно введен месяц\n");
		system("pause");
		return 0;
	};

	for (int i = 0; i < size; i++) {
		newArr[i] = arr[i];
	}
	newArr[size] = people;
	delete[] arr;
	arr = newArr;
	size++;
	return 1;
}

void PprintPrich(Information* arr, int size, char* filter)
{
	for (int i{}; i < 82; i++) {
		printf("-");
	}
	printf("\n");
	printf("| id |        Инициалы         |  Сумма   |          Причина        |    Дата    |\n");
	for (int i{}; i < 82; i++) {
		printf("-");
	}
	printf("\n");
	for (int i{ 0 }; i < size; i++)
	{
		if (!strcmp(arr[i].prichina, filter)) {
			printf("| %-3d| %-23s | %-8d | %-23s | %-02d.%-02d.%-4d |\n", i + 1, arr[i].name, arr[i].suma, arr[i].prichina, arr[i].datecin.day, arr[i].datecin.month, arr[i].datecin.year);
			for (int i{}; i < 82; i++) {
				printf("-");
			}
			printf("\n");
		}
	}
}

void PprintName(Information* arr, int size, char* filter)
{
	for (int i{}; i < 82; i++) {
		printf("-");
	}
	printf("\n");
	printf("| id |        Инициалы         |  Сумма   |          Причина        |    Дата    |\n");
	for (int i{}; i < 82; i++) {
		printf("-");
	}
	printf("\n");
	for (int i{ 0 }; i < size; i++)
	{
		if (!strcmp(arr[i].name, filter)) {
			printf("| %-3d| %-23s | %-8d | %-23s | %-02d.%-02d.%-4d |\n", i + 1, arr[i].name, arr[i].suma, arr[i].prichina, arr[i].datecin.day, arr[i].datecin.month, arr[i].datecin.year);
			for (int i{}; i < 82; i++) {
				printf("-");
			}
			printf("\n");
		}
	}
}

void PprintSuma(Information* arr, int size, int suma)
{
	for (int i{}; i < 82; i++) {
		printf("-");
	}
	printf("\n");
	printf("| id |        Инициалы         |  Сумма   |          Причина        |    Дата    |\n");
	for (int i{}; i < 82; i++) {
		printf("-");
	}
	printf("\n");
	for (int i{ 0 }; i < size; i++)
	{
		if (arr[i].suma == suma) {
			printf("| %-3d| %-23s | %-8d | %-23s | %-02d.%-02d.%-4d |\n", i + 1, arr[i].name, arr[i].suma, arr[i].prichina, arr[i].datecin.day, arr[i].datecin.month, arr[i].datecin.year);
			for (int i{}; i < 82; i++) {
				printf("-");
			}
			printf("\n");
		}
	}
}

void PprintDate(Information* arr, int size, Time time)
{
	for (int i{}; i < 82; i++) {
			printf("-");
		}
		printf("\n");
		printf("| id |        Инициалы         |  Сумма   |          Причина        |    Дата    |\n");
		for (int i{}; i < 82; i++) {
			printf("-");
		}
		printf("\n");
		for (int i{ 0 }; i < size; i++) {
			if (time.day == arr[i].datecin.day && time.month == arr[i].datecin.month && time.year == arr[i].datecin.year) {
				printf("| %-3d| %-23s | %-8d | %-23s | %-02d.%-02d.%-4d |\n", i + 1, arr[i].name, arr[i].suma, arr[i].prichina, arr[i].datecin.day, arr[i].datecin.month, arr[i].datecin.year);
				for (int i{}; i < 82; i++) {
					printf("-");
				}
				printf("\n");
			}
		}
}

int FindStructInfDolg(Information* arr, int size, char* namefind, char* prichinafind, char* time)
{
	Time date;
	char day[2];
	char month[2];
	char year[4];
	int filter;
	char buff[256]{ 0 };
	char test[] = " ";
	if (size == 0) {
		printf("Массив струтур пуст, считатйе данные с файла или введите вручную!");
		return 0;
	}
	printf("Введите по какому фильтру вы хотите найти должника.\n");
	printf("(1) - По имени\n");
	printf("(2) - По сумме\n");
	printf("(3) - По причине долга\n");
	printf("(4) - По дате долга\n");
	if (scanf_s("%d", &filter) != 1) {
		printf("Ошибка ввода, попробуйте снова");
		return 0;
	}
	switch (filter)
	{
	case 1:
		printf("Введите имя по которому найти информацию\n");
		gets_s(buff, 256);
		gets_s(buff, 256);
		for (int i{}; i < 256; i++) {
			if (isalpha(buff[i]) || isalpha(buff[i+1])) {
				namefind[i] = buff[i];
			}
			else {
				namefind[i] = '\0';
				break;
			}
		}
		PprintName(arr, size, namefind);
		break;
	case 2:
		printf("Введите сумму по которой найти информацию\n");
		scanf_s("%d", &filter);
		PprintSuma(arr, size, filter);
		break;
	case 3:
		printf("Введите причину долга по которой найти информацию\n");
		gets_s(buff, 256);
		gets_s(buff, 256);
		for (int i{}; i < 256; i++) {
			if (isalpha(buff[i]) || isalpha(buff[i + 1])) {
				prichinafind[i] = buff[i];
			}
			else {
				prichinafind[i] = '\0';
				break;
			}
		}
		PprintPrich(arr, size, prichinafind);
		break;
	case 4:
		printf("Введите дату по которой найти информацию\n");
		scanf_s("%s", time, 20);
		day[0] = time[0];
		day[1] = time[1];
		month[0] = time[3];
		month[1] = time[4];
		year[0] = time[6];
		year[1] = time[7];
		year[2] = time[8];
		year[3] = time[9];
		date.day = strtol(day, NULL, 10);
		date.month = strtol(month, NULL, 10);
		date.year = strtol(year, NULL, 10);
		PprintDate(arr, size, date);
		break;
	default:
		printf("Данный фильтр не найден, попробуйте ещё раз");
		break;
	}
	return 0;
}

//удаление из массива по индексу. первое вхождение
void delindone(Information*& arr, int& size, int delindex) // индекс начинается с 1
{
	Information* mass2 = new Information[size - 1];
	for (int j = 0; j < size - 1; j++) {
		if ((j != delindex) && (j < delindex)){
			mass2[j] = arr[j];
		}
		else
		{
			mass2[j] = arr[j + 1];
		}
	}
	delete[] arr;
	arr = mass2;
	size--;
}

// удаление всех вхождений
void delind(Information*& arr, int& size, int delindex) // индекс начинается с 1
{
	int fs = 0; // счётчик для массива в который записываем
	Information* mass2 = new Information[size - 1];
	for (int j = 0; j < size - 1; j++) {
		if (j != delindex) {
			mass2[fs] = arr[j];
			fs++;
		}
	}
	delete[] arr;
	arr = mass2;
	size = fs;
}

void DelStructOnName(Information*& arr, int& size, char* namedel) // индекс начинается с 1
{
	int fs = 0; // счётчик для массива в который записываем
	Information* mass2 = new Information[size - 1];
	for (int j = 0; j < size; j++) {
		if (strcmp(arr[j].name, namedel)) {
			mass2[fs] = arr[j];
			fs++;
		}
	}
	delete[] arr;
	arr = mass2;
	size = fs;
}

void DelStructOnSuma(Information*& arr, int& size, int suma)
{
	int fs = 0; // счётчик для массива в который записываем
	Information* mass2 = new Information[size - 1];
	for (int j = 0; j < size; j++) {
		if (arr[j].suma != suma) {
			mass2[fs] = arr[j];
			fs++;
		}
	}
	delete[] arr;
	arr = mass2;
	size = fs;
}

void DelStructOnPrich(Information*& arr, int& size, char* prichdel)
{
	int fs = 0; // счётчик для массива в который записываем
	Information* mass2 = new Information[size - 1];
	for (int j = 0; j < size; j++) {
		if (strcmp(arr[j].prichina, prichdel)) {
			mass2[fs] = arr[j];
			fs++;
		}
	}
	delete[] arr;
	arr = mass2;
	size = fs;
}

void DelStructOnDate(Information*& arr, int& size, Time time)
{
	int fs = 0; // счётчик для нового массива
	Information* mass2 = new Information[size - 1];
	for (int j{}; j < size; j++) {
		if ((time.day != arr[j].datecin.day) || (time.month != arr[j].datecin.month) || (time.year != arr[j].datecin.year)) {
			mass2[fs] = arr[j];
			fs++;
		}
	}
	delete[] arr;
	arr = mass2;
	size = fs;
}

int DeleteStructInfDolg(Information*& arr, int& size, char* verification, char* namedel, char* prichdel)
{
	Time time;
	int filter;
	char ch[] = "Y";
	int suma2;
	char buff[256];
	int flag = 0;
	int day, month, year;
	printf("Введите по какому филтру вы хотите удалить элемент из базы\n");
	printf("(1) - По имени\n");
	printf("(2) - По сумме\n");
	printf("(3) - По причине долга\n");
	printf("(4) - По дате долга\n");
	if (scanf_s("%d", &filter) != 1) {
		printf("Ошибка ввода, попробуйте ещё раз");
		return 0;
	}
	switch (filter)
	{
	case 1:
		printf("Введите имя человека, чьи данные удалить\n");
		gets_s(buff, 256);
		gets_s(buff, 256);
		for (int i{}; i < 256; i++) {
			if (isalpha(buff[i]) || isalpha(buff[i + 1])) {
				namedel[i] = buff[i];
			}
			else {
				namedel[i] = '\0';
				break;
			}
		}
		printf("Удалить все элементы с данным именем ? Y/N ");
		scanf_s("%s", verification, 2);

		for (int c{}; c < size; c++) {
			if (!strcmp(arr[c].name, namedel)) {
				flag = 1;
			}
		}
		if(flag == 0) {
			printf("Пользователя с данным именем нет !\n");
			return 0;
		}

		
		if (!strcmp(verification, ch))
		{
			DelStructOnName(arr, size, namedel);
			CreatedStruct(arr, size);
		}
		else
		{
			for (int i = 0; i < size; i++) {
				if (!strcmp(arr[i].name, namedel)) {
					delindone(arr, size, i);
					break;
				}
			}
		}
		break;
	case 2:
		printf("Введите сумму долга человека, чьи данные удалить\n");
		scanf_s("%d", &suma2);
		printf("Удалить все элементы с данной суммой долга? Y/N ");
		scanf_s("%s", verification, 2);

		for (int c{}; c < size; c++) {
			if (arr[c].suma == suma2) {
				flag = 1;
			}
		}
		if (flag == 0) {
			printf("Пользователя с данной суммой долга нет !\n");
			return 0;
		}
		if (!strcmp(verification, ch))
		{
			DelStructOnSuma(arr, size, suma2);
			CreatedStruct(arr, size);
		}
		else
		{
			for (int i = 0; i < size; i++) {
				if (arr[i].suma == suma2) {
					delindone(arr, size, i);
					break;
				}
			}
		}
		break;
	case 3:
		printf("Введите причину долга человека, чьи данные удалить\n");
		gets_s(buff, 256);
		gets_s(buff, 256);
		for (int i{}; i < 256; i++) {
			if (isalpha(buff[i]) || isalpha(buff[i + 1])) {
				prichdel[i] = buff[i];
			}
			else {
				prichdel[i] = '\0';
				break;
			}
		}
		printf("Удалить все элементы с данной причиной долга? Y/N ");
		scanf_s("%s", verification, 2);
		for (int c{}; c < size; c++) {
			if (!strcmp(arr[c].prichina, prichdel)) {
				flag = 1;
			}
		}
		if (flag == 0) {
			printf("Пользователя с данной причиной долга нет !\n");
			return 0;
		}
		if (!strcmp(verification, ch))
		{
			DelStructOnPrich(arr, size, prichdel);
			CreatedStruct(arr, size);
		}
		else
		{
			for (int i = 0; i < size; i++) {
				if (arr[i].prichina == prichdel) {
					delindone(arr, size, i);
					break;
				}
			}
		}
		break;
	case 4:
		printf("Введите дату по которой удалить(Формат День.Месяц.Год)\n");
		scanf_s("%d.%d.%d", &day, &month, &year);
		time.day = day;
		time.month = month;
		time.year = year;
		printf("Удалить все элементы с данной датой? Y/N ");
		scanf_s("%s", verification, 2);

		for (int c{}; c < size; c++) {
			if (arr[c].datecin.day == time.day && arr[c].datecin.month == time.month && arr[c].datecin.year == time.year) {
				flag = 1;
			}
		}
		if (flag == 0) {
			printf("Пользователя с данным именем нет !\n");
			return 0;
		}

		if (!strcmp(verification, ch))
		{
			DelStructOnDate(arr, size, time);
			CreatedStruct(arr, size);
		}
		else
		{
			for (int i = 0; i < size; i++) {
				if ((time.day == arr[i].datecin.day) && (time.month == arr[i].datecin.month) && (time.year == arr[i].datecin.year)) {
					delindone(arr, size, i);
					break;
				}
			}
		}
		break;
	default:
		printf("Ошибка ввода(данного фильтра не найдено), попробуйте снова");
		break;
	}
	return 0;
}

void HelpSorted(Information*& arr, int j)
{
	Information perm{};
	perm = arr[j];
	arr[j] = arr[j + 1];
	arr[j + 1] = perm;
}

// сортировка по имени - все случаи по возрастанию(сначала имя, если одинаковые сумма, если одинаковы причина).
void SortedStructOnName(Information*& arr, int size)
{
	for (int i{}; i < size; i++) {
		for (int j{}; j < size - 1; j++) {
			if (strcmp(arr[j].name, arr[j + 1].name) > 0) {
				HelpSorted(arr, j);
			}
			else if ((strcmp(arr[j].name, arr[j + 1].name) == 0)) {
				if (arr[j].suma > arr[j + 1].suma) {
					HelpSorted(arr, j);
				}
				else if (arr[j].suma == arr[j + 1].suma) {
					if (strcmp(arr[j].prichina, arr[j + 1].prichina) > 0) {
						HelpSorted(arr, j);
					}
					else if (!strcmp(arr[j].prichina, arr[j + 1].prichina)) {
						if (arr[j].datecin.year > arr[j + 1].datecin.year) {
							HelpSorted(arr, j);
						}
						else if (arr[j].datecin.year == arr[j + 1].datecin.year) {
							if (arr[j].datecin.month > arr[j + 1].datecin.month) {
								HelpSorted(arr, j);
							}
							else if (arr[j].datecin.month == arr[j + 1].datecin.month) {
								if (arr[j].datecin.day > arr[j + 1].datecin.day) {
									HelpSorted(arr, j);
								}
							}
						}
					}
				}
			}
		}
	}
}

// сортируем по сумме по убыванию(если одинаковы - по имени, если одинаковы по причине)
void SortedStructOnSuma(Information*& arr, int size)
{
	for (int i{}; i < size; i++) {
		for (int j{}; j < size - 1; j++) {
			if (arr[j].suma > arr[j + 1].suma) {
				HelpSorted(arr, j);
			}
			else if (arr[j].suma == arr[j + 1].suma) {
				if (strcmp(arr[j].name, arr[j + 1].name) > 0) {
					HelpSorted(arr, j);
				}
				else if (strcmp(arr[j].name, arr[j + 1].name) == 0) {
					if (strcmp(arr[j].prichina, arr[j + 1].prichina) > 0) {
						HelpSorted(arr, j);
					}
					else if (!strcmp(arr[j].prichina, arr[j + 1].prichina)) {
						if (arr[j].datecin.year > arr[j + 1].datecin.year) {
							HelpSorted(arr, j);
						}
						else if (arr[j].datecin.year == arr[j + 1].datecin.year) {
							if (arr[j].datecin.month > arr[j + 1].datecin.month) {
								HelpSorted(arr, j);
							}
							else if (arr[j].datecin.month == arr[j + 1].datecin.month) {
								if (arr[j].datecin.day > arr[j + 1].datecin.day) {
									HelpSorted(arr, j);
								}
							}
						}
					}
				}
			}
		}
	}
}

// сортировка по причине убыванию(если одинаковы по имени, если одинаковы по сумме)
void SortedStructOnPrichina(Information*& arr, int size)
{
	for (int i{}; i < size; i++) {
		for (int j{}; j < size - 1; j++) {
			if (strcmp(arr[j].prichina, arr[j + 1].prichina) > 0) {
				HelpSorted(arr, j);
			}
			else if ((strcmp(arr[j].prichina, arr[j + 1].prichina) == 0)) {
				if (strcmp(arr[j].name, arr[j + 1].name) > 0) {
					HelpSorted(arr, j);
				}
				else if (strcmp(arr[j].name, arr[j + 1].name) == 0) {
					if (arr[j].suma > arr[j + 1].suma) {
						HelpSorted(arr, j);
					}
					else if (!strcmp(arr[j].prichina, arr[j + 1].prichina)) {
						if (arr[j].datecin.year > arr[j + 1].datecin.year) {
							HelpSorted(arr, j);
						}
						else if (arr[j].datecin.year == arr[j + 1].datecin.year) {
							if (arr[j].datecin.month > arr[j + 1].datecin.month) {
								HelpSorted(arr, j);
							}
							else if (arr[j].datecin.month == arr[j + 1].datecin.month) {
								if (arr[j].datecin.day > arr[j + 1].datecin.day) {
									HelpSorted(arr, j);
								}
							}
						}
					}
				}
			}
		}
	}
}

void SortedStructOnDate(Information*& arr, int size) {
	for (int i{}; i < size; i++) {
		for (int j{}; j < size - 1; j++) {
			if (arr[j].datecin.year > arr[j + 1].datecin.year) {
				HelpSorted(arr, j);
			}
			else if (arr[j].datecin.year == arr[j + 1].datecin.year) {
				if (arr[j].datecin.month > arr[j + 1].datecin.month) {
					HelpSorted(arr, j);
				}
				else if (arr[j].datecin.month == arr[j + 1].datecin.month) {
					if (arr[j].datecin.day > arr[j + 1].datecin.day) {
						HelpSorted(arr, j);
					}
					else if (arr[j].datecin.day == arr[j + 1].datecin.day) {
						if (strcmp(arr[j].name, arr[j + 1].name) > 0) {
							HelpSorted(arr, j);
						}
						else if ((strcmp(arr[j].name, arr[j + 1].name) == 0)) {
							if (arr[j].suma > arr[j + 1].suma) {
								HelpSorted(arr, j);
							}
							else if (arr[j].suma == arr[j + 1].suma) {
								if (strcmp(arr[j].prichina, arr[j + 1].prichina) > 0) {
									HelpSorted(arr, j);
								}
							}
						}
					}
				}
			}
		}
	}
}


int FileInformationInStruct(Information*& arr, int& size, char* name, char* suma, char* prichina, char* time, char* namefile)
{

	FILE* fp;
	Information newPeople;
	char buff[256];
	size = 0;
	int lena_name = 0, lena_suma = 0, lena_prich = 0, lena_time = 0;
	char day[2], month[2], year[4];
	printf("Введите название файла который хотите открыть (Формат НазваниеФайла.Расширерение)\n");
	scanf_s("%s", namefile, 20);
	fopen_s(&fp, namefile, "r");
	if (fp == NULL) {
		printf("error with open file\n");
		return 0;
	}

	while (!feof(fp)) {
		fgets(buff, 256, fp);
		for (int i{}; i < max_lenght_name; i++) {
			if (!(buff[i] == ' ' && isdigit(buff[i + 1]))) {
				name[i] = buff[i];
			}
			else {
				lena_name = i + 1;
				for (int j{}; j < max_lenght_suma; j++) {
					if (!(buff[lena_name + j] == ' ' && isalpha(buff[lena_name + j + 1]))) {
						suma[j] = buff[lena_name + j];
					}
					else {
						lena_suma = j + 1;
						for (int k{}; k < max_lenght_payed; k++) {
							if (!(buff[lena_name + lena_suma + k] == ' ' && isdigit(buff[lena_name + lena_suma + k + 1]))) {
								prichina[k] = buff[lena_name + lena_suma + k];
							}
							else {
								lena_prich = k + 1;
								for (int s{}; s < max_time_lenght + 1; s++) {
									if (buff[lena_name + lena_prich + lena_suma + s] != '\n' && buff[lena_name + lena_prich + lena_suma + s] != '\0')
										time[s] = buff[lena_name + lena_prich + lena_suma + s];
									else {
										lena_time = s + 1;
										break;
									}
								}
								break;
							}
						}
						break;
					}
				}
				break;
			}
		}
		// замена strcpy name
		for (int count{}; count < lena_name-1; count++) {
			newPeople.name[count] = name[count];
		}
		newPeople.name[lena_name-1] = '\0';

		newPeople.suma = strtol(suma, NULL, 10);

		// замена strcpy prichina
		for (int count{}; count < lena_prich - 1; count++) {
			newPeople.prichina[count] = prichina[count];
		}
		newPeople.prichina[lena_prich - 1] = '\0';

		// замена strcpy time
		day[0] = time[0];
		day[1] = time[1];
		month[0] = time[3];
		month[1] = time[4];
		year[0] = time[6];
		year[1] = time[7];
		year[2] = time[8];
		year[3] = time[9];
		newPeople.datecin.day = strtol(day, NULL, 10);
		newPeople.datecin.month = strtol(month, NULL, 10);
		newPeople.datecin.year = strtol(year, NULL, 10);
		arr[size] = newPeople;
		size++;
	}
	fclose(fp);
	return 0;
}

int SaveStructInFile(Information* arr, int size, char* namefile)
{
	FILE* fp;
	printf("Введите название файла в который хотите сохранить данные (Формат НазваниеФайла.Расширерение)\n");
	scanf_s("%s", namefile, 20);
	fopen_s(&fp, namefile, "w");

	if (fp == NULL) {
		printf("error with open file");
		return 0;
	}

	for (int i{}; i < size-1; i++) {
		fprintf_s(fp, "%s %d %s %d.%d.%d\n", arr[i].name, arr[i].suma, arr[i].prichina, arr[i].datecin.day, arr[i].datecin.month, arr[i].datecin.year);
	}
	fprintf_s(fp, "%s %d %s %d.%d.%d", arr[size-1].name, arr[size-1].suma, arr[size-1].prichina, arr[size-1].datecin.day, arr[size-1].datecin.month, arr[size-1].datecin.year);
	fclose(fp);
	return 0;
}

int SortedStruct(Information* arr, int size)
{
	int filter;
	printf("Введите по какому филтру вы хотите отсортироватт элементы?\n");
	printf("(1) - По имени\n");
	printf("(2) - По сумме\n");
	printf("(3) - По причине долга\n");
	printf("(4) - По дате долга\n");
	if (scanf_s("%d", &filter) != 1) {
		printf("Ошибка ввода, попробуйте ещё раз");
		return 0;
	}
	switch (filter)
	{
	case 1:
		SortedStructOnName(arr, size);
		break;
	case 2:
		SortedStructOnSuma(arr, size);
		break;
	case 3:
		SortedStructOnPrichina(arr, size);
		break;
	case 4:
		SortedStructOnDate(arr, size);
		break;
	default:
		printf("Ошибка ввода(данного фильтра не найдено), попробуйте снова");
		break;
	}
	return 0;
}

int Menu(Information*& arr, int& size)
{
	int menu1, test, test2;
	char verification[2], namefind[max_lenght_name], prichinafind[max_lenght_payed], namedel[max_lenght_name];
	char name[max_lenght_name], suma[max_lenght_suma], prichina[max_lenght_payed], time[max_time_lenght];
	char namefile[20];
	char prichdel[max_lenght_payed];
	while (true) {
		system("cls");
		printf("Какое действие хотите сделать?\n");
		printf("(1) Ввод (информация о должнике)\n");
		printf("(2) Вывод (информации о должниках)\n");
		printf("(3) Добавление (информации о должнике)\n");
		printf("(4) Поиск (информации о должнике)\n");
		printf("(5) Удаление (должника)\n");
		printf("(6) Сортировка (должников)\n");
		printf("(7) Считать все данные с файла\n");
		printf("(8) Сохранить данные в файл\n");
		printf("(9) Выход\n");
		test = scanf_s("%d", &menu1);
		if (test != 1) {
			printf("Ошибка ввода, попробуйте ещё раз!");
			break;
		}
		switch (menu1)
		{
		case(1):
			printf("Введите о скольких должниках вы хотите сохранить информацию\n");
			if (!scanf_s("%d", &size)) {
				printf("Неккоректная информация, попробуйте заново");
				return 1;
			}
			CinStructInfDolg(arr, size, size, name, suma, prichina, time);
			break;
		case(2):
			system("cls");
			CoutStructInfDolg(arr, size);
			system("pause");
			break;
		case(3):
			system("cls");
			test2 = AddStructInfDolg(arr, size, name, suma, prichina, time);
			if (test2 == 1) {
				system("pause");
			}
			break;
		case(4):
			system("cls");
			FindStructInfDolg(arr, size, namefind, prichinafind, time);
			system("pause");
			break;
		case(5):
			system("cls");
			DeleteStructInfDolg(arr, size, verification, namedel, prichdel);
			system("pause");
			break;
		case(6):
			system("cls");
			SortedStruct(arr, size);
			system("pause");
			break;
		case(7):
			system("cls");
			CreatedStructMaxPerson(arr);
			FileInformationInStruct(arr, size, name, suma, prichina, time, namefile);
			CreatedStruct(arr, size);
			system("pause");
			break;
		case(8):
			system("cls");
			SaveStructInFile(arr, size, namefile);
			system("pause");
			break;
		case(9):
			return 0;
			break;
		default:
			return 0;
			break;
		}

	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "Rus");

	int sizestruct;
	struct Information* mass = new struct Information[max_count_people];
	Menu(mass, sizestruct);
	return 0;
}