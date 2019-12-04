GNU Make
6.1 Ćwiczenie: Wprowadzenie
Make jest narzędziem wspomagającym proces budowania wielomodułowego kodu ze złożonymi zależnościami pomiędzy plikami źródłowymi. W ogólnym przypadku jest przydatny tam, gdzie ma miejsce tworzenie plików wynikowych ze źródłowych, a zmiany w jednych pociągają rekurencyjnie zmiany w kolejnych.
Make działa zawsze w obrębie bieżącego katalogu. Do działania potrzebuje pliku konfiguracyjnego, o domyślnej nazwie Makefile. Celem tego laboratorium jest stopniowe tworzenie takiego pliku dla prostego projektu.

Do ćwiczeń będzie wykorzystywany przygotowany projekt, będący nieco rozbudowaną wersją dwumodułowego programu HelloWorld.

Plik znajduje się w archiwum projektu lab-make.tar.gz
Archiwum należy skopiować do swojego katalogu roboczego (np. $HOME /NAZWISKO) i rozpakować:
$ tar xvzf lab-make.tar.gz
Należy przejść do nowopowstałego katalogu lab-make i w nim ćwiczyć.
W czasie ćwiczeń nie powinny być wymagane jakiekolwiek modyfikacje samego kodu źródłowego w C!
Proszę przyglądnąć się kodowi projektu! Projekt składa się z 3 modułów: głównego i 2 pomocniczych, z których każdy ma swój plik nagłówkowy (proszę zwrócić uwagę na budowę nagłówków!), poza tym jest jeden główny plik nagłówkowy, używany przez wszystkie moduły.
6.2 Ćwiczenie: Ogólna budowa Makefile
Ogólne zasady:
plik Makefile składa się z szeregu reguł definiujących cele (ang. target) (cele pracy programu Make) i ew. definicji zmiennych,
każda reguła ma postać:
cel: prerekwizyty
     polecenia
     ...
     polecenia
UWAGA! w każdej linii gdzie są polecenia, na początku linii MUSI być podwójny znak tabulacji a nie spacje!
sposób interpretacji reguły jest następujący:
przyjmuje się domyślnie, że cel jest nazwą pliku, a
prerekwizyty listą nazw plików,
reguła jest uruchamiana (odpalana) jeżeli data modyfikacji choć jednego prerekwizytu jest późniejsza niż data modyfikacji celu,
dla każdego prerekwizytu, którego data modyfikacji jest późniejsza niż data modyfikacji celu, jest rekurencyjnie uruchamiana (o ile istnieje) reguła która go definiuje (prerekwizytem może być też plik nagłówkowy),
po spełnieniu prerekwizytów uruchamiane są polecenia.
make uruchamia dokładnie jedną, pierwszą regułę,
można również wymusić uruchomienie dowolnego celu z pliku Makefile, podając cel explicite: make cel
6.3 Ćwiczenie: Prosty plik Makefile
Należy zbudować prosty plik dla make, pozwalającący na zbudowanie każdego z modułów i całego programu. Plik należy zapisać pod nazwą Makefile.
UWAGA! proszę pamiętać o wpisywaniu znaku tabulacji w odpowiednich liniach!

hello: hw_hello.o hw_power.o hw_defs.h hw_hello.h hw_power.h
    gcc -Wall -ansi -pedantic -lm hw_main.c hw_hello.o hw_power.o -o hello
    echo hello: zbudowane!

hw_hello.o: hw_hello.c hw_defs.h 
    gcc -c -Wall -ansi -pedantic hw_hello.c

hw_power.o: hw_power.c hw_defs.h 
    gcc -c -Wall -ansi -pedantic hw_power.c
Teraz można zbudować program pisząc po prostu:

$ make
6.4 Ćwiczenie: Kiedy przydaje się Make?
Make przydaje się w wielu sytacjach, szczególnie wtedy gdy plik są powiązane złożonymi rekurencyjnymi zależnościami i modyfikacja jednego wymusza zmianę (rekompilację) innych.
   
