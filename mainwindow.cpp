#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <algorithm>
#include <cmath>
#include <random>
#include <QElapsedTimer>
#include <QDir>
#include <QDateTime>
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ecaResize(16);

    setupWaveforms();
}

MainWindow::~MainWindow()
{
    delete ui;
}


//
// public slots
//


void MainWindow::on_pushButtonRandom_clicked()
{
    std::random_device rnd;
    std::mt19937 mt(rnd());

    std::uniform_int_distribution<int> durationDist(10, 50);
    ui->spinBoxDuration->setValue(durationDist(mt));
    ui->spinBoxMaxStep->setValue(1000 / ui->spinBoxDuration->value());

    std::uniform_int_distribution<int> pitchDist(1, 50);
    ui->spinBoxPitch->setValue(pitchDist(mt));

    std::uniform_real_distribution<double> ratioDist(0.01, 12.0);
    ui->doubleSpinBoxRatio->setValue(ratioDist(mt));

    std::uniform_int_distribution<int> harmoDist(4, 20);
    ui->spinBoxHarmonics->setValue(harmoDist(mt));

    std::uniform_int_distribution<int> ruleDist(0, 255);
    ui->spinBoxRule->setValue(ruleDist(mt));

    std::uniform_int_distribution<int> seedDist(0, 65535);
    ui->spinBoxSeed->setValue(seedDist(mt));

    on_pushButtonRender_clicked();
}

void MainWindow::on_pushButtonRender_clicked()
{
    QElapsedTimer timer;

    timer.start();
    renderSound();
    ui->statusBar->showMessage("Render Time [msec]: " + QString("%1").arg(timer.elapsed()));

    soundPlayer.setWave(waveSound);
    ui->waveformMain->refresh();
    playSound();
}

void MainWindow::on_pushButtonPlay_clicked()
{
    playSound();
}

void MainWindow::on_pushButtonSave_clicked()
{
    saveSound();
}

void MainWindow::on_spinBoxHarmonics_valueChanged(int arg1)
{
    ecaResize(arg1);
}

void MainWindow::on_spinBoxSmooth_valueChanged(int arg1)
{
    ecaCar.setSmoothTime(static_cast<float>(arg1));
    ecaMod.setSmoothTime(static_cast<float>(arg1));
}

void MainWindow::on_spinBoxRule_valueChanged(int arg1)
{
    ecaCar.setRule(arg1);
    ecaMod.setRule(arg1);
}



//
// private
//

void MainWindow::setupWaveforms()
{
    ui->waveformMain->setWave(&waveSound);
}

void MainWindow::saveSound()
{
    QString dirNameRender = "render/";
    QString prefix = "ECAFM";

    // 保存先のディレクトリが無ければ作る
    QDir dir;
    if (!dir.exists(dirNameRender))
        dir.mkdir(dirNameRender);

    // wavの保存
    QString name;
    name.append(dirNameRender);
    name.append(prefix);
    name.append(QDateTime::currentDateTime().toString("_yyyy.MM.dd_hh.mm.ss.zzz"));
    name.append(".wav");
    soundPlayer.SaveWaveFile(name);

    // 保存先の表示
    ui->statusBar->showMessage("File is saved to: " + name);
}

void MainWindow::playSound()
{
    soundPlayer.play();
}

void MainWindow::renderSound()
{
    int numSamples = getNumberOfSamples();

    const int minSamples = 200;
    if (numSamples < minSamples)
        numSamples = minSamples; // 最低サンプル数の保証

    //fmto.clearBuffer();
    waveSound.resize(numSamples);

    int seed = ui->spinBoxSeed->value();
    ecaMod.init(seed);
    ecaCar.init(seed + 65536);

    float pitch = PitchCalc::intervalToFreq(100.0f * static_cast<float>(ui->spinBoxPitch->value()));
    float tt = ui->doubleSpinBoxRatio->value() * 2.0f * PI * pitch / SampleRate::get();
    int stepTime = ui->spinBoxDuration->value() * SampleRate::get() / 1000;
    for (int i = 0; i < numSamples; ++i)
    {
        float phase = tt * i;
        waveSound[i] = harmoTone(phase + 3.0f * harmoTone(phase, ecaMod), ecaCar);

        if (i % stepTime == 0)
        {
            ecaMod.next();
            ecaCar.next();
        }
    }
}

float MainWindow::harmoTone(float phase, ElementaryCA& eca)
{
    int harmonics = ui->spinBoxHarmonics->value();
    float temp = 0.0f;

    if (ui->comboBoxHarmoType->currentIndex() == 0)
    {
        for (int i = 0; i < harmonics; ++i)
        {
            temp += eca.gainAt(i) * sinf(phase * i);
        }
        return temp / harmonics;
    }
    else if (ui->comboBoxHarmoType->currentIndex() == 1)
    {
        for (int i = 0; i < harmonics; ++i)
        {
            temp += pow(0.5f, i) * eca.gainAt(i) * sinf(phase * i);
        }
        return temp * 0.5;
    }

    return 0.0f; // ここには到達しない
}

int MainWindow::getNumberOfSamples()
{
    double msec = static_cast<double>(ui->spinBoxDuration->value() * ui->spinBoxMaxStep->value()) * 0.001;
    return static_cast<int>(msec * SampleRate::get());
}

void MainWindow::ecaResize(int size)
{
    ecaCar.setSize(size);
    ecaMod.setSize(size);
}
