/*!
 * \file
 * \brief Implementacja klasy Wykresy
 */
#ifndef WYKRESY_H
#define WYKRESY_H

#include <QMainWindow>
#include <QPainter>
#include <QtCharts>
#include <QResizeEvent>
#include <QTranslator>

namespace Ui {
class Wykresy;
}

/**
 * \class Wykresy
 * \brief Klasa reprezentująca wykresy w aplikacji
 *
 * Klasa Wykresy dziedziczy po QMainWindow i zarządza tworzeniem,
 * wyświetlaniem oraz aktualizacją wykresów. Obsługuje również
 * zmiany języka, rozmiaru okna oraz interakcje użytkownika za pomocą przycisków
 * i elementów interfejsu graficznego.
 */
class Wykresy : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor
     * \param[in] parent - wskaźnik na obiekt rodzica
     */
    explicit Wykresy(QWidget *parent = nullptr);

    /**
     * @brief Destruktor
     */
    ~Wykresy();

    /**
     * @brief Funkcja do wykrycia zmian
     * @param[in] *event - wskaźnik na zdarzenie zmiany języka
     */
    virtual void changeEvent(QEvent *event) override;

    /**
     * @brief Funkcja ustawiająca dane dla wykresu
     * @param[in] CoZaWykres - typ wykresu (0 - X, 1 - Y, 2 - Z, 3 - X, Y, Z)
     * @param[in] *dane - tablica wartościej
     */
    void set_dane(int CoZaWykres, int *dane);

    /**
     * @brief Funkcja ustawiająca typ wykresu
     * @param[in] CoZaWykres - typ wykresu (0 - X, 1 - Y, 2 - Z, 3 - X, Y, Z)
     */
    void set_XYZWykres(int CoZaWykres);

    /**
     * @brief Funkcja do zmiany języka
     * @param[in] language - język na który tłumaczymy
     */
    void changeLanguage(const QString& language);

protected:
    /**
     * @brief Funkcja obsługująca zmianę rozmiaru okna
     * @param[in] *event - wskaźnik na zdarzenie zmiany rozmiaru okienka
     */
    void resizeEvent(QResizeEvent *event);

private slots:
    /**
     * @brief Obsługa przycisku "Wyjście"
     *
     * Zamknięcie okienka wykresów
     */
    void on_pushButton_clicked();

    /**
     * @brief Funkcja rysująca wykresy w zależności od typu wykresu (XYZWykres)
     */
    void rysuj();

    /**
     * @brief Odczytanie wyboru precyzji wykresu w comboBox
     * @param[in] index - indeks wybranej opcji
     */
    void on_comboBox_2_activated(int index);

    /**
     * @brief Odczytanie wyboru wykresa do wyświetlenia w comboBox
     * @param[in] index - indeks wybranego wykresu
     */
    void on_comboBox_currentIndexChanged(int index);

private:
    //! Wskaźnik na interfejs użytkownika.
    Ui::Wykresy *ui;

    //! Wskaźnik na tłumaczenie
    QTranslator *translator;

    //! Wskaźnik na szereg danych X
    QLineSeries *lineSeriesX;

    //! Wskaźnik na szereg danych Y
    QLineSeries *lineSeriesY;

    //! Wskaźnik na szereg danych Z
    QLineSeries *lineSeriesZ;

    //! Wskaźnik na wykres
    QChart *chart;

    //! Wskaźnik na widok wykresu
    QChartView *chartView;

    //! Zmiena do wybora wykresu: 0-X, 1-Y, 2-Z, 3-XYZ
    int XYZWykres;

    //! Tablica danych X
    int daneX[50];

    //! Tablica danych Y
    int daneY[50];

    //! Tablica danych Z
    int daneZ[50];
};

#endif // WYKRESY_H
