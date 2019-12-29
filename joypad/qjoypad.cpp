#include "qjoypad.h"
#include <QPainter>
#include <QDebug>

#include <stdlib.h>
#include <stdio.h>
#include <QApplication>
#include <QDesktopWidget>
#include <math.h>
#include <QResource>
#include <QString>
#include <qmath.h>

QJoypad::QJoypad(QWidget *parent, bool mouseActivate) :
    QWidget(parent)
{
    mJoyRelPos.setX( 0.0 );
    mJoyRelPos.setY( 0.0 );

    mPxScaleX = 1.0f;
    mPxScaleY = 1.0f;

    mMaxAxis = 100.0f;

    mouse = mouseActivate;

    if( !this->hasHeightForWidth() )
    {
        QSizePolicy sizePolicy =
                QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setWidthForHeight(true);
        this->setSizePolicy( sizePolicy );
    }
    QPixmap bgPm = QPixmap(":/joypad/images/joystick_background.png");

    this->setMinimumSize(bgPm.width(),bgPm.height());
    this->setMaximumSize(bgPm.width(),bgPm.height());
}

void QJoypad::setJoypadValues( float x, float y )
{
    //    if( !isVisible() )
    //        return;

    //static float oldX=0.0f,oldY=0.0f;

    //oldX = x; oldY = y;

    if( x < -mMaxAxis )
        mJoyRelPos.setX( qreal(-mMaxAxis) );
    else if( x > mMaxAxis )
        mJoyRelPos.setX( qreal(mMaxAxis) );
    else
        mJoyRelPos.setX( qreal(x) );

    if( y < -mMaxAxis )
        mJoyRelPos.setY( qreal(-mMaxAxis) );
    else if( y > mMaxAxis )
        mJoyRelPos.setY( qreal(mMaxAxis) );
    else
        mJoyRelPos.setY(qreal( y ));

    if( isVisible() )
        update();

    emit newJoypadValues( float(mJoyRelPos.x()), float(-mJoyRelPos.y()) );
    //qDebug() /*<< PREFIX*/ << "emitted newJoypadValues( mJoyRelPos.x(), -mJoyRelPos.y() );";
}

void QJoypad::reset()
{
    mJoyRelPos.setX( 0.0 );
    mJoyRelPos.setY( 0.0 );

    emit newJoypadValues( 0.0f, 0.0f );
}

void QJoypad::resizeEvent( QResizeEvent* event )
{
    //qDebug()<<"resize";
    QSize newSize = event->size();

    QPixmap bgPm = QPixmap(":/joypad/images/joystick_background.png");

    mJoyBg = bgPm.scaled( newSize,
                          Qt::IgnoreAspectRatio,
                          Qt::SmoothTransformation );

    float imScaleX = float(mJoyBg.width()/bgPm.width());
    float imScaleY = float(mJoyBg.height()/bgPm.height());

    QPixmap pm = QPixmap(":/joypad/images/joystick_thumb.png");
    QSize scaledPadSize;
    int newW = (int(float(pm.width()*imScaleX)+0.5f));
    scaledPadSize.setWidth( newW );
    int newH = (int(float(pm.height()*imScaleY)+0.5f));
    //int newH = pm.height()*int(ratio);
    scaledPadSize.setHeight( newH );
    mJoypad = pm.scaled( scaledPadSize,
                         Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation  );

    mBgSize = newSize.width();
    mPadSize = mJoypad.width();

    mMaxRho = (mBgSize-mPadSize)/2;

    // ---> Pixel scale according to range
    mPxScaleX = mMaxAxis/mMaxRho;
    mPxScaleY = mMaxAxis/mMaxRho;
    // <--- Pixel scale according to range

    emit newJoypadValues( 0.0, 0.0 );
    //qDebug() /*<< PREFIX*/ << "emitted newJoypadValues( 0.0, 0.0 );";

    //qDebug() << newSize;

    QWidget::resizeEvent(event);
}

