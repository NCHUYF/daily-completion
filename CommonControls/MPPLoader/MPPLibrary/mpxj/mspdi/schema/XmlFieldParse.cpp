#include "stdafx.h"
#include "XmlFieldParse.h"
#include "..\DatatypeConverter.h"
//#include "..\..\GarbageCollector.h"

namespace mspdi{
	namespace schema{

		std::map<CString, std::shared_ptr<NewXmlAdapter>> FieldValue::_typeAdapter;

		DatatypeConverter DataConvert;
		//static std::shared_ptr<DatatypeConverter> m_DataConvert;

		//static DatatypeConverter& getDataConvert()
		//{
		//	if (!m_DataConvert)
		//	{
		//		m_DataConvert.reset(new DatatypeConverter());
		//		GarbageCollector::add(new GcSharedPtr<DatatypeConverter>(m_DataConvert));
		//	}

		//	return *m_DataConvert;
		//}

		//// �ͷ����� NewXmlAdapterT
		//class FreeXmlAdapter : public IGcRecycle
		//{
		//public:
		//	virtual void gc()
		//	{
		//		FieldValue::freeAllTypeAdapter();
		//	}
		//};

		///////////////////////////////////////////////////////////////////////////////////////////////////
		// FieldValue
		//

		FieldValue::FieldValue(TiXmlElement* element)
		{
			_element = element;
		}

		FieldValue::~FieldValue()
		{
			_cache.clear();
			//_typeAdapter.clear();
		}

		VariantPtr FieldValue::getField(LPCSTR name, int defType)
		{
			auto itMap = _cache.find(CString(name));
			if (itMap != _cache.end())
				return std::dynamic_pointer_cast<Variant>(itMap->second);
//			ObjectPtr cache;
// 			if (_cache.Lookup(CString(name), cache))
// 				return std::dynamic_pointer_cast<Variant>(cache);

			ATLASSERT(_element != NULL);

			VariantPtr cacheValue;

			TiXmlElement* child = _element->FirstChildElement(name);
			if (child)
			{
				const char* text = child->GetText();
				CString value = CA2W(text);
				if (defType == VT_R8)
					cacheValue = VariantPtr(new Variant(_ttof(value)));
				else if (defType == VT_I4)
				{
					if (value.Find('.') >= 0)
						cacheValue = VariantPtr(new Variant(_ttof(value)));
					else
						cacheValue = VariantPtr(new Variant(_ttol(value)));
				}
				else if (defType == VT_BOOL)
					cacheValue = VariantPtr(new Variant(value == L"1" || value == L"true"));
				else
					cacheValue = VariantPtr(new Variant(value));
				//_cache.put(CString(name), cacheValue);
				_cache[CString(name)] = cacheValue;
			}
			return cacheValue;
		}

		int FieldValue::getInt(LPCSTR name)
		{
			return NumberHelper::getInt(getField(name, VT_I4));
		}

		bool FieldValue::getBool(LPCSTR name)
		{
			return NumberHelper::getBool(getField(name, VT_BOOL));
		}

		CString FieldValue::getString(LPCSTR name)
		{
			return NumberHelper::getString(getField(name));
		}

		double FieldValue::getDouble(LPCSTR name)
		{
			return NumberHelper::getDouble(getField(name, VT_R8));
		}

		NumberPtr FieldValue::getNumber(LPCSTR name)
		{
			return getField(name, VT_I4);
		}

		DatePtr FieldValue::getDate(LPCSTR name)
		{
			::CalendarPtr cal = DataConvert.parseDateTime(getString(name));
			if (cal) return cal->getTime();
			return NULL;
		}

		DatePtr FieldValue::getTime(LPCSTR name)
		{
			::CalendarPtr cal = DataConvert.parseTime(getString(name));
			if (cal) return cal->getTime();
			return NULL;
		}

		ObjectPtr FieldValue::getChildObject(LPCSTR name)
		{
			auto itMap = _cache.find(CString(name));
			if (itMap != _cache.end())
				return itMap->second;

 			ObjectPtr cache;
// 			if (_cache.Lookup(CString(name), cache))
// 				return cache;

			ATLASSERT(_element != NULL);

			TiXmlElement* child = _element->FirstChildElement(name);
			if (child)
			{
				cache = instanceType(name, child);
				//_cache.put(CString(name), cache);
				_cache[CString(name)] = cache;
			}
			return cache;
		}

