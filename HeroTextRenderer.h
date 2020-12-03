/**
 * \class HeroTextRenderer
 * 
 * \brief HeroTextRenderer class
 * 
 * \author AnonymDavid
 * 
 * \version 1.1
 * 
 * \date 2020/12/01 13:26
 * 
 * Created on 2020/12/01 13:26
*/
#ifndef HEROTEXTRENDERER_H
#define HEROTEXTRENDERER_H

#include <iostream>

#include "TextRenderer.h"

class HeroTextRenderer : public TextRenderer
{
public:
    /// Default constructor
    HeroTextRenderer() {}
    /// Constructor for ostream objects
    HeroTextRenderer(std::ostream& os):TextRenderer(os) {}
    /// Constructor for ostream pointers
    HeroTextRenderer(std::ostream* os):TextRenderer(os) {}

    /**
	 * \brief This function draws the game to the predefined output
	 * \param game
	*/
	virtual void render(const Game&) const;
};

#endif