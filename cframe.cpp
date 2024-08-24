#include "cframe.h"
#include "ui_cframe.h"
#include <iostream>
#include <vector>
#include <QMessageBox>
#include <QTableWidget>

using namespace std;

cframe::cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cframe)
    , n(0)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &cframe::on_bton_GenerarMatrizM_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &cframe::on_bton_GenerarMatrizN_clicked);
    connect(ui->bton_SumarMatriz, &QPushButton::clicked, this, &cframe::on_bton_SumarMatriz_clicked);
    connect(ui->bton_RestarMatriz, &QPushButton::clicked, this, &cframe::on_bton_RestarMatriz_clicked);
    connect(ui->bton_MultiplicarMatriz, &QPushButton::clicked, this, &cframe::on_bton_MultiplicarMatriz_clicked);

}

cframe::~cframe()
{
    delete ui;
}

// Slot del menu principal
void cframe::on_pushButton_5_clicked()
{
    exit(0);
}

void cframe::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void cframe::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void cframe::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void cframe::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}



// Ejercicio 4
void cframe::on_bton_generarMatriz_clicked()
{
    n = ui->sb_tamanoMatriz->value();


    matriz.resize(n, vector<int>(n));

    int contador = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = contador++;
        }
    }


    QString textoMatriz;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            textoMatriz += QString::number(matriz[i][j]) + "\t";
        }
        textoMatriz += "\n";
    }

    ui->te_GeneraMatriz->setPlainText(textoMatriz);
}

void cframe::on_bton_GirarMatriz_clicked()
{
    if (matriz.empty()) {
        ui->te_ResultadoGirarMatriz->setPlainText("Primero genera una matriz.");
        return;
    }

    vector<vector<int>> rotada(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rotada[j][n - i - 1] = matriz[i][j];
        }
    }
    matriz = rotada;
    QString textoMatrizRotada;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            textoMatrizRotada += QString::number(matriz[i][j]) + "\t";
        }
        textoMatrizRotada += "\n";
    }

    ui->te_ResultadoGirarMatriz->setPlainText(textoMatrizRotada);
}


//Ejercicio 1

void cframe::on_bton_GenerarMatrizM_clicked()
{
    int filas = ui->sb_FilaM->value();
    int columnas = ui->sb_ColumnaM->value();
    ui->tw_MatrizM->setRowCount(filas);
    ui->tw_MatrizM->setColumnCount(columnas);
}


void cframe::on_bton_GenerarMatrizN_clicked()
{
    int filas = ui->sb_FilaN->value();
    int columnas = ui->sb_ColumnaN->value();
    ui->tw_MatrizN->setRowCount(filas);
    ui->tw_MatrizN->setColumnCount(columnas);
}



void cframe::on_bton_SumarMatriz_clicked()
{
    if (ui->tw_MatrizM->rowCount() != ui->tw_MatrizN->rowCount() ||
        ui->tw_MatrizM->columnCount() != ui->tw_MatrizN->columnCount()) {
        QMessageBox::warning(this, "Error", "Las matrices deben tener el mismo tamaño para sumar.");
        return;
    }

    int filas = ui->tw_MatrizM->rowCount();
    int columnas = ui->tw_MatrizM->columnCount();

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            bool okM, okN;
            double valorM = ui->tw_MatrizM->item(i, j)->text().toDouble(&okM);
            double valorN = ui->tw_MatrizN->item(i, j)->text().toDouble(&okN);

            if (okM && okN) {
                double resultado = valorM + valorN;
                ui->tw_ResultadoMatriz->setItem(i, j, new QTableWidgetItem(QString::number(resultado)));
            } else {
                QMessageBox::warning(this, "Error", "Hay valores no válidos en las matrices.");
                return;
            }
        }
    }
}


