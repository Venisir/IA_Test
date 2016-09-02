/* 
 * File:   DebugTest.h
 * Author: Albert
 *
 * Created on 7 de junio de 2016, 13:23
 */

#ifndef DEBUGTEST_H
#define	DEBUGTEST_H

#include "RenderableDebug.h"


class DebugTest: public RenderableDebug {
    public:
        DebugTest();
        virtual ~DebugTest();
        private:
            sf::Shape* shape;
};

#endif	/* DEBUGTEST_H */

