/**
 * \brief klasa ulamek, bo tak
 *
 * klasa obiektow umozliwiajaca operacje na ulamkach zwyklych.
 *
 * \version wersja alfa
 */
class ulamek
{
private:
  long int licznik; /**< Licznik ulamka */
  long int mianownik; /**< Mianownik ulamka */
  long int nwd(long int, long int);
public:
  ulamek(long int = 1, long int = 1);
  void pisz();
  ulamek mnozenie(ulamek &);
};

/**
 * \brief Oblicza najwiekszy wspolny dzielnik dwoch liczb.
 *
 * Pobiera dwie wartosci typu long int i zwraca wartosc typu long int.
 *
 * \param[in] a pierwsza liczba.
 * \param[in] b druga liczba.
 * \return najwiekszy wspolny dzielnik pierwszej i drugiej liczby.
 * \attention jesli druga liczba jest rowna zeru, zwraca pierwsza liczbe.\n
 *            jesli pierwsza liczba jest rowna zeru, zwraca druga liczbe.\n
 *            jesli obie liczby sa rowne zeru, zwraca 1.
 */
long int ulamek::nwd(long int a, long int b)
{
  int temp;
  if (a < 0)
    a = -a;
  if (b < 0)
    b = -b;
  if (a == 0)
    {
      if (b == 0)
	return 1;
      else
	return b;
    }
  else
    {
      if (b == 0)
	return a;
    }
  if (a < b)
    {
      temp = a;
      a = b;
      b = temp;
    }
  while (a % b != 0)
    {
      temp = b;
      b = a % b;
      a = temp;
    }
  return b;
}

/**
 * \brief Konstruktor mieszany.
 *
 * Tworzy obiekt klasy ulamek, automatycznie skracajac ulamek do
 * najprostszej postaci za pomoca funkcji nwd().\n
 * Jesli konstruktor zostanie wywolany bez argumentow,
 * zostanie utworzony obiekt klasy ulamek o wartosciach:
 * \c licznik \c = \c 1,
 * \c mianownik \c = \c 1
 * 
 * \param[in] a licznik ulamka (domyslnie przyjmuje wartosc 1).
 * \param[in] b mianownik ulamka (domyslnie przyjmuje wartosc 1).
 * \attention jesli jako argument zostanie podany mianownik rowny zeru,
 *            wypisze komunikat na ekranie i przyjmnie mianownik rowny 1.
 */
ulamek::ulamek(long int a, long int b)
{
  long int temp;
  if (b == 0)
    {     cout << endl << "[BLAD DZIELENIA PRZEZ ZERO]" << endl;
      b = 1;
    }
  temp = nwd(a, b);
  licznik = a / temp;
  mianownik = b / temp;
}

/**
 * \brief Wypisuje na ekran zawartosc obiektu klasy ulamek.
 *
 * Wywolanie metody w pierwszej kolejnosci powoduje przejscie do nowej linii.
 * W nowej linii wypisuje na ekran licznik i mianownik oddzielony ukosnikiem (slash).
 */
void ulamek::pisz()
{
  cout << endl << licznik << "/" << mianownik;
}

/**
 * \brief Mnozy przez siebie dwa obiekty klasy ulamek.
 *
 * Pobiera obiekt klasy ulamek, mnozy go przez obiekt, na rzecz ktorego metoda zostala wywolana
 * i zwraca obiekt klasy ulamek do miejsca wywolania.
 *
 * \param[in] a obiekt klasy ulamek
 * \return Zwraca obiekt klasy ulamek, bedacy wynikiem mnozenia argumentu wejsciowego
 *         przez obiekt, na rzecz ktorego metoda zostala wywolana.
 */
ulamek ulamek::mnozenie(ulamek &a)
{
  long int licznik_new, mianownik_new;
  licznik_new = licznik * a.licznik;
  mianownik_new = mianownik * a.mianownik;
  ulamek temp(licznik_new, mianownik_new);
  return temp;
}
