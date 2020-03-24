#include "squirrel.h"
#include "sqmodule.h"

extern HSQAPI sq;

/*vm*/
SQUIRREL_API HSQUIRRELVM sq_open(SQInteger initialstacksize) {
	return sq->open(initialstacksize);
}
SQUIRREL_API HSQUIRRELVM sq_newthread(HSQUIRRELVM friendvm, SQInteger initialstacksize) {
	return sq->newthread(friendvm, initialstacksize);
}
SQUIRREL_API void sq_seterrorhandler(HSQUIRRELVM v) {
	return sq->seterrorhandler(v);
}
SQUIRREL_API void sq_close(HSQUIRRELVM v) {
	return sq->close(v);
}
SQUIRREL_API void sq_setforeignptr(HSQUIRRELVM v, SQUserPointer p) {
	return sq->setforeignptr(v, p);
}
SQUIRREL_API SQUserPointer sq_getforeignptr(HSQUIRRELVM v) {
	return sq->getforeignptr(v);
}
/*SQUIRREL_API void sq_setsharedforeignptr(HSQUIRRELVM v, SQUserPointer p) {
	return sq->setsharedforeignptr(v, p);
}
SQUIRREL_API SQUserPointer sq_getsharedforeignptr(HSQUIRRELVM v) {
	return sq->getsharedforeignptr(v);
}
SQUIRREL_API void sq_setvmreleasehook(HSQUIRRELVM v, SQRELEASEHOOK hook) {
	return sq->setvmreleasehook(v, hook);
}
SQUIRREL_API SQRELEASEHOOK sq_getvmreleasehook(HSQUIRRELVM v) {
	return sq->getvmreleasehook(v);
}
SQUIRREL_API void sq_setsharedreleasehook(HSQUIRRELVM v, SQRELEASEHOOK hook) {
	sq.sets
}*/
/*SQUIRREL_API SQRELEASEHOOK sq_getsharedreleasehook(HSQUIRRELVM v) {

}*/
SQUIRREL_API void sq_setprintfunc(HSQUIRRELVM v, SQPRINTFUNCTION printfunc, SQPRINTFUNCTION errfunc) {
	return sq->setprintfunc(v, printfunc, errfunc);
}
SQUIRREL_API SQPRINTFUNCTION sq_getprintfunc(HSQUIRRELVM v) {
	return sq->getprintfunc(v);
}
/*SQUIRREL_API SQPRINTFUNCTION sq_geterrorfunc(HSQUIRRELVM v) {
	s
}*/
SQUIRREL_API SQRESULT sq_suspendvm(HSQUIRRELVM v) {
	return sq->suspendvm(v);
}
SQUIRREL_API SQRESULT sq_wakeupvm(HSQUIRRELVM v, SQBool resumedret, SQBool retval, SQBool raiseerror, SQBool throwerror) {
	return sq->wakeupvm(v, resumedret, retval, raiseerror, throwerror);
}
SQUIRREL_API SQInteger sq_getvmstate(HSQUIRRELVM v) {
	return sq->getvmstate(v);
}
/*SQUIRREL_API SQInteger sq_getversion() {
	retur
}*/

/*compiler*/
SQUIRREL_API SQRESULT sq_compile(HSQUIRRELVM v, SQLEXREADFUNC read, SQUserPointer p, const SQChar *sourcename, SQBool raiseerror) {
	return sq->compile(v, read, p, sourcename, raiseerror);
}
SQUIRREL_API SQRESULT sq_compilebuffer(HSQUIRRELVM v, const SQChar *s, SQInteger size, const SQChar *sourcename, SQBool raiseerror) {
	return sq->compilebuffer(v, s, size, sourcename, raiseerror);
}
SQUIRREL_API void sq_enabledebuginfo(HSQUIRRELVM v, SQBool enable) {
	return sq->enabledebuginfo(v, enable);
}
SQUIRREL_API void sq_notifyallexceptions(HSQUIRRELVM v, SQBool enable) {
	return sq->notifyallexceptions(v, enable);
}
SQUIRREL_API void sq_setcompilererrorhandler(HSQUIRRELVM v, SQCOMPILERERROR f) {
	return sq->setcompilererrorhandler(v, f);
}