6.4.0.1 Przykład 1
Zmiana/modyfikacja pliku hw_power.c powoduje, że:
moduł hw_power musi być zrekompilowany, a
cały program hello zrelinkowany
Proszę zmodyfikować plik hw_power.c, wczytując go do edytora i nagrywając, ew. można tylko zmienić jego datę modyfikacji pisząc:
$ touch hw_power.c
Proszę teraz uruchomić:

$ make
Jakie polecenia zostały uruchomione przez make? Co z 2. modułem (hw_hello)?
Proszę jeszcze raz uruchomić make. Co teraz się dzieje? Dlaczego?

Proszę zmodyfikować plik wynikowy hello, pisząc:

$ touch hello
Proszę jeszcze raz uruchomić make. Co teraz się dzieje? Dlaczego?
   
6.4.0.2 Przykład 2
Zmiana/modyfikacja pliku nagłówkowego hw_hello.h powoduje, że:
moduł hw_main musi być zrekompilowany, a
cały program hello zrelinkowany
Proszę zmodyfikować plik hw_hello.h, wczytując go do edytora i nagrywając, ew. można tylko zmienić jego datę modyfikacji pisząc:
$ touch hw_hello.h
Proszę teraz uruchomić:

$ make
Jakie polecenia zostały uruchomione przez make? Co z modułami (hw_hello, hw_power)?
Proszę jeszcze raz uruchomić make. Co teraz się dzieje? Dlaczego?

Ten przykład ujawnia pewien niedostatek stworzonego pliku Makefile! Jaki?

   
6.4.0.3 Przykład 3
Zmiana/modyfikacja pliku nagłówkowego hw_defs.h powoduje, że:
wszystkie moduły muszą być zrekompilowane, a
cały program hello zrelinkowany
Proszę zmodyfikować plik hw_defs.h, wczytując go do edytora i nagrywając, ew. można tylko zmienić jego datę modyfikacji pisząc:
$ touch hw_defs.h
Proszę teraz uruchomić:

$ make
Jakie polecenia zostały uruchomione przez make?
Proszę jeszcze raz uruchomić make. Co teraz się dzieje? Dlaczego?

6.5 Ćwiczenie: Cele pozorne
Niektóre z reguł w pliku Makefile nie muszą być związane z samą kompilacją, ale czynnościami pomocniczymi. Są to tak zwane cele ,,pozorne'' (ang. phony).
Należy teraz stoworzyć ulepszoną wersję pliku. Starą wersję należy zachować pisząc:

$ cp Makefile Makefile-1
Do nowej wersji należy dopisać regułę, która będzie sprzątała po procesie kompilacji:

clean:
    rm -f *~
    rm -f *.bak
    rm -f hello hw_main.o hw_hello.o hw_power.o
Pierwsze dwa polecenia usuwają pliki kopii zapasowej, które mogą powstać w trakcie edycji plików źródłowych. Trzecie polecenie usuwa wszystkie pliki wynikowe powstające w procesie kompilacji.

Wszystkie cele pozorne muszą być zadeklarowane jako takie, robi się to poprzez specjalny cel .PHONY którego prerekwizytami są wszsytkie cele pozorne w pliku. Proszę dopisać do pliku linię:

.PHONY: clean
Cele pozorne mają ważną cechę: nigdy nie są zaktualizowane (ang. up to date) (tzn. będą budowane przy każdym ich wywołaniu, bez względnu na ich preprekwizyty!).

Proszę teraz uruchomić:

$ make clean
Jakie polecenia zostały uruchomione przez make?
Proszę jeszcze raz uruchomić make clean. Co teraz się dzieje? Dlaczego?

Proszę jeszcze raz uruchomić samo make. Co teraz się dzieje? Dlaczego?

Proszę jeszcze raz uruchomić samo make. Co teraz się dzieje? Dlaczego?

