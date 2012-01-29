#pragma once
#include <ctime>
class Stats
{
public:	
	static POINT	getResolution();
	static POINT	getScreenSize();
	static POINT	getMouse();
	static void		getMouseNormalized(float* float_point);

	static void		setResolution(int x, int y);
	static void		setScreenSize(RECT r);
	static void		setMouse(POINT p);
	static void		update();

	// Time elapsed from the last update, in seconds.
	static float	dt();
	// Time elapsed from the beginng of the program.
	static int		timeSinceStart();
	static void		startFPS();
	static void		endFPS();
	static float	getFPS();

	static int		getTilesize();

	static void		setMapsize(int x, int y);
	static POINT	getMapsize();

	static int		getGloryRate();

private:	
	static void		evalMouse();
	Stats(void);
	~Stats(void);

};

	