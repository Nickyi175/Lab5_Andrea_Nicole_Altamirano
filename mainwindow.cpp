#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <utility>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btn_operaciones->setVisible(false);
    ui->lbl_operaciones->setVisible(false);
    ui->comboBox_operacion->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_matriz1_clicked()
{
    fila1 = ui->spinBox_Fila1->value();
    columna1 = ui->spinBox_Colm1->value();
    M = new int*[fila1];

    for (int i = 0; i < fila1; ++i) {
        M[i] = new int[columna1];
    }

    for (int i = 0; i < fila1; ++i) {
        for (int j = 0; j < columna1; ++j) {
            M[i][j] = QRandomGenerator::global()->bounded(100);
        }
    }

    ui->tW_1->setRowCount(fila1);
    ui->tW_1->setColumnCount(columna1);
    for (int i = 0; i < fila1; ++i) {
        for (int j = 0; j < columna1; ++j) {
            listo1 = true;
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(M[i][j]));
            ui->tW_1->setItem(i, j, item);
        }
    }

    if(listo1 == true && listo2 == true){
        ui->btn_operaciones->setVisible(true);
        ui->lbl_operaciones->setVisible(true);
        ui->comboBox_operacion->setVisible(true);
    }
}

void MainWindow::on_btn_matriz2_clicked()
{
    fila2 = ui->spinBox_fila2->value();
    columna2 = ui->spinBox_Colm2->value();

    M2 = new int*[fila2];

    for (int i = 0; i < fila2; ++i) {
        M2[i] = new int[columna2];
    }
    for (int i = 0; i < fila2; ++i) {
        for (int j = 0; j < columna2; ++j) {
            M2[i][j] = QRandomGenerator::global()->bounded(100);
        }
    }

    ui->tW_2->setRowCount(fila2);
    ui->tW_2->setColumnCount(columna2);
    for (int i = 0; i < fila2; ++i) {
        for (int j = 0; j < columna2; ++j) {
            listo2 = true;
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(M2[i][j]));
            ui->tW_2->setItem(i, j, item);
        }
    }

    //dentro de un if
    if(listo1 == true && listo2 == true){
        ui->btn_operaciones->setVisible(true);
        ui->lbl_operaciones->setVisible(true);
        ui->comboBox_operacion->setVisible(true);
    }

}

int MainWindow::getFilas(int matrixNumber)
{
    if (matrixNumber == 1) {
        return fila1;
    } else if (matrixNumber == 2) {
        return fila2;
    }
    return 0;
}

int MainWindow::getColumnas(int matrixNumber)
{
    if (matrixNumber == 1) {
        return columna1;
    } else if (matrixNumber == 2) {
        return columna2;
    }
    return 0;
}

void MainWindow::on_btn_operaciones_clicked()
{
    int filas1 = getFilas(1);
    int columnas1 = getColumnas(1);
    int filas2 = getFilas(2);
    int columnas2 = getColumnas(2);
    QString operacion = ui->comboBox_operacion->currentText();
    int **resultado = nullptr;
    int filasResult = 0, columnasResult = 0;

    if ((operacion == "Sumar" || operacion == "Restar") && (filas1 != filas2 || columnas1 != columnas2)) {
        QMessageBox::warning(this, "ERROR", "Error\nLas matrices deben tener las mismas dimensiones para sumar o restar");
        return;
    }

    if (operacion == "Multiplicar" && columnas1 != filas2) {
        QMessageBox::warning(this, "ERROR", "Error\nEl número de columnas de la primera matriz debe ser igual "
                                            "que el número de filas de la segunda matriz para poder multiplicarlas");
        return;
    }

    if (operacion == "Sumar") {
        filasResult = filas1;
        columnasResult = columnas1;
        resultado = sumar(M, M2, filas1, columnas1);
    } else if (operacion == "Restar") {
        filasResult = filas1;
        columnasResult = columnas1;
        resultado = restar(M, M2, filas1, columnas1);
    } else if (operacion == "Multiplicar") {
        filasResult = filas1;
        columnasResult = columnas2;
        resultado = multiplicar(M, M2, filas1, columnas1, filas2, columnas2);
    }

    ui->tW_12->setRowCount(filasResult);
    ui->tW_12->setColumnCount(columnasResult);

    for (int f = 0; f < filasResult; f++) {
        for (int c = 0; c < columnasResult; c++) {
            listo1 = false;
            listo2 = false;
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(resultado[f][c]));
            ui->tW_12->setItem(f, c, item);
        }
    }

    for (int i = 0; i < filasResult; i++) {
        delete[] resultado[i];
    }
    delete[] resultado;
}



int** MainWindow::sumar(int **M, int **M2, int filas, int columnas)
{
    qDebug()<<"entro a sumas";
    int **resultado = new int*[filas];
    for (int i = 0; i < filas; i++) {
        resultado[i] = new int[columnas];
        for (int j = 0; j < columnas; j++) {
            resultado[i][j] = M[i][j] + M2[i][j];
        }
    }
    return resultado;
}

int** MainWindow::restar(int **M, int **M2, int filas, int columnas)
{
    qDebug()<<"entro a restas";
    int **resultado = new int*[filas];
    for (int i = 0; i < filas; i++) {
        resultado[i] = new int[columnas];
        for (int j = 0; j < columnas; j++) {
            resultado[i][j] = M[i][j] - M2[i][j];
        }
    }
    return resultado;
}

