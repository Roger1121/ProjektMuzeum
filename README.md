# ProjektMuzeum
Projekt systemu wspierającego pracę muzeum, wykonany na pierwszym semestrze studiów.

Muzeum\
Program pozwala na wprowadzenie danych eksponatów muzealnych. Każdy eksponat zawiera następujące dane: nazwa, opis, rok stworzenia (lub orientacyjny zakres), waga, data dodania do zbioru, stan (w skali od 1 do 5). Eksponaty można przeglądać (posortowane po numerze id,  stanie lub wieku), edytować i usuwać. Program pozwala również przechowywać dane ekspozycji, każda opisana jest przez nazwę, opis i salę, w której jest wystawiona. Do ekspozycji możemy dodawać posiadane w zbiorze eksponaty. Pojedyncza ekspozycja może zawierać wiele eksponatów, ale eksponat może być prezentowany tylko na jednej ekspozycji. Ekspozycję możemy usunąć lub oznaczyć w systemie jako zakończoną.\
Nie możemy usunąć z systemu eksponatu, który aktualnie jest prezentowany. Eksponaty możemy filtrować wg. Ekspozycji, na której są prezentowane lub wg. stanu.\
\
konwencje przyjęte w programie:\
daty są przyjmowane w formacie dd.mm.rrrr (przy czym można użyć dowolnego separatora, a rok może mieć dowolną długość, lecz format daty nie może przekroczyć 20 znaków);\
jeżeli dokładna data stworzenia eksponatu nie jest znana, okres, z jakiego pochodzi eksponat, należy zapisać w formacie xxxx-xxxx,\
gdzie xxxx oznacza liczbę całkowitą reprezentującą rok początku/końca okresu (format daty nie może przekroczyć 20 znaków);\
daty i okresy sprzed naszej ery powinny być poprzedzone minusem;\
przy sortowaniu eksponatów wg. daty powstania, dla eksponatów, dla których podano jedynie orientacyjny zakres powstania, pod uwagę brany jest początek tego okresu;\
nazwy eksponatów i wystaw mogą zawierać maksymalnie 50 znaków;\
opisy eksponatów i wystaw mogą zawierać maksymalnie 1000 znaków;\
po zmianie statusu wystawy z trwającej na zakończoną, eksponaty pozostają przypisane do tej wystawy, gdyż może ona zostać ponownie wystawiona z taką samą zawartością;\
Numery sal są przechowywane jako liczby całkowite, bez dodatkowych znaków (np. 101, ale 101A już nie);\
Teksty wczytywane do programu nie powinny zawierać znaku ^, gdyż jest to zarezerwowana wartość specjalna systemu;\
Program nie jest w stanie wykryć wszystkich nieprawidłowości w zapisie daty, dlatego też przed zatwierdzeniem należy się upewnić, że została wpisana poprawnie;\
Przy sortowaniu wg. stanu eksponaty są posortowane po stanie od wartości 1 do 5, tj. od najsłabiej do najlepiej zachowanych;\
\
Opis implementacji:\
Struktury:\
struct eksponat //struktura zawierająca dane eksponatu\
struct wystawa //struktura zawierająca dane wystawy\
Funkcje:\
void duplicate(char* from, char* to) //przepisuje jedna tablice char na druga ( strcpy z odwróconymi parametrami)\
char* from  -  tablica, która ma zostać skopiowana\
char* to  -  tablica, do której przepisujemy tekst\
void _fill(char text[], int n) //dopelnia tablice char do pelnego wymiaru [tekst^   '\0']\
char text[] – tablica do dopełnienia\
int n – dlugosc tablicy\
void write(char text[]) //wypisuje tablice char do pierwszego wystapienia znaku ^\
char text[] – tablica do wypisania\
bool parseage(char data[], int* age)//przepisuje date z tablicy char na int\
	char data[] – tablica z datą do konwersji\
	int* age – wskaźnik na komórkę, do której ma zostać zapisana data\
	zwraca true w przypadku poprawnej konwersji i false w przypadku błędu konwersji\
