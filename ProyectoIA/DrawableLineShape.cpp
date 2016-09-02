/* 
 * File:   DrawableLineShape.cpp
 * Author: oli92
 * 
 * Created on 8 de junio de 2016, 16:50
 */

#include "DrawableLineShape.h"

DrawableLineShape::DrawableLineShape() :
  m_fLineThickness(1.0f),
  m_bIsDisplayListCurrent(false)
{
    m_nDisplayListID = glGenLists(1);
}

DrawableLineShape::~DrawableLineShape()
{
    glDeleteLists(m_nDisplayListID, 1);
}

DrawableLineShape& DrawableLineShape::operator = (const DrawableLineShape& that)
{
    if (this != &that)
    {
        m_vPoints = that.m_vPoints;
        m_vLineSegments = that.m_vLineSegments;
        m_bIsDisplayListCurrent = that.m_bIsDisplayListCurrent;
    }

    return *this;
}

//anyade un punto a la linea, devuelve el id del punto
unsigned short DrawableLineShape::AddPoint(const sf::Vector2f& v2fPointPosition)
{
    //compruebo que no se este utilizando
    for (unsigned short i = 0; i < m_vPoints.size(); ++i)
    {
        if (!m_vPoints[i].bActive)
        {
            m_vPoints[i].v2fPoint = v2fPointPosition;
            m_vPoints[i].bActive = true;
            return i;
        }
    }

    //si no se utiliza se anyade
    m_vPoints.push_back(PointInfo(v2fPointPosition));
    return (unsigned short)(m_vPoints.size() - 1);

    m_bIsDisplayListCurrent = false;
}

//anyade un punto a la linea, devuelve el id del punto
unsigned short DrawableLineShape::AddPoint(const float fXPosition, const float fYPosition)
{
    return AddPoint(sf::Vector2f(fXPosition, fYPosition));
}

//quita el punto
void DrawableLineShape::RemovePoint(const unsigned short nPointID)
{
  
    m_vPoints[nPointID].bActive = false;

    //quita las linea que hacen referencia al punto
    for (unsigned int i = 0; i < m_vLineSegments.size(); ++i)
    {
        if (m_vLineSegments[i].bActive &&
            (m_vLineSegments[i].nPoint1 == nPointID ||
             m_vLineSegments[i].nPoint2 == nPointID))
            RemoveLineSegment(i);
    }
    m_bIsDisplayListCurrent = false;
}

//mueve el punto 
void DrawableLineShape::MovePoint(const unsigned short nPointID, const Vector2f& v2fNewPosition)
{
    m_vPoints[nPointID].v2fPoint = v2fNewPosition;
    m_bIsDisplayListCurrent = false;
}

//mueve el punto 
void DrawableLineShape::MovePoint(const unsigned short nPointID,
        const float fNewPositionX, const float fNewPositionY)
{
    m_vPoints[nPointID].v2fPoint.x = fNewPositionX;
    m_vPoints[nPointID].v2fPoint.y = fNewPositionY;
    m_bIsDisplayListCurrent = false;
}

//pone una linea donde se referencia por dos Id de puntos, devuelve la id de la linea
unsigned short DrawableLineShape::AddLineSegment(
        const unsigned short nPoint1ID, const unsigned short nPoint2ID, const sf::Color& color)
{
    //se ve si se esta utilizando la linea
    for (unsigned short = 0; i < m_vLineSegments.size(); ++i)
    {
        if (!m_vLineSegments[i].bActive)
        {
            m_vLineSegments[i].nPoint1 = nPoint1ID;
            m_vLineSegments[i].nPoint2 = nPoint2ID;
            m_vLineSegments[i].color = color;
            m_vLineSegments[i].bActive = true;
            return (unsigned short)i;
        }
    }
    //sino ,se crea
    m_vLineSegments.push_back(LineSegmentInfo(nPoint1ID, nPoint2ID, color));
    return (unsigned short)(m_vLineSegments.size() - 1);
    m_bIsDisplayListCurrent = false;
}

