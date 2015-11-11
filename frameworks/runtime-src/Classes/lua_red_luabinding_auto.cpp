#include "lua_red_luabinding_auto.hpp"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "red_luabinding.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_red_luabinding_UIThreadTask_push_task(lua_State* tolua_S)
{
    int argc = 0;
    UIThreadTask* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIThreadTask",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIThreadTask*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_red_luabinding_UIThreadTask_push_task'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void ()> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_red_luabinding_UIThreadTask_push_task'", nullptr);
            return 0;
        }
        cobj->push_task(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "UIThreadTask:push_task",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_red_luabinding_UIThreadTask_push_task'.",&tolua_err);
#endif

    return 0;
}
int lua_red_luabinding_UIThreadTask_do_tasks(lua_State* tolua_S)
{
    int argc = 0;
    UIThreadTask* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIThreadTask",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIThreadTask*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_red_luabinding_UIThreadTask_do_tasks'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_red_luabinding_UIThreadTask_do_tasks'", nullptr);
            return 0;
        }
        cobj->do_tasks();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "UIThreadTask:do_tasks",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_red_luabinding_UIThreadTask_do_tasks'.",&tolua_err);
#endif

    return 0;
}
int lua_red_luabinding_UIThreadTask_push_proto(lua_State* tolua_S)
{
    int argc = 0;
    UIThreadTask* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIThreadTask",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIThreadTask*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_red_luabinding_UIThreadTask_push_proto'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ValueMap arg0;

        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "UIThreadTask:push_proto");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_red_luabinding_UIThreadTask_push_proto'", nullptr);
            return 0;
        }
        cobj->push_proto(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "UIThreadTask:push_proto",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_red_luabinding_UIThreadTask_push_proto'.",&tolua_err);
#endif

    return 0;
}
int lua_red_luabinding_UIThreadTask_pop_protos(lua_State* tolua_S)
{
    int argc = 0;
    UIThreadTask* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIThreadTask",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIThreadTask*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_red_luabinding_UIThreadTask_pop_protos'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_red_luabinding_UIThreadTask_pop_protos'", nullptr);
            return 0;
        }
        cocos2d::ValueVector ret = cobj->pop_protos();
        ccvaluevector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "UIThreadTask:pop_protos",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_red_luabinding_UIThreadTask_pop_protos'.",&tolua_err);
#endif

    return 0;
}
int lua_red_luabinding_UIThreadTask_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"UIThreadTask",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_red_luabinding_UIThreadTask_getInstance'", nullptr);
            return 0;
        }
        UIThreadTask* ret = UIThreadTask::getInstance();
        object_to_luaval<UIThreadTask>(tolua_S, "UIThreadTask",(UIThreadTask*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "UIThreadTask:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_red_luabinding_UIThreadTask_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_red_luabinding_UIThreadTask_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (UIThreadTask)");
    return 0;
}

int lua_register_red_luabinding_UIThreadTask(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"UIThreadTask");
    tolua_cclass(tolua_S,"UIThreadTask","UIThreadTask","",nullptr);

    tolua_beginmodule(tolua_S,"UIThreadTask");
        tolua_function(tolua_S,"push_task",lua_red_luabinding_UIThreadTask_push_task);
        tolua_function(tolua_S,"do_tasks",lua_red_luabinding_UIThreadTask_do_tasks);
        tolua_function(tolua_S,"push_proto",lua_red_luabinding_UIThreadTask_push_proto);
        tolua_function(tolua_S,"pop_protos",lua_red_luabinding_UIThreadTask_pop_protos);
        tolua_function(tolua_S,"getInstance", lua_red_luabinding_UIThreadTask_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(UIThreadTask).name();
    g_luaType[typeName] = "UIThreadTask";
    g_typeCast["UIThreadTask"] = "UIThreadTask";
    return 1;
}

static int lua_red_luabinding_ConnDelegate_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ConnDelegate)");
    return 0;
}

int lua_register_red_luabinding_ConnDelegate(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ConnDelegate");
    tolua_cclass(tolua_S,"ConnDelegate","ConnDelegate","ConnDelegateImpl",nullptr);

    tolua_beginmodule(tolua_S,"ConnDelegate");
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(ConnDelegate).name();
    g_luaType[typeName] = "ConnDelegate";
    g_typeCast["ConnDelegate"] = "ConnDelegate";
    return 1;
}

