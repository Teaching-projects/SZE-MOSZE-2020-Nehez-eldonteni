/**
 * \class Renderer
 * 
 * \brief Renderer class
 * 
 * \author AnonymDavid
 * 
 * \version 1.1
 * 
 * \date 2020/12/01 13:26
 * 
 * Created on 2020/12/01 13:26
*/
#ifndef RENDERER_H
#define RENDERER_H

class Game;

class Renderer
{
public:
    /// Default constructor
    Renderer() {}
    /// Virtual destructor
    virtual ~Renderer() {}
    /**
	 * \brief This function draws the game to the predefined output
	 * \param game
	*/
	virtual void render(const Game&) const =0;
};

#endif