//borra todo los segmentos
void DrawableLineShape::RemoveLineSegment(const unsigned short nLineSegmentID, bool bRemoveOrphanedPoints)
{
    m_vLineSegments[nLineSegmentID].bActive = false;
    if (bRemoveOrphanedPoints)
    {
        unsigned short nPointID1 = m_vLineSegments[nLineSegmentID].nPoint1;
        unsigned short nPointID2 = m_vLineSegments[nLineSegmentID].nPoint2;
        bool bPoint1Referenced = false;
        bool bPoint2Referenced = false;

        for (unsigned int nLineIndex = 0; nLineIndex < m_vLineSegments.size(); ++nLineIndex)
        {
            if (!m_vLineSegments[nLineIndex].bActive)
                continue;
            if (m_vLineSegments[nLineIndex].nPoint1 == nPointID1 ||
                m_vLineSegments[nLineIndex].nPoint2 == nPointID1)
                bPoint1Referenced = true;
            if (m_vLineSegments[nLineIndex].nPoint1 == nPointID2 ||
                m_vLineSegments[nLineIndex].nPoint2 == nPointID2)
                bPoint2Referenced = true;
            if (bPoint1Referenced && bPoint2Referenced)
                break;
        }

        if (!bPoint1Referenced)
            m_vPoints[nPointID1].bActive = false;
        if (!bPoint2Referenced)
            m_vPoints[nPointID2].bActive = false;
    }
    m_bIsDisplayListCurrent = false;
}

//cambia el grosor de la linea
void DrawableLineShape::SetLineThickness(const float fLineThickness)
{
    m_fLineThickness = fLineThickness;
    m_bIsDisplayListCurrent = false;
}

//cambia el color de la linea
void DrawableLineShape::SetLineSegmentColor(
        const unsigned short nLineSegmentID, const sf::Color& color)
{
    m_vLineSegments[nLineSegmentID].color = color;
    m_bIsDisplayListCurrent = false;
}

//devuelve el color
const Color& DrawableLineShape::GetLineSegmentColor(const unsigned short nLineSegmentID) const
{
    return m_vLineSegments[nLineSegmentID].color;
}


//devuelve el numero de segmentos
int DrawableLineShape::GetNumLineSegments()
{
    int nNumLineSegments = 0;
    for (unsigned int i = 0; i < m_vLineSegments.size(); ++i)
    {
        if (m_vLineSegments[i].bActive)
            ++nNumLineSegments;
    }

    return nNumLineSegments;
}

//borra todo, todo
void DrawableLineShape::Clear()
{
    unsigned int i;
    for (i = 0; i < m_vPoints.size(); ++i)
        m_vPoints[i].bActive = false;
    for (i = 0; i < m_vLineSegments.size(); ++i)
        m_vLineSegments[i].bActive = false;
    m_bIsDisplayListCurrent = false;
}

void DrawableLineShape::Render(const RenderWindow& Window)
{
    if (m_bIsDisplayListCurrent)
    {
        glCallList(m_nDisplayListID);
        return;
    }
    if (m_vLineSegments.size() < 1)
        return;

    glNewList(m_nDisplayListID, GL_COMPILE_AND_EXECUTE);
    //no se usa texturas
    glDisable(GL_TEXTURE_2D);
    //dibujo
    Color lineColor;
    Vector2f v2fLinePoint1, v2fLinePoint2;
    //cambia el grosor
    glLineWidth(m_fLineThickness);
    glBegin(GL_LINES);
    for (unsigned int i = 0; i < m_vLineSegments.size(); ++i)
    {
        if (!m_vLineSegments[i].bActive)
            continue;

        //cambia el color
        lineColor = m_vLineSegments[i].color;
        glColor4ub(lineColor.r, lineColor.g, lineColor.b, lineColor.a);
        v2fLinePoint1 = m_vPoints[m_vLineSegments[i].nPoint1].v2fPoint;
        v2fLinePoint2 = m_vPoints[m_vLineSegments[i].nPoint2].v2fPoint;
        glVertex2f(v2fLinePoint1.x, v2fLinePoint1.y);
        glVertex2f(v2fLinePoint2.x, v2fLinePoint2.y);
    }
    glEnd();
    glEndList();
    m_bIsDisplayListCurrent = true;
}