6.6 Ćwiczenie: Zmienne i poprawny plik
W miarę rozbudowywania programu plik Makefile będzie powiększany i aktualizowany. Przy dopisywaniu kolejnych modułów można zauważyć pewne niedogodności w obecnym pliku:
trzeba każdorazowo wpisywać opcje kompilacji dla gcc
trzeba każdorazowo dodawać odpowiednie pliki binarne modułów jako prerekwizyty i do celu clean
jeszcze kilka innych...
Dlatego też używa się zmiennych.

Należy teraz stowrzyć ulepszoną wersję pliku. Starą wersję należy zachować pisząc:

$ cp Makefile Makefile-2
Należy do pliku Makefile dopisać na początku linijki z deklaracjami zmiennych:

CC     = gcc
CFLAGS = -Wall -ansi -pedantic
LFLAGS = -lm
OBJS   = hw_hello.o hw_power.o hw_main.o
EXEC   = hello
Następnie rozbić dotychczasowy cel hello na dwa. Jest to dużo bardziej sensowne i poprawne rozwiąznie niż dotychczasowe (patrz powyższe przykłady uruchomienia):

$(EXEC): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXEC)
	echo hello: zbudowane!

hw_main.o: hw_defs.h hw_hello.h hw_power.h
	$(CC) -c $(CFLAGS) hw_main.c
Następnie należy uaktualnić pozostały fragment:

hw_hello.o: hw_hello.c hw_defs.h 
	$(CC) -c $(CFLAGS) hw_hello.c

hw_power.o: hw_power.c hw_defs.h 
	$(CC) -c $(CFLAGS) hw_power.c

clean:
	rm -f *~ *.bak
	rm -f $(EXEC) $(OBJS)

.PHONY: clean
Taki plik jest znacznie bardziej uniwersalny! Wprowadzenie zmiennych i wydzielenie hw_main jako osobnego modułu nie tylko usunęło w.w. niedogodności, lecz również uczyniło zależności znacznie bardziej przejrzyste (np. plik wynikowy jest jedynie linkowany i nie zależy od plików nagłówkowych!)

Proszę jeszcze raz przećwiczyć wszystkie poprzednie przykłady z nowym plikiem i sprawdzić, czy działa poprawnie!

6.7 Ćwiczenie: Zaawansowany Makefile
Choć teraz plik Makefile jest dużo lepszy, to przy jeszcze większych projektach można by go udoskonalić. W szczególności należy zwrócić uwagę, iż budowanie każdego z 3 modułów jest praktycznie identyczne z dokładnością do:
nazw plików
zależności (prerekwizytów)
Make posiada mechanizmy, które potrafią jeszcze bardziej uprościć budowanie kodu w tym wzorce reguł.
Należy teraz stowrzyć ulepszoną wersję pliku. Starą wersję należy zachować pisząc:

$ cp Makefile Makefile-3
Nowy plik Makefile powinien wyglądać teraz tak:

CC     = gcc
CFLAGS = -Wall -ansi -pedantic
LFLAGS = -lm
OBJS   = hw_hello.o hw_power.o hw_main.o
EXEC   = hello

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LFLAGS) $+ -o $@
	echo hello: zbudowane!

%.o: %.c
	$(CC) -c $(CFLAGS) $<

hw_main.o : hw_defs.h hw_hello.h hw_power.h
hw_hello.o: hw_defs.h 
hw_power.o: hw_defs.h 

clean:
	rm -f *~
	rm -f *.bak
	rm -f $(EXEC) $(OBJS)

.PHONY: clean
Proszę zwrócić uwagę co się zmieniło:

dodano jako pierwszy nowy cel all, jedyne co robi to powoduje zbudowanie programu. Jego dodanie jest zwyczjowe (każdy Makefile powienien go mieć, podobnie jak cel clean), poza tym ułatwia wybór domyślengo celu, gdyby program miał więcej niż jedną możliwości budowania.
w celu odpowiedzialnym za linkowanie użyto 2 specjalne zmienne: $@ oznacza nazwę danego celu, $+ oznacza nazwy wszystkich prerekwizytów
reguły budujące (kompilujące) pliki obiektów binarnych zastąpiono jednym wzorcem, metaregułą budującą wszystkie z nich. Zmienna $< oznacza nazwę danego dopasowanego pliku (w tym przypadku z rozszerzenim .c).
zależności poszczególnych plików zostały podane osobno. Do analizowania zależności z plikami nagłówkowymi Make używa wewnętrzych reguł (tzn. ,,wie'' że plików nagłówkowych nie trzeba budować, a jedynie sprawdzić ich daty modyfikacji).
Proszę ponownie przećwiczyć przykłady z nowym plikiem Makefile.

