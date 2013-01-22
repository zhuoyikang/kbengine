/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2012 KBEngine.

KBEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KBEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public License
along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __CLIENTAPP_ENTITY_H__
#define __CLIENTAPP_ENTITY_H__
	
// common include
#include "profile.hpp"
#include "cstdkbe/timer.hpp"
#include "cstdkbe/cstdkbe.hpp"
#include "helper/debug_helper.hpp"
#include "entitydef/entity_mailbox.hpp"
#include "pyscript/math.hpp"
#include "pyscript/scriptobject.hpp"
#include "entitydef/datatypes.hpp"	
#include "entitydef/entitydef.hpp"	
#include "entitydef/scriptdef_module.hpp"
#include "entitydef/entity_macro.hpp"	
#include "server/script_timers.hpp"	

//#define NDEBUG
// windows include	
#if KBE_PLATFORM == PLATFORM_WIN32
#else
// linux include
#endif
	
namespace KBEngine{
class EntityMailbox;
class ClientObjectBase;

namespace Mercury
{
class Channel;
}

class Entity : public script::ScriptObject
{
	/** ���໯ ��һЩpy�������������� */
	BASE_SCRIPT_HREADER(Entity, ScriptObject)	
	ENTITY_HEADER(Entity)
public:
	Entity(ENTITY_ID id, const ScriptDefModule* scriptModule, EntityMailbox* base, EntityMailbox* cell);
	~Entity();
	
	/** 
		�����������ݱ��ı��� 
	*/
	void onDefDataChanged(const PropertyDescription* propertyDescription, 
			PyObject* pyData);
	
public:
	/** 
		mailbox section
	*/
	INLINE EntityMailbox* getBaseMailbox()const;
	DECLARE_PY_GET_MOTHOD(pyGetBaseMailbox);
	INLINE void setBaseMailbox(EntityMailbox* mailbox);
	
	INLINE EntityMailbox* getCellMailbox()const;
	DECLARE_PY_GET_MOTHOD(pyGetCellMailbox);
	INLINE void setCellMailbox(EntityMailbox* mailbox);

	/** 
		�ű���ȡ������entity��position 
	*/
	INLINE Position3D& getPosition();
	void setPosition(Position3D& pos);
	DECLARE_PY_GETSET_MOTHOD(pyGetPosition, pySetPosition);

	/** 
		�ű���ȡ������entity�ķ��� 
	*/
	INLINE Direction3D& getDirection();
	INLINE void setDirection(Direction3D& dir);
	DECLARE_PY_GETSET_MOTHOD(pyGetDirection, pySetDirection);
	
	/** 
		pClientApp section
	*/
	DECLARE_PY_GET_MOTHOD(pyGetClientApp);
	INLINE void pClientApp(ClientObjectBase* p);
	INLINE ClientObjectBase* pClientApp()const;

	/** 
		�������entity 
	*/
	void onDestroy(void){};

	void onEnterWorld();
	void onLeaveWorld();
public:
	/**
		Զ�̺��б�entity�ķ��� 
	*/
	void onRemoteMethodCall(Mercury::Channel* pChannel, MemoryStream& s);

	/**
		����������entity����
	*/
	void onUpdatePropertys(MemoryStream& s);
protected:
	EntityMailbox*							cellMailbox_;						// ���entity�Ŀͻ���mailbox
	EntityMailbox*							baseMailbox_;						// ���entity��baseapp mailbox

	Position3D								position_;							// entity�ĵ�ǰλ��
	Direction3D								direction_;							// entity�ĵ�ǰ����

	ClientObjectBase*						pClientApp_;
};																										

}

#ifdef CODE_INLINE
#include "entity.ipp"
#endif
#endif