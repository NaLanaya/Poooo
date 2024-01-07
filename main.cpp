#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

class TemperatureConverterApp : public QWidget {
    Q_OBJECT

public:
    TemperatureConverterApp(QWidget *parent = 0) : QWidget(parent) {
        setupUi();
        connectSignalsAndSlots();
    }

private slots:
    void convertTemperature() {
        double temp = temperatureLineEdit->text().toDouble();
        char grad = unitComboBox->currentText().toStdString()[0];

        if (grad == 'C' || grad == 'F' || grad == 'K') {
            if (grad == 'F') {
                double c = (temp - 32) * (5.0 / 9.0);
                double k = c + 273.15;
                displayResults(c, k);
            } else if (grad == 'C') {
                double f = (temp * (9.0 / 5.0)) + 32;
                double k = temp + 273.15;
                displayResults(f, k);
            } else if (grad == 'K') {
                double c = temp - 273.15;
                double f = (c * 9.0 / 5.0) + 32;
                displayResults(c, f);
            }
        } else {
            QMessageBox::warning(this, "Ошибка", "Некорректная единица измерения. Введите 'C', 'F' или 'K'.");
        }
    }

private:
    QLineEdit *temperatureLineEdit;
    QComboBox *unitComboBox;
    QLabel *resultLabel;

    void setupUi() {
        QVBoxLayout *layout = new QVBoxLayout;

        QLabel *titleLabel = new QLabel("Конвертер температуры");
        layout->addWidget(titleLabel);

        temperatureLineEdit = new QLineEdit;
        temperatureLineEdit->setPlaceholderText("Введите температуру");
        layout->addWidget(temperatureLineEdit);

        unitComboBox = new QComboBox;
        unitComboBox->addItem("C");
        unitComboBox->addItem("F");
        unitComboBox->addItem("K");
        layout->addWidget(unitComboBox);

        QPushButton *convertButton = new QPushButton("Конвертировать");
        layout->addWidget(convertButton);

        resultLabel = new QLabel;
        layout->addWidget(resultLabel);

        setLayout(layout);
    }

    void connectSignalsAndSlots() {
        connect(convertButton, SIGNAL(clicked()), this, SLOT(convertTemperature()));
    }

    void displayResults(double value1, double value2) {
        resultLabel->setText(QString("Результаты:\n%1\n%2").arg(value1).arg(value2));
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    TemperatureConverterApp converterApp;
    converterApp.show();

    return app.exec();
}
