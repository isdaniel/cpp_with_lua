
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

extern "C" {
#include "lua-5.4.2/include/lua.h"
#include "lua-5.4.2/include/lauxlib.h"
#include "lua-5.4.2/include/lualib.h"
}

#pragma comment(lib,"lua-5.4.2/lua54.lib")

bool CheckLua(lua_State* L, int r) {
	if (r != LUA_OK)
	{
		string errormsg = lua_tostring(L, -1);
		cout << errormsg << endl;
		return false;
	}
	return true;
}

int CppHost_Function(lua_State* L) {
	float a = (float)lua_tonumber(L, 1);
	float b = (float)lua_tonumber(L, 2);
	cout << "[C++] CppHost_Function (" << a << ", " << b << ") called" << endl;
	float c = a * b;
	lua_pushnumber(L, c);
	return 1;
}

int main()
{


	string cmd = "a = 12 + 1 + math.sin(10.88)";

	lua_State* L = luaL_newstate();

	//add basic library
	luaL_openlibs(L);

#pragma region basic way
	//int r = luaL_dostring(L, cmd.c_str());
	//if (r == LUA_OK)
	//{
	//    lua_getglobal(L, "a");
	//    if (lua_isnumber(L,-1))
	//    {
	//        double val = (double)lua_tonumber(L,-1);
	//        cout << "val is :" << val << endl;
	//    }
	//}
	//else {
	//    string errormsg = lua_tostring(L, -1);
	//    cout << errormsg << endl;
	//}
#pragma endregion

#pragma region file read lua
	//if (CheckLua(L, luaL_dofile(L, "lab-script.lua")))
	//{
	//	lua_getglobal(L, "a");
	//	if (lua_isnumber(L, -1))
	//	{
	//		double val = (double)lua_tonumber(L, -1);
	//		cout << "val is :" << val << endl;
	//	}
	//}
#pragma endregion

	struct Player
	{
		string title;
		string name;
		string family;
		int level;
	} player;

#pragma region read one by one
	/*if (CheckLua(L, luaL_dofile(L, "lab-script.lua")))
	{
		lua_getglobal(L, "t");
		player.title = lua_tostring(L, -1);
		lua_getglobal(L, "n");
		player.name = lua_tostring(L, -1);
		lua_getglobal(L, "f");
		player.family = lua_tostring(L, -1);
		lua_getglobal(L, "l");
		player.level = (int)lua_tonumber(L, -1);
		cout << "player.title is :" << player.title << endl
			<< "player.name is :" << player.name << endl
			<< "player.family is :" << player.family << endl
			<< "player.level is :" << player.level << endl;
	}*/
#pragma endregion

#pragma region lua function call
	//if (CheckLua(L, luaL_dofile(L, "lab-script.lua")))
	//{
	//	lua_getglobal(L, "Add");
	//	if (lua_isfunction(L,-1))
	//	{
	//		lua_pushnumber(L, 5.5f);
	//		lua_pushnumber(L, 4.5f);

	//		if (CheckLua(L,lua_pcall(L,2,1,0)))
	//		{
	//			cout << "val is " << (float)lua_tonumber(L,-1) << endl;
	//		}
	//	}
	//}
#pragma endregion

	lua_register(L, "Cpp_Function", CppHost_Function);

	if (CheckLua(L, luaL_dofile(L, "lab-script.lua"))) {
		lua_getglobal(L, "DoSomething");
		if (lua_isfunction(L, -1))
		{
			lua_pushnumber(L, 5.5f);
			lua_pushnumber(L, 4.5f);

			if (CheckLua(L, lua_pcall(L, 2, 1, 0)))
			{
				cout << "val is " << (float)lua_tonumber(L, -1) << endl;
			}
		}

	}

	system("pause");
	lua_close(L);
	return 0;
}

