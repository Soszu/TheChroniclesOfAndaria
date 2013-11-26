#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QtWidgets>

//TODO CFiend zmienic nazwe klasy?
//TODO CFiend do czego to w ogole jest? Nie wystarczy uzyc gdzies QSignalMapper?
class MyButton : public QPushButton {
	Q_OBJECT;
public:
	explicit MyButton(int n);
	void setID(int n);

signals:
	void kliknietyID(int n);

private slots:
	void emitujID();

private:
	int ID;
};

#endif
