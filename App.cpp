#include "App.h"

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;
	
	game = new Game("../includes/map3.txt");
}

void App::draw() {
	game->refresh();
	
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	for (int i = 0; i < game->getBoardSize(); i++) {
		for (int j = 0; j < game->getBoardSize(i); j++) {
			glColor3d( game->getBoardRed(i,j), game->getBoardGreen(i,j), game->getBoardBlue(i,j) );
			glPolygonMode(GL_FRONT, GL_FILL);
			glBegin(GL_POLYGON);

			glVertex2f(game->getBoardX(i,j), game->getBoardY(i,j));
			glVertex2f(game->getBoardX(i,j) + game->getBoardWidth(i,j), game->getBoardY(i,j));
			glVertex2f(game->getBoardX(i,j) + game->getBoardWidth(i,j), game->getBoardY(i,j) - game->getBoardHeight(i,j));
			glVertex2f(game->getBoardX(i,j), game->getBoardY(i,j) - game->getBoardHeight(i,j));

			glEnd();
		}
	}
	
	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();

	if (game->isWon()) {
		system("PAUSE");
		exit(0);
	}
}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;
	
	game->onClick(mx, my);
    
    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }
	game->onPress(key);
	
	redraw();
}