int** MainWindow::multiplicar(int **M, int **M2, int fila1, int columna1, int fila2, int columna2)
{
    qDebug()<<"entro a mulplicacion";
    int **resultado = new int*[fila1];
    for (int i = 0; i < fila1; i++) {
        resultado[i] = new int[columna2];
        for (int j = 0; j < columna2; j++) {
            resultado[i][j] = 0;
            for (int k = 0; k < columna1; k++) {
                resultado[i][j] += M[i][k] * M2[k][j];
            }
        }
    }
    return resultado;
}


void MainWindow::on_btn_crearMatrizB_clicked()
{
    int fila;
    int columna;
    fila = ui->spinBox_FilaBuscar->text().toInt();
    columna = ui->spinBox_ColmBuscar->text().toInt();

    M = new int *[fila];
    for (int f = 0; f < fila; f++) {
        M[f] = new int[columna];
    }

    for (int f = 0; f < fila; f++) {
        for (int c = 0; c < columna; c++) {
            M[f][c] = QRandomGenerator::global()->bounded(100);
        }
    }

    ui->tW_MatrizBuscar->setRowCount(fila);
    ui->tW_MatrizBuscar->setColumnCount(columna);

    for (int f = 0; f < fila; f++) {
        for (int c = 0; c < columna; c++) {
            ui->lE_ColumnNum->clear();
            ui->lE_FilaNum->clear();
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(M[f][c]));
            ui->tW_MatrizBuscar->setItem(f, c, item);
        }
    }
}


void MainWindow::on_btn_buscarNum_clicked()
{
    int number = ui->spinBox_Num->text().toInt();
    int fila = ui->tW_MatrizBuscar->rowCount();
    int columna = ui->tW_MatrizBuscar->columnCount();

    for( int f = 0; f<fila; f++){
        for(int c = 0; c < columna; c++){
            QTableWidgetItem *cont = ui->tW_MatrizBuscar->item(f,c);
            if(cont->text().toInt() == number){
                ui->lE_FilaNum->setText(QString::number(f+1));
                ui->lE_ColumnNum->setText(QString::number(c+1));
                return;
            }
        }
    }

    QMessageBox::warning(this,"Error","Número no encontrado");
}


void MainWindow::on_btn_crearMatrizT_clicked()
{
    int fila = ui->spinBox_FilaT->text().toInt();
    int columna = ui->spinBox_ColmT->text().toInt();

    M = new int *[fila];
    for (int f = 0; f < fila; f++) {
        M[f] = new int[columna];
    }

    for (int f = 0; f < fila; f++) {
        for (int c = 0; c < columna; c++) {
            M[f][c] = QRandomGenerator::global()->bounded(100);
        }
    }

    ui->tW_MatrizOriginal->setRowCount(fila);
    ui->tW_MatrizOriginal->setColumnCount(columna);

    for (int f = 0; f < fila; f++) {
        for (int c = 0; c < columna; c++) {
            ui->lE_ColumnNum->clear();
            ui->lE_FilaNum->clear();
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(M[f][c]));
            ui->tW_MatrizOriginal->setItem(f, c, item);
        }
    }

    transpuesta = new int *[columna];
    for (int i = 0; i < columna; i++) {
        transpuesta[i] = new int[fila];
    }

    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            transpuesta[j][i] = M[i][j];
        }
    }

    ui->tW_MatrizTranspuesta->setRowCount(columna);
    ui->tW_MatrizTranspuesta->setColumnCount(fila);

    for (int i = 0; i < columna; i++) {
        for (int j = 0; j < fila; j++) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(transpuesta[i][j]));
            ui->tW_MatrizTranspuesta->setItem(i, j, item);
        }
    }
}


void MainWindow::on_btn_rotacion_clicked()
{
    int n = ui->spinBox_FCR->value();
    M = new int*[n];
    for (int i = 0; i < n; i++) {
        M[i] = new int[n];
    }

    ui->tW_MatrizOriginal_1->setRowCount(n);
    ui->tW_MatrizOriginal_1->setColumnCount(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            creada = true;
            M[i][j] = QRandomGenerator::global()->bounded(100);
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(M[i][j]));
            ui->tW_MatrizOriginal_1->setItem(i, j, item);
        }
    }
    rotacion = new int*[n];
    for (int i = 0; i < n; i++) {
        rotacion[i] = new int[n];
    }
}


void MainWindow::on_btn_rotacion_2_clicked()
{
    if(creada == true){
        int n = ui->spinBox_FCR->value();

        int** tempMatrix = new int*[n];
        for (int i = 0; i < n; i++) {
            tempMatrix[i] = new int[n];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                tempMatrix[j][n - 1 - i] = M[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                M[i][j] = tempMatrix[i][j];
            }
        }

        ui->tW_MatrizRotacion->setRowCount(n);
        ui->tW_MatrizRotacion->setColumnCount(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(M[i][j]));
                ui->tW_MatrizRotacion->setItem(i, j, item);
            }
        }

        for (int i = 0; i < n; i++) {
            delete[] tempMatrix[i];
        }
        delete[] tempMatrix;

    }else{
        QMessageBox::warning(this,"Error","Primero debe crear la matriz");
    }

}

