#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define WATCHER_MARK        1 << 1
#define MAKER_MARK          1


#ifdef __DEBUG__

static inline void byte_print(unsigned char a) {
    char s[9];
    itoa((int)a, s, 2);
    printf("%s\n", s);
}

#define deep_print(format,...) printf(format, ##__VA_ARGS__)
#define bin_print(a) byte_print(a)

#else

#define deep_print(format,...)
#define bin_print(a)

#endif

#define MT_NAME ("_aoi_metatable")

struct map {
    int width;
    int height;
    int grid_w;
    int grid_h;

    int max_row;
    int max_col;
};

static int _aoi_add(lua_State *L) {
    return 0;
}

static int _aoi_remove(lua_State *L) {
    return 0;
}

static int _aoi_set(lua_State *L) {
    return 0;
}

static int _aoi_update(lua_State *L) {
    return 0;
}

static int _aoi_get_objs_by_obj(lua_State *L) {
    return 0;
}

static int
gc(lua_State *L) {
    return 0;
}

static int
lmetatable(lua_State *L) {
    if (luaL_newmetatable(L, MT_NAME)) {
        luaL_Reg l[] = {
            {"aoi_add", _aoi_add},
            {"aoi_remove", _aoi_remove},
            {"aoi_set", _aoi_set},
            {"aoi_update", _aoi_update},
            {"aoi_get_objs_by_obj", _aoi_get_objs_by_obj},
            { NULL, NULL }
        };
        luaL_newlib(L, l);
        lua_setfield(L, -2, "__index");

        lua_pushcfunction(L, gc);
        lua_setfield(L, -2, "__gc");
    }
    return 1;
}

static int
lnew_aoiobject(lua_State *L) {
    lua_settop(L, 4);
    int mw = lua_tointeger(L, -1);
    int mh = lua_tointeger(L, -2);
    int gw = lua_tointeger(L, -3);
    int gh = lua_tointeger(L, -4);
    lua_assert(mw > 0 && mh > 0 && gw > 0 && gh > 0 && gw <= mw && gh <= mh);
    struct map *m = lua_newuserdata(L, sizeof(struct map));
    m->width = mw;
    m->height = mh;
    m->grid_w = gw;
    m->grid_h = gh;
    m->max_row = ceil(mw / gw);
    m->max_col = ceil(mh / gh);

    lmetatable(L);
    lua_setmetatable(L, -2);
    return 1;
}

LUAMOD_API int
luaopen_aoi(lua_State *L) {
    luaL_checkversion(L);
    luaL_Reg l[] = {
        { "aoi_new", lnew_aoiobject },
        { NULL, NULL },
    };
    luaL_newlib(L, l);
    lua_pushinteger(L, WATCHER_MARK);
    lua_setfield(L, -2, "WATCHER_MARK");
    lua_pushinteger(L, MAKER_MARK);
    lua_setfield(L, -2, "MAKER_MARK");
    return 1;
}