6.8 Ćwiczenie: Konwencje make, nie tylko kompilacja
Make może zarządzać dowolnym procesem budowania plików, nie tylko kompilacją. W używanych plików występował jeden cel nie związany w ogóle bezpośrednio z kompilatorem, tzn. clean.
Wg konwencji plik Makefile powinien mieć przynajmniej 3 cele:

all
budujący cały program, cel domyślny,
clean
czyszczący kod po kompilacji
install
instalujący program po kompilacji
Często występuje też cel dist powodujący stworzenie archiwum kodu.
Należy teraz stworzyć ulepszoną wersję pliku. Starą wersję należy zachować pisząc:

$ cp Makefile Makefile-4
Aby uzupełnić plik Makefile proszę dopisać do zmiennych na początku pliku:

MANIFEST= *.c *.h Makefile*
DESTDIR = $(HOME)/bin
VER     = 0.1
a następnie do celów na końcu:
install: all
	sh -c "if [ ! -d $(DESTDIR) ] ; then mkdir $(DESTDIR) ; fi"
	cp $(EXEC) $(DESTDIR)/$(EXEC)
	echo hello: zainstalowane!

dist: clean
	tar cvzf ../$(EXEC)-$(VER).tar.gz $(MANIFEST)
Jakie są prerekwizyty celów? Dlaczego?

6.9 Ćwiczenie: Podsumowanie i przydatne opcje Make
Podsumowując, można stwierdzić, iż udało się stworzyć plik Makefile dla projektu programistycznego pozwalający na kompilację i instalację oprogramowania:

$ make
$ make install
a także na tworzenie archiwum - przydatne, gdyby się np. zmodyfikowało kod i chciało go komuś przekazać.
$ make dist
make można też uruchomić w trybie silent w którym nie wyświetla poleceń które wykonuje, a jedynie komunikaty wypisywane przez echo. W tym celu należy podac opcję -s

Przydatna jest też opcja -k która próbuje zrealizować jak najwięcej celów nawet w przpadku napotkania błędów, a także opcja -j N pozwalająca na równoległe uruchomienie N instancji make i zrównoleglenie procesu kompilacji, co jest przydatne w przypadku maszyn wieloprocesorowych.

Zadając opcję -f plik można podać plik o innej niż Makefile nazwie.

6.10 Zakónczenie
Przygotowane pliki makefile proszą załadować do Państwa archiwum w github, a link do klonowania przesłać do prowadzącego zajęcia.

6.11 BIBLIOGRAFIA
GNU Make WWW, http://www.gnu.org/software/make
GNU Make Manual, http://www.gnu.org/software/make/manual
Jennifer Vesperman, Introduction to Make, http://www.linuxdevcenter.com/pub/a/linux/2002/01/31/make_intro.html
Ben Yoshino, Make - a tutorial, http://www.eng.hawaii.edu/Tutor/Make
Makefile Conventions, rozdział w: GNU Coding Standards, http://www.gnu.org/prep/standards/html_node/Makefile-Conventions.html#Makefile-Conventions
Dla zaawansownaych plecane są źródła dotyczące narzędzi wspomagających pracę z Make:

Gnu AutoMake WWW, http://www.gnu.org/software/automake
Felipe Bergo, autotut: Using GNU auto{conf,make,header}, http://seul.org/docs/autotut
Gary V. Vaughan, Ben Elliston, Tom Tromey, Ian Lance Taylor, GNU Autoconf, Automake, and Libtool, http://sources.redhat.com/autobook
