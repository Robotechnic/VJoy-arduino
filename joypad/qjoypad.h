#ifndef QJoypad_H
#define QJoypad_H

#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QDebug>
class QJoypad : public QWidget
{
    Q_OBJECT
public:
    explicit QJoypad(QWidget *parent = nullptr, bool mouseActivate = true);

    float getMaxAbsAxisValue(){return mMaxAxis;} ///< @return Max axis absolute value

    void setMouse(bool mouseActivate);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );

    //int heightForWidth( int w ) Q_DECL_OVERRIDE;

signals:
    void newJoypadValues( float x, float y ); // Joypad values in range [-100,+100]
    void mouseButtonDown( QMouseEvent *event ); // Emitted on mouse button down
    void mouseButtonUp( QMouseEvent *event ); // Emitted on mouse button up

public slots:
    void    setJoypadValues( float x, float y ); // Set Joypad position in range [-100,+100]
    void    reset(); // Reset current values, used in emergency

private:
    QPointF   mJoyRelPos;  ///< Relative joy position

    float   mPxScaleX; ///< Scale factor on X axis
    float   mPxScaleY; ///< Scale factor on Y axis

    float   mMaxAxis;  ///< Max abs axis value (100) -> range [-mMaxAxis, +mMaxAxis]
    float   mMaxRho;   ///< Max radius of the joypad

    QPixmap mJoyBg; ///< Background Image
    QPixmap mJoypad;   ///< Joypad paddle

    int mBgSize; ///< Size of the background image
    int mPadSize; ///< Size of the pad image

    bool mouse;
};

#endif // QJoypad_H
