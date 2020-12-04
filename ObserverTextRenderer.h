/**
 * \class ObserverTextRenderer
 * 
 * \brief ObserverTextRenderer class
 * 
 * \author AnonymDavid
 * 
 * \version 1.1
 * 
 * \date 2020/12/01 13:26
 * 
 * Created on 2020/12/01 13:26
*/
#ifndef OBSERVERTEXTRENDERER_H
#define OBSERVERTEXTRENDERER_H

#include <iostream>
#include "TextRenderer.h"

class ObserverTextRenderer : public TextRenderer
{
public:
    /// Constructor for ostream objects
    ObserverTextRenderer(std::ostream& output):TextRenderer(output) {}
    /// Constructor for ostream pointers
    ObserverTextRenderer(std::ostream* output):TextRenderer(output) {}

    /**
	 * \brief This function draws the game to the predefined output
	 * \param game
	*/
	virtual void render(const Game&) const;
};

#endif