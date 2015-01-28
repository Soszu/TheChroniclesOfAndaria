#include "Editor/CustomWidgets/PrizeEdit.hpp"

PrizeEdit::PrizeEdit(QWidget *parent) : QWidget(parent)
{
	setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	initLayout();
}

Prize PrizeEdit::prize() const
{
	return prize_;
}

void PrizeEdit::reset()
{
	emit prizeChanged(prize_);
}

void PrizeEdit::setPrize(const Prize &prize)
{
	qDebug() << "hura";
	if (prize_ == prize)
		return;

	prize_ = prize;
	emit prizeChanged(prize_);
	simulateFocusLoss();
}

void PrizeEdit::initLayout()
{

}

void PrizeEdit::simulateFocusLoss()
{
	setFocus(Qt::OtherFocusReason);
	clearFocus();
}
