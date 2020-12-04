/**
 * \class SVGRenderer
 * 
 * \brief SVGRenderer class
 * 
 * \author AnonymDavid
 * 
 * \version 1.1
 * 
 * \date 2020/12/02 13:26
 * 
 * Created on 2020/12/02 13:26
*/
#ifndef SVGRENDERER_H
#define SVGRENDERER_H

#include <iostream>
#include <fstream>

#include "Renderer.h"

class SVGRenderer : public Renderer
{
public:
    /// Constructor that sets the output filename
    SVGRenderer(std::string _filename):filename(_filename) { }

	/**
	 * \brief This function draws the game to the predefined output
	 * \param game
	*/
	virtual void render(const Game&) const =0;

protected:
    std::string filename; ///< String containing the output filename
};

#endif