/*stack operations*/
SQUIRREL_API void sq_push(HSQUIRRELVM v, SQInteger idx) {
	return sq->push(v, idx);
}
SQUIRREL_API void sq_pop(HSQUIRRELVM v, SQInteger nelemstopop) {
	return sq->pop(v, nelemstopop);
}
SQUIRREL_API void sq_poptop(HSQUIRRELVM v) {
	return sq->poptop(v);
}
SQUIRREL_API void sq_remove(HSQUIRRELVM v, SQInteger idx) {
	return sq->remove(v, idx);
}
SQUIRREL_API SQInteger sq_gettop(HSQUIRRELVM v) {
	return sq->gettop(v);
}
SQUIRREL_API void sq_settop(HSQUIRRELVM v, SQInteger newtop) {
	return sq->settop(v, newtop);
}
SQUIRREL_API SQRESULT sq_reservestack(HSQUIRRELVM v, SQInteger nsize) {
	return sq->reservestack(v, nsize);
}
SQUIRREL_API SQInteger sq_cmp(HSQUIRRELVM v) {
	return sq->cmp(v);
}
SQUIRREL_API void sq_move(HSQUIRRELVM dest, HSQUIRRELVM src, SQInteger idx) {
	return sq->move(dest, src, idx);
}

/*object creation handling*/
SQUIRREL_API SQUserPointer sq_newuserdata(HSQUIRRELVM v, SQUnsignedInteger size) {
	return sq->newuserdata(v, size);
}
SQUIRREL_API void sq_newtable(HSQUIRRELVM v) {
	return sq->newtable(v);
}
/*SQUIRREL_API void sq_newtableex(HSQUIRRELVM v, SQInteger initialcapacity) {
	return sq->newtabl
}*/
SQUIRREL_API void sq_newarray(HSQUIRRELVM v, SQInteger size) {
	return sq->newarray(v, size);
}
SQUIRREL_API void sq_newclosure(HSQUIRRELVM v, SQFUNCTION func, SQUnsignedInteger nfreevars) {
	return sq->newclosure(v, func, nfreevars);
}
SQUIRREL_API SQRESULT sq_setparamscheck(HSQUIRRELVM v, SQInteger nparamscheck, const SQChar *typemask) {
	return sq->setparamscheck(v, nparamscheck, typemask);
}
SQUIRREL_API SQRESULT sq_bindenv(HSQUIRRELVM v, SQInteger idx) {
	return sq->bindenv(v, idx);
}
/*SQUIRREL_API SQRESULT sq_setclosureroot(HSQUIRRELVM v, SQInteger idx) {
	sq.setclosureroo
}*/
/*SQUIRREL_API SQRESULT sq_getclosureroot(HSQUIRRELVM v, SQInteger idx) {
	sq.getc
}*/
SQUIRREL_API void sq_pushstring(HSQUIRRELVM v, const SQChar *s, SQInteger len) {
	return sq->pushstring(v, s, len);
}
SQUIRREL_API void sq_pushfloat(HSQUIRRELVM v, SQFloat f) {
	return sq->pushfloat(v, f);
}
SQUIRREL_API void sq_pushinteger(HSQUIRRELVM v, SQInteger n) {
	return sq->pushinteger(v, n);
}
SQUIRREL_API void sq_pushbool(HSQUIRRELVM v, SQBool b) {
	return sq->pushbool(v, b);
}
SQUIRREL_API void sq_pushuserpointer(HSQUIRRELVM v, SQUserPointer p) {
	return sq->pushuserpointer(v, p);
}
SQUIRREL_API void sq_pushnull(HSQUIRRELVM v) {
	return sq->pushnull(v);
}
/*SQUIRREL_API void sq_pushthread(HSQUIRRELVM v, HSQUIRRELVM thread) {
	return sq->pushth
}*/
SQUIRREL_API SQObjectType sq_gettype(HSQUIRRELVM v, SQInteger idx) {
	return sq->gettype(v, idx);
}
/*SQUIRREL_API SQRESULT sq_typeof(HSQUIRRELVM v, SQInteger idx) {
	return sq->typeof_(v, idx);
}*/
SQUIRREL_API SQInteger sq_getsize(HSQUIRRELVM v, SQInteger idx) {
	return sq->getsize(v, idx);
}
/*SQUIRREL_API SQHash sq_gethash(HSQUIRRELVM v, SQInteger idx) {
	sq.gethash
}*/
SQUIRREL_API SQRESULT sq_getbase(HSQUIRRELVM v, SQInteger idx) {
	return sq->getbase(v, idx);
}
SQUIRREL_API SQBool sq_instanceof(HSQUIRRELVM v) {
	return sq->instanceof(v);
}
SQUIRREL_API SQRESULT sq_tostring(HSQUIRRELVM v, SQInteger idx) {
	return sq->tostring(v, idx);
}
SQUIRREL_API void sq_tobool(HSQUIRRELVM v, SQInteger idx, SQBool *b) {
	return sq->tobool(v, idx, b);
}
/*SQUIRREL_API SQRESULT sq_getstringandsize(HSQUIRRELVM v, SQInteger idx, const SQChar **c, SQInteger *size) {
	sq.gets
}*/
SQUIRREL_API SQRESULT sq_getstring(HSQUIRRELVM v, SQInteger idx, const SQChar **c) {
	return sq->getstring(v, idx, c);
}
SQUIRREL_API SQRESULT sq_getinteger(HSQUIRRELVM v, SQInteger idx, SQInteger *i) {
	return sq->getinteger(v, idx, i);
}
SQUIRREL_API SQRESULT sq_getfloat(HSQUIRRELVM v, SQInteger idx, SQFloat *f) {
	return sq->getfloat(v, idx, f);
}
SQUIRREL_API SQRESULT sq_getbool(HSQUIRRELVM v, SQInteger idx, SQBool *b) {
	return sq->getbool(v, idx, b);
}
SQUIRREL_API SQRESULT sq_getthread(HSQUIRRELVM v, SQInteger idx, HSQUIRRELVM *thread) {
	return sq->getthread(v, idx, thread);
}
SQUIRREL_API SQRESULT sq_getuserpointer(HSQUIRRELVM v, SQInteger idx, SQUserPointer *p) {
	return sq->getuserpointer(v, idx, p);
}
SQUIRREL_API SQRESULT sq_getuserdata(HSQUIRRELVM v, SQInteger idx, SQUserPointer *p, SQUserPointer *typetag) {
	return sq->getuserdata(v, idx, p, typetag);
}
SQUIRREL_API SQRESULT sq_settypetag(HSQUIRRELVM v, SQInteger idx, SQUserPointer typetag) {
	return sq->settypetag(v, idx, typetag);
}
SQUIRREL_API SQRESULT sq_gettypetag(HSQUIRRELVM v, SQInteger idx, SQUserPointer *typetag) {
	return sq->gettypetag(v, idx, typetag);
}
SQUIRREL_API void sq_setreleasehook(HSQUIRRELVM v, SQInteger idx, SQRELEASEHOOK hook) {
	return sq->setreleasehook(v, idx, hook);
}
/*SQUIRREL_API SQRELEASEHOOK sq_getreleasehook(HSQUIRRELVM v, SQInteger idx) {
	sq.getrel
}*/
SQUIRREL_API SQChar *sq_getscratchpad(HSQUIRRELVM v, SQInteger minsize) {
	return sq->getscratchpad(v, minsize);
}
/*SQUIRREL_API SQRESULT sq_getfunctioninfo(HSQUIRRELVM v, SQInteger level, SQFunctionInfo *fi) {
	sq.getfun
}*/
SQUIRREL_API SQRESULT sq_getclosureinfo(HSQUIRRELVM v, SQInteger idx, SQInteger *nparams, SQInteger *nfreevars) {
	return sq->getclosureinfo(v, idx, (SQUnsignedInteger*) nparams, (SQUnsignedInteger*) nfreevars);
}
/*SQUIRREL_API SQRESULT sq_getclosurename(HSQUIRRELVM v, SQInteger idx) {
	s
}*/
SQUIRREL_API SQRESULT sq_setnativeclosurename(HSQUIRRELVM v, SQInteger idx, const SQChar *name) {
	return sq->setnativeclosurename(v, idx, name);
}
SQUIRREL_API SQRESULT sq_setinstanceup(HSQUIRRELVM v, SQInteger idx, SQUserPointer p) {
	return sq->setinstanceup(v, idx, p);
}
SQUIRREL_API SQRESULT sq_getinstanceup(HSQUIRRELVM v, SQInteger idx, SQUserPointer *p, SQUserPointer typetag) {
	return sq->getinstanceup(v, idx, p, typetag);
}
SQUIRREL_API SQRESULT sq_setclassudsize(HSQUIRRELVM v, SQInteger idx, SQInteger udsize) {
	return sq->setclassudsize(v, idx, udsize);
}
SQUIRREL_API SQRESULT sq_newclass(HSQUIRRELVM v, SQBool hasbase) {
	return sq->newclass(v, hasbase);
}
SQUIRREL_API SQRESULT sq_createinstance(HSQUIRRELVM v, SQInteger idx) {
	return sq->createinstance(v, idx);
}
SQUIRREL_API SQRESULT sq_setattributes(HSQUIRRELVM v, SQInteger idx) {
	return sq->setattributes(v, idx);
}
SQUIRREL_API SQRESULT sq_getattributes(HSQUIRRELVM v, SQInteger idx) {
	return sq->getattributes(v, idx);
}
SQUIRREL_API SQRESULT sq_getclass(HSQUIRRELVM v, SQInteger idx) {
	return sq->getclass(v, idx);
}
SQUIRREL_API void sq_weakref(HSQUIRRELVM v, SQInteger idx) {
	return sq->weakref(v, idx);
}
SQUIRREL_API SQRESULT sq_getdefaultdelegate(HSQUIRRELVM v, SQObjectType t) {
	return sq->getdefaultdelegate(v, t);
}
/*SQUIRREL_API SQRESULT sq_getmemberhandle(HSQUIRRELVM v, SQInteger idx, HSQMEMBERHANDLE *handle) {
	sq.getmem
}*/
/*SQUIRREL_API SQRESULT sq_getbyhandle(HSQUIRRELVM v, SQInteger idx, const HSQMEMBERHANDLE *handle) {
	sq.getby
}*/
/*SQUIRREL_API SQRESULT sq_setbyhandle(HSQUIRRELVM v, SQInteger idx, const HSQMEMBERHANDLE *handle) {
	sq.setbyha
}*/

