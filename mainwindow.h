#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <vector>
#include "soundplayer.h"
#include "ElementaryCA.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonPlay_clicked();

    void on_pushButtonRender_clicked();

    void on_pushButtonSave_clicked();

    void on_spinBoxHarmonics_valueChanged(int arg1);

    void on_spinBoxRule_valueChanged(int arg1);

    void on_pushButtonRandom_clicked();

    void on_spinBoxSmooth_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    // 機能
    SoundPlayer soundPlayer;
    ElementaryCA ecaCar, ecaMod;

    // 音データ
    QVector<float> waveSound;

    // 音生成
    float harmoTone(float phase, ElementaryCA &eca);

    //
    void setupWaveforms();
    void saveSound();
    void playSound();
    void renderSound();
    int getNumberOfSamples();
    void ecaResize(int size);
};

#endif // MAINWINDOW_H
