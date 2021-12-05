#include "startdialog.hh"
#include "ui_startdialog.h"

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
    this->setFixedSize(400,300);
    QString fileContent;
    QString path = ":/introText/introText.txt";
    QFile file;
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileContent = file.readAll();
    file.close();
    ui->introTextBrowser->setText(fileContent);
    connect(ui->settingButton, &QPushButton::clicked, this, &StartDialog::onOpenSetting);
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::onOpenSetting()
{
    QDialog* settingDialog = new QDialog(this);
    settingDialog->setFixedSize(400, 500);
    settingDialog->setWindowTitle("Game Setting");

    QLabel* location_number = new QLabel("Number of locations", settingDialog);
    location_number->move(10, 10);
    auto font = location_number->font();
    font.setPointSize(14);
    location_number->setFont(font);
    QSpinBox* no_of_location = new QSpinBox(settingDialog);
    no_of_location->move(250, 10);
    no_of_location->setValue(4);
    no_of_location->setMaximum(9);
    no_of_location->setMinimum(4);

    QLabel* game_duration = new QLabel("Game duration", settingDialog);
    game_duration->move(10, 50);
    font = game_duration->font();
    font.setPointSize(14);
    game_duration->setFont(font);
    QSpinBox* game_time = new QSpinBox(settingDialog);
    game_time->move(250, 50);
    game_time->setValue(10);
    game_time->setMaximum(100);
    game_time->setMinimum(1);

    QLabel* player_number = new QLabel("Number of players", settingDialog);
    player_number->move(10, 90);
    font = player_number->font();
    font.setPointSize(14);
    player_number->setFont(font);
    QSpinBox* no_of_player = new QSpinBox(settingDialog);
    no_of_player->move(250,90);
    no_of_player->setValue(2);
    no_of_player->setMaximum(4);
    no_of_player->setMinimum(2);

    QLabel* player_1 = new QLabel("Player 1", settingDialog);
    player_1->move(20, 130);
    font = player_1->font();
    font.setPointSize(14);
    player_1->setFont(font);
    QLineEdit* player_1_name = new QLineEdit(settingDialog);
    player_1_name->move(250,130);
    player_1_name->setMaxLength(10);

    QLabel* player_2 = new QLabel("Player 2", settingDialog);
    player_2->move(20, 170);
    font = player_2->font();
    font.setPointSize(14);
    player_2->setFont(font);
    QLineEdit* player_2_name = new QLineEdit(settingDialog);
    player_2_name->move(250,170);
    player_2_name->setMaxLength(10);

    QLabel* player_3 = new QLabel("Player 3", settingDialog);
    player_3->move(20, 210);
    font = player_3->font();
    font.setPointSize(14);
    player_3->setFont(font);
    player_3->setVisible(false);
    QLineEdit* player_3_name = new QLineEdit(settingDialog);
    player_3_name->move(250,210);
    player_3_name->setVisible(false);
    player_3_name->setMaxLength(10);

    QLabel* player_4 = new QLabel("Player 4", settingDialog);
    player_4->move(20, 250);
    font = player_4->font();
    font.setPointSize(14);
    player_4->setFont(font);
    player_4->setVisible(false);
    QLineEdit* player_4_name = new QLineEdit(settingDialog);
    player_4_name->move(250,250);
    player_4_name->setVisible(false);
    player_4_name->setMaxLength(10);

    connect(no_of_player, QOverload<int>::of(&QSpinBox::valueChanged), [=](int i){
        if (i == 3) {
            player_3->setVisible(true);
            player_3_name->setVisible(true);
            player_4->setVisible(false);
            player_4_name->setVisible(false);
        } else if (i == 4) {
            player_4->setVisible(true);
            player_4_name->setVisible(true);
        } else {
            player_3->setVisible(false);
            player_3_name->setVisible(false);
            player_4->setVisible(false);
            player_4_name->setVisible(false);
        }
    });

    QPushButton* confirm = new QPushButton("OK", settingDialog);
    confirm->move(10, 350);

    connect(confirm, &QPushButton::clicked, [=]() {
        std::vector<QString> name_;
        if (player_1_name->text() == "") {
            name_.push_back("player 1");
        } else {
            name_.push_back(player_1_name->text());
        }
        if (player_2_name->text() == "") {
            name_.push_back("player 2");
        } else {
            name_.push_back(player_2_name->text());
        }
        if (player_3_name->isVisible()) {
            if (player_3_name->text() == "") {
                name_.push_back("player 3");
            } else {
                name_.push_back(player_3_name->text());
            }
        }
        if (player_4_name->isVisible()) {
            if (player_4_name->text() == "") {
                name_.push_back("player 4");
            } else {
                name_.push_back(player_4_name->text());
            }
        }
        emit gameSettingChange({   no_of_location->value(),
                                   game_time->value(),
                                   no_of_player->value(),
                                   name_
                               });
    });
    connect(confirm, &QPushButton::clicked, settingDialog, &QDialog::accept);
    settingDialog->show();
}
