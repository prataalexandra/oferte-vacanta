#include "cos_read_gui.h"
#include "Service_Cos.h"
#include <cstdlib>
#include <ctime>

CartCRUDRead::CartCRUDRead(CosService& cart_serv) : cart_serv{ cart_serv }
{
    cart_serv.addObserver(this);
    repaint();
}

void CartCRUDRead::paintEvent(QPaintEvent* event) {

    QPainter g{ this };
    g.setPen(Qt::red);

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> x_coord(0, this->width());
    std::uniform_int_distribution<> y_coord(0, this->height());
    std::uniform_int_distribution<> width(15, RECTANGLE_MAX_DIM);
    std::uniform_int_distribution<> height(15, RECTANGLE_MAX_DIM);

    int z_coord = 1000;
    int p_coord = 150;
    auto lst = cart_serv.cos_get_all_service();

    QPen pen(Qt::black);
    g.setPen(pen);

    
    int x = 0;
    int y = 0;
    int xx = 100;
    int yy = 100;
    QPoint startPoint(x, y);
    QPoint endPoint(xx, yy);


    int i;
    for (i = 0; i < lst.size(); i++)
    {
        if (lst[i].getDenumire() == "Excursie")
            g.drawRect(x_coord(mt), height(mt), z_coord, p_coord);
        else if (lst[i].getDenumire() == "City Break")
            g.drawPie(x_coord(mt), y_coord(mt), width(mt), height(mt), z_coord, p_coord);
        else
        {
            //srand(time(NULL));
            xx += rand()%140;
            yy += rand()%200;
            x += rand()%100;
            y += rand()%200;
            startPoint.setX(xx);
            startPoint.setY(yy);
            endPoint.setX(x);
            endPoint.setY(y);
            g.drawLine(startPoint, endPoint);
            
        }



    }

}

void CartCRUDRead::update() {
    repaint();
}