/*!
 * \file
 * \brief Implementacja klasy MainWindow
 *
 * Początkowe i główne okno
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QTranslator>

#include "../inc/wykresy.h"
#include "../inc/gra.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * \class MainWindow
 * \brief Klasa reprezentująca główne okno aplikacji.
 *
 * Klasa MainWindow dziedziczy po QMainWindow i zarządza interfejsem użytkownika oraz logiką aplikacji, w tym obsługą zdarzeń,
 * połączeń szeregowych, wykresów oraz gry labiryntowej.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor
     * \param[in] parent - wskaźnik na obiekt rodzica
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destruktor
     */
    ~MainWindow();

    /**
     * @brief Funkcja do wykrycia zmian
     * @param[in] *event - wskaźnik na zdarzenie zmiany języka
     */
    virtual void changeEvent(QEvent *event) override;

private slots:
    /**
     * \brief Funkcja do odczytu danych z portu szeregowego
     */
    void readFromPort();

    /**
     * @brief Obsługa przycisku "Szukaj" do znalezienia podłączonych urządzeń
     */
    void on_pushButton_4_clicked();

    /**
     * @brief Obsługa przycisku "Połącz" do podłączenia wybranego urządzenia
     */
    void on_pushButton_5_clicked();

    /**
     * @brief Obsługa przycisku "Rozlącz" do zakończenia połączenia
     */
    void on_pushButton_6_clicked();

    /**
     * @brief Pokaż wykres z danymi X
     */
    void on_actionWykres_X_triggered();

    /**
     * @brief Pokaż wykres z danymi Y
     */
    void on_actionWykres_Y_triggered();

    /**
     * @brief Pokaż wykres z danymi Z
     */
    void on_actionWykres_Z_triggered();

    /**
     * @brief Pokaż wykres z danymi X, Y, Z
     */
    void on_actionWykres_XYZ_triggered();

    /**
     * @brief Obsługa przycisku "Wyjście" do zamknięcie aplikacji
     */
    void on_pushButton_3_clicked();

    /**
     * @brief Obsługa przycisku "Labirynt" do uruchomienie okienka gry
     */
    void on_pushButton_clicked();

    /**
     * @brief Obsługa przycisku "Restartuj Labirynt"
     *
     * Jeżeli okienko gry było otwarte, zamkni i uruchom ponowne
     */
    void on_pushButton_2_clicked();

    /**
     * @brief Obsługa przycisku "Wykresy" do uruchomienie okienka wykresów
     */
    void on_pushButton_7_clicked();

    /**
     * @brief Uruchomienie okienka gry
     */
    void on_actionLabirynt_triggered();

    /**
     * @brief Zmiana poziomu trudności na uproszczony
     */
    void on_actionUproszczona_triggered();

    /**
     * @brief Zmiana poziomu trudności na standardowy
     */
    void on_actionStandardowa_triggered();

    /**
     * @brief Zmiana poziomu trudności na  zaawansowany
     */
    void on_actionZaawansowana_triggered();

    /**
     * @brief Zmiana języka na polski
     */
    void on_actionPolski_triggered();

    /**
     * @brief Zmiana języka na angielski
     */
    void on_actionEnglish_triggered();

    /**
     * @brief Zmiana języka na rosyjski
     */
    void on_action_triggered();

private:
    //! Wskaźnik na interfejs użytkownika.
    Ui::MainWindow *ui;

    //! Wskaźnik na podłączone urządzenie
    QSerialPort *device;

    //! Wskaźnik na tłumaczenie
    QTranslator *translator;

    //! Wskaźnik na obiekt gry
    Gra *LabKulk;

    //! Wskaźnik na obiekt wykresów
    Wykresy *wyk;

    //! Tablica danych X
    int daneX[50];

    //! Tablica danych Y
    int daneY[50];

    //! Tablica danych Z
    int daneZ[50];

    /**
     * @brief Funkcja do wyświetlania danych w logach
     * @param[in] message - wiadomość do wyświetlenia
     */
    void addToLogs(const QString& message);

    /**
     * @brief Funkcja do zmiany języka
     * @param[in] language - język na który tłumaczymy
     */
    void changeLanguage(const QString& language);
};
#endif // MAINWINDOW_H
