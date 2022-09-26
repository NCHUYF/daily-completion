#include "StdAfx.h"
#include "Factory.h"

namespace CommBase
{
	/**
	*  @class     Object��������ʵ��
	*
	*  @brief
	*/
	class KObjectFactoryImpl : public KObjectFactory
	{
		/*
		*  Object�ഴ���ӿ�AMP
		*/
		typedef std::map<CString, KObjectCreator*> ObjectCreaterMap;
		typedef ObjectCreaterMap::iterator ObjectCreaterMapIter;

	public:
		/**
		*  @brief    �ӹ����л�ȡObject����(��Ҫ�����ͷ�ָ��)
		*
		*  @param    LPCWSTR lpName ��������
		*  @return   KObject* ����ʧ�ܷ���NULL
		*/
		virtual KObject* NewObject(LPCWSTR lpName) override
		{
			return FindObject(lpName);
		}

		/**
		*  @brief    �ӹ����л�ȡService����(����)
		*
		*  @param    LPCWSTR lpName ��������
		*  @return   KObject* ����ʧ�ܷ���NULL
		*/
		virtual KObject* GetService(LPCWSTR lpName) override
		{
			return FindObject(lpName);
		}

		/**
		*  @brief    ���Object����
		*
		*  @param    LPCWSTR lpName ��������
		*  @param    IKObjectCreator * pObjCreater ������Ķ���
		*  @param    bool bCoverExist �Ƿ񸲸���ע���
		*  @return   bool �ɹ�����true
		*/
		virtual bool AddFactory(LPCWSTR lpName, KObjectCreator* pObjCreater,
			bool bCoverExist = false) override
		{
			if (NULL == lpName || (NULL == pObjCreater))
				return false;

			ObjectCreaterMapIter findIter = _objectCreatorMap.find(lpName);
			if (findIter != _objectCreatorMap.end())
			{
				// �������򷵻�
				if (!bCoverExist)
					return false;

				// ���ǲ���Ҫɾ��ԭ�У���Ϊע��ĵط����Լ�ɾ��
				//delete findIter->second;
			}

			_objectCreatorMap[lpName] = pObjCreater;

			return true;
		}

		/**
		*  @brief    ɾ��Object����
		*
		*  @param    LPCWSTR lpName ��������
		*  @param    IKObjectCreator * pObjCreater ������Ķ���
		*  @return   bool �ɹ�����true
		*/
		virtual bool RemoveFactory(LPCWSTR lpName, KObjectCreator* pObjCreater) override
		{
			if (NULL == lpName || (NULL == pObjCreater))
				return false;

			ObjectCreaterMapIter findIter = _objectCreatorMap.find(lpName);
			if (findIter != _objectCreatorMap.end())
			{
				_objectCreatorMap.erase(findIter);
				return true;
			}

			return false;
		}

		/**
		*  @brief    ɾ��Object����
		*
		*  @param    LPCWSTR lpName ��������
		*  @return   bool �ɹ�����true
		*/
		virtual bool DeleteFactory(LPCWSTR lpName) override
		{
			if (NULL == lpName)
				return false;

			ObjectCreaterMapIter findIter = _objectCreatorMap.find(lpName);
			if (findIter != _objectCreatorMap.end())
			{
				delete findIter->second;
				_objectCreatorMap.erase(findIter);
				return true;
			}

			return false;
		}

	private:
		/**
		*  @brief    �ӹ����д�������
		*
		*  @param    LPCWSTR lpName ��������
		*  @return   KObject* ʧ�ܷ���NULL
		*/
		virtual KObject* FindObject(LPCWSTR lpName)
		{
			ObjectCreaterMapIter findIter = _objectCreatorMap.find(lpName);
			if (findIter != _objectCreatorMap.end())
			{
				return findIter->second->NewInstance();
			}

			return NULL;
		}

	protected:
		ObjectCreaterMap	_objectCreatorMap;	///< Object�ഴ������
	};

	static KObjectFactoryImpl* g_pObjectFactory = NULL;

	void InitKObjectFactory()
	{
		if (NULL == g_pObjectFactory)
		{
			g_pObjectFactory = new KObjectFactoryImpl();
		}
	}

	KObjectFactory* GetKObjectFactory()
	{
		return g_pObjectFactory;
	}

	void UninitKObjectFactory()
	{
		if (NULL != g_pObjectFactory)
		{
			delete g_pObjectFactory;
			g_pObjectFactory = NULL;
		}
	}
}