void QJoypad::mousePressEvent( QMouseEvent *event )
{
    if (mouse)
    {
        QPoint pos = event->pos();

        //    fprintf( stderr, "Pos: (%3d,%3d)/n", (int)pos.x(), (int)pos.y());
        //    fflush(stderr);

        QPointF centerWidget;
        centerWidget.setX( width()/2);
        centerWidget.setY( height()/2 );

        // >>>>> Let's keep the thumb inside the Joypad area
        double rho = qSqrt( (centerWidget.x()-pos.x())*(centerWidget.x()-pos.x()) +
                            (centerWidget.y()-pos.y())*(centerWidget.y()-pos.y()) );

        //qDebug() << centerWidget << rho << maxPos;

        double X = pos.x()-centerWidget.x();
        double Y = pos.y()-centerWidget.y();

        if( rho>double(mMaxRho) )
        {
            double ratio = double(mMaxRho)/rho;

            X *= ratio;
            Y *= ratio;

        }
        // <<<<< Let's keep the thumb inside the Joypad area

        mJoyRelPos.setX( X * double(mPxScaleX) );
        mJoyRelPos.setY( Y * double(mPxScaleY) );

        //    fprintf( stderr, "Rel Pos: (%g,%g)/n", posX, posY );
        //    fflush(stderr);

        update();

        emit newJoypadValues( float(mJoyRelPos.x()),float(-mJoyRelPos.y()) );

        emit mouseButtonDown( event );

        //qDebug() /*<< PREFIX*/ << "emitted mouseButtonDown( event );";
        //qDebug() /*<< PREFIX*/ << "emitted newJoypadValues( mJoyRelPos.x(), -mJoyRelPos.y() );";
    }
}

void QJoypad::mouseMoveEvent( QMouseEvent *event )
{
    if (mouse)
    {
        QPoint pos = event->pos();

        //    fprintf( stderr, "Pos: (%3d,%3d)/n", (int)pos.x(), (int)pos.y());
        //    fflush(stderr);

        QPointF centerWidget;
        centerWidget.setX( width()/2);
        centerWidget.setY( height()/2 );

        // >>>>> Let's keep the thumb inside the Joypad area
        double rho = qSqrt( (centerWidget.x()-pos.x())*(centerWidget.x()-pos.x()) +
                            (centerWidget.y()-pos.y())*(centerWidget.y()-pos.y()) );

        //qDebug() << centerWidget << rho << maxPos;

        double X = pos.x()-centerWidget.x();
        double Y = pos.y()-centerWidget.y();

        if( rho>double(mMaxRho) )
        {
            double ratio = double(mMaxRho)/rho;

            X *= ratio;
            Y *= ratio;

        }
        // <<<<< Let's keep the thumb inside the Joypad area

        mJoyRelPos.setX( X * double(mPxScaleX));

        mJoyRelPos.setY( Y * double(mPxScaleY));

        //    fprintf( stderr, "Rel Pos: (%g,%g)/n", posX, posY );
        //    fflush(stderr);

        update();

        emit newJoypadValues( float(mJoyRelPos.x()),float(-mJoyRelPos.y()) );
        //qDebug() /*<< PREFIX*/ << "emitted newJoypadValues( mJoyRelPos.x(), -mJoyRelPos.y() );";
    }
}

void QJoypad::mouseReleaseEvent( QMouseEvent *event )
{
    if (mouse)
    {
        mJoyRelPos.setX( 0.0 );
        mJoyRelPos.setY( 0.0 );

        update();

        emit mouseButtonUp( event );
        emit newJoypadValues( float(mJoyRelPos.x()),float(-mJoyRelPos.y()) );

        //qDebug() /*<< PREFIX*/ << "emitted mouseButtonUp( event );";
        //qDebug() /*<< PREFIX*/ << "emitted newJoypadValues( mJoyRelPos.x(), -mJoyRelPos.y() );";
    }
}

void QJoypad::paintEvent(QPaintEvent *event)
{
    event->accept();

    int realJoyPosX = int(mJoyRelPos.x()/double(mPxScaleX));
    int realJoyPosY = int(mJoyRelPos.y()/double(mPxScaleY));

    int padOrigX = int((realJoyPosX-mJoypad.width()/2)+0.5f) + width()/2;
    int padOrigY = int((realJoyPosY-mJoypad.height()/2)+0.5f) + height()/2;

    QPainter painter(this);

    /*painter.setOpacity( 0.2 );
    painter.drawLine( width()/2, height()/2,
                      realJoyPosX+width()/2, realJoyPosY+height()/2 );*/

    // Background
    painter.setOpacity(1.0);
    painter.drawPixmap( 0, 0, mJoyBg);

    // Pad
    painter.setOpacity( 0.8 );
    painter.drawPixmap( padOrigX, padOrigY, mJoypad );
}

/*int QJoypad::heightForWidth( int w )
{
    return w;
}*/

void QJoypad::setMouse(bool mouseActivate)
{
    mouse = mouseActivate;
}
