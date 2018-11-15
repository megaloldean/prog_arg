#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include <unistd.h> // для usleep
#include <time.h>

#include <my_global.h>
#include <mysql.h>

using namespace std;

int power(int t, int k) // возведение t в степень k
{
  int res = 1;
  while (k) 
      {
        if (k & 1) 
            res *= t;
	t *= t;
	k >>= 1;
      }
  return res;
}


void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

int main(int argc, char *argv[])
{
  char str_data[40];
  char str_time[40];	
  char str[80];
	
	int x; // переменная для модификации char в int
    int i = 1;
	int m_sec;
//_______________Определение времени задержки
	if (argv[1] == NULL)
	{
		x = 1; // микросекунда
	}
	else
	{
		
		sscanf(argv[1], "%d", &x); 
		
	}
		printf("The value of x : %d \n", x); 
	// перевод в секунду из микросекунд (10^6)
	m_sec = x*power(10,6);
	
	printf("St  x : %d \n", m_sec); 
//____________________________________
	
	
	// инициализация MySQL	
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }
		// устанавливаю соединение
  if (mysql_real_connect(con, "localhost", "root", "12345678qW", 
          NULL, 0, NULL, 0) == NULL) 
  {
		finish_with_error(con);
  }  

  // выбираем базу данных для работы
  if (mysql_query(con, "use test_db")) 
  {
      finish_with_error(con);
  }
	
  // цикл для записи данных в таблицу БД
  while(1)
  {
	  
  time_t t = time(NULL); 
  struct tm* aTm = localtime(&t);// структура из библиотеки

  
  sprintf(str_data,"%04d-%02d-%02d",aTm->tm_year+1900, aTm->tm_mon+1, aTm->tm_mday);// запись данных из массива в переменую str_data
  sprintf(str_time,"%02d:%02d:%02d",aTm->tm_hour, aTm->tm_min, aTm->tm_sec);
  printf("new data - %s \n",str_data);// принт для теста
  printf("new time - %s \n",str_time);
	  // формируем, что будем писать
  sprintf (str, "INSERT INTO d_t VALUES ('%s', '%s')", str_data, str_time); // С этим надо быть аккуратнее - возможность sql инъекции
  printf("%s \n", str);
	// вставляем команду для записи
  if (mysql_query(con, str)) 
  {
	//можно добавить принт 
  }
  
	  
	  usleep(m_sec); // задержка
  }
  
}