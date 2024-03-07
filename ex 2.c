#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct Bank {
    int id_client;
    char currency[100];
    float wallet;
    float income;
    int tranzactions;
} Bank;

void generate_client_money(Bank **bank, int number_of_clients, int start_index) {
    for (int i = start_index; i < number_of_clients; i++) {
        (*bank)[i].income = (float)rand() / RAND_MAX * 10000;
        (*bank)[i].tranzactions = rand() % 100;
        (*bank)[i].wallet = (float)rand() / RAND_MAX * 100000;

    }
}

void generate_currency_type(Bank **bank, int number_of_clients, int start_index) {

    for (int i = start_index; i < number_of_clients; i++) {

        (*bank)[i].id_client =i;
        int type = rand() % 3;
        if (type == 0) strcpy((*bank)[i].currency, "euro");
        else if (type == 1) strcpy((*bank)[i].currency, "lei");
        else if (type == 2) strcpy((*bank)[i].currency, "dolari");

    }
}

void generate_client(Bank **bank, int number_of_clients, int start_index) {

    generate_client_money(bank, number_of_clients, start_index);
    generate_currency_type(bank, number_of_clients, start_index);
}

void print_bank_client(Bank *bank) {
    printf("\n\nid-ul clientului: %d \n valuta: %s \n nr de tranzactii: %d \n venitul lunar: %f\n soldu-ul contului: %f\n\n",
           bank->id_client, bank->currency, bank->tranzactions, bank->income, bank->wallet);
}

void print_array_of_clients(Bank **bank, int number_of_clients) {
    if (bank == NULL) {
        printf("Array of clients is NULL\n");
        return;
    }
    printf("\nClients are:\n");
    for (int i = 0; i < number_of_clients; i++) {
        print_bank_client(*bank + i);
    }
}

void search_income(Bank **bank, int number_of_clients) {
    printf("Ce income lunar cautati ?\n");
    float searched_income;
    int count = 0;
    scanf("%f", &searched_income);
    for (int i = 0; i < number_of_clients; i++) {
        if (searched_income == (*bank)[i].income) {
            printf("Acest income a fost gasit la pozitia %d \n", i);
            count++;
            break;
        }
    }
    if (count == 0) printf("Acest income nu a fost gasit in baza de date a bancii\n");
}

void sort_income(Bank **bank, int number_of_clients) {
    Bank temp;
    for (int i = 0; i < number_of_clients; i++) {
        for (int j = 0; j < number_of_clients - 1; j++) {
            if ((*bank)[j].income < (*bank)[j + 1].income) {
                temp = (*bank)[j];
                (*bank)[j] = (*bank)[j + 1];
                (*bank)[j + 1] = temp;
            }
        }
    }
}

void shift_right(Bank **bank, int number_of_clients, int end) {
    for (int i = number_of_clients - 1; i > end; i--) {
        (*bank)[i].id_client = i;
        strcpy((*bank)[i].currency, (*bank)[i - 1].currency);
        (*bank)[i].tranzactions = (*bank)[i - 1].tranzactions;
        (*bank)[i].wallet = (*bank)[i - 1].wallet;
        (*bank)[i].income = (*bank)[i - 1].income;
    }
}

void delete_client(Bank **bank, int *number_of_clients, int poz) {
    for (int i = poz; i < *number_of_clients - 1; i++) {
        (*bank)[i].id_client =i;
        strcpy((*bank)[i].currency, (*bank)[i + 1].currency);
        (*bank)[i].tranzactions = (*bank)[i + 1].tranzactions;
        (*bank)[i].wallet = (*bank)[i + 1].wallet;
        (*bank)[i].income = (*bank)[i + 1].income;
    }
    (*number_of_clients)--;
}

int main() {
    srand(time(NULL));
    int answer;
    int number_of_clients;
    Bank *bank = malloc(sizeof(Bank));

    while (1) {
        back:
        printf("\nCe optiune alegeti din acest program ?\n\n");
        printf("Tastati un numar de la 1 pana la 10 pentru a alege\n\n");
        printf("1: pentru a citi elementele de la tastatura\n");
        printf("2: pentru a afisa elementele din tablou\n");
        printf("3: pentru a cauta un element\n");
        printf("4: pentru a elibera memoria tabloului\n");
        printf("5: pentru a sorta elementele din campul ales al structurii\n");
        printf("6: pentru a insera un element nou la capatul tabloului\n");
        printf("7: pentru a insera un element nou la inceputul tabloului\n");
        printf("8: pentru a insera un element nou la pozitia X \n");
        printf("9: pentru a sterge un element de pe pozitia X\n");
        printf("10: pentru a incheia programul \n");

        scanf("%d", &answer);

        switch (answer) {
            case 1: {
                printf("Cati clienti are banca noastra ?\n");

                scanf("%d", &number_of_clients);

                bank = realloc(bank, number_of_clients * sizeof(Bank));

                generate_client(&bank, number_of_clients, 0);
                break;
            }
            case 2: {
                print_array_of_clients(&bank, number_of_clients);
                break;
            }
            case 3: {
                search_income(&bank, number_of_clients);
                break;
            }
            case 4: {
                free(bank);
                break;
            }
            case 5: {
                sort_income(&bank, number_of_clients);
                break;
            }
            case 6: {
                number_of_clients++;
                bank = realloc(bank, number_of_clients * sizeof(Bank));
                generate_client(&bank, number_of_clients, number_of_clients - 1);
                break;
            }
            case 7: {
                number_of_clients++;
                bank = realloc(bank, number_of_clients * sizeof(Bank));
                shift_right(&bank, number_of_clients, 0);
                generate_client(&bank, 1, 0);
                break;
            }
            case 8: {
                printf("La ce pozitie doriti sa inserati ?\n");
                int poz;
                scanf("%d", &poz);
                if(poz>number_of_clients && poz>-1) {
                    printf("dati alta pozitie ");
                    goto back;
                }
                number_of_clients++;
                bank = realloc(bank, number_of_clients * sizeof(Bank));
                shift_right(&bank, number_of_clients, poz);
                generate_client(&bank, 1, poz);
                break;
            }
            case 9: {
                printf("La ce pozitie doriti sa stergeti ?\n");
                int poz;
                scanf("%d", &poz);
                if(poz>number_of_clients && poz>-1) {
                    printf("nu se poate de ales asa pozitie ))) ");
                    goto back;}
                delete_client(&bank, &number_of_clients, poz);
                bank = realloc(bank, number_of_clients * sizeof(Bank));
                break;
            }
            case 10: {
               goto end;
            }
            default: {
                printf("Fii om si alege normal\n");
            }
        }
    }
    end:
    free(bank);
    return 0;
}