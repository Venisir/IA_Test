/* 
 * File:   DrawableLineShape.h
 * Author: oli92
 *
 * Created on 8 de junio de 2016, 16:49
 */

#ifndef DRAWABLE_LINE_SHAPE
#define DRAWABLE_LINE_SHAPE

#include <vector>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class DrawableLineShape : public sf::Drawable
{

protected:

    struct LineSegmentInfo
    {
        unsigned short nPoint1, nPoint2;
        sf::Color color;
        //falso si este segmento esta reutilizandose
        bool bActive;

        LineSegmentInfo(const unsigned short nPoint1ID, const unsigned short nPoint2ID, const Color& lineColor = Color(255, 255, 255)) :
                bActive(true)
        {
            nPoint1 = nPoint1ID;
            nPoint2 = nPoint2ID;
            color = lineColor;
        }
    };

    struct PointInfo
    {
        Vector2f v2fPoint;
        //falso si este segmento esta reutilizandose
        bool bActive;

        PointInfo(const Vector2f& v2fLinePoint = Vector2f(0.0f, 0.0f)) :
            bActive(true)
        {
            v2fPoint = v2fLinePoint;
        }
    };

public:

    DrawableLineShape();

    DrawableLineShape& operator = (const DrawableLineShape& that);

    ~DrawableLineShape();

    //anyade un punto a la linea, devuelve el id del punto
    unsigned short AddPoint(const Vector2f& v2fPointPosition);

    //anyade un punto a la linea, devuelve el id del punto
    unsigned short AddPoint(const float fXPosition, const float fYPosition);

    //quita el punto 
    void RemovePoint(const unsigned short nPointID);

    //mueve el punto 
    void MovePoint(const unsigned short nPointID, const Vector2f& v2fNewPosition);

    //mueve el punto 
    void MovePoint(const unsigned short nPointID, const float fNewPositionX, const float fNewPositionY);

    //pone una linea donde se referencia por dos Id de puntos, devuelve la id de la linea
    unsigned short AddLineSegment(const unsigned short nPoint1ID, const unsigned short nPoint2ID, const Color& color = sf::Color(255, 255, 255));

    //borra todo los segmentos
    void RemoveLineSegment(const unsigned short nLineSegmentID, bool bRemoveOrphanedPoints = true);

    //cambia el grosor de la linea
    void SetLineThickness(const float fLineThickness);

    //cambia el color de la linea
    void SetLineSegmentColor(const unsigned short nLineSegmentID, const Color& color);

    //devuelve el color
    const Color& GetLineSegmentColor(const unsigned short nLineSegmentID) const;

    //devuelve el numero de segmentos
    int GetNumLineSegments();

    //borra todo, todo
    void Clear();

protected:

    virtual void Render(const RenderWindow& Window);
    
protected:

    vector<PointInfo> m_vPoints;
    vector<LineSegmentInfo> m_vLineSegments;
    float m_fLineThickness;
    bool m_bIsDisplayListCurrent;
    int m_nDisplayListID;
};

#endif  
