#pragma once

#include <QtCore>

enum class ActionId : quint8;

class Terrain {
public:
	Terrain(QString name, QString imagePath, quint8 coefficient, QList <ActionId> actions);

	const QList <ActionId> & actions() const;
	quint8 coefficient() const;
	const QString & imagePath() const;
	const QString & name() const ;

private:
	QList <ActionId> actions_;
	quint8 coefficient_;
	QString imagePath_;
	QString name_;
};