/*object manipulation*/
SQUIRREL_API void sq_pushroottable(HSQUIRRELVM v) {
	return sq->pushroottable(v);
}
SQUIRREL_API void sq_pushregistrytable(HSQUIRRELVM v) {
	return sq->pushregistrytable(v);
}
SQUIRREL_API void sq_pushconsttable(HSQUIRRELVM v) {
	return sq->pushconsttable(v);
}
SQUIRREL_API SQRESULT sq_setroottable(HSQUIRRELVM v) {
	return sq->setroottable(v);
}
SQUIRREL_API SQRESULT sq_setconsttable(HSQUIRRELVM v) {
	return sq->setconsttable(v);
}
SQUIRREL_API SQRESULT sq_newslot(HSQUIRRELVM v, SQInteger idx, SQBool bstatic) {
	return sq->newslot(v, idx, bstatic);
}
SQUIRREL_API SQRESULT sq_deleteslot(HSQUIRRELVM v, SQInteger idx, SQBool pushval) {
	return sq->deleteslot(v, idx, pushval);
}
SQUIRREL_API SQRESULT sq_set(HSQUIRRELVM v, SQInteger idx) {
	return sq->set(v, idx);
}
SQUIRREL_API SQRESULT sq_get(HSQUIRRELVM v, SQInteger idx) {
	return sq->get(v, idx);
}
SQUIRREL_API SQRESULT sq_rawget(HSQUIRRELVM v, SQInteger idx) {
	return sq->rawget(v, idx);
}
SQUIRREL_API SQRESULT sq_rawset(HSQUIRRELVM v, SQInteger idx) {
	return sq->rawset(v, idx);
}
SQUIRREL_API SQRESULT sq_rawdeleteslot(HSQUIRRELVM v, SQInteger idx, SQBool pushval) {
	return sq->rawdeleteslot(v, idx, pushval);
}
/*SQUIRREL_API SQRESULT sq_newmember(HSQUIRRELVM v, SQInteger idx, SQBool bstatic) {
	sq.newmem
}*/
/*SQUIRREL_API SQRESULT sq_rawnewmember(HSQUIRRELVM v, SQInteger idx, SQBool bstatic) {
	sq.rawnew
}*/
SQUIRREL_API SQRESULT sq_arrayappend(HSQUIRRELVM v, SQInteger idx) {
	return sq->arrayappend(v, idx);
}
SQUIRREL_API SQRESULT sq_arraypop(HSQUIRRELVM v, SQInteger idx, SQBool pushval) {
	return sq->arraypop(v, idx, pushval);
}
SQUIRREL_API SQRESULT sq_arrayresize(HSQUIRRELVM v, SQInteger idx, SQInteger newsize) {
	return sq->arrayresize(v, idx, newsize);
}
SQUIRREL_API SQRESULT sq_arrayreverse(HSQUIRRELVM v, SQInteger idx) {
	return sq->arrayreverse(v, idx);
}
SQUIRREL_API SQRESULT sq_arrayremove(HSQUIRRELVM v, SQInteger idx, SQInteger itemidx) {
	return sq->arrayremove(v, idx, itemidx);
}
SQUIRREL_API SQRESULT sq_arrayinsert(HSQUIRRELVM v, SQInteger idx, SQInteger destpos) {
	return sq->arrayinsert(v, idx, destpos);
}
SQUIRREL_API SQRESULT sq_setdelegate(HSQUIRRELVM v, SQInteger idx) {
	return sq->setdelegate(v, idx);
}
SQUIRREL_API SQRESULT sq_getdelegate(HSQUIRRELVM v, SQInteger idx) {
	return sq->getdelegate(v, idx);
}
SQUIRREL_API SQRESULT sq_clone(HSQUIRRELVM v, SQInteger idx) {
	return sq->clone(v, idx);
}
SQUIRREL_API SQRESULT sq_setfreevariable(HSQUIRRELVM v, SQInteger idx, SQUnsignedInteger nval) {
	return sq->setfreevariable(v, idx, nval);
}
SQUIRREL_API SQRESULT sq_next(HSQUIRRELVM v, SQInteger idx) {
	return sq->next(v, idx);
}
SQUIRREL_API SQRESULT sq_getweakrefval(HSQUIRRELVM v, SQInteger idx) {
	return sq->getweakrefval(v, idx);
}
SQUIRREL_API SQRESULT sq_clear(HSQUIRRELVM v, SQInteger idx) {
	return sq->clear(v, idx);
}