int lua_red_luabinding_GameManager_protoService(lua_State* tolua_S)
{
    int argc = 0;
    GameManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_red_luabinding_GameManager_protoService'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_red_luabinding_GameManager_protoService'", nullptr);
            return 0;
        }
        ProtoServiceEntity* ret = cobj->protoService();
        object_to_luaval<ProtoServiceEntity>(tolua_S, "ProtoServiceEntity",(ProtoServiceEntity*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameManager:protoService",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_red_luabinding_GameManager_protoService'.",&tolua_err);
#endif

    return 0;
}
int lua_red_luabinding_GameManager_sendProto(lua_State* tolua_S)
{
    int argc = 0;
    GameManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_red_luabinding_GameManager_sendProto'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ValueMap arg0;

        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "GameManager:sendProto");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_red_luabinding_GameManager_sendProto'", nullptr);
            return 0;
        }
        cobj->sendProto(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameManager:sendProto",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_red_luabinding_GameManager_sendProto'.",&tolua_err);
#endif

    return 0;
}
int lua_red_luabinding_GameManager_connectService(lua_State* tolua_S)
{
    int argc = 0;
    GameManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_red_luabinding_GameManager_connectService'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_red_luabinding_GameManager_connectService'", nullptr);
            return 0;
        }
        ConnectService* ret = cobj->connectService();
        object_to_luaval<ConnectService>(tolua_S, "ConnectService",(ConnectService*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameManager:connectService",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_red_luabinding_GameManager_connectService'.",&tolua_err);
#endif

    return 0;
}
int lua_red_luabinding_GameManager_stop(lua_State* tolua_S)
{
    int argc = 0;
    GameManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_red_luabinding_GameManager_stop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_red_luabinding_GameManager_stop'", nullptr);
            return 0;
        }
        cobj->stop();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameManager:stop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_red_luabinding_GameManager_stop'.",&tolua_err);
#endif

    return 0;
}
int lua_red_luabinding_GameManager_connDelegate(lua_State* tolua_S)
{
    int argc = 0;
    GameManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_red_luabinding_GameManager_connDelegate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_red_luabinding_GameManager_connDelegate'", nullptr);
            return 0;
        }
        ConnDelegate* ret = cobj->connDelegate();
        object_to_luaval<ConnDelegate>(tolua_S, "ConnDelegate",(ConnDelegate*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameManager:connDelegate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_red_luabinding_GameManager_connDelegate'.",&tolua_err);
#endif

    return 0;
}
int lua_red_luabinding_GameManager_start(lua_State* tolua_S)
{
    int argc = 0;
    GameManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_red_luabinding_GameManager_start'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_red_luabinding_GameManager_start'", nullptr);
            return 0;
        }
        cobj->start();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameManager:start",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_red_luabinding_GameManager_start'.",&tolua_err);
#endif

    return 0;
}
int lua_red_luabinding_GameManager_init(lua_State* tolua_S)
{
    int argc = 0;
    GameManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_red_luabinding_GameManager_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_red_luabinding_GameManager_init'", nullptr);
            return 0;
        }
        cobj->init();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameManager:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_red_luabinding_GameManager_init'.",&tolua_err);
#endif

    return 0;
}
int lua_red_luabinding_GameManager_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"GameManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_red_luabinding_GameManager_getInstance'", nullptr);
            return 0;
        }
        GameManager* ret = GameManager::getInstance();
        object_to_luaval<GameManager>(tolua_S, "GameManager",(GameManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "GameManager:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_red_luabinding_GameManager_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_red_luabinding_GameManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GameManager)");
    return 0;
}

int lua_register_red_luabinding_GameManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"GameManager");
    tolua_cclass(tolua_S,"GameManager","GameManager","",nullptr);

    tolua_beginmodule(tolua_S,"GameManager");
        tolua_function(tolua_S,"protoService",lua_red_luabinding_GameManager_protoService);
        tolua_function(tolua_S,"sendProto",lua_red_luabinding_GameManager_sendProto);
        tolua_function(tolua_S,"connectService",lua_red_luabinding_GameManager_connectService);
        tolua_function(tolua_S,"stop",lua_red_luabinding_GameManager_stop);
        tolua_function(tolua_S,"connDelegate",lua_red_luabinding_GameManager_connDelegate);
        tolua_function(tolua_S,"start",lua_red_luabinding_GameManager_start);
        tolua_function(tolua_S,"init",lua_red_luabinding_GameManager_init);
        tolua_function(tolua_S,"getInstance", lua_red_luabinding_GameManager_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(GameManager).name();
    g_luaType[typeName] = "GameManager";
    g_typeCast["GameManager"] = "GameManager";
    return 1;
}
TOLUA_API int register_all_red_luabinding(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"red",0);
	tolua_beginmodule(tolua_S,"red");

	lua_register_red_luabinding_GameManager(tolua_S);
	lua_register_red_luabinding_UIThreadTask(tolua_S);
	lua_register_red_luabinding_ConnDelegate(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

#endif
