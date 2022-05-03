/*
Principios de Programacao Procedimental
Mariana Aveleira Andrade
2017249648

run: gcc -Wall -Wextra main.c -o exe
*/

#include "PPP.c"

int main(){
  StudentsList students;
  ExpenseList expenses;
  // cria lista de alunos e vai buscar alunos ao ficheiro
  readFile(&students, 0);
  readFile(&expenses, 1);

  while(1){
    int choice = -1, id = -1;
    printf("======= MENU =======\n1.New student\n2.Delete student\n3.List students\n4.List students (filtered)\n5.See student\n6.New expense\n7.Update student balance\n0.Exit\n=====================\n");
    scanf("Option: %d", &choice);
    switch(choice){
      // Introduzir dados de um novo aluno.
      case 1:
        ;
        char name[MAX];
        Date nasc;
        int year, class, num;
        float balance;

        printf("Insert student's name: ");
        scanf("%s", name);
        printf("Insert student's day of birth: ");
        scanf("%d", &nasc.day);
        printf("Insert student's month of birth: ");
        scanf("%d", &nasc.month);
        printf("Insert student's year of birth: ");
        scanf("%d", &nasc.year);
        printf("Insert student's curricular year: ");
        scanf("%d", &year);
        printf("Insert student's class number: ");
        scanf("%d", &class);
        printf("Insert student's ID: ");
        scanf("%d", &num);
        printf("Insert student's balance: ");
        scanf("%f", &balance);
        new_student(&students, name, nasc, year, class, num, balance);
        break;
      // Eliminar um aluno existente.
      case 2:
        printf("Insert student's ID: ");
        scanf("%d", &id);
        delete_student(&students, id);
        break;
      // Listar todos os alunos por ordem alfabética.
      case 3:
        list_student_alpha(&students);
        break;
      // Listar os alunos com saldo abaixo de um determinado valor (por ordem decrescente de saldos).
      case 4:
        ;
        int min_b = 0;
        printf("Insert minimum balance: ");
        scanf("%d", &min_b);
        list_student_filter(&students, min_b);
        break;
      // Apresentar toda a informação de um determinado aluno.
      case 5:
        printf("Insert student's ID: ");
        scanf("%d", &id);
        list_student_details(&students, id);
        break;
      // Efetuar uma despesa por um determinado aluno.
      case 6:
        ;
        int exp = 0;
        printf("Insert student's ID: ");
        scanf("%d", &id);
        printf("Insert amount: ");
        scanf("%d", &exp);
        student_expense(&students, id, exp);
        break;
      // Carregar a conta de um aluno com um valor.
      case 7:
        ;
        int amount = 0;
        printf("Insert student's ID: ");
        scanf("%d", &id);
        printf("Insert amount: ");
        scanf("%d", &amount);
        student_update_balance(&students, id, amount);
        break;
      case 0:
        // atualizar ficheiro
        if(writeFile(&students, 0) && writeFile(&expenses, 1)){
          printf("Exiting...\n");
        }else{
          printf("Error writing to file\n");
        }
        // apagar Lista
        delete_list(&students, &expenses);
        // fechar
        return 0;
      default:
        printf("Try valid input\n");
        break;
    }
    //printf("TOU?");
  }
  // atualizar ficheiro
  if(writeFile(&students)){
    printf("Exiting...\n");
  }else{
    printf("Error writing to file\n");
  }
  // apagar Lista
  delete_list(&students);
  // fechar
  return 0;
}