/*calls*/
SQUIRREL_API SQRESULT sq_call(HSQUIRRELVM v, SQInteger params, SQBool retval, SQBool raiseerror) {
	return sq->call(v, params, retval, raiseerror);
}
SQUIRREL_API SQRESULT sq_resume(HSQUIRRELVM v, SQBool retval, SQBool raiseerror) {
	return sq->resume(v, retval, raiseerror);
}
SQUIRREL_API const SQChar *sq_getlocal(HSQUIRRELVM v, SQUnsignedInteger level, SQUnsignedInteger idx) {
	return sq->getlocal(v, level, idx);
}
/*SQUIRREL_API SQRESULT sq_getcallee(HSQUIRRELVM v) {
	sq.getcal
}*/
SQUIRREL_API const SQChar *sq_getfreevariable(HSQUIRRELVM v, SQInteger idx, SQUnsignedInteger nval) {
	return sq->getfreevariable(v, idx, nval);
}
SQUIRREL_API SQRESULT sq_throwerror(HSQUIRRELVM v, const SQChar *err) {
	return sq->throwerror(v, err);
}
/*SQUIRREL_API SQRESULT sq_throwobject(HSQUIRRELVM v) {
	return sq->throwobject(v);
}*/
SQUIRREL_API void sq_reseterror(HSQUIRRELVM v) {
	return sq->reseterror(v);
}
SQUIRREL_API void sq_getlasterror(HSQUIRRELVM v) {
	return sq->getlasterror(v);
}
/*SQUIRREL_API SQRESULT sq_tailcall(HSQUIRRELVM v, SQInteger nparams) {
	sq.tailca
}*/

