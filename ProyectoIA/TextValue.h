/* 
 * File:   TextValue.h
 * Author: Guillermo
 *
 * Created on 11 de julio de 2016, 12:48
 */

#ifndef TEXTVALUE_H
#define	TEXTVALUE_H
#include "RenderableDebug.h"

class TextValue : public RenderableDebug {
public:
    TextValue();
    virtual ~TextValue();
    sf::Text* GetValue() const;
    
    int x;
    int y;
    
private:
    sf::Text* value;
};

#endif	/* TEXTVALUE_H */