void eksponatbyage(eksponat** lista, eksponat** nowy)//dodaje eksponat do listy posortowanej wg. wieku\
eksponat** lista –adres wskaźnika na początek listy eksponatów\
eksponat** nowy – adres wskaźnika na nowy eksponat\
void eksponatbycondition(eksponat** lista, eksponat** nowy)// dodaje eksponat do listy posortowanej wg. stanu\
eksponat** lista –adres wskaźnika na początek listy eksponatów\
eksponat** nowy – adres wskaźnika na nowy element\
void clone(eksponat** stary, eksponat** nowy)//duplikuje strukture eksponatu\
eksponat** stary – adres wskaźnika na strukturę, która ma zostać skopiowana\
eksponat** nowy  – adres wskaźnika na strukturę, do której przepisujemy dane\
void dodajeksponat(eksponat** lista, eksponat** powieku, eksponat** postanie)//przypisuje eksponat do wystawy\
eksponat** lista  – adres wskaźnika na początek listy eksponatów\
	eksponat** powieku - adres wskaźnika na początek listy eksponatów posortowanych wg. wieku\
eksponat** postanie - adres wskaźnika na początek listy eksponatów posortowanych wg. stanu\
void wyswietlwystawy(wystawa** lista)//wyswietla liste wystaw\
	wystawa** lista - adres wskaźnika na początek listy wystaw\
void wyswietleksponaty(eksponat** lista, char filtr, wystawa** wystawy)//wyswietla liste eksponatow (posortowana i przefiltrowana)\
eksponat** lista  – adres wskaźnika na początek listy eksponatów\
	char filtr – wartość odpowiadająca filtrowaniu eksponatów\
‘1’ – filtrowanie wg. wystawy\
‘2’– filtrowanie wg. stanu\
‘3’ – brak filtra\
wystawa** wystawy - adres wskaźnika na początek listy wystaw\
void usuneksponat(eksponat** lista, wystawa** wystawy, eksponat** powieku, eksponat** postanie)//usuwa eksponat z systemu\
eksponat** lista  – adres wskaźnika na początek listy eksponatów\
wystawa** wystawy - adres wskaźnika na początek listy wystaw\
eksponat** powieku - adres wskaźnika na początek listy eksponatów posortowanych wg. wieku\
eksponat** postanie - adres wskaźnika na początek listy eksponatów posortowanych wg. stanu\
void nowawystawa(wystawa** lista)//dodaje nowa wystawe do systemu\
wystawa** lista - adres wskaźnika na początek listy wystaw\
void zmienstatus(wystawa** lista)//zmienia status wystawy (trwajaca<->zakonczona)\
wystawa** lista - adres wskaźnika na początek listy wystaw\
void przypiszeksponat(eksponat** lista, wystawa** wystawy, eksponat** powieku, eksponat** postanie)//dodaje eksponat do wystawy\
eksponat** lista  – adres wskaźnika na początek listy eksponatów\
wystawa** wystawy - adres wskaźnika na początek listy wystaw\
eksponat** powieku - adres wskaźnika na początek listy eksponatów posortowanych wg. wieku\
eksponat** postanie - adres wskaźnika na początek listy eksponatów posortowanych wg. stanu\
void edytujeksponat(eksponat** lista, wystawa** wystawy, eksponat** powieku, eksponat** postanie)//modyfikuje dane eksponatow\
eksponat** lista  – adres wskaźnika na początek listy eksponatów\
wystawa** wystawy - adres wskaźnika na początek listy wystaw\
eksponat** powieku - adres wskaźnika na początek listy eksponatów posortowanych wg. wieku\
eksponat** postanie - adres wskaźnika na początek listy eksponatów posortowanych wg. stanu\
void usunwystawe(wystawa** lista, eksponat** eksponaty)//usuwa wystawe\
wystawa** lista - adres wskaźnika na początek listy wystaw\
eksponat** eksponaty  – adres wskaźnika na początek listy eksponatów\
void zmiennazwewystawy(wystawa** lista)//zmienia nazwe wystawy\
wystawa** lista - adres wskaźnika na początek listy wystaw\
void zmianasali(wystawa** lista)//przenosi wystawe do innej Sali\
wystawa** lista - adres wskaźnika na początek listy wystaw\
void zawartoscwystawy(wystawa** lista, eksponat** eksponaty)//dodawanie i usuwanie eksponatow do i z wystawy\
wystawa** lista - adres wskaźnika na początek listy wystaw\
eksponat** eksponaty  – adres wskaźnika na początek listy eksponatów\
void wystawadetails(wystawa** lista, eksponat** eksponaty)//wyswietla dane szczegolowe wystawy\
wystawa** lista - adres wskaźnika na początek listy wystaw\
eksponat** eksponaty  – adres wskaźnika na początek listy eksponatów\
void eksponatdetails(eksponat** lista, wystawa** wystawy)//wyswietla dane szczegolowe eksponatu\
wystawa** lista - adres wskaźnika na początek listy wystaw\
eksponat** eksponaty  – adres wskaźnika na początek listy eksponatów\
void kontrolaeksponatow(eksponat** lista, wystawa** wystawy, eksponat** powieku, eksponat** postanie)//wyswietla menu kontroli eksponatow\
eksponat** lista  – adres wskaźnika na początek listy eksponatów\
wystawa** wystawy - adres wskaźnika na początek listy wystaw\
eksponat** powieku - adres wskaźnika na początek listy eksponatów posortowanych wg. wieku\
eksponat** postanie - adres wskaźnika na początek listy eksponatów posortowanych wg. stanu\
void kontrolawystaw(wystawa** lista, eksponat** eksponaty)//wyswietla menu kontroli wystaw\
wystawa** lista - adres wskaźnika na początek listy wystaw\
eksponat** eksponaty  – adres wskaźnika na początek listy eksponatów\
void zapiszeksponaty(eksponat** lista, const char* plik)//zapisuje dane eksponatow do pliku\
eksponat** lista  – adres wskaźnika na początek listy eksponatów\
	const char* plik – ścieżka dostępu do pliku\
