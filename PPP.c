/*
   Principios de Programacao Procedimental
   Mariana Aveleira Andrade
   2017249648
 */

#include "PPP.h"

//////////////////////// FUNCOES ////////////////////////
/////////// FICHEIROS ///////////
void readFileStudents(StudentsList *list) {
  // ler ficheiro
  fptr = fopen("users.txt", "r");
  if (!fptr) { // se nao encontrar ficheiro inicializa a lista a NULL
    list->first = NULL;
    // printf("Criei lista vazia de alunos\n");
  } else {
    char buffer[MAX_LINE];
    while (fgets(buffer, MAX_LINE, fptr)) {
      ///// ler linha do ficheiro
      // cria aluno
      Student *new = (Student *)malloc(sizeof(Student));
      char name[MAX];
      if (sscanf(buffer, "%s,%d-%d-%d,%d,%d,%d,%f", name, &new->nasc.day,
                 &new->nasc.month, &new->nasc.year, &new->year, &new->class,
                 &new->num, &new->balance) == 8) {
        string_toupper(name);
        strcpy(new->name, name);
        ///// adicionar a lista
        // cria o aluno para acrescentar à lista
        noStudent *aux;
        aux = (noStudent *)malloc(sizeof(noStudent));
        noStudent *act = list->first;
        if (aux) {
          aux->user = *new;
          aux->next = NULL;
          // adicionar aluno à lista de alunos
          act = aux;
          act->next = NULL;
        }
        act = act->next;
      }
    }
    // printf("Criei lista de alunos a partir do ficheiro\n");
  }
  fclose(fptr);
}
void readFileExpenses(StudentsList *stuList, ExpenseList *list) {
  // ler ficheiro
  fptr = fopen("expenses.txt", "r");
  if (!fptr) { // se nao encontrar ficheiro inicializa a lista a NULL
    list->first = NULL;
    // printf("Criei lista vazia de despesas\n");
  } else {
    char buffer[MAX_LINE];
    while (fgets(buffer, MAX_LINE, fptr)) {
      ///// ler linha do ficheiro
      // cria aluno
      Expense new;
      int num;
      if (sscanf(buffer, "%d,%f,%s,%d-%d-%d", &num, &new.amount, new.desc,
                 &new.date.day, &new.date.month, &new.date.year) == 6) {
        Student user = findStudent(stuList, num);
        if (user.num == -1) {
          printf("Student not found\n");
        } else {
          ///// adicionar a lista
          // cria o despesa para acrescentar à lista
          noExpense *aux;
          aux = (noExpense *)malloc(sizeof(noExpense));
          noExpense *act = list->first;
          if (aux) {
            aux->info = new;
            aux->next = NULL;
            // adicionar despesa à lista de despesas
            act = aux;
            act->next = NULL;
          }
          act = act->next;
        }
      }
    }
    // printf("Criei lista de despesas a partir do ficheiro\n");
  }
  fclose(fptr);
}

int writeFileStudents(StudentsList *list) {
  // atualiza ficheiro
  fptr = fopen("users.txt", "w");
  if (!list->first) {
    fclose(fptr);
    return 1;
  } else {
    noStudent *act = list->first;
    while (act) { // percorre a lista de alunos
      if (fwrite(&act, sizeof(Student), 1, fptr) == 0) {
        return 0;
      }
      free(act);
    }
    fclose(fptr);
    return 1;
  }
}

int writeFileExpenses(ExpenseList *list) {
  fptr = fopen("expenses.txt", "w");
  if (!list->first) {
    fclose(fptr);
    return 1;
  } else {
    noExpense *act = list->first;
    noExpense *aux = act;
    while (act) { // percorre a lista de alunos
      fprintf(fptr, "%d,%.2f,%s,%d-%d-%d", act->info.user->num,
              act->info.amount, act->info.desc, act->info.date.day,
              act->info.date.month, act->info.date.year);
      aux = act->next;
      free(act);
      act = aux;
    }
    fclose(fptr);
    return 1;
  }
}

