/**
 * \class CharacterSVGRenderer
 * 
 * \brief CharacterSVGRenderer class
 * 
 * \author AnonymDavid
 * 
 * \version 1.1
 * 
 * \date 2020/12/02 13:26
 * 
 * Created on 2020/12/02 13:26
*/
#ifndef CHARACTERSVGRENDERER_H
#define CHARACTERSVGRENDERER_H

#include <iostream>

#include "SVGRenderer.h"

class CharacterSVGRenderer : public SVGRenderer
{
public:
    /// Constructor that sets the output filename
    CharacterSVGRenderer(std::string filename):SVGRenderer(filename) {}
    
    /**
	 * \brief This function draws the game to the predefined output
	 * \param game
	*/
	virtual void render(const Game&) const;
};

#endif