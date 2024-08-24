#ifndef CFRAME_H
#define CFRAME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class cframe;
}
QT_END_NAMESPACE

class cframe : public QMainWindow
{
    Q_OBJECT

public:
    cframe(QWidget *parent = nullptr);
    ~cframe();

private slots:
    void on_pushButton_5_clicked();

    void on_bton_generarMatriz_clicked();

    void on_bton_GirarMatriz_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_bton_GenerarMatrizM_clicked();

    void on_bton_GenerarMatrizN_clicked();

    void on_bton_SumarMatriz_clicked();

    void on_bton_RestarMatriz_clicked();

    void on_bton_MultiplicarMatriz_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_bton_GenerarMatrizM_2_clicked();

    void on_bton_buscarNumero_clicked();

private:

    Ui::cframe *ui;
    //
    //int **matriz;
    //int n;
    std::vector<std::vector<int>> matriz;
    int n;
};
#endif // CFRAME_H
