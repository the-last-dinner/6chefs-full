#ifndef  _DEFINE_H_
#define  _DEFINE_H_
#define WIDTH 800
#define HEIGHT 600
#define MAX_COUNT 60

enum struct Key
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MENU,
	DASH,
	SPACE
};

enum struct GameState
{
	WAIT,
	TITLE_MAIN,
	TITLE_LOAD
};
#endif // _DEFINE_H_