		// ���ö���ֵ
		void FieldValue::set(LPCSTR name, bool value)
		{
			set(name, VariantPtr(new Variant(CString(value ? L"1" : L"0"))));
		}

		void FieldValue::set(LPCSTR name, int value)
		{
			//ATLASSERT(value != -65535);
			set(name, VariantPtr(new Variant(value)));
		}

		void FieldValue::set(LPCSTR name, double value)
		{
			set(name, VariantPtr(new Variant(value)));
		}

		void FieldValue::set(LPCSTR name, LPCTSTR value)
		{
			set(name, VariantPtr(new Variant(value)));
		}

		void FieldValue::set(LPCSTR name, VariantPtr value)
		{
			ObjectPtr cache;
			VariantPtr cache2;
			auto itMap = _cache.find(CString(name));
			if (itMap != _cache.end())
			//if (_cache.Lookup(CString(name), cache))
			{
				//cache2 = std::dynamic_pointer_cast<Variant>(cache);
				cache2 = std::dynamic_pointer_cast<Variant>(itMap->second);
				if (cache2 == NULL)
					throw toolkit::Exception(L"������ͬ���Ƶ����Ͳ�ͬ��ֵ��");
			}

			if (cache2 != NULL)
			{
				*cache2 = *value;
			}
			else
			{
				//_cache.put(CString(name), value);
				_cache[CString(name)] = value;
			}
		}

		// �����Ӷ���
		void FieldValue::set(LPCSTR name, FieldValuePtr value)
		{
			ObjectPtr cache;
			FieldValuePtr cache2;
			auto itMap = _cache.find(CString(name));
			if (itMap != _cache.end())
			//if (_cache.Lookup(CString(name), cache))
			{
				//cache2 = std::dynamic_pointer_cast<FieldValue>(cache);
				cache2 = std::dynamic_pointer_cast<FieldValue>(itMap->second);
				if (cache2 == NULL)
					throw toolkit::Exception(L"������ͬ���Ƶ����Ͳ�ͬ��ֵ��");
			}

			//_cache.put(CString(name), value);
			_cache[CString(name)] = value;
		}

		void  FieldValue::registerType(LPCSTR typeName, NewXmlAdapter* adapter)
		{
			//if (_typeAdapter.GetCount() == 0)
			//{
			//	// ��ӵ�����վ
			//	GarbageCollector::add(new FreeXmlAdapter());
			//}
			//_typeAdapter.put(CString(typeName), std::shared_ptr<NewXmlAdapter>(adapter));
			_typeAdapter[CString(typeName)] = std::shared_ptr<NewXmlAdapter>(adapter);
		}

		bool FieldValue::isRegisterType(LPCSTR typeName)
		{
			return _typeAdapter.find(CString(typeName)) != _typeAdapter.end();
// 			std::shared_ptr<NewXmlAdapter> adapter;
// 			return _typeAdapter.Lookup(CString(typeName), adapter);
		}

		ObjectPtr FieldValue::instanceType(LPCSTR typeName, TiXmlElement* element)
		{
			std::shared_ptr<NewXmlAdapter> adapter;
			auto it = _typeAdapter.find(CString(typeName));
			if(it == _typeAdapter.end())
			//if (!_typeAdapter.Lookup(CString(typeName), adapter))
			{
				throw toolkit::Exception(L"XML������Ͷ��󲻴���");
			}

			adapter = it->second;
			return ObjectPtr(adapter->NewObject(element));
		}

		void FieldValue::freeAllTypeAdapter()
		{
			//_typeAdapter.RemoveAll();
			_typeAdapter.clear();
		}

		// ��ȡ������ֶ������б���NULL����������sortCache����
		LPCTSTR* FieldValue::getFieldList()
		{
			return NULL;
		}

