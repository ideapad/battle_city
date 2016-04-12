#ifndef DATA_PLAYER_H
#define DATA_PLAYER_H

#include "QString"

struct data_player
{
    QString name;
    QString score;

    data_player(QString _name = "", QString _score = ""):
    name(_name), score(_score)   {}

    bool operator <(const data_player& rhs) const;
//    bool operator >(const data_player& rhs) const;
//    data_player& operator =( const data_player& other );


};


#endif // DATA_PLAYER_H
