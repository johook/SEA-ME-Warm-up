#ifndef CONTACT_H
#define CONTACT_H

#include<QString> //QT use string as QString

class Contact
{
private:
    // Contact attributes
    QString name, number, nickname, memo,email;
    bool bookmarked;
public:
    // Default Constructor initializes all attribute to "None" and bookmakred to False.
    Contact()
            : name("None"), number("None"), nickname("None"), memo("None"), email("None"), bookmarked(false) {}

    // Parameterized constructor
    Contact(const QString &name, const QString &number, const QString &nickname, const QString &email, bool bookmarked = false):
        name(name), number(number), nickname(nickname),email(email),bookmarked(bookmarked){}

    // Getters for the contact attributes.
    QString getName() const {return name; }
    QString getnumber() const {return number; }
    QString getnickname() const {return nickname;}
    QString getemail() const {return email; }
    bool isBookmarked() const {return bookmarked;}

    // Setters for the contact attributes.
    void setName(const QString &newname) {name = newname;}
    void setNumber(const QString &newnum) {number = newnum;}
    void setNickname(const QString &newnick) {nickname = newnick;}
    void setEmail(const QString &newemail) {email = newemail;}
    void setBookmarked(bool isbookmarked) {bookmarked=isbookmarked;}
};

#endif // CONTACT_H
