#include "stdafx.h"
// Maps all the vk keys to a more accessible class (intellisense yay!)
class KeyCodes
{
//------------------------ Virtual key mapping ----------------------------------------
public:
	// Alphabet
	static const unsigned int A = 0x41;
	static const unsigned int B = 0x42;
	static const unsigned int C = 0x43;
	static const unsigned int D = 0x44;
	static const unsigned int E = 0x45;
	static const unsigned int F = 0x46;
	static const unsigned int G = 0x47;
	static const unsigned int H = 0x48;
	static const unsigned int I = 0x49;
	static const unsigned int J = 0x4A;
	static const unsigned int K = 0x4B;
	static const unsigned int L = 0x4C;
	static const unsigned int M = 0x4D;
	static const unsigned int N = 0x4E;
	static const unsigned int O = 0x4F;
	static const unsigned int P = 0x50;
	static const unsigned int Q = 0x51;
	static const unsigned int R = 0x52;
	static const unsigned int S = 0x53;
	static const unsigned int T = 0x54;
	static const unsigned int U = 0x55;
	static const unsigned int V = 0x56;
	static const unsigned int W = 0x57;
	static const unsigned int X = 0x58;
	static const unsigned int Y = 0x59;
	static const unsigned int Z = 0x5A;

	// Numbers
	static const unsigned int Num_0 = 0x30;
	static const unsigned int Num_1 = 0x31;
	static const unsigned int Num_2 = 0x32;
	static const unsigned int Num_3 = 0x33;
	static const unsigned int Num_4 = 0x34;
	static const unsigned int Num_5 = 0x35;
	static const unsigned int Num_6 = 0x36;
	static const unsigned int Num_7 = 0x37;
	static const unsigned int Num_8 = 0x38;
	static const unsigned int Num_9 = 0x39;

	// Num pad.
	static const unsigned int NumPad_0 = VK_NUMPAD0;
	static const unsigned int NumPad_1 = VK_NUMPAD1;
	static const unsigned int NumPad_2 = VK_NUMPAD2;
	static const unsigned int NumPad_3 = VK_NUMPAD3;
	static const unsigned int NumPad_4 = VK_NUMPAD4;
	static const unsigned int NumPad_5 = VK_NUMPAD5;
	static const unsigned int NumPad_6 = VK_NUMPAD6;
	static const unsigned int NumPad_7 = VK_NUMPAD7;
	static const unsigned int NumPad_8 = VK_NUMPAD8;
	static const unsigned int NumPad_9 = VK_NUMPAD9;

	// Mouse
	static const unsigned int Mouse_L	= VK_LBUTTON;
	static const unsigned int Mouse_R	= VK_RBUTTON;
	static const unsigned int Mouse_X1 = VK_XBUTTON1;
	static const unsigned int Mouse_X2 = VK_XBUTTON2;
	static const unsigned int Mouse_M  = VK_MBUTTON;

	// Function Keys
	static const unsigned int F1 = VK_F1;
	static const unsigned int F2 = VK_F2;
	static const unsigned int F3 = VK_F3;
	static const unsigned int F4 = VK_F4;
	static const unsigned int F5 = VK_F5;
	static const unsigned int F6 = VK_F6;
	static const unsigned int F7 = VK_F7;
	static const unsigned int F8 = VK_F8;
	static const unsigned int F9 = VK_F9;
	static const unsigned int F10 = VK_F10;
	static const unsigned int F11 = VK_F11;
	static const unsigned int F12 = VK_F12;
	static const unsigned int F13 = VK_F13;
	static const unsigned int F14 = VK_F14;
	static const unsigned int F15 = VK_F15;
	static const unsigned int F16 = VK_F16;
	static const unsigned int F17 = VK_F17;
	static const unsigned int F18 = VK_F18;
	static const unsigned int F19 = VK_F19;
	static const unsigned int F20 = VK_F20;
	static const unsigned int F21 = VK_F21;
	static const unsigned int F22 = VK_F22;
	static const unsigned int F23 = VK_F23;
	static const unsigned int F24 = VK_F24;

	// Special Characters
	static const unsigned int Tilde = VK_OEM_3;

	// Control Keys
	static const unsigned int ALT	= VK_MENU;
	static const unsigned int UP	= VK_UP;
	static const unsigned int DOWN	= VK_DOWN;
	static const unsigned int RIGHT	= VK_RIGHT;
	static const unsigned int LEFT	= VK_LEFT;
	static const unsigned int ENTER	= VK_RETURN;
	static const unsigned int BACKSPACE = VK_BACK;
	static const unsigned int ESCAPE= VK_ESCAPE;
	static const unsigned int DELETE_B = VK_DELETE;
	static const unsigned int SPACE	= VK_SPACE;
	static const unsigned int SHIFT = VK_SHIFT;
	static const unsigned int CTRL	= VK_CONTROL;
};