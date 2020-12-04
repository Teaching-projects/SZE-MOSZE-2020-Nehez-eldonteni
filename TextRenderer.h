/**
 * \class TextRenderer
 * 
 * \brief TextRenderer class
 * 
 * \author AnonymDavid
 * 
 * \version 1.1
 * 
 * \date 2020/12/01 13:26
 * 
 * Created on 2020/12/01 13:26
*/
#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <iostream>
#include <ostream>

#include "Renderer.h"

class TextRenderer : public Renderer
{
public:
    /// Default constructor that sets the default output to std::cout
    TextRenderer(): outputStream(&std::cout) { }
    /// Constructor for ostream objects
    TextRenderer(std::ostream& os): outputStream(&os) {}
    /// Constructor for ostream pointers
    TextRenderer(std::ostream* os): outputStream(os) {}

	/**
	 * \brief This function draws the game to the predefined output
	 * \param game
	*/
	virtual void render(const Game&) const =0;
    /**
	 * \brief This function sets the output stream
	 * \param os
	*/
    virtual void setOutputStream(std::ostream& os) const {
        outputStream = &os;
    }

protected:
    mutable std::ostream* outputStream; ///< The output for the derived classes
};

#endif