/*raw object handling*/
SQUIRREL_API SQRESULT sq_getstackobj(HSQUIRRELVM v, SQInteger idx, HSQOBJECT *po) {
	return sq->getstackobj(v, idx, po);
}
SQUIRREL_API void sq_pushobject(HSQUIRRELVM v, HSQOBJECT obj) {
	return sq->pushobject(v, obj);
}
SQUIRREL_API void sq_addref(HSQUIRRELVM v, HSQOBJECT *po) {
	return sq->addref(v, po);
}
SQUIRREL_API SQBool sq_release(HSQUIRRELVM v, HSQOBJECT *po) {
	return sq->release(v, po);
}
/*SQUIRREL_API SQUnsignedInteger sq_getrefcount(HSQUIRRELVM v, HSQOBJECT *po) {
	return sq->getrefcount(v, po);
}*/
SQUIRREL_API void sq_resetobject(HSQOBJECT *po) {
	return sq->resetobject(po);
}
SQUIRREL_API const SQChar *sq_objtostring(const HSQOBJECT *o) {
	return sq->objtostring(o);
}
SQUIRREL_API SQBool sq_objtobool(const HSQOBJECT *o) {
	return sq->objtobool(o);
}
SQUIRREL_API SQInteger sq_objtointeger(const HSQOBJECT *o) {
	return sq->objtointeger(o);
}
SQUIRREL_API SQFloat sq_objtofloat(const HSQOBJECT *o) {
	return sq->objtofloat(o);
}
/*SQUIRREL_API SQUserPointer sq_objtouserpointer(const HSQOBJECT *o) {
	sq.objtou
}*/
SQUIRREL_API SQRESULT sq_getobjtypetag(const HSQOBJECT *o, SQUserPointer * typetag) {
	return sq->getobjtypetag(o, typetag);
}
/*SQUIRREL_API SQUnsignedInteger sq_getvmrefcount(HSQUIRRELVM v, const HSQOBJECT *po) {
	sq.getvmre
}*/


