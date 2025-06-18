#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"Contact.h"
#include"Classmate.h"
#include"Colleague.h"
#include"Friend.h"
#include"Relative.h"
#include"ContactManager.h"
#include<QMessageBox>
#include <QFile>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //菜单绑定页面
    connect(ui->actionadd, &QAction::triggered,this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->addP);
    });

    connect(ui->actiondel, &QAction::triggered,this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->delP);
    });

    connect(ui->actionfind, &QAction::triggered,this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->findP);
    });

    connect(ui->actionupdate, &QAction::triggered,this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->updateP);
    });
    connect(ui->Sall, &QAction::triggered, this, &MainWindow::showAll);
    connect(ui->Scla, &QAction::triggered, this, &MainWindow::showClassmates);
    connect(ui->Scol, &QAction::triggered, this, &MainWindow::showColleagues);
    connect(ui->Sfri, &QAction::triggered, this, &MainWindow::showFriends);
    connect(ui->Srel, &QAction::triggered, this, &MainWindow::showRelatives);

    connect(ui->actionb1,&QAction::triggered, this,[=](){
        ui->stackedWidget->setCurrentWidget(ui->birthInMonth);
    });
    connect(ui->actionb2,&QAction::triggered, this,&MainWindow::showNearBirth);
    connect(ui->showNearBirth, &QListWidget::itemClicked,
            this, &MainWindow::on_birthdayItemClicked);

    // 初始显示添加页
    ui->stackedWidget->setCurrentWidget(ui->addP);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//添加按钮逻辑
void MainWindow::on_addBT_clicked()
{
    QString nameStr = ui->name->text();
    QString telStr = ui->tel->text();
    QString emailStr = ui->email->text();
    QString extraStr = ui->extra->text();
    int year = ui->year->text().toInt();
    int month = ui->month->text().toInt();
    int day = ui->day->text().toInt();
    int cat = ui->cat->text().toInt();
    if(!Date::isValid(year,month,day))
    {
        QMessageBox::warning(this, "失败", "非法的日期");
    }
    else
    {
    Contact*c=nullptr;
    switch(cat)
    {
        case 1:
        {
            c=new Classmate(nameStr, year, month, day, telStr, emailStr, extraStr);
            break;
        }
        case 2:
        {
            c=new Colleague(nameStr, year, month, day, telStr, emailStr, extraStr);
            break;
        }
        case 3:
        {
            c=new Friend(nameStr, year, month, day, telStr, emailStr, extraStr);
            break;
        }
        case 4:
        {
            c=new Relative(nameStr, year, month, day, telStr, emailStr, extraStr);
            break;
        }
        default:
        {
            QMessageBox::warning(this, "失败", "添加失败，类别错误。");
        }
    }
        if(c!=nullptr)
        {
            if (ContactManager::addContact(c)) {
                QMessageBox::information(this, "成功", "联系人添加成功！");
            } else {
                QMessageBox::warning(this, "失败", "添加失败，请检查数据库连接。");
            }
        }
    }
    // 清空表单
    ui->name->clear();
    ui->tel->clear();
    ui->email->clear();
    ui->extra->clear();
    ui->year->clear();
    ui->month->clear();
    ui->day->clear();
    ui->cat->clear();
}