		// ��_cacheת�����б�������getFieldList��ֵ��������
		std::shared_ptr<List<std::pair<CString, ObjectPtr>>> FieldValue::sortCacheFields()
		{
			if (_cache.size() == 0)
				return NULL;

			// ����һ��cache
			std::map<CString, ObjectPtr> tempCache;
			tempCache = _cache;
// 			POSITION pos = _cache.GetStartPosition();
// 			while (pos)
// 			{
// 				Map<CString, ObjectPtr>::CPair* pair = _cache.GetNext(pos);
// 				tempCache.put(pair->m_key, pair->m_value);
// 			}

			std::shared_ptr<List<std::pair<CString, ObjectPtr>>> fieldList (
								new List<std::pair<CString, ObjectPtr>>());

			// ��ȡȡ�����ֶ������б�
			LPCTSTR* fieldNames = getFieldList();

			if (fieldNames)
			{
				// �ȸ����ֶ�˳���ȡֵ
				int index = 0;
				while (fieldNames[index] != NULL)
				{
					LPCTSTR key = fieldNames[index];
// 					pos = tempCache.Lookup(key);
// 					if (pos != NULL)
// 					{
// 						Map<CString, ObjectPtr>::CPair* pair = tempCache.GetAt(pos);
// 						fieldList->Add(std::pair<CString, ObjectPtr>(pair->m_key, pair->m_value));
// 						tempCache.RemoveAtPos(pos);
// 					}
					auto itMap = tempCache.find(CString(key));
					if (itMap != tempCache.end())
					{
						fieldList->Add(std::pair<CString, ObjectPtr>(itMap->first, itMap->second));
						tempCache.erase(itMap);
					}
					index++;
				}
			}

			// ��ʣ�µ��ֶ��ٴ����б�
// 			pos = tempCache.GetStartPosition();
// 			while (pos)
// 			{
// 				Map<CString, ObjectPtr>::CPair* pair = tempCache.GetNext(pos);
// 				fieldList->Add(std::pair<CString, ObjectPtr>(pair->m_key, pair->m_value));
// 			}
// 			tempCache.RemoveAll();

			for(auto itMap = tempCache.begin();  itMap != tempCache.end(); ++itMap)
				fieldList->Add(std::pair<CString, ObjectPtr>(itMap->first, itMap->second));
			tempCache.clear();

			return fieldList;
		}

		// ���浽XML�����
		void FieldValue::saveElement(TiXmlElement* element)
		{
			saveFieldToXml(shared_from_this(), element);
		}

		void FieldValue::saveVariantToXml(ObjectPtr object, CString name, TiXmlElement* element)
		{
			if (object == NULL)
			{
				return;
			}

			// ���ֵ
			ATLASSERT(name.GetLength() > 0);
			CString content = object->toString();
			if (content.GetLength() > 0)
			{
				TiXmlElement newChild = TiXmlElement(CW2A(name));
				TiXmlText text = TiXmlText(CW2A(content));
				newChild.InsertEndChild(text);
				element->InsertEndChild(newChild);
			}
		}

		void FieldValue::saveFieldToXml(FieldValuePtr field, TiXmlElement* element)
		{
			std::shared_ptr<List<std::pair<CString, ObjectPtr>>> fieldList = field->sortCacheFields();
			for (size_t i = 0; i < fieldList->GetCount(); i++)
			{
				std::pair<CString, ObjectPtr> pair = fieldList->GetAt(i);
				CString name = pair.first;
				ObjectPtr value = pair.second;
				
				// �����ӽ��
				FieldValuePtr testFieldValue = std::dynamic_pointer_cast<FieldValue>(value);
				if (testFieldValue != NULL)
				{
					TiXmlElement newChild = TiXmlElement(CW2A(name));
					testFieldValue->saveElement(&newChild);
					element->InsertEndChild(newChild);
					continue;
				}

				// �����б���
				ListIteratorPtr testListIterator = std::dynamic_pointer_cast<ListIterator>(value);
				if (testListIterator != NULL)
				{
					saveListToXml(testListIterator, name, element);
					continue;
				}

				// ����������
				saveVariantToXml(value, name, element);
			}
		}

		void FieldValue::saveListToXml(ListIteratorPtr list, CString name, TiXmlElement* element)
		{
			if (list->get_count() == 0) return;
			for (size_t i = 0; i < list->get_count(); i++)
			{
				ObjectPtr listItem = list->get_item(i);
				if (listItem == NULL) continue;

				FieldValuePtr testFieldValue = std::dynamic_pointer_cast<FieldValue>(listItem);

				if (testFieldValue)
				{
					TiXmlElement newChild = TiXmlElement(CW2A(name));
					saveFieldToXml(testFieldValue, &newChild);
					element->InsertEndChild(newChild);
				}
				else
				{
					saveVariantToXml(listItem, name, element);
				}
					
			}
		}
	}
}