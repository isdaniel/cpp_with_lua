
#include <iostream>
#include <string>

using namespace std;

extern "C" {
#include "lua-5.4.2/include/lua.h"
#include "lua-5.4.2/include/lauxlib.h"
#include "lua-5.4.2/include/lualib.h"
}

#pragma comment(lib,"lua-5.4.2/lua54.lib")

int main()
{
    

    string cmd = "a = 12 + 1";

    lua_State* L = luaL_newstate();
    
    int r = luaL_dostring(L,cmd.c_str());

    if (r == LUA_OK)
    {
        lua_getglobal(L, "a");
        if (lua_isnumber(L,-1))
        {
            double val = (double)lua_tonumber(L,-1);
            cout << "val is :" << val << endl;
        }
    }
    else {
        string errormsg = lua_tostring(L, -1);
        cout << errormsg << endl;
    }

    system("pause");
    lua_close(L);
    return 0;
}

