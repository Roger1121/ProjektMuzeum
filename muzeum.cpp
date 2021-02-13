#include<windows.h>
#include<bits/stdc++.h>
using namespace std;
int ideksponatu=1, idwystawy=1;
const char byexhibition='1', bycondition='2', nofilter='3';
bool program=true;
char whatever;
void duplicate(char* from, char* to)//przepisuje jedna tablice char na druga
{
    strcpy(to, from);
}
struct eksponat //struktura eksponatu
{
    int id;
    char nazwa[51];
    char opis[1001];
    char datapowstania[21];
    int wiek;
    float waga;
    char datadodania[21];
    int stan;
    int id_wystawy;
    struct eksponat *next;
};
struct wystawa //struktura wystawy
{
    int id;
    char nazwa[51];
    char opis[1001];
    int status;
    int nr_sali;
    struct wystawa *next;
};
void _fill(char text[], int n) //dopelnia tablice char do pelnego wymiaru [tekst^   '\0']
{
    int i=0;
    while(text[i]!='\0')
        i++;
    text[i]='^';
    i++;
    while(i<n-1)
    {
        text[i]=' ';
        i++;
    }
    text[i]='\0';
}
void write(char text[]) //wypisuje tablice char do pierwszego wystapienia znaku ^
{
    int i=0;
    while(text[i]!='^')
    {
        printf("%c", text[i]);
        i++;
    }
    printf("\n");
}
bool parseage(char data[], int* age)//przepisuje date z tablicy char na int
{
    if(data[0]=='-')
    {
        int i=1;
        while(data[i]>='0'&&data[i]<='9') i++;
        if(i==3&&data[i+1]>='0'&&data[i+1]<='9')
        {
            //format -dd.mm.rrrr
            int j=7;
            while(data[j]>='0'&&data[j]<='9')
            {
                (*age)*=10;
                (*age)+=(data[j]-'0');
                j++;
            }
            j=10*(data[4]-'0')+data[5]-'0';
            if(j>12||j<1) return false;
            else (*age)=100*(*age)+j;
            j=10*(data[1]-'0')+data[2]-'0';
            if(j>31||j<1) return false;
            else (*age)=100*(*age)+j;
            (*age)*=(-1);
            return true;
        }
        else
        {
            //format -rrrr-rrrr
            int j=1;
            while(data[j]>='0'&&data[j]<='9')
            {
                (*age)*=10;
                (*age)+=(data[j]-'0');
                j++;
            }
            (*age)*=(-10000);
            return true;
        }
    }
    else
    {
        int i=0;
        while(data[i]>='0'&&data[i]<='9') i++;
        if(i==2&&data[i+1]>='0'&&data[i+1]<='9')
        {
            //format dd.mm.rrrr
            int j=6;
            while(data[j]>='0'&&data[j]<='9')
            {
                (*age)*=10;
                (*age)+=(data[j]-'0');
                j++;
            }
            j=10*(data[3]-'0')+data[4]-'0';
            if(j>12||j<1) return false;
            else (*age)=100*(*age)+j;
            j=10*(data[0]-'0')+data[1]-'0';
            if(j>31||j<1) return false;
            else (*age)=100*(*age)+j;
            return true;
        }
        else
        {
            //format rrrr-rrrr
            int j=0;
            while(data[j]>='0'&&data[j]<='9')
            {
                (*age)*=10;
                (*age)+=(data[j]-'0');
                j++;
            }
            (*age)*=(10000);
            return true;
        }
    }
}
void eksponatbyage(eksponat** lista, eksponat** nowy)//sortuje eksponaty wg. wieku
{
    if((*lista)==NULL) (*lista)=(*nowy);
    else if((*lista)->next==NULL)
    {
        if((*lista)->wiek<=(*nowy)->wiek)
            (*lista)->next=(*nowy);
        else
        {
            (*nowy)->next=(*lista);
            (*lista)=(*nowy);
        }
    }
    else
    {
        if((*nowy)->wiek<=(*lista)->wiek)
        {
            (*nowy)->next=(*lista);
            (*lista)=(*nowy);
        }
        else
        {
            eksponat* pom=(*lista);
            while(pom!=NULL)
            {
                if(pom->next==NULL||((*nowy)->wiek<=pom->next->wiek))
                {
                    (*nowy)->next=pom->next;
                    pom->next=(*nowy);
                    break;
                }
                pom=pom->next;
            }
        }
    }
}
void eksponatbycondition(eksponat** lista, eksponat** nowy)//sortuje eksponaty wg. stanu
{
    if((*lista)==NULL) (*lista)=(*nowy);
    else if((*lista)->next==NULL)
    {
        if((*lista)->stan<=(*nowy)->stan)
            (*lista)->next=(*nowy);
        else
        {
            (*nowy)->next=(*lista);
            (*lista)=(*nowy);
        }
    }
    else
    {
        if((*lista)->stan>=(*nowy)->stan)
        {
            (*nowy)->next=(*lista);
            (*lista)=(*nowy);
            return;
        }
        eksponat* pom=(*lista);
        while(pom!=NULL)
        {
            if((pom->next==NULL||(pom->next->stan)>=(*nowy)->stan))
            {
                (*nowy)->next=pom->next;
                pom->next=(*nowy);
                break;
            }
            pom=pom->next;
        }
    }
}
void clone(eksponat** stary, eksponat** nowy)//duplikuje strukture eksponatu
{
    (*nowy)=(eksponat*)malloc(sizeof(eksponat));
    (*nowy)->id=(*stary)->id;
    duplicate((*stary)->nazwa, (*nowy)->nazwa);
    duplicate((*stary)->opis, (*nowy)->opis);
    (*nowy)->wiek=(*stary)->wiek;
    duplicate((*stary)->datapowstania, (*nowy)->datapowstania);
    duplicate((*stary)->datadodania, (*nowy)->datadodania);
    (*nowy)->waga=(*stary)->waga;
    (*nowy)->stan=(*stary)->stan;
    (*nowy)->next=NULL;
    (*nowy)->id_wystawy=(*stary)->id_wystawy;
}
void dodajeksponat(eksponat** lista, eksponat** powieku, eksponat** postanie)//dodaje eksponat do wystawy
{
    system("cls");
    printf("Witaj w kreatorze eksponatow. Prosze o wpisanie danych eksponatu, ktory chcesz zapisac w systemie:\n");
    eksponat* nowy=(eksponat*)malloc(sizeof(eksponat));
    eksponat* nowy2;
    eksponat* nowy3;
    nowy->id=ideksponatu;
    ideksponatu++;
    printf("Nazwa eksponatu: ");
    fflush(stdin);
    gets(nowy->nazwa);
    _fill(nowy->nazwa, 51);
    printf("Opis eksponatu: ");
    fflush(stdin);
    gets(nowy->opis);
    _fill(nowy->opis, 1001);
    printf("Data lub okres powstania: ");
    fflush(stdin);
    gets(nowy->datapowstania);
    nowy->wiek=0;
    while(!parseage(nowy->datapowstania, &(nowy->wiek)))
    {
        system("cls");
        printf("Nieprawidlowy format daty!!!\n");
        printf("Data lub okres powstania: ");
        fflush(stdin);
        gets(nowy->datapowstania);
        nowy->wiek=0;
    }
    _fill(nowy->datapowstania, 21);
    printf("Data dodania do zbioru muzealnego: ");
    fflush(stdin);
    gets(nowy->datadodania);
    _fill(nowy->datadodania, 21);
    printf("Waga w kg: ");
    fflush(stdin);
    scanf("%f", &(nowy->waga));
    nowy->stan=0;
    printf("Podaj stan w skali od 1 do 5: ");
    fflush(stdin);
    scanf("%d", &(nowy->stan));
    while(nowy->stan>5||nowy->stan<1)
    {
        printf("To nie jest prawidlowa wartosc!!!\n");
        printf("Podaj stan w skali od 1 do 5: ");
        fflush(stdin);
        scanf("%d", &(nowy->stan));
    }
    nowy->next=NULL;
    nowy->id_wystawy=0;
    clone(&nowy, &nowy2);
    clone(&nowy, &nowy3);
    if((*lista)==NULL) (*lista)=nowy;
    else if(((*lista)->next)==NULL)
    {
        ((*lista)->next)=nowy;
    }
    else
    {
        eksponat* pom=(*lista);
        while(pom!=NULL)
        {
            if(pom->next==NULL)
            {
                pom->next=nowy;
                break;
            }
            pom=pom->next;
        }
    }
    eksponatbyage(powieku, &nowy2);
    eksponatbycondition(postanie, &nowy3);
    printf("Pomyslnie dodano eksponat do systemu\n");
    printf("Wpisz dowolny znak, aby kontynuowac: ");
    fflush(stdin);
    scanf("%c", &whatever);
    system("cls");
}
void wyswietlwystawy(wystawa** lista)//wyswietla liste wystaw
{
    if((*lista)==NULL)
    {
        printf("Do systemu nie dodano jeszcze zadnej wystawy.\n");
        return;
    }
    wystawa* pom=*lista;
    while(pom!=NULL)
    {
        printf("%d. ", pom->id);
        write(pom->nazwa);
        if(pom->next==NULL) break;
        pom=pom->next;
    }
}
void wyswietleksponaty(eksponat** lista, char filtr, wystawa** wystawy)//wyswietla liste eksponatow (posortowana i przefiltrowana)
{
    if((*lista)==NULL)
    {
        printf("Do systemu nie dodano jeszcze zadnego eksponatu.\n");
        return;
    }
    int counter=0;
    bool success=false;
    int nr=0;
    eksponat* pom=*lista;
    wystawa* pom2=*wystawy;
    switch(filtr)
    {
    case nofilter:
        while(pom!=NULL)
        {
            printf("%d. ", pom->id);
            write(pom->nazwa);
            if(pom->next!=NULL) pom=pom->next;
            else break;
        }
        break;
    case byexhibition:
        if(wystawy==NULL)
        {
            system("cls");
            printf("Nie dodano zadnej wystawy!!!");
            return;
        }
        while(!success)
        {
            wyswietlwystawy(wystawy);
            printf("Podaj numer id ekspozycji, aby wyswietlic wystawione na niej przedmioty lub wpisz 0, aby wyjsc do menu: ");
            fflush(stdin);
            scanf("%d", &nr);
            if(nr==0) break;
            while(pom2!=NULL)
            {
                if(nr>=idwystawy)
                {
                    system("cls");
                    printf("Na liscie nie ma ekspozycji o id = %d", nr);
                }
                else if(pom2->id==nr)
                {
                    while(pom!=NULL)
                    {
                        if(pom->id_wystawy==nr)
                        {
                            printf("%d. ", pom->id);
                            write(pom->nazwa);
                            counter++;
                        }
                        if(pom->next!=NULL) pom=pom->next;
                        else break;
                    }
                    success=true;
                }
                if(pom2->next!=NULL) pom2=pom2->next;
                else break;
            }
        }
        if(counter==0) printf("Zaden z eksponatow nie spelnia kryteriow wyszukiwania.\n");
        break;
    case bycondition:
        system("cls");
        printf("Podaj stan zachowania przedmiotow do wyswietlenia w skali od 1 do 5: ");
        fflush(stdin);
        scanf("%d", &nr);
        while(nr>5||nr<1)
        {
            system("cls");
            printf("Prosze podac liczbe od 1 do 5: ");
            fflush(stdin);
            scanf("%d", &nr);
        }
        while(pom!=NULL)
        {
            if(pom->stan==nr)
            {
                printf("%d. ", pom->id);
                write(pom->nazwa);
                counter++;
            }
            if(pom->next!=NULL) pom=pom->next;
            else break;
        }
        if(counter==0) printf("Zaden z eksponatow nie spelnia kryteriow wyszukiwania.\n");
        break;
    }
}
void usuneksponat(eksponat** lista, wystawa** wystawy, eksponat** powieku, eksponat** postanie)//usuwa eksponat z systemu
{
    bool success=false;
    int nr;
    eksponat* pom=(*lista);
    eksponat* pom3=NULL;
    eksponat* pom2=NULL;
    system("cls");
    while(!success)
    {
        wyswietleksponaty(lista, nofilter, wystawy);
        printf("Podaj id eksponatu, ktory chcesz usunac lub wpisz 0, aby wyjsc do menu: ");
        fflush(stdin);
        scanf("%d", &nr);
        if(nr==0) break;
        if(nr>=ideksponatu)
        {
            system("cls");
            printf("Na liscie nie ma eksponatu o id = %d", nr);
        }
        else if((*lista)->id==nr)
        {
            if((*lista)->id_wystawy==0)
            {
                pom=(*lista)->next;
                free(*lista);
                (*lista)=pom;
                pom2=(*powieku);
                if((*powieku)->id==nr)
                {
                    pom2=(*powieku)->next;
                    free(*powieku);
                    (*powieku)=pom2;
                }
                else
                {
                    while(pom2!=NULL)
                    {
                        if(pom2->next->id==nr)
                        {
                            pom3=pom2->next;
                            pom2->next=pom3->next;
                            free(pom3);
                            break;
                        }
                        pom2=pom2->next;
                    }
                }
                pom2=(*postanie);
                if((*postanie)->id==nr)
                {
                    if((*postanie)->id==0)
                    {
                        pom2=(*postanie)->next;
                        free(*postanie);
                        (*postanie)=pom2;
                    }
                }
                else
                {
                    while(pom2!=NULL)
                    {
                        if(pom2->next->id==nr)
                        {
                            pom3=pom2->next;
                            pom2->next=pom3->next;
                            free(pom3);
                            break;
                        }
                        pom2=pom2->next;
                    }
                }
                printf("Pomyslnie usunieto wybrany eksponat.\n");
                break;
            }
            else
            {
                printf("Biezacy eksponat nie moze zostac usuniety, gdyz aktualnie znajduje sie na wystawie nr %d", pom->id_wystawy);
            }
        }
        else
        {
            while(pom!=NULL)
            {
                if(pom->next->id>nr)
                {
                    system("cls");
                    printf("Na liscie nie ma eksponatu o id = %d", nr);
                }
                else if(pom->next->id==nr)
                {
                    if(pom->next->id_wystawy==0)
                    {
                        pom2=pom->next;
                        pom->next=pom2->next;
                        free(pom2);
                        pom2=(*powieku);
                        if((*powieku)->id==nr)
                        {
                            pom2=(*powieku)->next;
                            free(*powieku);
                            (*powieku)=pom2;
                        }
                        else
                        {
                            while(pom2!=NULL)
                            {
                                if(pom2->next->id==nr)
                                {
                                    pom3=pom2->next;
                                    pom2->next=pom3->next;
                                    free(pom3);
                                    break;
                                }
                                pom2=pom2->next;
                            }
                        }
                        pom2=(*postanie);
                        if((*postanie)->id==nr)
                        {
                            if((*postanie)->id==0)
                            {
                                pom2=(*postanie)->next;
                                free(*postanie);
                                (*postanie)=pom2;
                            }
                        }
                        else
                        {
                            while(pom2!=NULL)
                            {
                                if(pom2->next->id==nr)
                                {
                                    pom3=pom2->next;
                                    pom2->next=pom3->next;
                                    free(pom3);
                                    break;
                                }
                                pom2=pom2->next;
                            }
                        }
                        printf("Pomyslnie usunieto wybrany eksponat.\n");
                    }
                    else
                    {
                        printf("Biezacy eksponat nie moze zostac usuniety, gdyz aktualnie znajduje sie na wystawie nr %d", pom->next->id_wystawy);
                    }
                    success=true;
                    break;
                }
                pom=pom->next;
            }
        }
    }
    printf("Wpisz dowolny znak, aby kontynuowac: ");
    fflush(stdin);
    scanf("%c", &whatever);
    system("cls");
}
void nowawystawa(wystawa** lista)//dodaje nowa wystawe do systemu
{
    system("cls");
    printf("Witaj w kreatorze ekspozycji. Prosze o wpisanie danych ekspozycji, ktora chcesz zapisac w systemie:\n");
    wystawa* nowa=(wystawa*)malloc(sizeof(wystawa));
    nowa->id=idwystawy++;
    printf("Podaj nazwe wystawy: ");
    fflush(stdin);
    gets(nowa->nazwa);
    _fill(nowa->nazwa, 51);
    printf("Opis wystawy: ");
    fflush(stdin);
    gets(nowa->opis);
    _fill(nowa->opis, 1001);
    printf("Podaj status wystawy:\n 1.trwajaca\n 2.zakonczona\n");
    int status=0;
    fflush(stdin);
    scanf("%d", &status);
    while(status!=1&&status!=2)
    {
        system("cls");
        printf("Nieprawidlowa wartosc!!!");
        printf("Podaj status wystawy:\n 1.trwajaca\n 2.zakonczona\n");
        fflush(stdin);
        scanf("%d", &status);
    }
    nowa->status=status;
    printf("Podaj numer sali, w ktorej zostanie umieszczona nowa wystawa: ");
    fflush(stdin);
    scanf("%d", &(nowa->nr_sali));
    nowa->next=NULL;
    if((*lista)==NULL) (*lista)=nowa;
    else if((*lista)->next==NULL)
    {
        (*lista)->next=nowa;
    }
    else
    {
        wystawa* pom=*lista;
        while(pom!=NULL)
        {
            if(pom->next==NULL)
            {
                pom->next=nowa;
                break;
            }
            pom=pom->next;
        }
    }
    printf("Pomyslnie dodano wystawe do systemu.\n");
    printf("Wpisz dowolny znak, aby kontynuowac: ");
    fflush(stdin);
    scanf("%c", &whatever);
    system("cls");
}
void zmienstatus(wystawa** lista)//zmienia status wystawy (trwajaca<->zakonczona)
{
    bool success=false;
    system("cls");
    while(!success)
    {
        wyswietlwystawy(lista);
        printf("Podaj numer id wystawy, ktorej status mam zmienic lub wpisz 0, aby wyjsc do menu: ");
        int nr;
        fflush(stdin);
        scanf("%d", &nr);
        if(nr==0) break;
        wystawa* pom=*lista;
        while(pom!=NULL)
        {
            if(pom->id>nr)
            {
                system("cls");
                printf("Na liscie nie ma wystawy o id = %d\n", nr);
            }
            else if(nr>=idwystawy)
            {
                system("cls");
                printf("Na liscie nie ma wystawy o id = %d\n", nr);
            }
            else if(pom->id==nr)
            {
                if(pom->status==1)
                {
                    printf("Czy mam zmienic status tej wystawy z TRWAJACA na ZAKONCZONA?\n1.TAK\n2.NIE\n");
                    fflush(stdin);
                    scanf("%c", &whatever);
                    while(whatever!='1'&&whatever!='2')
                    {
                        system("cls");
                        printf("Nie a takiej opcji!!!\n");
                        printf("Czy mam zmienic status tej wystawy z TRWAJACA na ZAKONCZONA?\n1.TAK\n2.NIE\n");
                        fflush(stdin);
                        scanf("%c", &whatever);
                    }
                    switch(whatever)
                    {
                    case '1':
                        pom->status=2;
                        printf("Pomyslnie zakonczono wybrana wystawe\n");
                        break;
                    case '2':
                        break;
                    }
                }
                else
                {
                    printf("Czy mam zmienic status tej wystawy z ZAKONCZONA na TRWAJACA?\n1.TAK\n2.NIE\n");
                    fflush(stdin);
                    scanf("%c", &whatever);
                    while(whatever!='1'&&whatever!='2')
                    {
                        system("cls");
                        printf("Nie a takiej opcji!!!\n");
                        printf("Czy mam zmienic status tej wystawy z ZAKONCZONA na TRWAJACA?\n1.TAK\n2.NIE\n");
                        fflush(stdin);
                        scanf("%c", &whatever);
                    }
                    switch(whatever)
                    {
                    case '1':
                        pom->status=1;
                        printf("Pomyslnie zakonczono wybrana wystawe\n");
                        break;
                    case '2':
                        break;
                    }
                }
                success=true;
                break;
            }
            pom=pom->next;
        }
    }
    printf("Wpisz dowolny znak, aby kontynuowac: ");
    fflush(stdin);
    scanf("%c", &whatever);
    system("cls");
}
void przypiszeksponat(eksponat** lista, wystawa** wystawy, eksponat** powieku, eksponat** postanie)//dodaje eksponat do wystawy
{
    system("cls");
    bool success=false, success2=false;
    while(!success)
    {
        wyswietleksponaty(lista, nofilter, wystawy);
        printf("Podaj numer id szukanego eksponatu lub wpisz 0, aby wyjsc do menu: ");
        int nr, nr2;
        fflush(stdin);
        scanf("%d", &nr);
        if(nr==0) break;
        eksponat* pom=*lista;
        while(pom!=NULL)
        {
            if(pom->id>nr)
            {
                system("cls");
                printf("Na liscie nie ma eksponatu o id = %d\n", nr);
            }
            else if(nr>=ideksponatu)
            {
                system("cls");
                printf("Na liscie nie ma eksponatu o id = %d\n", nr);
            }
            else if(pom->id==nr)
            {
                while(!success2)
                {
                    wyswietlwystawy(wystawy);
                    printf("Podaj numer id wystawy, do ktorej mam przypisac wybrany eksponat: ");
                    fflush(stdin);
                    scanf("%d", &nr2);
                    wystawa* pom2=*wystawy;
                    while(pom2!=NULL)
                    {
                        if(pom2->id>nr2)
                        {
                            system("cls");
                            printf("Na liscie nie ma wystawy o id = %d\n", nr2);
                        }
                        else if(nr2>=idwystawy)
                        {
                            system("cls");
                            printf("Na liscie nie ma wystawy o id = %d\n", nr2);
                    }
                        else if(pom2->id==nr2)
                        {
                            if(pom->id_wystawy==0)
                            {
                                pom->id_wystawy=nr2;

                                eksponat* pom3=(*powieku);
                                while(pom3->id!=pom->id) pom3=pom3->next;
                                pom3->id_wystawy=nr2;

                                pom3=(*postanie);
                                while(pom3->id!=pom->id) pom3=pom3->next;
                                pom3->id_wystawy=nr2;

                                printf("Pomyslnie dodano wybrany eksponat do wystawy");
                            }
                            else
                            {
                                printf("Nie mozna dodac eksponatu, gdyz znajduje sie juz na innej ekspozycji!!!");
                            }
                            success2=true;
                            break;
                        }
                        pom2=pom2->next;
                    }
                }
                success=true;
                break;
            }
            pom=pom->next;
        }
    }
    printf("Wpisz dowolny znak, aby kontynuowac: ");
    fflush(stdin);
    scanf("%c", &whatever);
    system("cls");
}
void edytujeksponat(eksponat** lista, wystawa** wystawy, eksponat** powieku, eksponat** postanie)//modyfikuje dane eksponatow
{
    system("cls");
    eksponat* copy;
    eksponat* pom2;
    eksponat* pom3;
    bool success=false;
    while(!success)
    {
        wyswietleksponaty(lista, nofilter, wystawy);
        printf("Podaj id eksponatu, ktorego dane chcesz zmienic lub wpisz 0, aby wyjsc do menu: ");
        int nr;
        char n;
        fflush(stdin);
        scanf("%d", &nr);
        if(nr==0) break;
        eksponat* pom=*lista;
        while(pom!=NULL)
        {
            if(pom->id>nr)
            {
                system("cls");
                printf("Na liscie nie ma eksponatu o id = %d\n", nr);
            }
            else if(nr>=ideksponatu)
            {
                system("cls");
                printf("Na liscie nie ma eksponatu o id = %d\n", nr);
            }
            else if(pom->id==nr)
            {
                printf("Ktore dane chcesz zmienic?\n");
                printf("1.Nazwa\n");
                printf("2.Opis\n");
                printf("3.Data powstania\n");
                printf("4.Data dodania\n");
                printf("5.Waga\n");
                printf("6.Stan\n");
                fflush(stdin);
                scanf("%c", &n);
                switch(n)
                {
                case '1':
                    printf("Podaj nowa nazwe: ");
                    fflush(stdin);
                    gets(pom->nazwa);
                    _fill(pom->nazwa, 51);

                    pom3=(*powieku);
                    while(pom3->id!=pom->id) pom3=pom3->next;
                    duplicate(pom->nazwa, pom3->nazwa);

                    pom3=(*postanie);
                    while(pom3->id!=pom->id) pom3=pom3->next;
                    duplicate(pom->nazwa, pom3->nazwa);

                    break;
                case '2':
                    printf("Podaj nowy opis: ");
                    fflush(stdin);
                    gets(pom->opis);
                    _fill(pom->opis, 1001);
                    break;
                case '3':
                    printf("Podaj date powstania: ");
                    fflush(stdin);
                    do
                    {
                        gets(pom->datapowstania);
                        _fill(pom->datapowstania, 21);
                        pom->wiek=0;
                    }while(!parseage(pom->datapowstania, &(pom->wiek)));
                    clone(&pom, &copy);
                    pom2=(*powieku);
                    if((*powieku)->id==pom->id)
                    {
                        pom2=(*powieku)->next;
                        free(*powieku);
                        (*powieku)=pom2;
                    }
                    else
                    {
                        while(pom2!=NULL)
                        {
                            if(pom2->next->id==pom->id)
                            {
                                eksponat* pom3=pom2->next;
                                pom2->next=pom3->next;
                                free(pom3);
                                break;
                            }
                            pom2=pom2->next;
                        }
                    }
                    eksponatbyage(powieku, &copy);
                    break;
                case '4':
                    printf("Podaj date dodania: ");
                    fflush(stdin);
                    gets(pom->datadodania);
                    _fill(pom->datadodania, 21);
                    break;
                case '5':
                    printf("Podaj wage w kg: ");
                    fflush(stdin);
                    scanf("%f", &(pom->waga));
                    break;
                case '6':
                    printf("Podaj stan eksponatu w skali od 1 do 5: ");
                    fflush(stdin);
                    scanf("%d", &(pom->stan));
                    clone(&pom, &copy);
                    pom2=(*postanie);
                    if((*postanie)->id==pom->id)
                    {
                        pom2=(*postanie)->next;
                        free(*postanie);
                        (*postanie)=pom2;
                    }
                    else
                    {
                        while(pom2!=NULL)
                        {
                            if(pom2->next->id==nr)
                            {
                                eksponat* pom3=pom2->next;
                                pom2->next=pom3->next;
                                free(pom3);
                                break;
                            }
                            pom2=pom2->next;
                        }
                    }
                    eksponatbycondition(postanie, &copy);
                    break;
                }
                printf("Pomyslnie zaktualizowano dane eksponatu\n");
                success=true;
                break;
            }
            pom=pom->next;
        }
    }
    printf("Wpisz dowolny znak, aby kontynuowac: ");
    fflush(stdin);
    scanf("%c", &whatever);
    system("cls");
}
void usunwystawe(wystawa** lista, eksponat** eksponaty)//usuwa wystawe
{
    system("cls");
    bool success=false;
    while(!success)
    {
        wyswietlwystawy(lista);
        printf("Podaj numer id wystawy, ktora mam usunac, lub wpisz 0, aby wyjsc do menu: ");
        int nr;
        fflush(stdin);
        scanf("%d", &nr);
        if(nr==0) break;
        wystawa* pom=(*lista);
        wystawa* pom3=NULL;
        eksponat* pom2=(*eksponaty);
        if(pom->id==nr)
        {
            while(pom2!=NULL)
            {
                if(pom2->id_wystawy==nr)
                    pom2->id_wystawy=0;
                pom2=pom2->next;
            }
            pom3=pom->next;
            free(pom);
            (*lista)=pom3;
            printf("Pomyslnie usunieto wybrana wystawe\n");
            printf("Wpisz dowolny znak, aby kontynuowac: ");
            fflush(stdin);
            scanf("%c", &whatever);
            system("cls");
            return;
        }
        if(nr>=idwystawy)
        {
            system("cls");
            printf("Na liscie nie ma wystawy o id = %d\n", nr);
            break;
        }
        else
        {
            while(pom!=NULL)
            {
                if(pom->next!=NULL)
                {
                    if(pom->next->id>nr)
                    {
                        system("cls");
                        printf("Na liscie nie ma wystawy o id = %d\n", nr);
                    }
                    else if(pom->next->id==nr)
                    {
                        while(pom2!=NULL)
                        {
                            if(pom2->id_wystawy==nr)
                                pom2->id_wystawy=0;
                            pom2=pom2->next;
                        }
                        pom3=pom->next->next;
                        free(pom->next);
                        pom->next=pom3;
                        printf("Pomyslnie usunieto wybrana wystawe\n");
                        success=true;
                        break;
                    }
                    pom=pom->next;
                }
                else
                {
                    if(pom->id==nr)
                    {
                        while(pom2!=NULL)
                        {
                            if(pom2->id_wystawy==nr)
                                pom2->id_wystawy=0;
                            pom2=pom2->next;
                        }
                        pom3=(*lista);
                        while(pom3->next!=pom) pom3=pom3->next;
                        free(pom3->next);
                        pom3->next=NULL;
                        printf("Pomyslnie usunieto wybrana wystawe\n");
                        success=true;
                        break;
                    }
                    if(pom->next!=NULL) pom=pom->next;
                    else break;
                }
            }
        }

    }
    printf("Wpisz dowolny znak, aby kontynuowac: ");
    fflush(stdin);
    scanf("%c", &whatever);
    system("cls");
}
void zmiennazwewystawy(wystawa** lista)//zmienia nazwe wystawy
{
    int nr;
    system("cls");
    bool success=false;
    while(!success)
    {
        wyswietlwystawy(lista);
        printf("Podaj numer id wystawy, ktorej nazwe chcesz zmienic lub wpisz 0, aby wyjsc do menu: ");
        fflush(stdin);
        scanf("%d", &nr);
        if(nr==0) break;
        wystawa* pom=*lista;
        while(pom!=NULL)
        {
            if(pom->id>nr)
            {
                system("cls");
                printf("Na liscie nie ma wystawy o id = %d\n", nr);
            }
            else if(nr>=idwystawy)
            {
                system("cls");
                printf("Na liscie nie ma wystawy o id = %d\n", nr);
            }
            else if(pom->id==nr)
            {
                printf("Podaj nowa nazwe wystawy: ");
                fflush(stdin);
                gets(pom->nazwa);
                _fill(pom->nazwa, 51);
                printf("Pomyslnie zmieniono nazwe wystawy\n");
                success=true;
                break;
            }
            pom=pom->next;
        }
    }
    printf("Wpisz dowolny znak, aby kontynuowac: ");
    fflush(stdin);
    scanf("%c", &whatever);
    system("cls");
}
void zmianasali(wystawa** lista)//przenosi wystawe do innej sali
{
    int nr, nowasala;
    system("cls");
    bool success=false;
    while(!success)
    {
        cout<<2<<endl;
        wyswietlwystawy(lista);
        printf("Podaj numer id wystawy, ktora chcesz przeniesc lub wpisz 0, aby wyjsc do menu: ");
        fflush(stdin);
        scanf("%d", &nr);
        if(nr==0) break;
        wystawa* pom=*lista;
        while(pom!=NULL)
        {
            if(pom->id>nr)
            {
                system("cls");
                printf("Na liscie nie ma wystawy o id = %d\n", nr);
            }
            else if(nr>=idwystawy)
            {
                system("cls");
                printf("Na liscie nie ma wystawy o id = %d\n", nr);
            }
            else if(pom->id==nr)
            {
                printf("Do ktorej sali mamy przeniesc wystawe?\n");
                fflush(stdin);
                scanf("%d", &nowasala);
                pom->nr_sali=nowasala;
                printf("Wystawa zostala pomyslnie przeniesiona do sali nr %d\n", nowasala);
                success=true;
                break;
            }
            pom=pom->next;
        }
    }
    printf("Wpisz dowolny znak, aby kontynuowac: ");
    fflush(stdin);
    scanf("%c", &whatever);
    system("cls");
}
void zawartoscwystawy(wystawa** lista, eksponat** eksponaty)//dodawanie i usuwanie eksponatow do i z wystawy
{
    system("cls");
    printf("Dostepne akcje:\n");
    printf("1.Przypisz eksponat do wystawy.\n");
    printf("2.Usun eksponat z wystawy.\n");
    int nr, nr2;
    char n;
    bool success=false, success2=false;
    wystawa* pom;
    eksponat* pom2;
    fflush(stdin);
    scanf("%c", &n);
    while(n!='1'&&n!='2')
    {
        system("cls");
        printf("Nie ma takiej opcji.\n");
        printf("Dostepne akcje:\n");
        printf("1.Przypisz eksponat do wystawy.\n");
        printf("2.Usun eksponat z wystawy.\n");
        fflush(stdin);
        scanf("%c", &n);
    }
    switch(n)
    {
    case '1':
        while(!success)
        {
            wyswietlwystawy(lista);
            printf("Podaj numer id szukanej wystawy: ");
            fflush(stdin);
            scanf("%d", &nr);
            if(nr==0) return;
            pom=*lista;
            while(pom!=NULL)
            {
                if(pom->id>nr)
                {
                    system("cls");
                    printf("Na liscie nie ma wystawy o id = %d\n", nr);
                }
                else if(nr>=idwystawy)
                {
                    system("cls");
                    printf("Na liscie nie ma wystawy o id = %d\n", nr);
                }
                else if(pom->id==nr)
                {
                    while(!success2)
                    {
                        wyswietleksponaty(eksponaty, nofilter, lista);
                        printf("Podaj numer id eksponatu, ktory mam przypisac do wybranej wystawy lub wpisz 0, aby wyjsc do menu: ");
                        fflush(stdin);
                        scanf("%d", &nr2);
                        if(nr2==0)
                        {
                            system("cls");
                            return;
                        }
                        pom2=*eksponaty;
                        while(pom2!=NULL)
                        {
                            if(pom2->id>nr2)
                            {
                                system("cls");
                                printf("Na liscie nie ma eksponatu o id = %d\n", nr2);
                            }
                            else if(nr2>=ideksponatu)
                            {
                                system("cls");
                                printf("Na liscie nie ma eksponatu o id = %d\n", nr2);
                            }
                            else if(pom2->id==nr2)
                            {
                                if(pom2->id_wystawy==0)
                                {
                                    pom2->id_wystawy=nr;
                                    printf("Pomyslnie dodano wybrany eksponat do wystawy\n");
                                }
                                else
                                {
                                    printf("Nie mozna dodac eksponatu, gdyz znajduje sie on juz na innej ekspozycji!!!\n");
                                }
                                success2=true;
                                break;
                            }
                        pom2=pom2->next;
                        }
                    }
                    success=true;
                    break;
                }
            pom=pom->next;
            }
        }
        break;
    case '2':
        while(!success)
        {
            wyswietlwystawy(lista);
            printf("Podaj numer id szukanej wystawy lub wpisz 0, aby wyjsc do menu: ");
            fflush(stdin);
            scanf("%d", &nr);
            if(nr==0)
            {
                system("cls");
                return;
            }
            pom=*lista;
            while(pom!=NULL)
            {
                if(pom->id>nr)
                {
                    system("cls");
                    printf("Na liscie nie ma wystawy o id = %d\n", nr);
                }
                else if(nr>=idwystawy)
                {
                    system("cls");
                    printf("Na liscie nie ma wystawy o id = %d\n", nr);
                }
                else if(pom->id==nr)
                {
                    while(!success2)
                    {
                        eksponat* pom3=*eksponaty;
                        while(pom3!=NULL)
                        {
                            if(pom3->id_wystawy==nr)
                            {
                                printf("%d. ", pom3->id);
                                write(pom3->nazwa);
                            }
                            pom3=pom3->next;
                        }
                        printf("Podaj numer id eksponatu, ktory mam usunac z wybranej wystawy lub wpisz 0, aby wyjsc do menu: ");
                        fflush(stdin);
                        scanf("%d", &nr2);
                        if(nr2==0) return;
                        pom2=*eksponaty;
                        while(pom2!=NULL)
                        {
                            if(pom2->id>nr2)
                            {
                                system("cls");
                                printf("Na liscie nie ma eksponatu o id = %d\n", nr2);
                            }
                            else if(nr2>=ideksponatu)
                            {
                                system("cls");
                                printf("Na liscie nie ma eksponatu o id = %d\n", nr2);
                            }
                            else if(pom2->id==nr2)
                            {
                                if(pom2->id_wystawy==nr)
                                {
                                    pom2->id_wystawy=0;
                                    printf("Pomyslnie usunieto wybrany eksponat z wystawy\n");
                                }
                                else
                                {
                                    printf("Nie mozna dodac eksponatu, gdyz znajduje sie on juz na innej ekspozycji!!!\n");
                                }
                                success2=true;
                                break;
                            }
                        pom2=pom2->next;
                        }
                    }
                    success=true;
                    break;
                }
                pom=pom->next;
            }
        }
        break;
    }
    printf("Wpisz dowolny znak, aby kontynuowac: ");
    fflush(stdin);
    scanf("%c", &whatever);
    system("cls");
}
void wystawadetails(wystawa** lista, eksponat** eksponaty)//wyswietla dane szczegolowe wystawy
{
    int nr, counter=0;
    system("cls");
    bool success=false;
    while(!success)
    {
        wyswietlwystawy(lista);
        printf("Podaj numer id wystawy lub wpisz 0, aby wyjsc do menu: ");
        fflush(stdin);
        scanf("%d", &nr);
        if(nr==0) break;
        wystawa* pom=*lista;
        eksponat* pom2=*eksponaty;
        while(pom!=NULL)
        {
            if(pom->id>nr)
            {
                system("cls");
                printf("Na liscie nie ma wystawy o id = %d\n", nr);
            }
            else if(nr>=idwystawy)
            {
                system("cls");
                printf("Na liscie nie ma wystawy o id = %d\n", nr);
            }
            else if(pom->id==nr)
            {
                system("cls");
                printf("id wystawy: %d\n", pom->id);
                printf("nazwa wystawy: ");
                write(pom->nazwa);
                printf("opis wystawy: ");
                write(pom->opis);
                printf("nr sali: %d\n", pom->nr_sali);
                printf("status: ");
                if(pom->status==1)
                    printf("trwajaca\n");
                else
                    printf("zakonczona\n");
                printf("Przedmioty przypisane do wystawy:");
                while(pom2!=NULL)
                {
                    if(pom2->id_wystawy==nr) counter++;
                    pom2=pom2->next;
                }
                pom2=*eksponaty;
                if(counter)
                {
                    printf("\nid  nazwa\n");
                    while(pom2!=NULL)
                    {
                        if(pom2->id_wystawy==nr)
                        {
                            printf("%d. ", pom2->id);
                            write(pom2->nazwa);
                        }
                        pom2=pom2->next;
                    }
                }
                else printf(" Brak przedmiotow na wystawie.\n");
                success=true;
                break;
            }
            pom=pom->next;
        }
    }
    printf("Wpisz dowolny znak, aby kontynuowac: ");
    fflush(stdin);
    scanf("%c", &whatever);
    system("cls");
}
void eksponatdetails(eksponat** lista, wystawa** wystawy)//wyswietla dane szczegolowe eksponatu
{
    int nr=0;
    bool success=false;
    system("cls");
    while(!success)
    {
        printf("Lista eksponatow:\n");
        wyswietleksponaty(lista, nofilter, wystawy);
        printf("Podaj numer id eksponatu lub wpisz 0, aby wyjsc do menu: ");
        fflush(stdin);
        scanf("%d", &nr);
        if(nr==0) break;
        eksponat* pom=(*lista);
        while(pom!=NULL)
        {
            if((pom->id)>nr)
            {
                system("cls");
                printf("Na liscie nie ma eksponatu o id = %d\n", nr);
            }
            else if(nr>=ideksponatu)
            {
                system("cls");
                printf("Na liscie nie ma eksponatu o id = %d\n", nr);
            }
            else if(pom->id==nr)
            {
                system("cls");
                printf("id eksponatu: %d\n", pom->id);
                printf("nazwa eksponatu: ");
                write(pom->nazwa);
                printf("opis: ");
                write(pom->opis);
                printf("data powstania: ");
                write(pom->datapowstania);
                printf("waga: %.2f kg\n", pom->waga);
                printf("data dodania: ");
                write(pom->datadodania);
                printf("stan: %d\n", pom->stan);
                if(pom->id_wystawy==0) printf("przedmiot nie jest przypisany do zadnej wystawy\n");
                else printf("przedmiot jest przypisany do ekspozycji nr %d\n", pom->id_wystawy);
                success=true;
                break;
            }
            pom=pom->next;
        }
    }
    printf("Wpisz dowolny znak, aby kontynuowac: ");
    fflush(stdin);
    scanf("%c", &whatever);
    system("cls");
}
void kontrolaeksponatow(eksponat** lista, wystawa** wystawy, eksponat** powieku, eksponat** postanie)//wyswietla menu kontroli eksponatow
{
    char n, n2, nr;
    do
    {
        if((*lista)==NULL)
        {
            printf("Witamy w panelu kontroli eksponatow.\nAktualnie do systemu nie ma dodanych zadnych eksponatow.\n\n");
            printf("Lista mozliwych akcji:\n");
            printf("1.Dodaj nowy eksponat\n");
            printf("2.Wyjdz do menu glownego.\n");
            fflush(stdin);
            scanf("%c", &n);
            switch(n)
            {
            case '1':
                dodajeksponat(lista, powieku, postanie);
                break;
            case '2':
                return;
            default:
                system("cls");
                printf("Nie ma takiej opcji. Sprobuj jeszcze raz.\n");
                break;
            }
        }
        else if((*wystawy)!=NULL)
        {
            printf("Witamy w panelu kontroli eksponatow. Oto lista wszystkich eksponatow zapisanych w systemie:\n");
            wyswietleksponaty(lista, nofilter, wystawy);
            printf("\nLista mozliwych akcji:\n");
            printf("1.Dodaj nowy eksponat\n");
            printf("2.Usun eksponat z bazy\n");
            printf("3.Dodaj eksponat do istniejacej wystawy\n");
            printf("4.Edytuj dane eksponatu\n");
            printf("5.Wyswietl szczegolowe dane nt. eksponatu.\n");
            printf("6.Wyswietl liste eksponatow zamieszczonych w systemie.\n");
            printf("7.Wyjdz do menu glownego.\n");
            fflush(stdin);
            scanf("%c", &n);
            switch(n)
            {
            case '1':
                dodajeksponat(lista, powieku, postanie);
                break;
            case '2':
                usuneksponat(lista, wystawy, powieku, postanie);
                break;
            case '3':
                przypiszeksponat(lista, wystawy, powieku, postanie);
                break;
            case '4':
                edytujeksponat(lista, wystawy, powieku, postanie);
                break;
            case '5':
                eksponatdetails(lista, wystawy);
                break;
            case '6':
                system("cls");
                printf("W jakiej kolejnosci mam wyswietlic eksponaty?\n");
                printf("1.Wedlug wieku\n2.Wedlug stanu\n3.Wedlug numeru id\n");
                fflush(stdin);
                scanf("%c", &n2);
                while(n2>'3'||n2<'1')
                {
                    system("cls");
                    printf("Nie ma takiego sortowania\n");
                    printf("W jakiej kolejnosci mam wyswietlic eksponaty?\n");
                    printf("1.Wedlug wieku\n2.Wedlug stanu\n3.Wedlug numeru id\n");
                    fflush(stdin);
                    scanf("%c", &n2);
                }
                printf("Czy chcesz dodatkowo przefiltrowac eksponaty?\n");
                printf("1.filtrowanie wg. ekspozycji\n2. filtrowanie wg. stanu\n3. brak filtrowania\n");
                fflush(stdin);
                scanf("%c", &nr);
                while(nr>'3'||nr<'1')
                {
                    system("cls");
                    printf("Nie ma takiego filtrowania\n");
                    printf("Czy chcesz dodatkowo przefiltrowac eksponaty?\n");
                    printf("1.filtrowanie wg. ekspozycji\n2. filtrowanie wg. stanu\n3. brak filtrowania\n");
                    fflush(stdin);
                    scanf("%c", &nr);
                }
                system("cls");
                switch(n2)
                {
                case '1':
                    wyswietleksponaty(powieku, nr, wystawy);
                    break;
                case '2':
                    wyswietleksponaty(postanie, nr, wystawy);
                    break;
                case '3':
                    wyswietleksponaty(lista, nr, wystawy);
                    break;
                }
                printf("Wpisz dowolny znak, aby kontynuowac: ");
                fflush(stdin);
                scanf("%c", &whatever);
                system("cls");
                break;
            case '7':
                return;
            default:
                system("cls");
                printf("Nie ma takiej opcji. Sprobuj jeszcze raz.\n");
                break;
            }
        }
        else
        {
            printf("Witamy w panelu kontroli eksponatow. Oto lista wszystkich eksponatow zapisanych w systemie:\n");
            wyswietleksponaty(lista, nofilter, wystawy);
            printf("\nLista mozliwych akcji:\n");
            printf("1.Dodaj nowy eksponat\n");
            printf("2.Usun eksponat z bazy\n");
            printf("3.Edytuj dane eksponatu\n");
            printf("4.Wyswietl szczegolowe dane nt. eksponatu.\n");
            printf("5.Wyswietl liste eksponatow zamieszczonych w systemie.\n");
            printf("6.Wyjdz do menu glownego.\n");
            fflush(stdin);
            scanf("%c", &n);
            switch(n)
            {
            case '1':
                dodajeksponat(lista, powieku, postanie);
                break;
            case '2':
                usuneksponat(lista, wystawy, powieku, postanie);
                break;
            case '3':
                edytujeksponat(lista, wystawy, powieku, postanie);
                break;
            case '4':
                eksponatdetails(lista, wystawy);
                break;
            case '5':
                system("cls");
                printf("W jakiej kolejnosci mam wyswietlic eksponaty?\n");
                printf("1.Wedlug wieku\n2.Wedlug stanu\n3.Wedlug numeru id\n");
                fflush(stdin);
                scanf("%c", &n2);
                while(n2>'3'||n2<'1')
                {
                    system("cls");
                    printf("Nie ma takiego sortowania\n");
                    printf("W jakiej kolejnosci mam wyswietlic eksponaty?\n");
                    printf("1.Wedlug wieku\n2.Wedlug stanu\n3.Wedlug numeru id\n");
                    fflush(stdin);
                    scanf("%c", &n2);
                }
                printf("Czy chcesz dodatkowo przefiltrowac eksponaty?\n");
                printf("1.filtrowanie wg. ekspozycji\n2. filtrowanie wg. stanu\n3. brak filtrowania\n");
                fflush(stdin);
                scanf("%c", &nr);
                while(nr>'3'||nr<'1')
                {
                    system("cls");
                    printf("Nie ma takiego filtrowania\n");
                    printf("Czy chcesz dodatkowo przefiltrowac eksponaty?\n");
                    printf("1.filtrowanie wg. ekspozycji\n2. filtrowanie wg. stanu\n3. brak filtrowania\n");
                    fflush(stdin);
                    scanf("%c", &nr);
                }
                system("cls");
                switch(n2)
                {
                case '1':
                    wyswietleksponaty(powieku, nr, wystawy);
                    break;
                case '2':
                    wyswietleksponaty(postanie, nr, wystawy);
                    break;
                case '3':
                    wyswietleksponaty(lista, nr, wystawy);
                    break;
                }
                printf("Wpisz dowolny znak, aby kontynuowac: ");
                fflush(stdin);
                scanf("%c", &whatever);
                system("cls");
                break;
            case '6':
                return;
            default:
                system("cls");
                printf("Nie ma takiej opcji. Sprobuj jeszcze raz.\n");
                break;
            }
        }
    }while(true);
}
void kontrolawystaw(wystawa** lista, eksponat** eksponaty)//wyswietla menu kontroli wystaw
{
    char n;
    while(true)
    {
        if((*lista)==NULL)
        {
            printf("Witamy w panelu kontroli wystaw.\nAktualnie w systemie nie ma zadnych zapisanych ekspozycji.\n");
            printf("\nLista mozliwych akcji:\n");
            printf("1.Dodaj nowa wystawe.\n");
            printf("2.Wyjdz do menu glownego.\n");
            fflush(stdin);
            scanf("%c", &n);
            switch(n)
            {
            case '1':
                nowawystawa(lista);
                break;
            case '2':
                return;
            default:
                system("cls");
                printf("Nie ma takiej opcji. Sprobuj jeszcze raz.\n");
                break;
            }
        }
        else
        {
            printf("Witamy w panelu kontroli wystaw. Oto lista wszystkich ekspozycji zapisanych w systemie:\n");
            printf("id  nazwa wystawy\n");
            wyswietlwystawy(lista);
            printf("\nLista mozliwych akcji:\n");
            printf("1.Dodaj nowa wystawe.\n");
            printf("2.Usun wystawe z bazy.\n");
            printf("3.Zmien nazwe wystawy.\n");
            printf("4.Zmien status wystawy.\n");
            printf("5.Przenies wystawe do innej sali.\n");
            printf("6.Aktualizuj spis eksponatow znajdujacych sie na wystawie.\n");
            printf("7.Wyswietl szczegolowe informacje nt. wystawy.\n");
            printf("8.Wyjdz do menu glownego.\n");
            fflush(stdin);
            scanf("%c", &n);
            switch(n)
            {
            case '1':
                nowawystawa(lista);
                break;
            case '2':
                usunwystawe(lista, eksponaty);
                break;
            case '3':
                zmiennazwewystawy(lista);
                break;
            case '4':
                zmienstatus(lista);
                break;
            case '5':
                zmianasali(lista);
                break;
            case '6':
                zawartoscwystawy(lista, eksponaty);
                break;
            case '7':
                wystawadetails(lista, eksponaty);
                break;
            case '8':
                return;
            default:
                system("cls");
                printf("Nie ma takiej opcji. Sprobuj jeszcze raz.\n");
                break;
            }
        }
    }
}
void zapiszeksponaty(eksponat** lista, const char* plik)//zapisuje dane eksponatow do pliku
{
    FILE* eksponaty=fopen(plik, "w");
    eksponat* pom=(*lista);
    while(pom!=NULL)
    {
        fprintf(eksponaty, "%d", pom->id);
        fprintf(eksponaty, " ");
        fputs(pom->nazwa, eksponaty);
        fputs(pom->opis, eksponaty);
        fputs(pom->datapowstania, eksponaty);
        fprintf(eksponaty, "%d", pom->wiek);
        fprintf(eksponaty, " ");
        fprintf(eksponaty, "%f", pom->waga);
        fprintf(eksponaty, " ");
        fputs(pom->datadodania, eksponaty);
        fprintf(eksponaty, "%d", pom->stan);
        fprintf(eksponaty, " ");
        fprintf(eksponaty, "%d", pom->id_wystawy);
        fprintf(eksponaty, " ");
        pom=pom->next;
    }
    fclose(eksponaty);
    pom=(*lista);
    eksponat* pom2=pom;
    while(pom!=NULL)
    {
        pom2=pom;
        pom=pom->next;
        free(pom2);
    }
}
void zapisziwyjdz(eksponat** lista, wystawa** wystawy, eksponat** powieku, eksponat** postanie)//zapisuje dane z biezacej sesji do plikow
{
    zapiszeksponaty(lista, "eksponaty.txt");
    zapiszeksponaty(postanie, "eksponatywgstanu.txt");
    zapiszeksponaty(powieku, "eksponatywgwieku.txt");
    FILE* exhibition=fopen("wystawy.txt", "w");
    wystawa* pom3=(*wystawy);
    while(pom3!=NULL)
    {
        fprintf(exhibition, "%d", pom3->id);
        fprintf(exhibition, " ");
        fputs(pom3->nazwa, exhibition);
        fputs(pom3->opis, exhibition);
        fprintf(exhibition, "%d", pom3->status);
        fprintf(exhibition, " ");
        fprintf(exhibition, "%d", pom3->nr_sali);
        fprintf(exhibition, " ");
        pom3=pom3->next;
    }
    fclose(exhibition);
    pom3=(*wystawy);
    wystawa* pom4=pom3;
    while(pom3!=NULL)
    {
        pom4=pom3;
        pom3=pom3->next;
        free(pom4);
    }
}
void wczytajeksponaty(eksponat** lista, const char* plik)//wczytuje dane eksponatow
{
    char c='0';
    FILE* eksponaty=fopen(plik, "r");
    eksponat* pom=NULL;
    if(eksponaty==NULL)
    {
        printf("Nie znaleziono pliku zawierajacego dane eksponatow.\nPrzed ponownym uruchomieniem programu upewnij sie, ze katalog z programem zawiera plik %s  i nie jest on otwarty w innym programie\n", plik);
        program=false;
        return;
    }
    else
    {
        c=fgetc(eksponaty);
        if(!feof(eksponaty))
        {
            fseek(eksponaty, -1, SEEK_CUR);
            (*lista)=(eksponat*)malloc(sizeof(eksponat));
            pom=(*lista);
            fscanf(eksponaty, "%d", &((*lista)->id));
            c=fgetc(eksponaty);
            fgets((*lista)->nazwa, 51, eksponaty);
            fgets((*lista)->opis, 1001, eksponaty);
            fgets((*lista)->datapowstania, 21, eksponaty);
            fscanf(eksponaty, "%d", &((*lista)->wiek));
            c=fgetc(eksponaty);
            fscanf(eksponaty, "%f", &((*lista)->waga));
            c=fgetc(eksponaty);
            fgets((*lista)->datadodania, 21, eksponaty);
            fscanf(eksponaty, "%d", &((*lista)->stan));
            c=fgetc(eksponaty);
            fscanf(eksponaty, "%d", &((*lista)->id_wystawy));
            c=fgetc(eksponaty);
            c=fgetc(eksponaty);
            ideksponatu=max(ideksponatu, (*lista)->id);
            if(ideksponatu==(*lista)->id) ideksponatu++;
            (*lista)->next=NULL;
            while(!feof(eksponaty))
            {
                fseek(eksponaty, -1, SEEK_CUR);
                (*lista)->next=(eksponat*)malloc(sizeof(eksponat));
                fscanf(eksponaty, "%d", &((*lista)->next->id));
                c=fgetc(eksponaty);
                fgets((*lista)->next->nazwa, 51, eksponaty);
                fgets((*lista)->next->opis, 1001, eksponaty);
                fgets((*lista)->next->datapowstania, 21, eksponaty);
                fscanf(eksponaty, "%d", &((*lista)->next->wiek));
                c=fgetc(eksponaty);
                fscanf(eksponaty, "%f", &((*lista)->next->waga));
                c=fgetc(eksponaty);
                fgets((*lista)->next->datadodania, 21, eksponaty);
                fscanf(eksponaty, "%d", &((*lista)->next->stan));
                c=fgetc(eksponaty);
                fscanf(eksponaty, "%d", &((*lista)->next->id_wystawy));
                c=fgetc(eksponaty);
                c=fgetc(eksponaty);
                ideksponatu=max(ideksponatu, (*lista)->next->id);
                if(ideksponatu==(*lista)->next->id) ideksponatu++;
                (*lista)=(*lista)->next;
                (*lista)->next=NULL;
            }
        }
        (*lista)=pom;
    }
    fclose(eksponaty);
}
void inicjalizacja(eksponat** lista, wystawa** wystawy, eksponat** powieku, eksponat** postanie)//wczytuje dane z plikow
{
    char c='0';
    wczytajeksponaty(lista, "eksponaty.txt");
    wczytajeksponaty(postanie, "eksponatywgstanu.txt");
    wczytajeksponaty(powieku, "eksponatywgwieku.txt");
    FILE* exhibition=fopen("wystawy.txt", "r");
    if(exhibition==NULL)
    {
        printf("Nie znaleziono pliku zawierajacego dane ekspozycji.\nPrzed ponownym uruchomieniem programu upewnij sie, ze katalog z programem zawiera plik wystawy.txt i nie jest on otwarty w innym programie\n");
        program=false;
        return;
    }
    else
    {
        c=getc(exhibition);
        wystawa* pom2=NULL;
        if((int)c!=EOF)
        {
            (*wystawy)=(wystawa*)malloc(sizeof(wystawa));
            fseek(exhibition, -1, SEEK_CUR);
            pom2=(*wystawy);
            fscanf(exhibition, "%d", &((*wystawy)->id));
            getc(exhibition);
            fgets((*wystawy)->nazwa, 51, exhibition);
            fgets((*wystawy)->opis, 1001, exhibition);
            fscanf(exhibition, "%d", &((*wystawy)->status));
            fgetc(exhibition);
            fscanf(exhibition, "%d", &((*wystawy)->nr_sali));
            getc(exhibition);
            idwystawy=max(idwystawy, (*wystawy)->id);
            if(idwystawy==(*wystawy)->id) idwystawy++;
            c=getc(exhibition);
            (*wystawy)->next=NULL;
            while((int)c!=EOF)
            {
                (*wystawy)->next=(wystawa*)malloc(sizeof(wystawa));
                fseek(exhibition, -1, SEEK_CUR);
                fscanf(exhibition, "%d", &((*wystawy)->next->id));
                getc(exhibition);
                fgets((*wystawy)->next->nazwa, 51, exhibition);
                fgets((*wystawy)->next->opis, 1001, exhibition);
                fscanf(exhibition, "%d", &((*wystawy)->next->status));
                fgetc(exhibition);
                fscanf(exhibition, "%d", &((*wystawy)->next->nr_sali));
                getc(exhibition);
                idwystawy=max(idwystawy, (*wystawy)->next->id);
                if(idwystawy==(*wystawy)->next->id) idwystawy++;
                c=getc(exhibition);
                (*wystawy)=(*wystawy)->next;
                (*wystawy)->next=NULL;
            }
        }
        (*wystawy)=pom2;
    }
    fclose(exhibition);
}
void menu(eksponat** listaeksponatow, wystawa** listawystaw, eksponat** powieku, eksponat** postanie)//wyswietla menu glowne programu
{
    char n;
    do
    {
        printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
        printf("\t%c MENU GLOWNE %c\n", 186, 186);
        printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
        printf("1.Panel kontroli eksponatow\n");
        printf("2.Panel edycji wystaw\n");
        printf("3.Wyjdz z programu\n");
        fflush(stdin);
        scanf("%c", &n);
        switch(n)
        {
        case '1':
            system("cls");
            kontrolaeksponatow(listaeksponatow, listawystaw, powieku, postanie);
            break;
        case '2':
            system("cls");
            kontrolawystaw(listawystaw, listaeksponatow);
            break;
        case '3':
            system("cls");
            zapisziwyjdz(listaeksponatow, listawystaw, powieku, postanie);
            program=false;
            break;
        default:
            system("cls");
            printf("Nie ma takiej opcji. :(\n\n");
            break;
        }
    }while(n<'1'||n>'3');
}
int main()
{
    eksponat* listaeksponatow=NULL;
    eksponat* powieku=NULL;
    eksponat* postanie=NULL;
    wystawa* listawystaw=NULL;
    inicjalizacja(&listaeksponatow, &listawystaw, &powieku, &postanie);
    while(program)
    {
        system("cls");
        menu(&listaeksponatow, &listawystaw, &powieku, &postanie);
    }
    printf("Dziekujemy za skorzystanie z naszego programu. Do zobaczenia wkrotce.\n");
    Sleep(3500);
    return 0;
}