void zapiszeksponaty(eksponat** lista, const char* plik)//zapisuje dane eksponatow do pliku\
eksponat** lista  – adres wskaźnika na początek listy eksponatów\
	const char* plik – ścieżka dostępu do pliku\
void wczytajeksponaty(eksponat** lista, const char* plik)//wczytuje dane eksponatow\
eksponat** lista  – adres wskaźnika na początek listy eksponatów\
	const char* plik – ścieżka dostępu do pliku\
void inicjalizacja(eksponat** lista, wystawa** wystawy, eksponat** powieku, eksponat** postanie)//wczytuje dane z plikow\
eksponat** lista  – adres wskaźnika na początek listy eksponatów\
wystawa** wystawy - adres wskaźnika na początek listy wystaw\
eksponat** powieku - adres wskaźnika na początek listy eksponatów posortowanych wg. wieku\
eksponat** postanie - adres wskaźnika na początek listy eksponatów posortowanych wg. stanu\
void menu(eksponat** listaeksponatow, wystawa** listawystaw, eksponat** powieku, eksponat** postanie)//wyswietla menu glowne programu\
eksponat** listaeksponatow  – adres wskaźnika na początek listy eksponatów\
wystawa** listawystaw - adres wskaźnika na początek listy wystaw\
eksponat** powieku - adres wskaźnika na początek listy eksponatów posortowanych wg. wieku\
eksponat** postanie - adres wskaźnika na początek listy eksponatów posortowanych wg. stanu\
\
Pliki:\
eksponaty.txt – lista eksponatów\
eksponatywgwieku.txt – lista eksponatów posortowana wg. wieku\
eksponatywgstanu.txt – lista eksponatów posortowana wg. stanu\
wystawy.txt – lista wystaw
