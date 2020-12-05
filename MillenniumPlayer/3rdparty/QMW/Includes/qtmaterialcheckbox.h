#ifndef QTMATERIALCHECKBOX_H
#define QTMATERIALCHECKBOX_H

//#include "components/lib/qtmaterialcheckable.h"
#include "3rdparty/QMW/Includes/qtmaterialcheckable.h"
class QtMaterialCheckBoxPrivate;

class QtMaterialCheckBox : public QtMaterialCheckable
{
    Q_OBJECT

public:
    explicit QtMaterialCheckBox(QWidget *parent = 0);
    ~QtMaterialCheckBox();

private:
    Q_DISABLE_COPY(QtMaterialCheckBox)
    Q_DECLARE_PRIVATE(QtMaterialCheckBox)
};

#endif // QTMATERIALCHECKBOX_H
