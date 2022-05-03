/*
Principios de Programacao Procedimental
Mariana Aveleira Andrade
2017249648
*/

#ifndef PPP_PPP_H
#define PPP_PPP_H

//////////// INCLUDES ////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//////////// DEFINEs ////////////
#define MAX 50
#define MAX_ARRAY 100
#define MAX_LINE 100

//////////////////////// DATA STRUCTS ////////////////////////
typedef struct data{ // Data - auxiliar
  int day;
  int month;
  int year;
}Date;

typedef struct user{ // Utilizador
  char name[MAX];
  Date nasc;
  int year;
  int class;
  int num;
  float balance; // float?
}Student;

typedef struct noStudent{
  Student user;
  struct noStudent *next;
}noStudent;

typedef struct studentList{
  noStudent *first;
}StudentsList;

/////////

typedef struct Expense{ // Despesa
  Student * user;
  float amount;
  char desc[MAX_LINE];
  Date date;
}Expense;

typedef struct noExpense{
  Expense info;
  struct noExpense *next;
}noExpense;

typedef struct expenseList{
  noExpense *first;
}ExpenseList;

//////////////////////// VARIAVEIS GLOBAIS ////////////////////////
FILE *fptr;
//////////////////////// INICIALIZACOES ////////////////////////
// para o menu
void new_student(StudentsList *list, char name[], Date nasc, int year, int class, int num, float balance);
void delete_student(StudentsList *list, int num);
void list_student_alpha(StudentsList *list);
void list_student_filter(StudentsList *list, float balance);
void list_student_details(StudentsList *list, int num);
void student_expense(StudentsList *list, ExpenseList *expenses, int num, float exp, char desc[], Date date);
void student_update_balance(StudentsList *list, int num, float amount);
// auxiliares
void string_toupper(char str[]);
void sortStudents(Student array[], int size);
Student findStudent(StudentsList * list, int num);
void delete_list(StudentsList* list);
void print_list(StudentsList * list);
// ficheiros
void readFile(StudentsList *list);
void readFileExpenses(StudentsList* stuList, ExpenseList *list);
int writeFile(StudentsList *list);
#endif
