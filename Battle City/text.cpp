#include "text.h"

Text::Text(int wight,int height)
{
   QPixmap one(wight,height);
   image = one;

   image.fill(Qt::transparent);
   p = new QPainter(&image);
}

QRect Text::pos()
{
    return size;
}

QPixmap Text::img()
{
    return image;
}

void Text::drawText(QString text)
{
    image.fill(Qt::transparent);
    p->drawText(QRect(0,0,image.width(),image.height()),Qt::AlignLeft,text);
}

void Text::setText(QString text,QRect rect, QString color)
{
    QFont font("bcFont 7x7");
    font.setPixelSize(22);
    p->setFont(font);

    size.setRect(rect.x(),rect.y(),image.width(),image.height());

    image.fill(Qt::transparent);

   if (color == "white")
       p->setPen(Qt::white);

   if (color == "black")
       p->setPen(Qt::black);

    p->drawText(QRect(0,0,image.width(),image.height()),Qt::AlignLeft,text);
}

