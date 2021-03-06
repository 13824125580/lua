#include <stdio.h>
#include <math.h>
#define MAX_COLOR       255

#include "lauxlib.h"
#include "lualib.h"
/*#include "lstate.h"*/

static int add(int a, int b)
{
    return a+b;
}

static int sub(int a, int b)
{
    return a-b;
}

static int mul(int a, int b)
{
    return a*b;
}

static int lua_add_api(lua_State *L) 
{   
    //至少要有两个参数 
    if ((!lua_isinteger(L, 1)) || (!lua_isinteger(L, 2))) return 0; 

    int a = lua_tointeger(L, 1); 
    int b = lua_tointeger(L, 2); 
    int ret = add(a, b); 
    lua_pushnumber(L, ret); 
    return 1; 
}
static int lua_sub_api(lua_State *L) 
{ 
    //至少要有两个参数 
    if ((!lua_isinteger(L, 1)) || (!lua_isinteger(L, 2))) return 0; 
    
    int a = lua_tointeger(L, 1); 
    int b = lua_tointeger(L, 2); 
    int ret = sub(a, b); 
    lua_pushnumber(L, ret); 
    return 1; 
}

static int lua_mul_api(lua_State *L) 
{ 
    //至少要有两个参数 
    if ((!lua_isinteger(L, 1)) || (!lua_isinteger(L, 2))) return 0; 
    
    int a = lua_tointeger(L, 1); 
    int b = lua_tointeger(L, 2); 
    int ret = mul(a, b); 
    lua_pushnumber(L, ret); 

    return 1; 
}

static int luaope_api(lua_State* L) 
{ 
    static luaL_Reg ope_lib[] = { { "add", lua_add_api}, { "sub", lua_sub_api}, { "mul", lua_mul_api}, {NULL, NULL} }; 
    // 创建导出库函数 
    luaL_newlib(L, ope_lib); 
    return 1; 
}

void pre_loadlibs(lua_State* L) { 
    // 预加载扩展静态库 
    luaL_getsubtable(L, LUA_REGISTRYINDEX, "_PRELOAD"); 
    lua_pushcfunction(L, luaope_api); 
    lua_setfield(L, -2, "ope_api"); 
    lua_pop(L, 1); 
}


/*
参数lua_State，返回值为返回值的个数
在push结果的时候不需要清空栈，因为有表示结果个数的返回值，在函数返回后lua自动清除栈返回结果下面的内容
*/
static int l_sin(lua_State* L)
{
    double d = luaL_checknumber(L, 1);
    lua_pushnumber(L, sin(d));
    return 1;
}
/*
lua注册c库，将函数名和对应的函数指针传递到lua中，lua中用table去保存这些信息，lua那些c库也是这样实现的，这些table应该是lua全局变量
*/
int main(int argc, char *argv[])
{
    lua_State* L = luaL_newstate();
    // quick and dirty
    //函数入栈
    lua_pushcfunction(L, l_sin);
    //赋给全局，从栈中弹出一个值并将其设置成全局变量mysin
    lua_setglobal(L, "mysin");

    pre_loadlibs(L);
    getchar();

    return 0;
}
