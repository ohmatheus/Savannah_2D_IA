#include "stdafx.h"

#include "QSceneControllerW.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>

#include <QPushButton>
//----------------------------------------------------------

QSceneControllerW::QSceneControllerW(QWidget *parent)
:	Super(parent)
{
	auto		*dummy = new QWidget(this);

	auto		*layout = new QGridLayout(dummy);
	layout->setSpacing(20);
	//layout->setContentsMargins(0, 0, 0, 0);
	//layout->setColumnMinimumWidth(0, 50);
	//layout->setColumnMinimumWidth(1, 50);
	//layout->setColumnMinimumWidth(2, 50);

	int row = 0;
	{
		QLabel		*label = new QLabel("Lions", this);
		layout->addWidget(label, row, 1);
	}

	{
		QLabel		*label = new QLabel("Antelope", this);
		layout->addWidget(label, row, 2);
	}

	{
		QLabel		*label = new QLabel("Spawn Count", this);
		layout->addWidget(label, ++row, 0);

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			//QDoubleValidator *dv = new QDoubleValidator(0.0, 5.0, 2); // [0, 5] with 2 decimals of precision
			QIntValidator		*iv = new QIntValidator(1, 75);
			line->setValidator(iv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 1);
		}

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QIntValidator		*iv = new QIntValidator(1, 300);
			line->setValidator(iv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 2);
		}
	}

	{
		QLabel	*label = new QLabel("Velocity", this);
		layout->addWidget(label, ++row, 0);

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 1);
		}

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 2);
		}
	}

	{
		QLabel	*label = new QLabel("Rotation Speed", this);
		layout->addWidget(label, ++row, 0);

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 1);
		}

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 2);
		}
	}

	{
		QLabel	*label = new QLabel("Initial Health", this);
		layout->addWidget(label, ++row, 0);

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 1);
		}

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 2);
		}
	}

	{
		QLabel	*label = new QLabel("Dps", this);
		layout->addWidget(label, ++row, 0);

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 1);
		}

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 2);
		}
	}

	{
		QLabel	*label = new QLabel("Attack Range", this);
		layout->addWidget(label, ++row, 0);

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 1);
		}

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 2);
		}
	}

	{
		QLabel	*label = new QLabel("Radius To Flee", this);
		layout->addWidget(label, ++row, 0);

		/*{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 1);
		}*/

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 2);
		}
	}

	{
		QLabel	*label = new QLabel("Near Friend to Attack", this);
		layout->addWidget(label, ++row, 0);

		/*{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 1);
		}*/

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 2);
		}
	}

	{
		QLabel	*label = new QLabel("Near Friend Radius", this);
		layout->addWidget(label, ++row, 0);
		/*{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 1);
		}*/

		{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 2);
		}
	}

	{
		QLabel	*label = new QLabel("Near Friend Radius", this);
		layout->addWidget(label, ++row, 0);
	}
}

//----------------------------------------------------------

QSceneControllerW::~QSceneControllerW()
{}

//----------------------------------------------------------