/////////// MENU ///////////
void new_student(StudentsList *list, char name[], Date nasc, int year,
                 int class, int num, float balance) {
  // cria aluno
  int flag = 0;

  Student new;
  string_toupper(name);
  strcpy(new.name, name);
  new.nasc = nasc;
  new.year = year;
  new.class = class;
  new.num = num;
  new.balance = balance;
  printf("Criei campos\n");
  // cria no aluno para acrescentar à lista
  noStudent *aux;
  aux = (noStudent *)malloc(sizeof(noStudent));
  noStudent *act = list->first;
  noStudent *prev = NULL;

  printf("Criei aux\n");
  if (aux) {
    printf("if aux\n");
    aux->user = new;
    aux->next = NULL;
    printf("pus new no aux\n");
    // adicionar aluno à lista de alunos
    if (act == NULL) { // se ainda nao houver nenhum aluno
      printf("act == NULL\n");
      list->first = aux;
      list->first->next = NULL;
    } else {
      if (!act->next) { // so tem um aluno
        if (strcmp(act->user.name, new.name) > 0) {
          aux->next = act;
          list->first = aux;
        } else {
          act->next = aux;
          aux->next = NULL;
        }
      } else { // tem mais que um
        while (act->next) {
          if (strcmp(act->user.name, new.name) > 0) {
            if (!prev) {
              aux->next = act;
              list->first = aux;
            } else {
              aux->next = act;
              prev->next = aux;
            }
            flag = 1;
            break;
          } else {
            prev = act;
            act = act->next;
          }
        }
        if (!flag) {
          act->next = aux;
          aux->next = NULL;
        }
      }
      // if (strcmp(act->user.name, new.name) > 0)
      // { // é depois
      //   printf("BIM");
      //   act->next = aux;
      //   aux->next = NULL;
      // }
      // else
      // { // e antes
      //   printf("BOOM");
      //   aux->next = act;
      //   list->first = aux;
      // }
      // printf("while act\n");
    }
    //       do{
    //         if (strcmp(act->next->user.name, new.name) >
    //             0)
    //         { // encontra o lugar certo na lista
    //           printf("encontrar sitio certo\n");
    //           aux->next = act->next;
    //           act->next = aux;
    //         }
    //         act = act->next;
    //       } while (act->next);
  }
}
void delete_student(StudentsList *list, int num) {
  Student user = findStudent(list, num);
  if (user.num == -1) {
    printf("Student not found\n");
  } else {
    // if (act != NULL)
    // {
    //         ant->next = act->next;
    //         free(act);
    // }
  }
}
void list_student_alpha(StudentsList *list) {
  noStudent *usr = list->first;
  while (usr) {
    printf("Name: %s\tID: %d\n", usr->user.name, usr->user.num);
    usr = usr->next;
  }
}
void list_student_filter(StudentsList *list, float balance) {
  noStudent *usr = list->first;
  Student users[MAX_ARRAY];
  int i = 0;
  while (usr) {
    if (usr->user.balance < balance) {
      users[i] = usr->user;
      i++;
    }
    usr = usr->next;
  }
  // ordena e imprime ordenado
  sortStudents(users, (i - 1));
}

void list_student_details(StudentsList *list, int num) {
  Student aux = findStudent(list, num);
  if (aux.num == -1) {
    printf("Student not found\n");
  } else {
    if (aux.num != -1) {
      printf("Name: %s\nBirthdate: %d-%d-%d\nYear: %d\nClass: %d\nID: "
             "%d\nBalance: %.2f\n",
             aux.name, aux.nasc.day, aux.nasc.month, aux.nasc.year, aux.year,
             aux.class, aux.num, aux.balance);
    } else {
      printf("User not found\n");
    }
  }
}

void student_expense(StudentsList *list, ExpenseList *expenses, int num,
                     float exp, char desc[], Date date) {
  Student aux = findStudent(list, num);
  if (aux.num == -1) {
    printf("Student not found\n");
  } else {
    // atualizar saldo do user
    aux.balance -= exp;

    // criar despesa
    Expense new_exp;
    // new_exp.user = aux;
    new_exp.amount = exp;
    strcpy(new_exp.desc, desc);
    new_exp.date = date;
    noExpense *new = (noExpense *)malloc(sizeof(noExpense));

    // adicionar despesa a lista de despesas
    if (new) {
      new->info = new_exp;
      new->next = expenses->first->next;
      expenses->first = new;
    }
  }
}

void student_update_balance(StudentsList *list, int num, float amount) {
  Student aux = findStudent(list, num);
  if (aux.num == -1) {
    printf("Student not found\n");
  } else {
    if (aux.num != -1) {
      aux.balance += amount;
    } else {
      printf("User not found\n");
    }
  }
}

/////////// AUXILIARES ///////////
void string_toupper(char str[]) {
  for (int i = 0; i < ((int)strlen(str)); i++) {
    str[i] = toupper(str[i]);
  }
}

void sortStudents(Student array[], int size) {
  noStudent *aux = (noStudent *)malloc(sizeof(noStudent));
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if ((array[i]).balance < (array[j]).balance) {
        aux->user = array[i];
        array[i] = array[j];
        array[j] = aux->user;
      }
    }
  }
  for (int i = 0; i < size; i++) {
    printf("Name: %s\tBalance: %.2f\n", (array[i]).name, (array[i]).balance);
  }
}

Student findStudent(StudentsList *list, int num) {
  noStudent *act = list->first;
  Student user;
  user.num = -1;
  while (act) {
    if (act->user.num == num) {
      user = act->user;
      break;
    }
    act = act->next;
  }
  return user;
}

void delete_list(StudentsList *list) {
  noStudent *aux;
  while (list->first != NULL) {
    aux = list->first;
    list->first = list->first->next;
    free(aux);
  }
}

void print_list(StudentsList *list) {
  noStudent *aux = list->first;
  while (aux != NULL) {
    printf("Name: %s\tBirthdate: %d-%d-%d\tYear: %d\tClass: %d\tID: "
           "%d\tBalance: %.2f\n",
           aux->user.name, aux->user.nasc.day, aux->user.nasc.month,
           aux->user.nasc.year, aux->user.year, aux->user.class, aux->user.num,
           aux->user.balance);
    aux = aux->next;
  }
}
