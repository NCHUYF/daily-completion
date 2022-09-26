#pragma once
#include <MPPLoader/Toolkit/include/tinyxml.h>

namespace mspdi{
	namespace schema{

		///////////////////////////////////////////////////////////////////////////////////////////////////
		// FieldValue
		//
		class NewXmlAdapter
		{
		public:
			virtual Object2* NewObject(TiXmlElement* element) = 0;
		};

		class FieldValue : public Object2, public std::enable_shared_from_this<FieldValue>
		{
		public:
			FieldValue(TiXmlElement* element);
			virtual ~FieldValue();

			// ��ȡ�ֶ�ֵ
			VariantPtr getField(LPCSTR name, int defType = VT_BSTR);

			int getInt(LPCSTR name);
			bool getBool(LPCSTR name);
			CString getString(LPCSTR name);
			double getDouble(LPCSTR name);
			NumberPtr getNumber(LPCSTR name);
			DatePtr getDate(LPCSTR name);
			DatePtr getTime(LPCSTR name);

			// ��ȡ�ӽ�����
			ObjectPtr getChildObject(LPCSTR name);

			// ��ȡ�ӽ������б�
			template<class T>
			std::shared_ptr<ObjectList<std::shared_ptr<T>>> getChildList(LPCSTR name)
			{
				auto itMap = _cache.find(CString(name));
				if(itMap != _cache.end())
					return std::dynamic_pointer_cast<ObjectList<std::shared_ptr<T>>> (itMap->second);
// 				ObjectPtr cache;
// 				if (_cache.Lookup(CString(name), cache))
// 					return std::dynamic_pointer_cast<ObjectList<std::shared_ptr<T>>> (cache);

				std::shared_ptr<ObjectList<std::shared_ptr<T>>> list(new ObjectList<std::shared_ptr<T>>());

				if (_element)
				{
					TiXmlElement* child = _element->FirstChildElement(name);
					while (child)
					{
						std::shared_ptr<T> obj = std::dynamic_pointer_cast<T>(instanceType(name, child));
						if (obj)
						{
							list->Add(std::shared_ptr<T>(obj));
						}
						child = child->NextSiblingElement(name);
					}
				}

				//_cache.put(CString(name), std::dynamic_pointer_cast<Object>(list));
				_cache[CString(name)] = std::dynamic_pointer_cast<Object2>(list);

				return list;
			}

			typedef std::shared_ptr<FieldValue> FieldValuePtr;

			// ���ö���ֵ
			void set(LPCSTR name, bool value);
			void set(LPCSTR name, int value);
			void set(LPCSTR name, double value);
			void set(LPCSTR name, LPCTSTR value);

			void set(LPCSTR name, VariantPtr value);

			// �����Ӷ���
			void set(LPCSTR name, FieldValuePtr value);

			// ע�������
			static void registerType(LPCSTR typeName, NewXmlAdapter* adapter);
			static bool isRegisterType(LPCSTR typeName);

			// ���浽XML�����
			void saveElement(TiXmlElement* element);

			void static saveVariantToXml(ObjectPtr object, CString name, TiXmlElement* element);
			void static saveFieldToXml(FieldValuePtr field, TiXmlElement* element);
			void static saveListToXml(ListIteratorPtr list, CString name, TiXmlElement* element);

			static void freeAllTypeAdapter();

		protected:
			static ObjectPtr instanceType(LPCSTR typeName, TiXmlElement* element);
			
			// ��ȡ������ֶ������б���NULL����������sortCache����
			virtual LPCTSTR* getFieldList();

			// ��_cacheת�����б�������getFieldList��ֵ��������
			std::shared_ptr<List<std::pair<CString, ObjectPtr>>> sortCacheFields();

			std::map<CString, ObjectPtr> _cache;
			TiXmlElement* _element;

			static std::map<CString, std::shared_ptr<NewXmlAdapter>> _typeAdapter;
		};

	}
}	// end namespace mspdi::schema