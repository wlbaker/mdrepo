#include "shortcuticonarea.h"

#include <QSize>
#include <QGridLayout>

ShortcutIconArea::ShortcutIconArea(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout(this);

    for (int row = 0; row < 4; ++row) {
        pixmapLabels[row] = createPixmapLabel();
        mainLayout->addWidget(pixmapLabels[row], row + 1, 1);
    }
}

ShortcutIconArea::~ShortcutIconArea()
{
}

void ShortcutIconArea::updateIcon(int row, const QIcon &icon) {

    QWindow *window = Q_NULLPTR;
    if (const QWidget *nativeParent = nativeParentWidget())
            window = nativeParent->windowHandle();

    QSize size(32,32);

    // QIcon::Normal, QIcon::Active, QIcon::Disabled, QIcon::Selected;
    QIcon::Mode mode = QIcon::Disabled;

    // {QIcon::Off, QIcon::On};
    QIcon::State state = QIcon::On;

    const QPixmap pixmap = icon.pixmap(window, size, mode, state);

    QLabel *pixmapLabel = pixmapLabels[row];

    pixmapLabel->setPixmap(pixmap);
    pixmapLabel->setEnabled(!pixmap.isNull());
}

QLabel *ShortcutIconArea::createPixmapLabel()
{
    QLabel *label = new QLabel;
    label->setEnabled(false);
    label->setAlignment(Qt::AlignCenter);
    label->setFrameShape(QFrame::Box);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label->setBackgroundRole(QPalette::Base);
    label->setAutoFillBackground(true);
    label->setMinimumSize(132, 132);
    return label;
}
