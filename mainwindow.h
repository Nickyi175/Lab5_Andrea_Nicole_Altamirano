#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_matriz1_clicked();

    void on_btn_matriz2_clicked();

    void on_btn_operaciones_clicked();

    void on_btn_crearMatrizB_clicked();

    void on_btn_buscarNum_clicked();

    void on_btn_crearMatrizT_clicked();

    void on_btn_rotacion_clicked();

    void on_btn_rotacion_2_clicked();

private:
    Ui::MainWindow *ui;
    int **M;
    int **M2;
    int **matriz;
    int fc,fila,columna,newNum1,newNum2;
    int fila1, columna1;
    int fila2, columna2;
    int getFilas(int matrixNumber);
    int getColumnas(int matrixNumber);
    int **sumar(int **matriz1, int **matriz2, int filas, int columnas);
    int **restar(int **matriz1, int **matriz2, int filas, int columnas);
    int **multiplicar(int **matriz1, int **matriz2, int fila1, int columna1, int fila2, int columna2);
    bool listo1 = false;
    bool listo2 = false;
    int **transpuesta;
    int **rotacion;
    bool creada = false;

};
#endif // MAINWINDOW_H
