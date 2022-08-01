#ifndef MYMOVIE_H
#define MYMOVIE_H

#include <QMovie>

class MyMovie: public QMovie
{
public:
    MyMovie(int tupe,int horisontal,int vertical);
};

#endif // MYMOVIE_H
