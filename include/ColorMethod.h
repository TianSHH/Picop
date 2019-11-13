#ifndef COLORMETHOD_H
#define COLORMETHOD_H

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtCore/QtAlgorithms>
#include <QtGui/QImage>
#include <algorithm>

class ColorMethod
{
public:
    ColorMethod();
    ~ColorMethod();

public:
    QImage toGrayImage(QImage originImage);
    QImage to256ColorImage(QImage originImage);

    static inline int pixel_distance(QRgb p1, QRgb p2)
    {
        int r1 = qRed(p1);
        int g1 = qGreen(p1);
        int b1 = qBlue(p1);
        int a1 = qAlpha(p1);

        int r2 = qRed(p2);
        int g2 = qGreen(p2);
        int b2 = qBlue(p2);
        int a2 = qAlpha(p2);

        return abs(r1 - r2) + abs(g1 - g2) + abs(b1 - b2) + abs(a1 - a2);
    }

    static inline int closestMatch(QRgb pixel, const QVector<QRgb> &clut)
    {
        int idx = 0;
        int current_distance = INT_MAX;
        for (int i = 0; i < clut.size(); ++i)
        {
            int dist = pixel_distance(pixel, clut.at(i));
            if (dist < current_distance)
            {
                current_distance = dist;
                idx = i;
            }
        }
        return idx;
    }
};

#endif // COLORMETHOD_H