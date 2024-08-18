#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "contact.h"
#include <QMessageBox>
#include <QInputDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStandardItemModel(0,5,this))
{
    ui->setupUi(this);
    this->setWindowTitle("PhoneBook"); // Set window title to "Phonebook"

    // Set header labels for the table view(Contact list).
    model ->setHeaderData(0,Qt::Horizontal,"name");
    model ->setHeaderData(1,Qt::Horizontal,"Bookmarked");
    model ->setHeaderData(2,Qt::Horizontal,"PhoneNum");
    model ->setHeaderData(3,Qt::Horizontal,"Nickname");
    model ->setHeaderData(4,Qt::Horizontal,"Email");



    ui->ContactTableView->setModel(model); // Link the model to the table view(Contact list)
    ui->ContactTableView->horizontalHeader()->setStretchLastSection(true);

    // When the ADD Button is clicked, the AddContact is executed.
    connect(ui->AddButton, &QPushButton::clicked,this,&MainWindow::AddContact);

    // When the Search Button is clicked, the SearchContact is executed.
    connect(ui->SearchButton, &QPushButton::clicked,this,&MainWindow::SearchContact);

    // When the Remove Button is clicked, the RemoveContact is executed.
    connect(ui->RemoveButton, &QPushButton::clicked, this, &MainWindow::RemoveContact);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddContact()
{
    // Get input from the LineEdits.
    QString name = ui->NameLineEdit->text();
    QString number = ui->NumLineEdit->text();
    QString nickname = ui->NickLineEdit->text().isEmpty()? "None":ui->NickLineEdit->text();
    QString email = ui->EmailLineEdit->text().isEmpty()?"None":ui->EmailLineEdit->text();

    bool bookmarked = ui->BookmarkedCheckBox->isChecked();

    // Validate input
    if (number.isEmpty() || name.isEmpty()){
        QMessageBox::warning(this,"INPUT ERROR", "Name or Number field cannot be empty");
        return;
    }
    // Check for duplicate contact.
    for (const Contact &contact : contacts)
    {
        if(contact.getName() == name || contact.getnumber() == number)
        {
            QMessageBox::warning(this,"Same Contact","Please check again input name or number, if there's already exists.");
            return;
        }
    }

    // Add a new contact to the list
    Contact newContact(name, number,nickname,email, bookmarked);
    contacts.append(newContact);

    // Add the new contact to the table view(Contact list).
    QList<QStandardItem*> rowItems;
    rowItems.append(new QStandardItem(newContact.getName()));
    rowItems.append(new QStandardItem(newContact.isBookmarked() ? "Yes" : "No"));
    rowItems.append(new QStandardItem(newContact.getnumber()));
    rowItems.append(new QStandardItem(newContact.getnickname()));
    rowItems.append(new QStandardItem(newContact.getemail()));



    model->appendRow(rowItems);

    // Clear the input fields after adding the contact.
    ui->NameLineEdit->clear();
    ui->NumLineEdit->clear();
    ui->NickLineEdit->clear();
    ui->EmailLineEdit->clear();
    ui->BookmarkedCheckBox->setChecked(false);


}

void MainWindow::SearchContact()
{
    // Get information for searching
    QString SearchName = ui->NameLineEdit->text();
    QString SearchNumber = ui->NumLineEdit->text();

    // Validate input.
    if (SearchName.isEmpty() && SearchNumber.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please enter either a Name or a Number to search.");
            return;
        }

    // Search through contacts
    for (const Contact &contact : contacts){
        if(contact.getName() == SearchName || contact.getnumber()==SearchNumber){
            QString contactInfo = QString("Name: %1\nNumber: %2\nNickname: %3\nEmail: %4\nBookmarked: %5")
                    .arg(contact.getName())
                    .arg(contact.getnumber())
                    .arg(contact.getnickname())
                    .arg(contact.getemail())
                    .arg(contact.isBookmarked() ? "Yes" : "No");

            // Show found contact information.
            QMessageBox::information(this,"Contact Found", contactInfo);

            // Clear the input fields after searching.
            ui->NameLineEdit->clear();
            ui->NumLineEdit->clear();
            return;

        }
    }
    // When no contact is found.
    QMessageBox::information(this,"No Match","No contact found with the given information.");
}

void MainWindow::RemoveContact()
{
    // Get the name of the contact to remove.
    QString RemoveName = QInputDialog::getText(this, "Remove Contact", "Enter the Name: ");

    // Validate input.
    if (RemoveName.isEmpty())
    {
        QMessageBox::warning(this,"Input Error", "Name cannot be empty.");
        return;
    }

    int index = -1; // Index of the contact to remove.

    // Search for the contact to remove.
    for(int i=0; i<contacts.size();i++){
        const Contact &contact = contacts[i];
        if(contact.getName()==RemoveName)
        {
            // Confirm delection with the user.
            QString contactInfo = QString("Are you sure you want to delete this contact?\n\nName: %1\nNumber: %2\nNickname: %3\nEmail: %4\nBookmarked: %5")
                    .arg(contact.getName())
                    .arg(contact.getnumber())
                    .arg(contact.getnickname())
                    .arg(contact.getemail())
                    .arg(contact.isBookmarked() ? "Yes" : "No");

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirm Delete", contactInfo, QMessageBox::Yes | QMessageBox::No);

            if(reply==QMessageBox::Yes)
            {
                index = i; // Save the index of the contact to remove.
                break;
            }
            else
            {
                QMessageBox::information(this,"Not Deleted", "Contact was not deleted.");
                return;
            }
        }
    }
    if (index != -1)
    {
        contacts.removeAt(index); // Remove the contact.
        UpdateTableView(); // Update the table view(Contact list), after remove the contact.
        QMessageBox::information(this, "Deleted", "Contact has been deleted.");
    }else {
        QMessageBox::information(this, "No Match", "No contact found with the given name.");
    }

}

void MainWindow::UpdateTableView()
{
    model -> clear(); // Clear the current table view(Contact list)

    // Set header labels again after delection.
    model ->setHeaderData(0,Qt::Horizontal,"Name");
    model ->setHeaderData(1,Qt::Horizontal,"PhoneNum");
    model ->setHeaderData(2,Qt::Horizontal,"Nickname");
    model ->setHeaderData(3,Qt::Horizontal,"Email");
    model ->setHeaderData(4,Qt::Horizontal,"Bookmarked");

    // Re-poppulate the table view with updated contacts
    for (const Contact &contact : contacts)
    {
        QList<QStandardItem*> rowItems;
        rowItems.append(new QStandardItem(contact.getName()));
        rowItems.append(new QStandardItem(contact.getnumber()));
        rowItems.append(new QStandardItem(contact.getnickname()));
        rowItems.append(new QStandardItem(contact.getemail()));
        rowItems.append(new QStandardItem(contact.isBookmarked() ? "Yes" : "No"));

        model ->appendRow(rowItems);
    }


}
