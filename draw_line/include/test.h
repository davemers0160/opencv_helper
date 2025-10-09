#pragma once

#include <QLabel>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QImage>


class ImageWidget : public QLabel
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget* parent = nullptr);
    void setImage(const QImage& image);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
};

#include "ImageWidget.h"
#include <QPainter>

ImageWidget::ImageWidget(QWidget* parent) : QLabel(parent)
{
    // Set up initial widget properties if needed
}

void ImageWidget::setImage(const QImage& image)
{
    this->setPixmap(QPixmap::fromImage(image));
}

void ImageWidget::mousePressEvent(QMouseEvent* event)
{
    // Do nothing. The base class's implementation would propagate this event.
    event->ignore();
}

void ImageWidget::mouseMoveEvent(QMouseEvent* event)
{
    // Do nothing.
    event->ignore();
}

void ImageWidget::wheelEvent(QWheelEvent* event)
{
    // Do nothing to disable zooming.
    event->ignore();
}

{
    QApplication a(argc, argv);
    QWidget window;

    // Load an image with OpenCV
    cv::Mat cvImage = cv::imread("image.jpg");
    if (cvImage.empty()) {
        // Handle error
        return -1;
    }

    // Convert OpenCV Mat to Qt QImage
    cv::cvtColor(cvImage, cvImage, cv::COLOR_BGR2RGB);
    QImage qImage(cvImage.data, cvImage.cols, cvImage.rows, cvImage.step, QImage::Format_RGB888);

    // Create and use the custom widget
    ImageWidget* imageWidget = new ImageWidget();
    imageWidget->setImage(qImage);

    QVBoxLayout* layout = new QVBoxLayout(&window);
    layout->addWidget(imageWidget);

    window.setWindowTitle("Fixed Image Display");
    window.show();

    return a.exec();
}
