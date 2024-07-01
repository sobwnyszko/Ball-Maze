/*!
 * \file
 * \brief Implementacja klasy Gra
 */
#ifndef GRA_H
#define GRA_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QTranslator>

namespace Ui {
class Gra;
}

/**
 * \class Gra
 * \brief Klasa reprezentująca grę labiryntową
 *
 * Klasa Gra dziedziczy po QMainWindow i zarządza logiką gry,
 * w tym obsługą zdarzeń, rysowaniem, zmianą języka, poziomami trudności
 * oraz interakcją z użytkownikiem przez przyciski i interfejs graficzny.
 */
class Gra : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor
     * \param[in] parent - wskaźnik na obiekt rodzica
     */
    explicit Gra(QWidget *parent = nullptr);

    /**
     * @brief Destruktor
     */
    ~Gra();

    /**
     * @brief Funkcja do wykrycia zmian
     * @param[in] *event - wskaźnik na zdarzenie zmiany języka
     */
    virtual void changeEvent(QEvent *event) override;

    /**
     * @brief Wypełnienie bitmapy
     */
    void zapolni();

    /**
     * @brief Funkcja do zapisywania odczytanych danuch z płytki
     * @param[in] x - dane X
     * @param[in] y - dane Y
     */
    void set_XY(int x, int y){
        plytkaX = x;
        plytkaY = y;
    }

    /**
     * @brief Funkcja do ustawienia poziomu trudności
     * @param[in] zlo - poziom trudności: 0-uproszczony, 1-standardowy, 2-zaawansowany
     */
    void set_Zlozonosc(int zlo);

    /**
     * @brief Ustawienie pozycji startowej, statusu oraz zerowej prędkości
     */
    void StartPosition(){
        currentX = 60;
        currentY = 170;
        timer->stop();
        Status = 0;
        Vx = 0;
        Vy = 0;
    };

    /**
     * @brief Funkcja do zmiany języka
     * @param[in] language - język na który tłumaczymy
     */
    void changeLanguage(const QString& language);

protected:
    /**
     * @brief Funkcja do rysowania
     * @param[in] *event - wskaźnik na zdarzenie
     */
    void paintEvent(QPaintEvent *event);

private slots:
    /**
     * @brief Obsługa przycisku "Wyjście", zamknięcie okienka gry
     */
    void on_pushButton_clicked();

    /**
     * @brief Obsługa przycisku "Start", uruchamienie gry
     */
    void on_pushButton_3_clicked();

    /**
     * @brief Obsługa przycisku "Stop", zatrzymanie gry
     */
    void on_pushButton_2_clicked();

    /**
     * @brief Funkcja do wyświetlania "MessageBox", o wygraniu
     */
    void victory();

    /**
     * @brief Funkcja do wyświetlania "MessageBox", o przegraniu
     */
    void lose();

    /**
     * @brief Funkcja do sprawdzenia Statusu gry
     */
    void sprawdzStatus();

    /**
     * @brief Funkcja do sprawdzenia kolizji
     * @param[in] strona - z której strony sprawdzić
     *
     * @retval true - możemy podążać w tym kierunku
     * @retval false - niemożemy podążać w tym kierunku
     */
    bool collision(QString strona);

    /**
     * @brief Funkcja do uruchmiania fizyki gry w zależności do poziomu trudnosci
     * oraz sprawdzenie wyjścia poza granice labiryntu i zmiana statusu
     */
    void graj();

    /**
     * @brief Fizyka kulki w uproszczonej wersji gry
     *
     * Jeśli płytka jest nachylona, zmieniamy położenie kulki o zadaną wartość
     */
    void versjaUproszczona();

    /**
     * @brief Fizyka kulki w standardowej wersji gry
     *
     * Kulka ma prędkość po osiach X oraz Y
     */
    void versjaStandartowa();

    /**
     * @brief Fizyka kulki w zaawansowanej wersji gry
     *
     * Kulka ma prędkość po osiach X oraz Y, labirynt jest z dodatkowymi przeszkodami
     */
    void versjaZaawansowana();

    /**
     * @brief Odczytanie wyboru pozioma trudności w comboBox
     * @param[in] index - indeks wybranego poziomu trudności
     */
    void on_comboBox_activated(int index);

private:
    //! Wskaźnik na interfejs użytkownika.
    Ui::Gra *ui;

    //! Wskaźnik na timer
    QTimer *timer;

    //! Wskaźnik na tłumaczenie
    QTranslator *translator;

    //! BitMapa
    int bitMap[641][801];

    //! Ostatnie odczytane dane X
    int plytkaX;

    //! Ostatnie odczytane dane Y
    int plytkaY;

    //! Aktualne polozenie po X
    int currentX;

    //! Aktualne polozenie po Y
    int currentY;

    //! Status gry: 0-początek, 1-victory, 2-lose, 3-pause
    int Status;

    //! Prędkość wzdłuż osi X
    double Vx;

    //! Prędkość wzdłuż osi Y
    int Vy;

    //! Poziom trudności gry: 0-uproszczona, 1-standardowa, 2-zaawansowana
    int Zlozonosc;
};

#endif // GRA_H