void cframe::on_bton_RestarMatriz_clicked()
{
    if (ui->tw_MatrizM->rowCount() != ui->tw_MatrizN->rowCount() ||
        ui->tw_MatrizM->columnCount() != ui->tw_MatrizN->columnCount()) {
        QMessageBox::warning(this, "Error", "Las matrices deben tener el mismo tamaño para restar.");
        return;
    }

    int filas = ui->tw_MatrizM->rowCount();
    int columnas = ui->tw_MatrizM->columnCount();

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            bool okM, okN;
            double valorM = ui->tw_MatrizM->item(i, j)->text().toDouble(&okM);
            double valorN = ui->tw_MatrizN->item(i, j)->text().toDouble(&okN);

            if (okM && okN) {
                double resultado = valorM - valorN;
                ui->tw_ResultadoMatriz->setItem(i, j, new QTableWidgetItem(QString::number(resultado)));
            } else {
                QMessageBox::warning(this, "Error", "Hay valores no válidos en las matrices.");
                return;
            }
        }
    }
}


void cframe::on_bton_MultiplicarMatriz_clicked()
{
    if (ui->tw_MatrizM->columnCount() != ui->tw_MatrizN->rowCount()) {
        QMessageBox::warning(this, "Error", "El número de columnas de la primera matriz debe ser igual al número de filas de la segunda matriz.");
        return;
    }

    int filasM = ui->tw_MatrizM->rowCount();
    int columnasM = ui->tw_MatrizM->columnCount();
    int columnasN = ui->tw_MatrizN->columnCount();

    ui->tw_ResultadoMatriz->setRowCount(filasM);
    ui->tw_ResultadoMatriz->setColumnCount(columnasN);

    for (int i = 0; i < filasM; ++i) {
        for (int j = 0; j < columnasN; ++j) {
            double resultado = 0;
            for (int k = 0; k < columnasM; ++k) {
                bool okM, okN;
                double valorM = ui->tw_MatrizM->item(i, k)->text().toDouble(&okM);
                double valorN = ui->tw_MatrizN->item(k, j)->text().toDouble(&okN);

                if (okM && okN) {
                    resultado += valorM * valorN;
                } else {
                    QMessageBox::warning(this, "Error", "Hay valores no válidos en las matrices.");
                    return;
                }
            }
            ui->tw_ResultadoMatriz->setItem(i, j, new QTableWidgetItem(QString::number(resultado)));
        }
    }
}

// Ejercicio 2
void cframe::on_pushButton_7_clicked()
{
    int filas1 = ui->tablaT->rowCount();
    int columnas1 = ui->tablaT->columnCount();


    ui->transpuesta->setRowCount(columnas1);
    ui->transpuesta->setColumnCount(filas1);


    for (int i = 0; i < filas1; ++i) {
        for (int j = 0; j < columnas1; ++j) {
            int valor = ui->tablaT->item(i, j)->text().toInt();
            ui->transpuesta->setItem(j, i, new QTableWidgetItem(QString::number(valor)));
        }
    }
}


void cframe::on_pushButton_6_clicked()
{
    ui->tablaT->setRowCount(ui->sbFilaT->value());
    ui->tablaT->setColumnCount(ui->sbColumnaT->value());

    for (int i = 0; i < ui->sbFilaT->value(); ++i) {
        for (int j = 0; j < ui->sbColumnaT->value(); ++j) {
            ui->tablaT->setItem(i, j, new QTableWidgetItem(QString::number(0)));
        }
    }
}

// ejercico 2


void cframe::on_bton_GenerarMatrizM_2_clicked()
{
    int filas = ui->sb_Columna->value();
    int columnas = ui->sb_Fila->value();

    ui->tw_matriz->setRowCount(filas);
    ui->tw_matriz->setColumnCount(columnas);


    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            ui->tw_matriz->setItem(i, j, new QTableWidgetItem(QString::number(0)));
        }
    }
}


void cframe::on_bton_buscarNumero_clicked()
{ int numeroBuscado = ui->sb_buscarNumero->value();

    int filas = ui->tw_matriz->rowCount();
    int columnas = ui->tw_matriz->columnCount();

    bool encontrado = false;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            bool okM;
            int valor = ui->tw_matriz->item(i, j)->text().toInt(&okM);
            if (okM && valor == numeroBuscado) {
                encontrado = true;
                QMessageBox::information(this, "Resultado", QString("Número %1 encontrado en la posición (%2, %3)").arg(numeroBuscado).arg(i).arg(j));
                return;
            }
        }
    }

    if (!encontrado) {
        QMessageBox::information(this, "Resultado", QString("Número %1 no encontrado.").arg(numeroBuscado));
    }
}
