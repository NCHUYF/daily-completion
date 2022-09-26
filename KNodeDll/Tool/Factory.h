//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           Factory.H
//    @author         KG
//    @date           2017/11/06 20:20
//    @brief          ���󹤳��ӿ���
//
//*****************************************************

#pragma once

namespace CommBase
{
	/**
	*  @class    ƽ̨��չ����ӿ�
	*
	*  @brief
	*/
	class COMMBASE_API KObject
	{
	public:
		KObject()
		{
			_nVersion = 0x8000;	// VER: 1.0.0.0
		}

		virtual ~KObject() {}

		/**
		*  @brief    ��ȡ��չ�ӿڰ汾(���ں��ڼ������ж�);
		*
		*  @return   LPCWSTR ���ؽӿڰ汾
		*/
		int GetVersion()
		{
			return _nVersion;
		}

	protected:
		int	_nVersion;	///< �ӿڰ汾
	};


	/**
	*  @class    Object�ഴ���ӿ�
	*
	*  @brief
	*/
	class KObjectCreator
	{
	public:
		virtual ~KObjectCreator() {}

		/**
		*  @brief    ����ʵ��
		*
		*  @return   KObject* �����´�����Objectָ��
		*/
		virtual KObject* NewInstance() = 0;
	};

	/**
	*  @class    Object�ഴ��ʵ����
	*
	*  @brief
	*/
	template<typename SubT>
	class KObjectCreatorProxy : public KObjectCreator
	{
	public:
		KObjectCreatorProxy(bool bSingleton)
		{
			_pInstance = NULL;
			_bSingleton = bSingleton;
		}

		~KObjectCreatorProxy()
		{
			if (NULL != _pInstance)
				delete _pInstance;
		}

		KObject* NewInstance()
		{
			if (_bSingleton)
			{
				if (NULL == _pInstance)
					_pInstance = new SubT();
				return _pInstance;
			}
			else
			{
				return new SubT();
			}
		}

	private:
		bool _bSingleton;	// �Ƿ���
		SubT* _pInstance;	// ����ָ��
	};

	// ������ȡ����ӿڷ���
#define DECLARE_KOBJECT(ObjectName, ObjectInterface) \
	_inline ObjectInterface* New##ObjectInterface() \
	{\
		return (ObjectInterface*)(GetKObjectFactory()->NewObject(ObjectName)); \
	}

	// ������ȡ����ӿڷ���
#define DECLARE_KSERVICE(ServiceName, ServiceInterface) \
	_inline ServiceInterface* Get##ServiceInterface() \
	{\
		return (ServiceInterface*)(GetKObjectFactory()->GetService(ServiceName)); \
	}

	/**
	* REGISTER_OBJECT(����ID, ����);
	* ע��Object����
	*/
#ifndef _LIB
#define REGISTER_KOBJECT(ObjectName, ObjectClass) \
	class Register##ObjectClass##ObjectCreator \
	{ \
	public: \
		Register##ObjectClass##ObjectCreator () \
			{\
				GetKObjectFactory()->AddFactory(ObjectName, new KObjectCreatorProxy<ObjectClass>(false));\
			} \
		~Register##ObjectClass##ObjectCreator () \
			{\
				GetKObjectFactory()->DeleteFactory(ObjectName);\
			} \
	} Register##ObjectClass##ObjectCreator##Instance;

	/**
	* REGISTER_KSERVICE(����ID, ����);
	* ע��Service����
	*/
#define REGISTER_KSERVICE(ServiceName, ServiceClass) \
	class Register##ServiceClass##ObjectCreator \
	{ \
	public: \
		Register##ServiceClass##ObjectCreator () \
			{\
				GetKObjectFactory()->AddFactory(ServiceName, new KObjectCreatorProxy<ServiceClass>(true));\
			} \
		~Register##ServiceClass##ObjectCreator () \
		{\
				GetKObjectFactory()->DeleteFactory(ServiceName);\
		} \
	} Register##ServiceClass##ObjectCreator##Instance;
#endif

	/**
	*  @class    KObject���������ӿ�
	*
	*  @brief
	*/
	class KObjectFactory
	{
	private:
		virtual ~KObjectFactory() {}
		friend class KObjectFactoryImpl;

	public:
		/**
		*  @brief    �ӹ����л�ȡObject����(��Ҫ�����ͷ�ָ��)
		*
		*  @param    LPCWSTR lpName ��������
		*  @return   KObject* ����ʧ�ܷ���NULL
		*/
		virtual KObject* NewObject(LPCWSTR lpName) = 0;

		/**
		*  @brief    �ӹ����л�ȡService����(����)
		*
		*  @param    LPCWSTR lpName ��������
		*  @return   KObject* ����ʧ�ܷ���NULL
		*/
		virtual KObject* GetService(LPCWSTR lpName) = 0;

		/**
		*  @brief    ���Object����
		*
		*  @param    LPCWSTR lpName ��������
		*  @param    KObjectCreator * pObjCreater ������Ķ���
		*  @param    bool bCoverExist �Ƿ񸲸���ע���
		*  @return   bool �ɹ�����true
		*/
		virtual bool AddFactory(LPCWSTR lpName, KObjectCreator* pObjCreater,
			bool bCoverExist = false) = 0;

		/**
		*  @brief    �Ƴ�Object����
		*
		*  @param    LPCWSTR lpName ��������
		*  @param    KObjectCreator * pObjCreater ������Ķ���
		*  @return   bool �ɹ�����true
		*/
		virtual bool RemoveFactory(LPCWSTR lpName, KObjectCreator* pObjCreater) = 0;

		/**
		*  @brief    ɾ��Object����
		*
		*  @param    LPCWSTR lpName ��������
		*  @return   bool �ɹ�����true
		*/
		virtual bool DeleteFactory(LPCWSTR lpName) = 0;
	};

	/**
	*  @brief    ��ʼ��Object����
	*
	*/
	COMMBASE_API void InitKObjectFactory();

	/**
	*  @brief    ��ȡObject�����ӿ�ָ��
	*
	*  @return   IObjectFactory* ����Object�����ӿ�
	*/
	COMMBASE_API KObjectFactory* GetKObjectFactory();

	/**
	*  @brief    ����ʼ��Object����
	*
	*/
	COMMBASE_API void UninitKObjectFactory();
}