//查询按钮逻辑
void MainWindow::on_findBT_clicked()
{
    QString name=ui->Fname->text();
    QVector<Contact*>res=ContactManager::searchByName(name);
    ui->findShow->clear();
    if(res.isEmpty())
    {
        ui->findShow->addItem("未找到联系人");
        return ;
    }
    int n=res.size();
    for(int i=0;i<n;i++)
    {
        ui->findShow->addItem(res[i]->show());
    }
}
//在删除页的查询按钮逻辑
void MainWindow::on_delFind_clicked()
{
    QString name=ui->delName->text();
    QVector<Contact*>res=ContactManager::searchByName(name);
    ui->delShow->clear();
    if(res.isEmpty())
    {
        ui->delShow->addItem("未找到联系人");
        return ;
    }
    int n=res.size();
    for(int i=0;i<n;i++)
    {
        QListWidgetItem* item = new QListWidgetItem(res[i]->show());

        item->setData(Qt::UserRole, res[i]->getId());
        item->setData(Qt::UserRole + 1, res[i]->getClassName());
        ui->delShow->addItem(item);
    }
}
//删除按钮
void MainWindow::on_delBT_clicked()
{
    QListWidgetItem* item = ui->delShow->currentItem();
    if (!item) {
        QMessageBox::warning(this, "删除失败", "请先选中要删除的联系人");
        return;
    }

    int id = item->data(Qt::UserRole).toInt();
    QString className = item->data(Qt::UserRole + 1).toString();

    if (ContactManager::deleteContact(className,id)) {
        delete item;
        QMessageBox::information(this, "删除成功", "联系人已删除");
    } else {
        QMessageBox::critical(this, "删除失败", "数据删除失败");
    }
}
//显示所有联系人
void MainWindow::showAll()
{
    ui->stackedWidget->setCurrentWidget(ui->showAll);
    ContactManager a;
    a.loadAll();
    QVector<Contact*>all=a.getContacts();
    ui->all->clear();
    for(Contact*c:all)
    {
        ui->all->addItem(c->show());
    }
}
//显示同学
void MainWindow::showClassmates()
{
    ui->stackedWidget->setCurrentWidget(ui->showCla);
    ContactManager a;
    a.loadFromDB<Classmate>(); // 加载同学
    QVector<Contact*> classmates = a.getContacts();
    ui->classmate->clear();
    for (Contact* c : classmates)
    {
        ui->classmate->addItem(c->show());
    }
}
//显示同事
void MainWindow::showColleagues()
{
    ui->stackedWidget->setCurrentWidget(ui->showCol);
    ContactManager a;
    a.loadFromDB<Colleague>(); // 加载同事
    QVector<Contact*> colleagues = a.getContacts();
    ui->colleague->clear();
    for (Contact* c : colleagues)
    {
        ui->colleague->addItem(c->show());
    }
}
//显示朋友
void MainWindow::showFriends()
{
    ui->stackedWidget->setCurrentWidget(ui->showFri);
    ContactManager a;
    a.loadFromDB<Friend>(); // 加载朋友
    QVector<Contact*> friends = a.getContacts();
    ui->friend_2->clear();
    for (Contact* c : friends)
    {
        ui->friend_2->addItem(c->show());
    }
}
//显示亲戚
void MainWindow::showRelatives()
{
    ui->stackedWidget->setCurrentWidget(ui->showRel);
    ContactManager a;
    a.loadFromDB<Relative>(); // 加载亲戚
    QVector<Contact*> relatives = a.getContacts();
    ui->relative->clear();
    for (Contact* c : relatives)
    {
        ui->relative->addItem(c->show());
    }
}
//给所有联系人排序
void MainWindow::on_NSall_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->showAll);

    ContactManager a;
    a.loadAll();
    a.sortByName();  // 内部排序
    QVector<Contact*> all = a.getContacts();

    ui->all->clear();
    for (Contact* c : all)
    {
        ui->all->addItem(c->show());
    }
}

void MainWindow::on_BSall_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->showAll);

    ContactManager a;
    a.loadAll();
    a.sortByBirth();  // 内部排序
    QVector<Contact*> all = a.getContacts();

    ui->all->clear();
    for (Contact* c : all)
    {
        ui->all->addItem(c->show());
    }
}
//写个模板归并相似操作
template<typename T>
void MainWindow::sortAndDisplay(bool byName, QListWidget* listWidget, QWidget* pageWidget)
{
    ui->stackedWidget->setCurrentWidget(pageWidget);

    ContactManager a;
    a.loadFromDB<T>();
    if (byName)
    {
        a.sortByName();
    }
    else
    {
        a.sortByBirth();
    }
    QVector<Contact*> data = a.getContacts();
    listWidget->clear();
    for (Contact* c : data)
    {
        listWidget->addItem(c->show());
    }
}
// 同学
void MainWindow::on_NScla_clicked()
{
    sortAndDisplay<Classmate>(true, ui->classmate, ui->showCla);
}

void MainWindow::on_BScla_clicked()
{
    sortAndDisplay<Classmate>(false, ui->classmate, ui->showCla);
}