/*GC*/
SQUIRREL_API SQInteger sq_collectgarbage(HSQUIRRELVM v) {
	return sq->collectgarbage(v);
}
/*SQUIRREL_API SQRESULT sq_resurrectunreachable(HSQUIRRELVM v) {
	sq.resurr
}*/

/*serialization*/
SQUIRREL_API SQRESULT sq_writeclosure(HSQUIRRELVM vm, SQWRITEFUNC writef, SQUserPointer up) {
	return sq->writeclosure(vm, writef, up);
}
SQUIRREL_API SQRESULT sq_readclosure(HSQUIRRELVM vm, SQREADFUNC readf, SQUserPointer up) {
	return sq->readclosure(vm, readf, up);
}

/*mem allocation*/
SQUIRREL_API void *sq_malloc(SQUnsignedInteger size) {
	return sq->malloc(size);
}
SQUIRREL_API void *sq_realloc(void* p, SQUnsignedInteger oldsize, SQUnsignedInteger newsize) {
	return sq->realloc(p, oldsize, newsize);
}
SQUIRREL_API void sq_free(void *p, SQUnsignedInteger size) {
	return sq->free(p, size);
}

/*debug*/
/*SQUIRREL_API SQRESULT sq_stackinfos(HSQUIRRELVM v, SQInteger level, SQStackInfos *si) {
	sq.gets
}*/
/*SQUIRREL_API void sq_setdebughook(HSQUIRRELVM v) {
	sq.getd
}*/
/*SQUIRREL_API void sq_setnativedebughook(HSQUIRRELVM v, SQDEBUGHOOK hook) {
	sq.setna
}*/