// 同事
void MainWindow::on_NScol_clicked()
{
    sortAndDisplay<Colleague>(true, ui->colleague, ui->showCol);
}

void MainWindow::on_BScol_clicked()
{
    sortAndDisplay<Colleague>(false, ui->colleague, ui->showCol);
}

// 朋友
void MainWindow::on_NSfri_clicked()
{
    sortAndDisplay<Friend>(true, ui->friend_2, ui->showFri);
}

void MainWindow::on_BSfri_clicked()
{
    sortAndDisplay<Friend>(false, ui->friend_2, ui->showFri);
}

// 亲戚
void MainWindow::on_NSrel_clicked()
{
    sortAndDisplay<Relative>(true, ui->relative, ui->showRel);
}

void MainWindow::on_BSrel_clicked()
{
    sortAndDisplay<Relative>(false, ui->relative, ui->showRel);
}

//同一个月的生日查询
void MainWindow::on_queryBT_clicked()
{
    int month=ui->theMonth->text().toInt();
    ContactManager a;
    QVector<Contact*>same=a.countBirthMonth(month);
    ui->showSameMonth->clear();
    for(Contact*c:same)
    {
        ui->showSameMonth->addItem(c->show());
    }
    QString total=QString("总共%1人在%2月过生日").arg(same.size()).arg(month);
    ui->showSameMonth->addItem(total);
}
//找最近几天过生日的人
void MainWindow::showNearBirth()
{
    ui->stackedWidget->setCurrentWidget(ui->birthNear);
    ContactManager a;
    a.loadAll();
    QVector<Contact*>near=a.findBirthdayInDays(5);

    ui->showNearBirth->clear();
    Date today=Date::getToday();
    ui->showNearBirth->addItem("今天是"+today.show()+today.getWhatDay());
    for(Contact*c:near)
    {
        int year=today.getYear();
        Date birth=c->getBirth();
        birth.setYear(year);
        if(birth-today<0)
        {
            birth.setYear(year+1);
        }
        QString day = "生日在" + birth.getWhatDay();
        QListWidgetItem* item = new QListWidgetItem(day + " " + c->show());

        // 关键：把姓名存进去，方便点击后使用
        item->setData(Qt::UserRole, c->getName());
        ui->showNearBirth->addItem(item);
    }

}
//生成邮件
void MainWindow::on_birthdayItemClicked(QListWidgetItem* item)
{
    QString recipientName = item->data(Qt::UserRole).toString();
    QString myName = ui->myName->text();
    QString fileName = "祝贺_" + recipientName + ".txt";
    ContactManager::generateEmail(fileName, recipientName, myName);

    // 2. 读取并显示邮件内容
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString content = in.readAll();
        QMessageBox::information(this, "邮件内容", content);
        file.close();
    } else {
        QMessageBox::warning(this, "错误", "无法读取邮件内容");
    }
}
//更新中的查询
void MainWindow::on_updateFind_clicked()
{
    QString name = ui->updateName->text();
    QVector<Contact*> results = ContactManager::searchByName(name);
    ui->updateList->clear();
    for(Contact* c : results)
    {
        QListWidgetItem* item = new QListWidgetItem(c->show());  // show()返回QString
        item->setData(Qt::UserRole, c->getId()); // 绑定ID方便更新
        item->setData(Qt::UserRole + 1, c->getClassName()); // 绑定类别名
        ui->updateList->addItem(item);
    }
}
//更新操作
void MainWindow::on_updateBT_clicked()
{
    QListWidgetItem* item = ui->updateList->currentItem();
    if (!item) return;

    int id = item->data(Qt::UserRole).toInt();
    QString className = item->data(Qt::UserRole + 1).toString();

    QString newTel = ui->updateTel->text();
    QString newEmail = ui->updateEmail->text();
    QString newExtra = ui->updateExtra->text();

    if (ContactManager::updateContact(id, className, newTel, newEmail, newExtra)) {
        QMessageBox::information(this, "成功", "联系人信息已更新");
    } else {
        QMessageBox::warning(this, "失败", "更新失败");
    }
}


